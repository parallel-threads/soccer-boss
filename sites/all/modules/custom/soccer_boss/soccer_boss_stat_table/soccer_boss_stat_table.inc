<?php
/**
  @file
  @brief Defines the functions that create the stat tables.
*/

/**
  @brief Returns the Player Performance Stat table for the given player.
  @param $player (node) the player.
  @return (array) a render array representing the stat table.
*/
function soccer_boss_stat_table_pps ($player) {
  module_load_include ('inc', 'soccer_boss');

  $field_values = array ();

  $stats = node_load_multiple (soccer_boss_get_references ($player->nid, 'node', 'soccer_boss_pps_player'));

  $stat_years = array ();

  foreach ($stats as $stat) {
    $stat_years [] = $stat->soccer_boss_pps_year  ['und'][0]['value'];

    $field_values [] = array (
      'column_name' => $stat->title,
      'row_name'    => $stat->soccer_boss_pps_year  ['und'][0]['value'],
      'value'       => $stat->soccer_boss_pps_value ['und'][0]['value']
    );
  }

  sort ($stat_years);

  foreach (array_unique ($stat_years) as $stat_year) {
    $field_value = array (
      'column_name' => t ('Year'),
      'row_name'    => $stat_year,
      'value'       => $stat_year
    );
    array_unshift ($field_values, $field_value);
  }

  return simple_table ('', $field_values);
}
