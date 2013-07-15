<?php
/**
  @file
  @brief Defines the functions that create the core
    content types and roles along with their fields
    and basic operations.
*/

// ----- I. Defines the content type names. -----

/// Defines the coach content type's name.
define ('soccer_boss_COACH_TYPE', 'soccer_boss_coach');

/// Defines the game content type's name.
define ('soccer_boss_GAME_TYPE', 'soccer_boss_game');

/// Defines the player content type's name.
define ('soccer_boss_PLAYER_TYPE', 'soccer_boss_player');

/// Defines the player game stats content type's name.
define ('soccer_boss_PLAYER_GAME_STATS_TYPE', 'soccer_boss_player_game_stats');

/// Defines the team content type's name.
define ('soccer_boss_TEAM_TYPE', 'soccer_boss_team');

// ----- II. Defines the vocabularies -----

/// Returns an array listing the Player vocabularies.
function soccer_boss_vocabularies () {
  global $base_url;

  watchdog (
    'soccer_boss',
    '[soccer_boss_vocabularies] base url: @url',
    array ('@url' => $base_url)
  );

  return array (
    'soccer_boss_position' => array (
      'name'         => 'Player Position',
      'machine_name' => 'soccer_boss_position',
      'description'  => 'The set of possible player positions.',
      'url'          => url (drupal_get_path ('module', 'soccer_boss') . '/player_positions.csv', array ('absolute' => true))
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
function soccer_boss_import_terms ($vid, $url) {
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
function soccer_boss_create_vocabulary ($vocab_array) {
  if (!taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name'])) {
    // I. create the vocabulary.
    taxonomy_vocabulary_save ((object) $vocab_array);
    
    // II. import the terms if given.
    if ($vocab_array ['url']) {
      $vocab = taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name']);
      soccer_boss_import_terms ($vocab->vid, $vocab_array ['url']);
    }
  }
}

/// Creates the core vocabularies.
function soccer_boss_create_vocabularies () {
  foreach (soccer_boss_vocabularies () as $vocab) {
    soccer_boss_create_vocabulary ($vocab);
  }
}

/// Deletes the core vocabularies.
function soccer_boss_delete_vocabularies () {
  foreach (array_keys (soccer_boss_vocabularies ()) as $machine_name) {  
    $vocab = taxonomy_vocabulary_machine_name_load ($machine_name);
    taxonomy_vocabulary_delete ($vocab->vid);
  }
}

// ----- III. Defines the content types. -----


/// Defines the Coach content type.
function soccer_boss_coach_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_COACH_TYPE,
      'name'        => $t ('Coach'),
      'description' => $t ('Represents amateur soccer coaches.'),
      'help'        => $t ('Represents amateur soccer coaches.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Game content type.
function soccer_boss_game_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_GAME_TYPE,
      'name'        => $t ('Game'),
      'description' => $t ('Represents amateur soccer matches.'),
      'help'        => $t ('Represents amateur soccer matches.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Player content type.
function soccer_boss_player_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_PLAYER_TYPE,
      'name'        => $t ('Player'),
      'description' => $t ('Represents amateur soccer players.'),
      'help'        => $t ('Represents amateur soccer players.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Player Game Stats content type.
function soccer_boss_player_game_stats_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'name'        => $t ('Player Game Stats'),
      'description' => $t ('Represents player game stats.'),
      'help'        => $t ('Represents player game stats.'),
      'has_title'   => false,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Team content type.
function soccer_boss_team_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_TEAM_TYPE,
      'name'        => $t ('Team'),
      'description' => $t ('Represents amateur soccer teams.'),
      'help'        => $t ('Represents amateur soccer teams.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Returns the content type definitions array.
function soccer_boss_content_types () {
  return array (
    soccer_boss_COACH_TYPE => array (
      'type'       => soccer_boss_coach_content_type (),
      'body_label' => 'Bio',
      'fields'     => array (
        'soccer_boss_coach_photo'      => 'soccer_boss_create_coach_photo_field',
        'soccer_boss_coach_first_name' => 'soccer_boss_create_coach_first_name_field',
        'soccer_boss_coach_last_name'  => 'soccer_boss_create_coach_last_name_field'
    )),
    soccer_boss_GAME_TYPE => array (
      'type'       => soccer_boss_game_content_type (),
      'body_label' => 'Commentary',
      'fields'     => array (
        'soccer_boss_game_teams'   => 'soccer_boss_create_game_teams_field',
        'soccer_boss_game_date'    => 'soccer_boss_create_game_date_field',
        'soccer_boss_game_minutes' => 'soccer_boss_create_game_score_field',
    )),
    soccer_boss_PLAYER_TYPE => array (
      'type'       => soccer_boss_player_content_type (),
      'body_label' => 'Bio',
      'fields'     => array (
        'soccer_boss_player_photo'      => 'soccer_boss_create_player_photo_field',
        'soccer_boss_player_first_name' => 'soccer_boss_create_player_first_name_field',
        'soccer_boss_player_last_name'  => 'soccer_boss_create_player_last_name_field',
        'soccer_boss_player_team'       => 'soccer_boss_create_player_team_field',
        'soccer_boss_player_position'   => 'soccer_boss_create_player_position_field',
        'soccer_boss_player_height'     => 'soccer_boss_create_player_height_field',
        'soccer_boss_player_weight'     => 'soccer_boss_create_player_weight_field',
        'soccer_boss_player_birth_date' => 'soccer_boss_create_player_birth_date_field'
    )),
    soccer_boss_PLAYER_GAME_STATS_TYPE => array (
      'type'       => soccer_boss_player_game_stats_content_type (),
      'body_label' => 'Commentary',
      'fields'     => array (
        'soccer_boss_game_stats_player'  => 'soccer_boss_create_player_game_stats_player_field',
        'soccer_boss_game_stats_game'    => 'soccer_boss_create_player_game_stats_game_field',
        'soccer_boss_game_stats_minutes' => 'soccer_boss_create_player_game_stats_minutes_field',
        'soccer_boss_game_stats_goals'   => 'soccer_boss_create_player_game_stats_goals_field',
        'soccer_boss_game_stats_assists' => 'soccer_boss_create_player_game_stats_assists_field',
        'soccer_boss_game_stats_shots'   => 'soccer_boss_create_player_game_stats_shots_field',
        'soccer_boss_game_stats_sog'     => 'soccer_boss_create_player_game_stats_sog_field'
    )),
    soccer_boss_TEAM_TYPE => array (
      'type'       => soccer_boss_team_content_type (),
      'body_label' => 'Description',
      'fields'     => array (
        'soccer_boss_team_logo'    => 'soccer_boss_create_team_logo_field',
        'soccer_boss_team_coach'   => 'soccer_boss_create_team_coach_field'
    ))
  );
}

/// Creates the content types.
function soccer_boss_create_content_types () {
  module_load_include ('inc', 'soccer_boss', 'soccer_boss.field');

  foreach (soccer_boss_content_types () as $name => $definition) {
    // I. create the content type.
    node_type_save ($definition ['type']);

    // II. create the fields.
    node_add_body_field ($definition ['type'], $definition ['body_label']);
    foreach ($definition ['fields'] as $field_name => $field_hook) {
      call_user_func ($field_hook);
    }

    // III. disable commenting.
    variable_set ($name, '0');
  }
}

/// Deletes the content types.
function soccer_boss_delete_content_types () {
  foreach (soccer_boss_content_types () as $name => $definition) {
    // I. delete the nodes.
    soccer_boss_delete_nodes ($name);

    // II. delete the fields.
    foreach (array_keys ($definition ['fields']) as $field_name) {
      field_delete_field ($field_name);
    }

    // III. delete the type.
    node_type_delete ($name);
  }
}

// ----- IV. Defines the basic node operations. -----

/**
  @brief Returns the node id of every node that has the given type.
  @param $type (string) the node type.
  @return (array) the node ids.
*/
function soccer_boss_get_nodes ($type) {
  $records = db_select   ('{node}', 'tbl')
             ->fields    ('tbl', array ('nid'))
             ->condition ('type', $type)
             ->execute   ();

  $nids = array ();
  foreach ($records as $record) {
    $nids [] = $record->nid;
  }
  return $nids;
}

/**
  @brief Deletes every node that has the given type.
  @param $type (string) the node type.
*/
function soccer_boss_delete_nodes ($type) {
  foreach (soccer_boss_get_nodes ($type) as $nid) {
    node_delete ($nid);
  }
}
