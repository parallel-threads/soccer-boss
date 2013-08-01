<?php
/**
  @file
  @brief Defines the pages created by the Soccer
    Boss module.
*/

/**
  @brief Redirects the user to the Team page
    associated with the given coach node.
  @param $node (object) the coach node.
*/
function soccer_boss_coach_team_page ($node) {
  module_load_include ('inc', 'soccer_boss');

  watchdog (
    'soccer_boss',
    '[soccer_boss_coach_team_page]'
  );

  // I. Retrieve the team node ids.
  $ids = soccer_boss_get_references ($node->nid, 'node', 'soccer_boss_team_coach');

  watchdog (
    'soccer_boss',
    '[soccer_boss_coach_team_page] ids: <pre>@ids</pre>',
    array (
      '@ids' => print_r ($ids, true)
  ));

  // II. Retrieve the team node uri.
  if (empty ($ids)) {
    drupal_set_message ('This coach is not currently affiliated with any known teams.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($ids [0])); 
  }

  // III. Redirect the user.
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to the Player's Stats view.
  @param $node (object) the player node.
*/
function soccer_boss_player_stats_page ($node) {
  drupal_goto ("player-stats/$node->nid");
}

/**
  @brief Redirects the user to the Player's Team page.
  @param $node (object) the player node.
*/
function soccer_boss_player_team_page ($node) {
  if (empty ($node->soccer_boss_player_team ['und'])) {
    drupal_set_message ('This player is not associated with a team.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($node->soccer_boss_player_team ['und'][0]['target_id']));
  }
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to profile of the head
    coach associated with the given team.
  @param $node (object) the team node.
*/
function soccer_boss_team_coach_page ($node) {
  if (empty ($node->soccer_boss_team_coach ['und'])) {
    drupal_set_message ('This team does not have a Head Coach.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($node->soccer_boss_team_coach ['und'][0]['target_id']));
  }
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to the Team Roster page.
  @param $node (object) the current team node.
*/
function soccer_boss_team_roster_page ($node) {
  drupal_goto ('team-roster/' . $node->nid);
}

/**
  @brief Redirects the user to the Team Games page.
  @param $node (object) the current team node.
*/
function soccer_boss_team_games_page ($node) {
  drupal_goto ('team-games/' . $node->nid);
}

/**
  @brief Returns a Stats Comparison table for the given entities.
  @param $x (integer) the first entity id.
  @param $y (integer) the second entity id.
  @return (array) a render array representing the table.
*/
function soccer_boss_stats_comparison_tables ($x, $y) {
  // Initialize the stat values array.
  $stat_values = array ();

  // Retrieve the stats.
  $x_stats = stats_load_multiple (stats_get_stats ($x));
  $y_stats = stats_load_multiple (stats_get_stats ($y));

  // Set the stat values array.
  foreach ((array) $x_stats as $x_stat) {
    // I. Find the y stat that has the same name.
    $y_stat = null;
    foreach ((array) $y_stats as $stat) {
      if ($stat->name === $x_stat->name) {
        $y_stat = $stat;
        break;
      }
    }

    // ignore stats that can not be cross-compared.
    if (is_null ($y_stat)) {
      continue;
    }

    // II. Retrieve the stat values.
    $x_stat_values = stats_value_load_multiple (stats_get_stat_values ($x_stat->id));
    $y_stat_values = stats_value_load_multiple (stats_get_stat_values ($y_stat->id));

    // III. Store values for each year.
    foreach ((array) $x_stat_values as $x_stat_value) {
      // III.A. Get the value date.
      $x_stat_value_year = date ('Y', $x_stat_value->date);

      // III.B. Get the y stat value that has the given date.
      $y_stat_value = null;
      foreach ((array) $y_stat_values as $stat_value) {
        $stat_value_year = date ('Y', $stat_value->date);

        if ($x_stat_value_year === $stat_value_year) {
          $y_stat_value = $stat_value;
          break;
        }
      }

      // III.C. Store the stat values if defined.
      if (isset ($y_stat_value)) {
        $stat_values [$x_stat_value_year][$x_stat->name] = array (
          $x_stat_value->content,
          $y_stat_value->content
        );
      }
    }
  }

  watchdog (
    'soccer_boss',
    '[soccer_boss_stats_comparison_tables] stat values: <pre>@stat_values</pre>',
    array (
      '@stat_values' => print_r ($stat_values, true)
  ));

  // Create the stat tables.
  $stat_tables = '';
  foreach ((array) $stat_values as $year => $stats) {
    $stat_tables .= "<table>
                       <tr>
                         <th>$year</th>
                       </tr>";

    foreach ((array) $stats as $name => $values) {
      $stat_tables .= "<tr>
                         <td>$name</td>
                         <td>" . ($values [0] > $values [1] ? '<em>' . $values [0] . '</em>' : $values [0]) . "</td>
                         <td>" . ($values [1] > $values [0] ? '<em>' . $values [1] . '</em>' : $values [1]) . "</td>
                       </tr>";
    }
                       
    $stat_tables .= '</table>';
  }

  return $stat_tables;
}

/**
  @brief Returns the player comparison page.
  @param $x (object) the first player node.
  @param $y (object) the second player node.
  @return (array) a render array.
*/
function soccer_boss_player_comparison ($x, $y) {
  module_load_include ('inc', 'stats');

  // Exit if the page arguments are unset.
  if (!$x || !$y) {
    drupal_set_message (t ('Error: An internal error occured. The page arguments are not set.'), 'error');
    return array ();
  }

  // I. Load the player nodes.
  $x = node_load ($x);
  $y = node_load ($y);

  // Exit if the player nodes could not be loaded.
  if (is_null ($x) || is_null ($y)) {
    drupal_set_message (t ('Error: An error occured while trying to load one or both of the players.'), 'error');
    return array ();
  }

  // II. Create the Stat Comparison tables.
  $stat_tables = soccer_boss_stats_comparison_tables ($x->nid, $y->nid);

  // III. Define the Player Comparison Page.

  $x_uri = node_uri ($x);
  $y_uri = node_uri ($y);

  return array (
    'content' => array (
      '#type'   => 'markup',
      '#markup' => "<table>
                      <tr>
                        <th>" . l ($x->title, $x_uri ['path']) . "</th>
                        <th>" . l ($y->title, $y_uri ['path']) . "</th>
                      </tr>
                      <tr>
                        <td><img src='" . image_style_url ('thumbnail', $x->soccer_boss_player_photo ['und'][0]['uri']) . "' alt='player photo.' /></td>
                        <td><img src='" . image_style_url ('thumbnail', $y->soccer_boss_player_photo ['und'][0]['uri']) . "' alt='player photo.' /></td>
                      </tr>
                      <tr>
                        <td>" . text_summary ($x->body ['und'][0]['value']) . "</td>
                        <td>" . text_summary ($y->body ['und'][0]['value']) . "</td>
                      </tr>
                    </table>" . $stat_tables
  ));
}

/**
  @brief Returns the Team comparison page.
  @param $x (integer) the first team nid.
  @param $y (integer) the second team nid.
  @return (array) a render array.
*/
function soccer_boss_team_comparison ($x, $y) {
  module_load_include ('inc', 'stats');

  // Exit if the page arguments are unset.
  if (!$x || !$y) {
    drupal_set_message (t ('Error: An internal error occured. The page arguments are not set.'), 'error');
    return array ();
  }

  // I. Load the team nodes.
  $x = node_load ($x);
  $y = node_load ($y);

  // Exit if the team nodes could not be loaded.
  if (is_null ($x) || is_null ($y)) {
    drupal_set_message (t ('Error: An error occured while trying to load one or both of the teams.'), 'error');
    return array ();
  }

  // II. Create the Stats Comparison table.
  $stat_tables = soccer_boss_stats_comparison_tables ($x->nid, $y->nid);

  // III. Create the Team Comparison page.

  $x_uri = node_uri ($x);
  $y_uri = node_uri ($y);

  return array (
    'content' => array (
      '#type'   => 'markup',
      '#markup' => '<table>
                      <tr>
                        <th>' . l ($x->title, $x_uri ['path']) . '</th>
                        <th>' . l ($y->title, $y_uri ['path']) . '</th>
                      </tr>
                      <tr>
                        <td><img src="' . image_style_url ('thumbnail', $x->soccer_boss_team_logo ['und'][0]['uri']) . '" alt="team logo." /></td>
                        <td><img src="' . image_style_url ('thumbnail', $y->soccer_boss_team_logo ['und'][0]['uri']) . '" alt="team logo." /></td>
                      </tr>
                      <tr>
                        <td>' . text_summary ($x->body ['und'][0]['value']) . '</td>
                        <td>' . text_summary ($y->body ['und'][0]['value']) . '</td>
                      </tr>
                    </table>' . $stat_tables
  ));
}
