<?php
/**
  @file
  @brief Defines the pages created by the Soccer
    Boss module.
*/

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
  @brief Redirects the user to the Team Player Stats page.
  @param $node (object) the team node.
*/
function soccer_boss_team_player_stats_page ($node) {
  drupal_goto ('team-player-stats-form/' . $node->nid);
}

/**
  @brief Returns a Stats Comparison table for the given entities.
  @param $stat_values (array) the stat values array.
  @return (array) a render array representing the table.
*/
function soccer_boss_stats_comparison_tables ($stat_values) {

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
  module_load_include ('inc', 'soccer_boss');

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

  $x_stats = node_load_multiple (soccer_boss_get_references ($x->nid, 'node', 'soccer_boss_pps_player'));
  $y_stats = node_load_multiple (soccer_boss_get_references ($y->nid, 'node', 'soccer_boss_pps_player'));

  $stat_values = array ();
  foreach ($x_stats as $x_stat) {
    $y_stat = null;
    foreach ($y_stats as $_y_stat) {
      if (
        $x_stat->title == $_y_stat->title &&
        $x_stat->soccer_boss_pps_year ['und'][0]['value'] == $_y_stat->soccer_boss_pps_year ['und'][0]['value']
      ) {
        $y_stat = $_y_stat;
        break;
      }
    }
    if (!is_null ($y_stat)) {
      $stat_values [$x_stat->soccer_boss_pps_year ['und'][0]['value']][$x_stat->title] = array (
        $x_stat->soccer_boss_pps_value ['und'][0]['value'],
        $y_stat->soccer_boss_pps_value ['und'][0]['value']
      );
    }
  }
  
  $stat_tables = soccer_boss_stats_comparison_tables ($stat_values);

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
  module_load_include ('inc', 'soccer_boss');

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

  $x_stats = node_load_multiple (soccer_boss_get_references ($x->nid, 'node', 'soccer_boss_ts_team'));
  $y_stats = node_load_multiple (soccer_boss_get_references ($y->nid, 'node', 'soccer_boss_ts_team'));

  $stat_values = array ();
  foreach ($x_stats as $x_stat) {
    $y_stat = null;
    foreach ($y_stats as $_y_stat) {
      if (
        $x_stat->title == $_y_stat->title &&
        $x_stat->soccer_boss_ts_year ['und'][0]['value'] == $_y_stat->soccer_boss_ts_year ['und'][0]['year']
      ) {
        $y_stat = $_y_stat;
        break;
      }
    }
    if (!is_null ($y_stat)) {
      $stat_values [$x_stat->soccer_boss_ts_year ['und'][0]['value']][$x_stat->title] = array (
        $x_stat->soccer_boss_ts_value ['und'][0]['value'],
        $y_stat->soccer_boss_ts_value ['und'][0]['value']
      );
    }
  }

  $stat_tables = soccer_boss_stats_comparison_tables ($stat_values);

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
