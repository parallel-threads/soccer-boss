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
  $stat = stats_load ($id);
  return stats_view (
    $stat ? array ($stat) : stats_load_multiple (),
    'web', null, true
  );
}

/**
  @brief Returns the View Stat Value page.
  @param $statId (integer) the stat id.
  @param $statValueId (integer) the stat value id.
  @return (array) the page render array.
*/
function stats_value_page ($statValueId = null) {
  module_load_include ('inc', 'stats');
  $stat_value = stats_value_load ($statValueId);
  return stats_value_view (
    $stat_value ? array ($stat_value) : stats_value_load_multiple (),
    'web', null, true
  );
}
