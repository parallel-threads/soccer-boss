<?php
/**
  @file
  @brief This file defines the API for creating and
    manipulating the Stat content types used by the
    Hockey Boss site.
*/

// ----- I. Content Types -----

/// The Player Performance stat type name.
define ('hockey_boss_stat_PPS_TYPE', 'hockey_boss_stat_pps');

/// The Player Fitness stat type name.
define ('hockey_boss_stat_PFS_TYPE', 'hockey_boss_stat_pfs');

/// The Player Game stat type name.
define ('hockey_boss_stat_PGS_TYPE', 'hockey_boss_stat_pgs');

/// Returns the Player Game Stat type.
function hockey_boss_stat_pgs_type () {
  module_load_include ('inc', 'hockey_boss');
  return array (
    'name'              => 'Player Game Stat',
    'description'       => 'Represents player game statistics.',
    'node_type'         => hockey_boss_stat_PGS_TYPE,
    'subject_node_type' => hockey_boss_PLAYER_PROFILE_TYPE
  );
}

/// Returns the Player Fitness Stat type. 
function hockey_boss_stat_pfs_type () {
  module_load_include ('inc', 'hockey_boss');
  return array (
    'name'              => 'Player Fitness Stat',
    'description'       => 'Represents player fitness statistics.',
    'node_type'         => hockey_boss_stat_PFS_TYPE,
    'subject_node_type' => hockey_boss_PLAYER_PROFILE_TYPE
  );
}

/// Returns the Player Performance Stat type.
function hockey_boss_stat_pps_type () {
  module_load_include ('inc', 'hockey_boss');
  return array (
    'name'              => 'Player Performance Stat',
    'description'       => 'Represents player performance statistics.',
    'node_type'         => hockey_boss_stat_PPS_TYPE,
    'subject_node_type' => hockey_boss_PLAYER_PROFILE_TYPE
  );
}

/**
  @brief Returns an array listing the stat types
    defined by this module.
  @return (array) the stat types.
*/
function hockey_boss_stat_get_stat_types () {
  module_load_include ('inc', 'hockey_boss');

  return array (
    hockey_boss_stat_pgs_type (),
    hockey_boss_stat_pfs_type (),
    hockey_boss_stat_pps_type ()
  );
}

/**
  @brief Implements hook_stat_create_<node type>_stat_type_node_type ().
  @details
    Adds fields to the Player Game Stats node type.
*/
function hockey_boss_stat_stat_create_hockey_boss_stat_pgs_stat_type_node_type ($stat_type_node_type) {
  module_load_include ('inc', 'hockey_boss');
  simple_field_create_entity_reference ('node', $stat_type_node_type->type, $stat_type_node_type->type . '_game', t ('Game'), array (hockey_boss_GAME_TYPE), 'node', 1);
}

/**
  @brief Accepts a Player Game Stat node and returns its game node id.
  @param $stat_node (object) the stat node.
  @return (int) the game node id.
*/
function hockey_boss_stat_pgs_get_game ($stat_node) {
  return $stat_node->{$stat_node->type . '_game'}['und'][0]['target_id'];
}

/**
  @brief Accepts a Player Game Stat node and a game
    node id and sets the stat node to point to the
    given game node.
  @param $node (object) the stat node.
  @param $game_nid (int) the game node id.
*/
function hockey_boss_stat_pgs_set_game ($stat_node, $game_nid) {
  $stat_node->{$stat_node->type . '_game'}['und'][0]['target_id'] = $game_nid;
}

/// Creates the stat types defined by this module.
function hockey_boss_stat_create_stat_types () {
  module_load_include ('inc', 'stat');
  stat_type_create_multiple (hockey_boss_stat_get_stat_types ());
}

/// Deletes the stat types defined by this module.
function hockey_boss_stat_delete_stat_types () {
  module_load_include ('inc', 'stat');
  stat_type_delete_multiple (hockey_boss_stat_get_stat_types ());
}

/**
  @brief Returns the player performance stat.
  @param $player_nid (int) the player node id.
  @param $stat_name (string) the stat name.
  @param $year (int) the year.
  @return (array) the stat.
*/
function hockey_boss_stat_get_pps ($player_nid, $stat_name, $year) {
  module_load_include ('inc', 'stat');
  $pps_query = stat_node_query_create (hockey_boss_stat_PPS_TYPE);
  $pps_query = stat_node_query_add_year_filter ($pps_query, $year);
  $pps_query = stat_node_query_add_title_filter ($pps_query, $stat_name);
  $pps_query = stat_node_query_add_subject_filter ($pps_query, $player_nid);
  $pps_stat_nodes = stat_node_query_execute ($pps_query);
  $stat = empty ($pps_stat_nodes) ? null : stat_from_stat_node ($pps_stat_nodes [0]);

  if (is_null ($stat)) {
    $stat = stat_create ($stat_name, null, 0, 0, "$year-01-01 12:00:00", $player_nid);
    $pgs_query = stat_node_query_create (hockey_boss_stat_PGS_TYPE);
    $pgs_query = stat_node_query_add_year_filter ($pgs_query, $year);
    $pgs_query = stat_node_query_add_title_filter ($pgs_query, $stat_name);
    $pgs_query = stat_node_query_add_subject_filter ($pgs_query, $player_nid);
    $pgs_stat_nodes = stat_node_query_execute ($pgs_query);
    foreach ($pgs_stat_nodes as $pgs_stat_node) {
      $stat ['value'] += stat_node_get_value ($pgs_stat_node);
      $stat ['unit'] = stat_node_get_unit ($pgs_stat_node);
    }
  }
  return $stat;
}

/**
  @brief Returns the player fitess stat node.
  @param $player_nid (int) the player node id.
  @param $stat_name (string) the stat name.
  @param $year (int) the year.
  @return (object) the node.
*/
function hockey_boss_stat_get_pfs_node ($player_nid, $stat_name, $year) {
  module_load_include ('inc', 'stat');
  $query = stat_node_query_create (hockey_boss_stat_PFS_TYPE);
  $query = stat_node_query_add_year_filter ($query, $year);
  $query = stat_node_query_add_title_filter ($query, $stat_name);
  $query = stat_node_query_add_subject_filter ($query, $player_nid);
  $stat_nodes = stat_node_query_execute ($query);
  $stat_node = empty ($stat_nodes) ? null : $stat_nodes [0];

  if (is_null ($stat_node)) {
    $stat_date = "$year-01-01 12:00:00";
    $stat_type = hockey_boss_stat_pfs_type ();
    $stat_node = stat_node_create ($stat_type, $stat_name, '0', '0', $stat_date, $player_nid);
    node_save ($stat_node);
  }
  return $stat_node;
}

/**
  @brief Returns the team performance stat.
  @param $team_node (object) the team node.
  @param $stat_name (string) the stat name.
  @param $year (int) the year.
  @return (array) the stat.
*/
function hockey_boss_stat_get_tps ($team_node, $stat_name, $year) {
  module_load_include ('inc', 'hockey_boss');
  $stat = stat_create ($stat_name, null, 0, 0, "$year-01-01 12:00:0", $team_node->nid);
  $player_nids = hockey_boss_get_team_player_nids ($team_node);
  foreach ($player_nids as $player_nid) {
    $pps = hockey_boss_stat_get_pps ($player_nid, $stat_name, $year);
    $stat ['value'] += $pps ['value'];
    $stat ['unit']   = $pps ['unit'];
  } 
  return $stat;
}
