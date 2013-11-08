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
  @brief Returns a render array that represents the Player Fitness page.
  @param $node (object) the player node.
  @return (array) the render array.
  @note the Fitness Stats Table and Fitness Stats Chart blocks will be added to this page.
*/
function soccer_boss_player_fitness_page ($node) {
  return array ();
}

/**
  @brief Returns a render array that represents the Player Game Stats page.
  @param $node (node) the player node.
  @return (array) the render array.
*/
function soccer_boss_player_game_stats_page ($node) {
  return array ();
}

/**
  @brief Returns a render array that represents the Team Overview page.
  @param $node (node) the team node.
  @return (array) the render array.
*/
function soccer_boss_team_overview_page ($node) {
  return array (
    'content' => array (
      '#type'   => 'markup',
      '#markup' => $node->body ['und'][0]['safe_value']
  )); 
}

/**
  @brief Returns a render array that represents the Team Player Game Stats Page.
  @param $team_node (object) the team node.
*/
function soccer_boss_team_player_game_stats_page ($team_node) {
  module_load_include ('inc', 'soccer_boss');

  $player_nids = soccer_boss_get_references (
    $team_node->nid,
    'node',
    'soccer_boss_player_team'
  );

  $stat_values = array ();
  $stat_names  = array ();

  foreach ($player_nids as $player_nid) {
    $player_stats = node_load_multiple (soccer_boss_get_references ($player_nid, 'node', 'soccer_boss_pgs_player'));

    foreach ($player_stats as $player_stat) {
      $stat_values [$player_stat->soccer_boss_pgs_game ['und'][0]['target_id']][$player_nid][$player_stat->title] = 
        $player_stat->soccer_boss_pgs_value ['und'][0]['value'];
      $stat_names [] = $player_stat->title;
    }
  }
  $stat_names = array_unique ($stat_names);

  $stat_tables = '';
  foreach ($stat_values as $game_nid => $stat_value) {
    $game = node_load ($game_nid);
    if (!$game) {
      continue;
    }

    $game_uri = node_uri ($game);

    $stat_tables .= '<table><caption>' . l ($game->title, $game_uri ['path']) . ': ' . date ('Y-m-d', strtotime ($game->soccer_boss_game_date ['und'][0]['value'])) . '</caption><thead><tr><th>Name</th>';

    foreach ($stat_names as $stat_name) {
      $stat_tables .= "<th>$stat_name</th>"; 
    }
    $stat_tables .= '</thead><tbody>';

    foreach ($stat_value as $stat_player_nid => $stat_player_values) {
      $player     = node_load ($stat_player_nid);
      $player_uri = node_uri ($player);

      $stat_tables .= '<tr><td>' . l ($player->title, $player_uri ['path']) . '</td>';
      foreach ($stat_names as $stat_name) {
        $stat_tables .= '<td>' . (isset ($stat_player_values [$stat_name]) ? $stat_player_values [$stat_name] : '') . '</td>';
      }
      $stat_tables .= '</tr>';
    }
    $stat_tables .= '</tbody></table>';
  }

  return array (
    'content' => array (
      '#type'   => 'markup',
      '#markup' => '<h2>Individual Game Stats</h2>' . $stat_tables
  ));
}

/**
  @brief Returns a Stats Comparison table for the given entities.
  @param $stat_values (array) the stat values array.
  @return (array) a render array representing the table.
*/
function soccer_boss_stats_comparison_tables ($stat_values) {

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
  return array ();
}

/**
  @brief Returns the Team comparison page.
  @param $x (integer) the first team nid.
  @param $y (integer) the second team nid.
  @return (array) a render array.
*/
function soccer_boss_team_comparison ($x, $y) {
  module_load_include ('inc', 'soccer_boss');
  return array ();
}
