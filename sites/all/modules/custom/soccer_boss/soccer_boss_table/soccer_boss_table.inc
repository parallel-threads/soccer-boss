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
        'column_name'   => t ('Year'),
        'row_name'      => $stat_year,
        'value'         => $stat_year
      );
      $stat_years [] = $stat_year;
    }
    $stat_uri   = node_uri ($stat);
    $stat_value = $stat->soccer_boss_pfs_value ['und'][0]['value'];
    $data ['fields'][] = array (
      'column_name'   => $stat->title,
      'row_name'      => $stat_year,
      'value'         => $stat_value,
      'display_value' => user_access ('edit any soccer_boss_pfs content') ? l ($stat_value, $stat_uri ['path'] . '/edit') : $stat_value
    );
  } 

  return $data;
}

/**
  @brief Returns the Player Game Stats table for the given player.
  @param $player (node) the player.
  @return (array) a render array representing the stat table.
*/
function soccer_boss_table_pgs ($player) {
  module_load_include ('inc', 'soccer_boss');

  $stats = soccer_boss_get_pgs_nodes ($player->nid);

  $data = array (
    'columns' => array (
      array (
        'column_name' => t ('Date'),
        'weight'      => 2,
      ),
      array (
        'column_name' => t ('Game'),
        'weight'      => 1
    )),
    'show_totals' => true,
    'label_column_name' => t ('Date')
  );
  $games = array ();
  foreach ($stats as $stat) {
    $game = node_load ($stat->soccer_boss_pgs_game ['und'][0]['target_id']);
    $game_date = $game->soccer_boss_game_date ['und'][0]['value'];

    if (!$game) { continue; }
    if (!array_key_exists ($game_date, $games) ||
        !array_key_exists ($game->nid, $games [$game_date])) {
      $games [$game_date][$game->nid] = $game;
    }

    $stat_uri   = node_uri ($stat);
    $stat_value = $stat->soccer_boss_pgs_value ['und'][0]['value'];
    $data ['fields'][] = array (
      'column_name'   => $stat->title,
      'row_name'      => $game->nid,
      'value'         => $stat_value
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
  return $data;
}

function soccer_boss_table_pps_access ($user) {
  return user_access ('edit any soccer_boss_pps content', $user);
}

function soccer_boss_table_pps_default_value ($column_name, $row_name, $player_nid) {
  module_load_include ('inc', 'soccer_boss');
  $pps = soccer_boss_get_derived_pps ($player_nid, $column_name, $row_name); 
  return $pps ['value'];
}

function soccer_boss_table_pps_update () {
  drupal_set_message ('stats saved');
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
    'module' => 'soccer_boss_table',
    'rows' => array (),
    'columns' => array (
      array (
        'column_name' => t ('Year'),
        'weight'      => 3,
      ),
      array (
        'column_name' => 'Goals',
        'weight'      => 2,
      ),
      array (
        'column_name' => 'Assists',
        'weight'      => 1
    )),
    'sort_column' => t ('Year'),
    'label_column_name' => t ('Year'),
    'show_totals'       => true,
    'fields' => array (),
    'submit_function'               => 'soccer_boss_table_pps_update',
    'access_function'               => 'soccer_boss_table_pps_access',
    'default_field_value_function'  => 'soccer_boss_table_pps_default_value',
    'default_field_value_arguments' => array ($player->nid)
  );
  $stat_years = array ();
  foreach ($stats as $stat) {
    $stat_year = $stat->soccer_boss_pps_year ['und'][0]['value'];
    if (!in_array ($stat_year, $stat_years)) {
      $stat_years [] = $stat_year;
    }
    $stat_uri   = node_uri ($stat);
    $stat_value = $stat->soccer_boss_pps_value ['und'][0]['value'];
    $data ['fields'][] = array (
      'column_name'   => $stat->title,
      'row_name'      => $stat_year,
      'value'         => $stat_value,
      'display_value' => $stat_value
    );
  }

  $game_stats = soccer_boss_get_pgs_nodes ($player->nid);
  $current_year = date ('Y', time ());
  $min_year = $current_year;
  foreach ($game_stats as $game_stat) {
    $game = node_load ($game_stat->soccer_boss_pgs_game ['und'][0]['target_id']);
    $game_date = date_parse ($game->soccer_boss_game_date ['und'][0]['value']);
    $game_year = $game_date ['year'];
    if (!$game) { continue; }
    if ($game_year < $min_year) {
      $min_year = $game_year;
    }
  }
  for ($year = $min_year; $year <= $current_year; $year ++) {
    if (!in_array ($year, $stat_years)) {
      $stat_years [] = $year;
    }
  } 
  foreach ($stat_years as $stat_year) {
    $data ['rows'][] = $stat_year;
    $data ['fields'][] = array (
      'column_name' => t ('Year'),
      'row_name'    => $stat_year,
      'value'       => $stat_year
    );
  }
  return $data;
}
