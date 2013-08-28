<?php
/**
  @file
  @brief Defines the functions that create the core
    content types and roles along with their fields
    and basic operations.
*/

// ----- I. Defines the content type names. -----

/// Defines the club content type's name.
define ('soccer_boss_CLUB_TYPE', 'soccer_boss_club');

/// Defines the game content type's name.
define ('soccer_boss_GAME_TYPE', 'soccer_boss_game');

/// Defines the league content type's name.
define ('soccer_boss_LEAGUE_TYPE', 'soccer_boss_league');

/// Defines the player content type's name.
define ('soccer_boss_PLAYER_TYPE', 'soccer_boss_player');

/// Defines the team staff's type's name.
define ('soccer_boss_STAFF_TYPE', 'soccer_boss_staff');

/// Defines the team content type's name.
define ('soccer_boss_TEAM_TYPE', 'soccer_boss_team');
 
// ----- I.A. Define the stat type names. -----

/// Defines the player fitness stat (PFS) type's name.
define ('soccer_boss_PFS_TYPE', 'soccer_boss_pfs');

/// Defines the player game stat (PGS) type's name.
define ('soccer_boss_PGS_TYPE', 'soccer_boss_pgs');

/// Defines the player performance stat (PPS) type's name.
define ('soccer_boss_PPS_TYPE', 'soccer_boss_pps');

/// Defines the team stat (TS) type's name.
define ('soccer_boss_TS_TYPE', 'soccer_boss_ts');

// ----- II. Defines the vocabularies -----

