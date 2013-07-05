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

/**
  @brief Returns the stats that reference the given
    entity in their subject fields.
  @param $id (integer) the subject entity id.
  @return (array) the stat ids.
*/
function stats_get_stats ($id) {
  $records = db_select   ('{stats}', 'tbl')
             ->fields    ('tbl', array ('id'))
             ->condition ('subject', $id)
             ->execute   ();

  $ids = array ();
  foreach ($records as $record) {
    $ids [] = $record->id;
  }
  return $ids;
} 

/// Saves the given stat.
function stats_save ($stat) {
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
  $content = entity_view ('stat', $stats, $view_mode, $langcode, $page);

  foreach ($stats as $stat) {
    $node = node_load ($stat->subject);
    $content += array (
      'content' => array (
        '#type'   => 'markup',
        '#markup' => '<h2>Name:</h2><p>' . $stat->name . '</p>' .
                     '<h2>Subject:</h2><p>' . l ("$node->title ($stat->subject)", "node/$node->nid") . '</p>'
    ));
  }

  return $content;
}

/// Deletes the given stat.
function stats_delete ($id) {
  return entity_delete ('stat', $id);
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
function stats_value_save ($stat_value) {
  return entity_save ('stat_value', $stat_value);
}

/// Deletes the referenced stat value.
function stats_value_delete ($stat_value_id) {
  return entity_delete ('stat_value', $stat_value_id);
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
  $content = array ();
  foreach ($stat_values as $stat_value) {

    $stat = stats_load ($stat_value->stat);
    $node = node_load ($stat->subject);

    $content += array (
      'content' => array (
        '#type'   => 'markup',
        '#markup' => '<h2>Stat:</h2><p>' . l ($stat->name, "stat/$stat->id/view") . '</p>' .
                     '<h2>Subject:</h2><p>' . l ("$node->title ($stat->subject)", "node/$node->nid") . '</p>' .
                     '<h2>Value:</h2><p>' . l ("$stat_value->content", "stat/value/$stat_value->id/edit") . '</p>' .
                     '<h2>Date:</h2><p>'  . l (date ('F j, Y, g:i a', $stat_value->date), "stat/value/$stat_value->id/edit") . '</p>' 
    ));
  }

  return $content;
}

/**
  @brief Returns the stat values associated with
    the given stat sorted by date.
  @param $statId (integer) the stat id.
  @return (array) the stat value ids.
*/
function stats_get_stat_values ($statId) {
  $records = db_select   ('{stat_values}', 'tbl')
             ->fields    ('tbl', array ('id'))
             ->condition ('stat', $statId)
             ->orderBy   ('date', 'DESC')
             ->execute   (); 

  $ids = array (); 
  foreach ($records as $record) {
    $ids [] = $record->id;
  }
  return $ids;
}
