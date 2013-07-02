<?php
/**
  @file
  @brief Defines the pages that are defined by the
    Stats module.
*/

/**
  @brief Returns the View Stat page.
  @param $id (integer) the stat id.
  @return (array) the page render array.
*/
function stats_page ($id) {
  module_load_include ('inc', 'stats');
  drupal_set_title ('View Stat');
  $stat = stats_load ($id);
  return stats_view (
    $stat ? array ($stat) : stats_load_multiple (),
    'web', null, true
  );
}

/**
  @brief Returns the Edit Stat page.
  @param $statId (integer) the stat id.
  @return (array) the render array.
*/
function stats_edit_page ($statId) {
  drupal_set_title ('Edit Stat');
  return drupal_get_form ('stats_edit_form', $statId);
}

/**
  @brief Deletes the referenced stat and redirects
    to the referer page.
  @param $statId (integer) the stat id.
*/
function stats_delete_page ($statId) {
  module_load_include ('inc', 'stats');
  stats_delete ($statId);
  drupal_set_message ('Deleted the stat.');
  drupal_goto ('stat');
}

/**
  @brief Returns the View Stat Value page.
  @param $statId (integer) the stat id.
  @param $stat_value_id (integer) the stat value id.
  @return (array) the page render array.
*/
function stats_value_page ($stat_value_id = null) {
  module_load_include ('inc', 'stats');
  drupal_set_title ('View Stat Value');
  $stat_value = stats_value_load ($stat_value_id);
  return stats_value_view (
    $stat_value ? array ($stat_value) : stats_value_load_multiple (),
    'web', null, true
  );
}

/**
  @brief Returns the Edit Stat Value page.
  @param $stat_value_id (integer) the stat id.
  @return (array) the render array.
*/
function stats_value_edit_page ($stat_value_id) {
  drupal_set_title ('Edit Stat Value');
  return drupal_get_form ('stats_value_edit_form', $stat_value_id);
}

/**
  @brief Deletes the referenced stat value and
    redirects to the associated stat page.
  @param $stat_value_id (integer) the stat value id.
*/
function stats_value_delete_page ($stat_value_id) {
  module_load_include ('inc', 'stats');
  $stat_value = stats_value_load ($stat_value_id);
  stats_value_delete ($stat_value_id);
  drupal_set_message ('Deleted stat value.');
  drupal_goto ('stat/' . $stat_value->stat);
}