/// Returns an array listing the Player vocabularies.
function soccer_boss_vocabularies () {
  global $base_url;

  return array (
    'soccer_boss_age' => array (
      'name'         => 'Age Group',
      'machine_name' => 'soccer_boss_age',
      'description'  => 'The set of recognized age groups.'
    ),
    'soccer_boss_division' => array (
      'name'         => 'Division',
      'machine_name' => 'soccer_boss_division',
      'description'  => 'The set of league divisions.'
    ),
    'soccer_boss_gender' => array (
      'name'         => 'Gender',
      'machine_name' => 'soccer_boss_gender',
      'description'  => 'The set of genders.',
      'url'          => url (drupal_get_path ('module', 'soccer_boss') . '/genders.csv')
    ),
    'soccer_boss_player_position' => array (
      'name'         => 'Player Position',
      'machine_name' => 'soccer_boss_player_position',
      'description'  => 'The set of possible player positions.',
      'url'          => url (drupal_get_path ('module', 'soccer_boss') . '/player_positions.csv', array ('absolute' => true))
    ),
    'soccer_boss_staff_role' => array (
      'name'         => 'Staff Role',
      'machine_name' => 'soccer_boss_staff_role',
      'description'  => 'The set of possible staff member roles.',
      'url'          => url (drupal_get_path ('module', 'soccer_boss') . '/staff_roles.csv', array ('absolute' => true))
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

/// Defines the Club content type.
function soccer_boss_club_content_type () {
  $t = get_t ();
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_CLUB_TYPE,
      'name'        => $t ('Club'),
      'description' => $t ('Represents amateur soccer clubs.'),
      'help'        => $t ('Represents amateur soccer clubs.'),
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

/// Defines the League content type.
function soccer_boss_league_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_LEAGUE_TYPE,
      'name'        => $t ('League'),
      'description' => $t ('Represents amateur soccer leagues.'),
      'help'        => $t ('Represents amateur soccer leagues.'),
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

/// Defines the Staff content type.
function soccer_boss_staff_content_type () {
  $t = get_t ();
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_STAFF_TYPE,
      'name'        => $t ('Staff'),
      'description' => $t ('Represents team staff members.'),
      'help'        => $t ('Represents team staff members.'),
      'has_title'   => true,
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

// ----- III.A. Defines the Stat content types.

/// Defines the Player Fitness Stat (PFS) type.
function soccer_boss_pfs_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_PFS_TYPE,
      'name'        => $t ('Player Fitness Stat'),
      'description' => $t ('Represents player fitness stats.'),
      'help'        => $t ('Represents player fitness stats.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Player Game Stat (PGS) type.
function soccer_boss_pgs_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_PGS_TYPE,
      'name'        => $t ('Player Game Stat'),
      'description' => $t ('Represents player game stats.'),
      'help'        => $t ('Represents player game stats.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Player Performance Stat (PPS) type.
function soccer_boss_pps_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_PPS_TYPE,
      'name'        => $t ('Player Performance Stat'),
      'description' => $t ('Represents player performance stats.'),
      'help'        => $t ('Represents player performance stats.'),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'soccer_boss'
  )); 
}

/// Defines the Team Stat (TS) type.
function soccer_boss_ts_content_type () {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => soccer_boss_TS_TYPE,
      'name'        => $t ('Team Stat'),
      'description' => $t ('Represents team stats.'),
      'help'        => $t ('Represents team stats.'),
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
    soccer_boss_CLUB_TYPE => array (
      'type'       => soccer_boss_club_content_type (),
      'body_label' => 'Overview',
      'fields'     => array (
        'soccer_boss_club_league' => 'soccer_boss_create_club_league_field'
    )),
    soccer_boss_GAME_TYPE => array (
      'type'       => soccer_boss_game_content_type (),
      'body_label' => 'Commentary',
      'fields'     => array (
        'soccer_boss_game_teams' => 'soccer_boss_create_game_teams_field',
        'soccer_boss_game_date'  => 'soccer_boss_create_game_date_field',
        'soccer_boss_game_score' => 'soccer_boss_create_game_score_field',
    )),
    soccer_boss_LEAGUE_TYPE => array (
      'type'       => soccer_boss_league_content_type (),
      'body_label' => 'Overview',
      'fields'     => array ()
    ),
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
    soccer_boss_STAFF_TYPE => array (
      'type'       => soccer_boss_staff_content_type (),
      'body_label' => 'Bio',
      'fields'     => array (
        'soccer_boss_staff_photo'      => 'soccer_boss_create_staff_photo_field',
        'soccer_boss_staff_first_name' => 'soccer_boss_create_staff_first_name_field',
        'soccer_boss_staff_last_name'  => 'soccer_boss_create_staff_last_name_field',
        'soccer_boss_staff_team'       => 'soccer_boss_create_staff_team_field',
        'soccer_boss_staff_role'       => 'soccer_boss_create_staff_role_field'
    )),
    soccer_boss_TEAM_TYPE => array (
      'type'       => soccer_boss_team_content_type (),
      'body_label' => 'Overview',
      'fields'     => array (
        'soccer_boss_team_logo'    => 'soccer_boss_create_team_logo_field'
    )),
    soccer_boss_PFS_TYPE => array (
      'type'       => soccer_boss_pfs_content_type (),
      'body_label' => false,
      'fields'     => array (
        'soccer_boss_pfs_player' => 'soccer_boss_create_pfs_player_field',
        'soccer_boss_pfs_value'  => 'soccer_boss_create_pfs_value_field',
        'soccer_boss_pfs_date'   => 'soccer_boss_create_pfs_date_field'
    )),
    soccer_boss_PGS_TYPE => array (
      'type'       => soccer_boss_pgs_content_type (),
      'body_label' => false,
      'fields'     => array (
        'soccer_boss_pgs_player' => 'soccer_boss_create_pgs_player_field',
        'soccer_boss_pgs_game'   => 'soccer_boss_create_pgs_game_field',
        'soccer_boss_pgs_value'  => 'soccer_boss_create_pgs_value_field'
    )),
    soccer_boss_PPS_TYPE => array (
      'type'       => soccer_boss_pps_content_type (),
      'body_label' => false,
      'fields'     => array (
        'soccer_boss_pps_player' => 'soccer_boss_create_pps_player_field',
        'soccer_boss_pps_value'  => 'soccer_boss_create_pps_value_field',
        'soccer_boss_pps_year'   => 'soccer_boss_create_pps_year_field'
    )),
    soccer_boss_TS_TYPE => array (
      'type'       => soccer_boss_ts_content_type (),
      'body_label' => false,
      'fields'     => array (
        'soccer_boss_ts_team'  => 'soccer_boss_create_ts_team_field',
        'soccer_boss_ts_value' => 'soccer_boss_create_ts_value_field',
        'soccer_boss_ts_year'  => 'soccer_boss_create_ts_year_field'
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
    if ($definition ['body_label']) {
      node_add_body_field ($definition ['type'], $definition ['body_label']);
    }
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

// ----- V. Defines the core user roles. -----

/// Define the Team Coach role name.
define ('soccer_boss_COACH_ROLE', 'soccer_boss_coach');

/// Define the Player role name.
define ('soccer_boss_PLAYER_ROLE', 'soccer_boss_player');

/// Define the Team Staff role name.
define ('soccer_boss_TEAM_STAFF_ROLE', 'soccer_boss_team_staff');

/// Define the Club Staff role name.
define ('soccer_boss_CLUB_STAFF_ROLE', 'soccer_boss_club_staff');

/**
  @brief Creates the given user role.
  @param $name (string) the role name.
  @return (boolean) returns true iff the role was 
    created successfully.
  @note This function will display and log an error
    message on failure.
*/
function soccer_boss_create_role ($name) {
  if (!user_role_load_by_name ($name)) {
    if (!user_role_save ((object) array ('name' => $name))) {
      $msg = "Error: an error occured while trying to create the $name role.";
      drupal_set_message ($msg, 'error');
      watchdog (
        'soccer_boss',
        '[soccer_boss_create_role] ' . $msg,
        array (), 
        WATCHDOG_ERROR
      );
    }
  }
}

/**
  @brief Assigns the given permissions to the role
    that has the given name.
  @param $name (string) the role name.
  @param $permissions (array) the permission names.
*/
function soccer_boss_grant_permissions ($name, $permissions) {
  $role = user_role_load_by_name ($name);
  user_role_grant_permissions ($role->rid, $permissions);
}

/**
  @brief Returns a list of the core user roles and
    their permissions.
  @return (array) the core user roles.
*/
function soccer_boss_roles () {
  return array (
    soccer_boss_PLAYER_ROLE => array (
      'create '     . soccer_boss_PLAYER_TYPE            . ' content', 
      'edit own '   . soccer_boss_PLAYER_TYPE            . ' content', 
      'delete own ' . soccer_boss_PLAYER_TYPE            . ' content',
      'create '     . soccer_boss_PPS_TYPE               . ' content',
      'edit any '   . soccer_boss_PPS_TYPE               . ' content',
      'delete any ' . soccer_boss_PPS_TYPE               . ' content',
    ),
    soccer_boss_TEAM_STAFF_ROLE => array (
      'create '     . soccer_boss_GAME_TYPE              . ' content',
      'edit any '   . soccer_boss_GAME_TYPE              . ' content',
      'delete any ' . soccer_boss_GAME_TYPE              . ' content',
      'create '     . soccer_boss_PLAYER_TYPE            . ' content', 
      'edit any '   . soccer_boss_PLAYER_TYPE            . ' content', 
      'delete any ' . soccer_boss_PLAYER_TYPE            . ' content', 
      'create '     . soccer_boss_STAFF_TYPE             . ' content',
      'edit own '   . soccer_boss_STAFF_TYPE             . ' content',
      'delete own ' . soccer_boss_STAFF_TYPE             . ' content',
      'create '     . soccer_boss_TEAM_TYPE              . ' content',
      'edit own '   . soccer_boss_TEAM_TYPE              . ' content',
      'delete own ' . soccer_boss_TEAM_TYPE              . ' content',
      'create '     . soccer_boss_PGS_TYPE               . ' content',
      'edit any '   . soccer_boss_PGS_TYPE               . ' content',
      'delete any ' . soccer_boss_PGS_TYPE               . ' content',
      'create '     . soccer_boss_PPS_TYPE               . ' content',
      'edit any '   . soccer_boss_PPS_TYPE               . ' content',
      'delete any ' . soccer_boss_PPS_TYPE               . ' content',
      'create '     . soccer_boss_TS_TYPE               . ' content',
      'edit any '   . soccer_boss_TS_TYPE               . ' content',
      'delete any ' . soccer_boss_TS_TYPE               . ' content',
    ),
    soccer_boss_CLUB_STAFF_ROLE => array (
      'create '     . soccer_boss_CLUB_TYPE              . ' content',
      'edit any '   . soccer_boss_CLUB_TYPE              . ' content',
      'delete any ' . soccer_boss_CLUB_TYPE              . ' content',
      'create '     . soccer_boss_GAME_TYPE              . ' content',
      'edit any '   . soccer_boss_GAME_TYPE              . ' content',
      'delete any ' . soccer_boss_GAME_TYPE              . ' content',
      'create '     . soccer_boss_PLAYER_TYPE            . ' content', 
      'edit any '   . soccer_boss_PLAYER_TYPE            . ' content', 
      'delete any ' . soccer_boss_PLAYER_TYPE            . ' content', 
      'create '     . soccer_boss_STAFF_TYPE             . ' content',
      'edit own '   . soccer_boss_STAFF_TYPE             . ' content',
      'delete own ' . soccer_boss_STAFF_TYPE             . ' content',
      'create '     . soccer_boss_TEAM_TYPE              . ' content',
      'edit own '   . soccer_boss_TEAM_TYPE              . ' content',
      'delete own ' . soccer_boss_TEAM_TYPE              . ' content',
      'create '     . soccer_boss_PGS_TYPE               . ' content',
      'edit any '   . soccer_boss_PGS_TYPE               . ' content',
      'delete any ' . soccer_boss_PGS_TYPE               . ' content',
      'create '     . soccer_boss_PPS_TYPE               . ' content',
      'edit any '   . soccer_boss_PPS_TYPE               . ' content',
      'delete any ' . soccer_boss_PPS_TYPE               . ' content',
      'create '     . soccer_boss_TS_TYPE               . ' content',
      'edit any '   . soccer_boss_TS_TYPE               . ' content',
      'delete any ' . soccer_boss_TS_TYPE               . ' content',
    ),
  );
}


/**
  @brief Creates the core user roles and assigns
    them their default permissions.
*/
function soccer_boss_create_roles () {
  foreach (soccer_boss_roles () as $name => $permissions) {
    // I. create the user role.
    soccer_boss_create_role ($name);

    // II. assign the default permissions.
    soccer_boss_grant_permissions ($name, $permissions);
  }
}

/// Deletes the core user roles.
function soccer_boss_delete_roles () {
  foreach (array_keys (soccer_boss_roles ()) as $name) {
    // I. delete the user role.
    user_role_delete ($name);
  }
}

// ----- VI. Block visibility functions -----

/**
  @brief Restricts the given block to the given content types.
  @param $delta (string) the block delta.
  @param $type (string) the content type.
  @param $module (string) the module that defined the block.
*/
function soccer_boss_set_block_visibility ($delta, $type, $module) {
  db_insert ('block_node_type')
    ->fields (array ('type', 'module', 'delta'))
    ->values (array (
        'type'   => $type,
        'module' => $module,
        'delta'  => $delta
      ))
    ->execute ();
}

/**
  @brief Returns an array listing those blocks
    whose visibility settings are overriden by this
    module.
  @return (array) the settings array.
*/
function soccer_boss_block_settings () {
  return array (
    'club_teams-block' => array (
      'type'   => soccer_boss_CLUB_TYPE,
      'region' => 'content',
      'module' => 'views'
    ),
    'league_clubs-block' => array (
      'type'   => soccer_boss_LEAGUE_TYPE,
      'region' => 'content',
      'module' => 'views'
    ),
    'player_performance_stats-block'  => array (
      'type'   => soccer_boss_PLAYER_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 2
    ),
    'player_vital_stats-block' => array (
      'type'   => soccer_boss_PLAYER_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 1
    ),
    'team_games-block' => array (
      'type'   => soccer_boss_TEAM_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 2
    ),
    'team_roster-block' => array (
      'type'   => soccer_boss_TEAM_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 4
    ),
    'team_staff-block' => array (
      'type'   => soccer_boss_TEAM_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 3
    ),
    'team_vitals-block' => array (
      'type'   => soccer_boss_TEAM_TYPE,
      'region' => 'content',
      'module' => 'views',
      'weight' => 1
  ));
}

/**
  @brief Sets the default visibilities for the core blocks.
  @see soccer_boss_block_info_alter ().
*/
function soccer_boss_set_block_visibilities () {
  foreach (soccer_boss_block_settings () as $delta => $settings) {
    soccer_boss_set_block_visibility (
      $delta,
      $settings ['type'],
      $settings ['module']
    );
  }
}

/// Unsets the visibility settings for the core blocks.
function soccer_boss_clear_block_visibilities () {
  foreach (soccer_boss_block_settings () as $delta => $settings) {
    db_delete ('block_node_type')
      ->condition ('delta', $delta) 
      ->condition ('module', $settings ['module'])
      ->execute   ();
  }
}

// ----- VII. Miscellaneous -----

/**
  @brief Returns the ids of those entities that
    reference the given entity using the given
    entity reference field.
  @param $id (integer) the referenced entity id.
  @param $type (string) the referenced entity type.
  @param $field_name (string) the entity reference field name.
  @return (array) the referencing entity ids.
*/
function soccer_boss_get_references ($id, $type, $field_name) {
  $records = db_select     ('{field_data_' . $field_name . '}', 'tbl')
               ->fields    ('tbl', array ('entity_id'))
               ->condition ('entity_type', $type)
               ->condition ($field_name . '_target_id', $id)
               ->execute   ();

  $ids = array ();
  foreach ($records as $record) {
    $ids [] = $record->entity_id;
  }
  return $ids;
}
