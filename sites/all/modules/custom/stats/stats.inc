<?php
/**
  @file
  @brief The Stats module defines that Stat and
    Stat Value entity types. The stats.inc file
    defines the Stat API functions. 
*/

/// Loads the referenced stats.
function stats_load_multiple ($ids = false, $reset = false) {
  return entity_load ('stat', $ids, array (), $reset);
}

/// Loads the referenced stat.
function stats_load ($id, $reset = false) {
  return entity_load_single ('stat', $id, $reset);
}

/// Saves the given stat.
function stats_save ($stat) {
  watchdog (
    'stats',
    '[stats_save] stat: <pre>@stat</pre>',
    array (
      '@stat' => print_r ($stat, true)
  ));
  return entity_save ('stat', $stat);
}

/**
  @brief Returns a render array representing the given stats.
  @param $stats (array) the stats.
  @param $view_mode (string) the view mode.
  @param $lang_code (string) a language code.
  @param $page (boolean) whether or not the entities
    should be rendered without its title.
*/
function stats_view ($stats, $view_mode = 'web', $langcode = null, $page = null) {
  return entity_view ('stat', $stats, $view_mode, $langcode, $page);
}

/// Deletes the given stat.
function stats_delete ($stat) {
  return entity_delete ('stat', entity_id ('stat', $stat));
}

/**
  @brief Deletes the referenced stats. 
  @param $ids (array) the stat ids. This function
    loads all of the stats if this array is empty.
  @return (array) the stats.
*/
function stats_delete_multiple ($ids) {
  return entity_delete_multiple ('stat', $ids);
}

/// Loads the referenced stat values.
function stats_value_load_multiple ($ids = false, $reset = false) {
  return entity_load ('stat_value', $ids, array (), $reset);
}

/// Loads the referenced stat value.
function stats_value_load ($id, $reset = false) {
  return entity_load_single ('stat_value', $id, $reset);
}

/// Saves the given stat value.
function stats_value_save ($statValue) {
  watchdog (
    'stats',
    '[stats_value_save] stat_value: <pre>@statValue</pre>',
    array (
      '@statValue' => print_r ($statValue)
  ));
  return entity_save ('stat_value', $statValue);
}

/// Deletes the referenced stat value.
function stats_value_delete ($statValue) {
  return entity_delete ('stat_value', entity_id ('stat_value', $statValue));
}

/// Deletes the referenced stat values.
function stats_value_delete_multiple ($ids) {
  return entity_delete_multiple ('stat_value', $ids);
}

/**
  @brief Returns a render array representing the given stat value.
  @param $stat_values (array) the stat values.
  @param $view_mode (string) the view mode.
  @param $lang_code (string) a language code.
  @param $page (boolean) whether or not the entities
    should be rendered without its title.
*/
function stats_value_view ($stat_values, $view_mode = 'web', $langcode = null, $page = null) {
  return entity_view ('stat_value', $stat_values, $view_mode, $langcode, $page);
}
