<?php
/**
  @file
  @brief Defines the functions that create the
    Player content type, its fields, and the Player
    role.
*/

define ('player_PLAYER_TYPE', 'player_player');

/// Returns an array listing the Player vocabularies.
function player_vocabularies () {
  global $base_url;

  watchdog (
    'player',
    '[player_vocabularies] base url: @url',
    array ('@url' => $base_url)
  );

  return array (
    'player_position' => array (
      'name'         => 'Player Position',
      'machine_name' => 'player_position',
      'description'  => 'The set of possible player positions.',
      'url'          => url (drupal_get_path ('module', 'player') . '/player_positions.csv', array ('absolute' => true))
  ));
}

/**
  @brief imports the taxonomy terms listed in the
    CSV file that is referenced by the given url
    into the vocabulary that has the given vid.
  @param $vid (integer) the vocabulary id.
  @param $url (string) the CSV file url.
  @return (array) an error description or nothing.
*/
function player_import_terms ($vid, $url) {
  module_load_include ('inc', 'taxonomy_csv', 'import/taxonomy_csv.import.api');

  return taxonomy_csv_import (array (
    'import_format' => 'tree',
    'translate_by' => 'name',
    'translate_languages' => array (), 
    'keep_order' => 0,
    'source_choice' => 'url',
    'filter_format' => 'plain_text',
    'filter_format_custom' => 'none',
    'check_line' => 1,
    'check_utf8' => 1,
    'locale_custom' => '', 
    'vocabulary_target' => 'existing',
    'vocabulary_id' => $vid,
    'i18n_mode' => 0,
    'language' => 'und',
    'delete_terms' => 1,
    'check_hierarchy' => 1,
    'set_hierarchy' => 2,
    'update_or_ignore' => 'update',
    'result_stats' => 'result_stats',
    'result_terms' => 'result_terms',
    'result_level' => 'notices',
    'result_type' => 'by_message',
    'delimiter' => ',',
    'enclosure' => '"',
    'vocabulary_language' => 'und',
    'url' => $url,
    'check_options' => '', 
    'result_display' => 1
  )); 
}

/**
  @brief Creates a new vocabulary.
  @param $vocab_array (array) a vocabulary array.
*/
function player_create_vocabulary ($vocab_array) {
  if (!taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name'])) {
    // I. create the vocabulary.
    taxonomy_vocabulary_save ((object) $vocab_array);
    
    // II. import the terms if given.
    if ($vocab_array ['url']) {
      $vocab = taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name']);
      player_import_terms ($vocab->vid, $vocab_array ['url']);
    }
  }
}

/// Creates the player vocabularies.
function player_create_vocabularies () {
  foreach (player_vocabularies () as $vocab) {
    player_create_vocabulary ($vocab);
  }
}

/// Deletes the player vocabularies.
function player_delete_vocabularies () {
  foreach (array_keys (player_vocabularies ()) as $machine_name) {  
    $vocab = taxonomy_vocabulary_machine_name_load ($machine_name);
    taxonomy_vocabulary_delete ($vocab->vid);
  }
}

/// Defines the Player content type.
function player_player_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => player_PLAYER_TYPE,
      'name'        => $t ('Player'),
      'description' => $t ('Represents amateur soccer players.'),
      'help'        => $t ('Represents amateur soccer players.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'player'
  )); 
}

/// Create the Player content type.
function player_create_player_content_type () {
  module_load_include ('inc', 'player', 'player.field');

  $type = player_player_content_type ();
  node_type_save ($type);

  variable_set('comment_' . player_PLAYER_TYPE, '1');

  player_create_player_photo_field ();
  player_create_player_first_name_field ();
  player_create_player_last_name_field ();
  player_create_player_position_field ();
  player_create_player_height_field ();
  player_create_player_weight_field ();
  player_create_player_birth_date_field ();

  node_add_body_field ($type, 'Bio');
}

/**
  @brief Returns the node id of every Player node.
  @return (array) the node ids.
*/
function player_get_player_nodes () {
  $records = db_select   ('{node}', 'tbl')
             ->fields    ('tbl', array ('nid'))
             ->condition ('type', player_PLAYER_TYPE)
             ->execute   ();

  $nids = array ();
  foreach ($records as $record) {
    $nids [] = $record->nid;
  }
  return $nids;
}

/// Deletes every player node.
function player_delete_player_nodes () {
  foreach (player_get_player_nodes () as $nid) {
    node_delete ($nid);
  }
}
