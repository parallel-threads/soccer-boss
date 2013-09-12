<?php
/**
  @file
  @brief Defines the functions that create the stat tables.
*/

/**
  @brief Returns the Player Fitness Stats table for the given player.
  @param $player (node) the player.
  @return (array) a render array representing the stat table.
*/
function soccer_boss_table_pfs ($player) {
  module_load_include ('inc', 'soccer_boss');

  $stats = soccer_boss_get_pfs_nodes ($player->nid);

  $data = array (
    'columns' => array (
      array (
        'column_name' => t ('Year'),
        'weight'      => 0
    )),
    'sort_column' => t ('Year')
  );
  $stat_years = array ();
  foreach ($stats as $stat) {
    $stat_year = date ('Y', strtotime ($stat->soccer_boss_pfs_date ['und'][0]['value']));
    if (!in_array ($stat_year, $stat_years)) {
      $data ['fields'][] = array (
        'column_name' => t ('Year'),
        'row_name'    => $stat_year,
        'value'       => $stat_year
      );
      $stat_years [] = $stat_year;
    }
    $data ['fields'][] = array (
      'column_name' => $stat->title,
      'row_name'    => $stat_year,
      'value'       => $stat->soccer_boss_pfs_value ['und'][0]['value']
    );
  } 

  return simple_table ($data);
}

/**
  @brief Returns the Player Game Stats table for the given player.
  @param $player (node) the player.
  @return (array) a render array representing the stat table.
*/
function soccer_boss_table_pgs ($player) {
  module_load_include ('inc', 'soccer_boss');

  $stats = soccer_boss_get_pgs_nodes ($player->nid);

  $data = array ();
  $games = array ();
  foreach ($stats as $stat) {
    $game = node_load ($stat->soccer_boss_pgs_game ['und'][0]['target_id']);
    $game_date = $game->soccer_boss_game_date ['und'][0]['value'];

    if (!$game) { continue; }
    if (!array_key_exists ($game_date, $games) ||
        !array_key_exists ($game->nid, $games [$game_date])) {
      $games [$game_date][$game->nid] = $game;
    }

    $data ['fields'][] = array (
      'column_name' => $stat->title,
      'row_name'    => $game->nid,
      'value'       => $stat->soccer_boss_pgs_value ['und'][0]['value']
    );
  }
  ksort ($games);
  foreach ($games as $game_date => $_games) {
    ksort ($_games);
    foreach ($_games as $game) {
      $game_uri = node_uri ($game);
      $data ['fields'] = array_merge (
        array (
          array (
            'column_name' => t ('Date'),
            'row_name'    => $game->nid,
            'value'       => date ('Y-m-d', strtotime ($game_date))
          ),
          array (
            'column_name' => t ('Game'),
            'row_name'    => $game->nid,
            'value'       => l ($game->title, $game_uri ['path'])
        )), $data ['fields']);
    }
  }
  return simple_table ($data);
}

/**
  @brief Returns the Player Performance Stat table for the given player.
  @param $player (node) the player.
  @return (array) a render array representing the stat table.
*/
function soccer_boss_table_pps ($player) {
  module_load_include ('inc', 'soccer_boss');

  $stats = soccer_boss_get_pps_nodes ($player->nid);

  $data = array (
    'columns' => array (
      array (
        'column_name' => t ('Year'),
        'weight'      => 0,
      ),
      array (
        'column_name' => 'Goals',
        'weight'      => 1,
      ),
      array (
        'column_name' => 'Assists',
        'weight'      => 2
    )),
    'sort_column' => t ('Year'),
    'fields' => array (),
    'default_field_value' => create_function ('$column_name, $row_name',
                                              '$pps = soccer_boss_get_derived_pps (' . $player->nid . ', $column_name, $row_name); 
                                               return $pps [\'value\'];')
  );
  $stat_years = array ();
  foreach ($stats as $stat) {
    $stat_year = $stat->soccer_boss_pps_year ['und'][0]['value'];
    if (!in_array ($stat_year, $stat_years)) {
      $data ['fields'][] = array (
        'column_name' => t ('Year'),
        'row_name'    => $stat_year,
        'value'       => $stat_year
      );
    }
    $data ['fields'][] = array (
      'column_name' => $stat->title,
      'row_name'    => $stat->soccer_boss_pps_year  ['und'][0]['value'],
      'value'       => $stat->soccer_boss_pps_value ['und'][0]['value']
    );
  }
  return simple_table ($data);
}
