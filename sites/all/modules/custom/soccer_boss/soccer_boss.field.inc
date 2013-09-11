<?php
/**
  @file
  @brief Defines the functions that create the
    fields associated with the core content types.
*/

// ----- I. Defines generic field creation functions. -----

/**
  @brief Creates a photo field that has the given properties.
  @param $description (array) a field description.
*/
function soccer_boss_create_photo_field ($description) {
  module_load_include ('inc', 'soccer_boss');

  field_create_field (array (
    'field_name'  => $description ['name'],
    'type'        => 'image',
    'entity_type' => array ($description ['entity']),
    'cardinality' => $description ['cardinality']
  ));

  field_create_instance (array (
    'field_name'        => $description ['name'],
    'entity_type'       => $description ['entity'],
    'bundle'            => $description ['bundle'],
    'label'             => $description ['label'],
    'description'       => $description ['description'],
    'display'           => array (
      'default'         => array (
        'visible'       => $description ['visible'],
        'weight'        => $description ['weight']
      ),
      'teaser'          => array (
        'visible'       => $description ['visible'],
        'weight'        => $description ['weight']
    )),
    'instance_settings' => array (
      'file_extensions' => 'jpg jpeg png',
      'alt_field'       => 1,
      'title_field'     => 1
  )));
}

/**
  @brief Creates a text field that has the given properties.
  @param $description (array) a field description.
*/
function soccer_boss_create_text_field ($description) {
  module_load_include ('inc', 'soccer_boss');

  field_create_field (array (
    'field_name'   => $description ['name'],
    'type'         => 'text',
    'entity_types' => array ($description ['entity']),
    'cardinality'  => $description ['cardinality']
  ));

  field_create_instance (array (
    'field_name'    => $description ['name'],
    'entity_type'   => $description ['entity'],
    'bundle'        => $description ['bundle'],
    'label'         => $description ['label'],
    'description'   => $description ['description'],
    'required'      => true,
    'widget'        => array ('type' => 'text_textfield'),
    'display'       => array (
      'default'     => array (
        'visible'   => $description ['visible'],
        'weight'    => $description ['weight']
      ),
      'teaser'      => array (
        'visible'   => $description ['visible'],
        'weight'    => $description ['weight']
  ))));
} 

/**
  @brief Creates an entity reference field that has the given properties.
  @param $description (array) a field description.
*/
function soccer_boss_create_entity_reference_field ($description) {
  module_load_include ('inc', 'soccer_boss');

  field_create_field (array (
    'field_name'   => $description ['name'],
    'type'         => 'entityreference',
    'entity_types' => array ($description ['entity']),
    'cardinality'  => $description ['cardinality'],
    'settings'     => array (
      'handler_settings' => array (
        'target_bundles' => $description ['target_bundles'],
        'sort' => array ('type' => 'none')
  ))));

  field_create_instance (array (
    'field_name'   => $description ['name'],
    'entity_type'  => $description ['entity'],
    'bundle'       => $description ['bundle'],
    'label'        => $description ['label'],
    'description'  => $description ['description'],
    'widget'       => array ('type' => 'entityreference_autocomplete'),
    'display'      => array (
      'default'  => array (
        'label'   => $description ['label'],
        'type'    => 'entityreference_entity_view',
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
      ),
      'teaser'   => array (
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
    ))
  )); 
}

/**
  @brief Creates a taxonomy term reference field that has the given properties.
  @param $description (array) a field description.
*/
function soccer_boss_create_term_reference_field ($description) {
  module_load_include ('inc', 'soccer_boss');

  field_create_field (array (
    'field_name'   => $description ['name'],
    'type'         => 'taxonomy_term_reference',
    'entity_types' => array ($description ['entity']),
    'settings' => array (
      'allowed_values' => array (
        array ('vocabulary' => $description ['vocabulary'], 'parent' => 0)
      ),
    )
  )); 

  field_create_instance (array (
    'field_name'  => $description ['name'],
    'entity_type' => $description ['entity'],
    'bundle'      => $description ['bundle'],
    'label'       => $description ['label'],
    'description' => $description ['description'],
    'display'     => array (
      'default'   => array (
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
      ),
      'teaser'    => array (
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
    )),
    'widget' => array (
      'type' => 'options_select',
    ),  
    'settings' => array (
      'text_processing' => true
  )));
}

/**
  @brief Creates a date field that has the given properties.
  @param $description (array) a field description.
*/
function soccer_boss_create_date_field ($description) {
  module_load_include ('inc', 'soccer_boss');

  field_create_field (array (
    'field_name'   => $description ['name'],
    'type'         => 'date',
    'entity_type'  => array ($description ['entity'])
  ));

  field_create_instance (array (
    'field_name'   => $description ['name'],
    'entity_type'  => $description ['entity'],
    'bundle'       => $description ['bundle'],
    'label'        => $description ['label'],
    'description'  => $description ['description'],
    'required'     => true,
    'widget'       => array ('type' => 'date_text'), 
    'display'     => array (
      'default'   => array (
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
      ),
      'teaser'    => array (
        'visible' => $description ['visible'],
        'weight'  => $description ['weight']
  ))));
}


// ----- II. Defines the Club fields. -----

/// Creates the League field for the Club content type.
function soccer_boss_create_club_league_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_club_league',
      'entity'         => 'node',
      'bundle'         => soccer_boss_CLUB_TYPE,
      'label'          => t ('League'),
      'description'    => t ('The league that the club belongs to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_LEAGUE_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

// ----- III. Defines the Game fields. -----

/// Creates the Teams field for the Game content type.
function soccer_boss_create_game_teams_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_game_teams',
      'entity'         => 'node',
      'bundle'         => soccer_boss_GAME_TYPE,
      'label'          => t ('Teams'),
      'description'    => t ('The Teams involved in the match.'),
      'cardinality'    => 2,
      'target_bundles' => array (soccer_boss_TEAM_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

/// Creates the Date field for Game content type.
function soccer_boss_create_game_date_field () {
  soccer_boss_create_date_field (
    array (
      'name'        => 'soccer_boss_game_date',
      'entity'      => 'node',
      'bundle'      => soccer_boss_GAME_TYPE,
      'label'       => t ('Date'),
      'description' => t ('The date on which the match was held.'),
      'cardinality' => 1,
      'weight'      => 1,
      'visible'     => true
  ));
}

/// Creates the Score field for the Game content type.
function soccer_boss_create_game_score_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_score',
      'entity'      => 'node',
      'bundle'      => soccer_boss_GAME_TYPE,
      'label'       => t ('Score'),
      'description' => t ('The game\'s score.'),
      'cardinality' => 1,
      'weight'      => 2,
      'visible'     => true
  ));
}

// ----- IV. Defines the Player fields. -----

/// Creates the Photo field for Player content type.
function soccer_boss_create_player_photo_field () {
  soccer_boss_create_photo_field (
    array (
      'name'        => 'soccer_boss_player_photo',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Photo'),
      'description' => t ('A photo of the player.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => true
  ));
}

/// Creates the First Name field for Player content type.
function soccer_boss_create_player_first_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_player_first_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('First Name'),
      'description' => t ('The player\'s first name.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Last Name field for Player content type.
function soccer_boss_create_player_last_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_player_last_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Last Name'),
      'description' => t ('The player\'s last name.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Team field for the Player content type.
function soccer_boss_create_player_team_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_player_team',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PLAYER_TYPE,
      'label'          => t ('Team'),
      'description'    => t ('The player\'s team.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_TEAM_TYPE),
      'weight'         => 0,
      'visible'        => false
  ));
}

/// Creates the Position field the Player content type.
function soccer_boss_create_player_position_field () {
  soccer_boss_create_term_reference_field (
    array (
      'name'        => 'soccer_boss_player_position',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Position'),
      'description' => t ('The Player\'s position.'),
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'vocabulary'  => 'soccer_boss_player_position',
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Height field for Player content type.
function soccer_boss_create_player_height_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_player_height',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Height'),
      'description' => t ('The player\'s height in feet and inches (<feet>\' <inches>").'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Weight field for Player content type.
function soccer_boss_create_player_weight_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_player_weight',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Weight'),
      'description' => t ('The player\'s weight in lbs.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Birth Date field for Player content type.
function soccer_boss_create_player_birth_date_field () {
  soccer_boss_create_date_field (
    array (
      'name'        => 'soccer_boss_player_birth_date',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_TYPE,
      'label'       => t ('Birth Date'),
      'description' => t ('The player\'s date of birth.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

// ----- V. Defines the Staff fields. -----

/// Creates the Photo field for Staff Member content type.
function soccer_boss_create_staff_photo_field () {
  soccer_boss_create_photo_field (
    array (
      'name'        => 'soccer_boss_staff_photo',
      'entity'      => 'node',
      'bundle'      => soccer_boss_STAFF_TYPE,
      'label'       => t ('Photo'),
      'description' => t ('A photo of the staff member.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => true
  ));
}

/// Creates the First Name field for Staff Member content type.
function soccer_boss_create_staff_first_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_staff_first_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_STAFF_TYPE,
      'label'       => t ('First Name'),
      'description' => t ('The staff member\'s first name.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Last Name field for Staff Member content type.
function soccer_boss_create_staff_last_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_staff_last_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_STAFF_TYPE,
      'label'       => t ('Last Name'),
      'description' => t ('The staff member\'s last name.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Team field for the Staff Member content type.
function soccer_boss_create_staff_team_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_staff_team',
      'entity'         => 'node',
      'bundle'         => soccer_boss_STAFF_TYPE,
      'label'          => t ('Team'),
      'description'    => t ('The staff member\'s team.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_TEAM_TYPE),
      'weight'         => 0,
      'visible'        => false
  ));
}
/// Creates the Role field the Team Staff content type.
function soccer_boss_create_staff_role_field () {
  soccer_boss_create_term_reference_field (
    array (
      'name'        => 'soccer_boss_staff_role',
      'entity'      => 'node',
      'bundle'      => soccer_boss_STAFF_TYPE,
      'label'       => t ('Role'),
      'description' => t ('The staff member\'s role.'),
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'vocabulary'  => 'soccer_boss_staff_role',
      'weight'      => 0,
      'visible'     => false
  ));
}

// ----- VI. Defines the Team fields. -----

/// Creates the Age field for the Team content type.
function soccer_boss_create_team_age_field () {
  soccer_boss_create_term_reference_field (
    array (
      'name'        => 'soccer_boss_team_age',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Age'),
      'description' => t ('The age bracket that this team belongs to.'),
      'cardinality' => 1,
      'vocabulary'  => 'soccer_boss_age',
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Club field for the Team content type.
function soccer_boss_create_team_club_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_team_club',
      'entity'         => 'node',
      'bundle'         => soccer_boss_TEAM_TYPE,
      'label'          => t ('Club'),
      'description'    => t ('The club that the team belongs to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_CLUB_TYPE),
      'weight'         => 1,
      'visible'        => true
  ));
}

/// Creates the Division field for the Team content type.
function soccer_boss_create_team_division_field () {
  soccer_boss_create_term_reference_field (
    array (
      'name'        => 'soccer_boss_team_division',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Division'),
      'description' => t ('The division that this team belongs to.'),
      'cardinality' => 1,
      'vocabulary'  => 'soccer_boss_division',
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Gender field for the Team content type.
function soccer_boss_create_team_gender_field () {
  soccer_boss_create_term_reference_field (
    array (
      'name'        => 'soccer_boss_team_gender',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Gender'),
      'description' => t ('The team gender.'),
      'cardinality' => 1,
      'vocabulary'  => 'soccer_boss_gender',
      'weight'      => 0,
      'visible'     => false
  ));
}

/// Creates the Logo field for the Team content type.
function soccer_boss_create_team_logo_field () {
  soccer_boss_create_photo_field (
    array (
      'name'        => 'soccer_boss_team_logo',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Logo'),
      'description' => t ('The Team\'s logo.'),
      'cardinality' => 1,
      'weight'      => 0,
      'visible'     => true
  ));
}

// ----- VII. Defines the Player Fitness Stat fields. -----

/// Creates the Player field for the Player Fitness Stat content type.
function soccer_boss_create_pfs_player_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_pfs_player',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PFS_TYPE,
      'label'          => t ('Player'),
      'description'    => t ('The player that the stat applies to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_PLAYER_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

/// Creates the Value field for the Player Fitness Stat content type.
function soccer_boss_create_pfs_value_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_pfs_value',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PFS_TYPE,
      'label'       => t ('Value'),
      'description' => t ('The stat value.'),
      'cardinality' => 1,
      'weight'      => 1,
      'visible'     => true
  ));
}

/// Creates the Date field for Player Fitness Stat content type.
function soccer_boss_create_pfs_date_field () {
  soccer_boss_create_date_field (
    array (
      'name'        => 'soccer_boss_pfs_date',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PFS_TYPE,
      'label'       => t ('Date'),
      'description' => t ('The date on which the stat was measured or applied.'),
      'cardinality' => 1,
      'weight'      => 2,
      'visible'     => true
  ));
}

// ----- VIII. Defines the Player Game Stat fields. -----

/// Creates the Player field for the Player Game Stat content type.
function soccer_boss_create_pgs_player_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_pgs_player',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PGS_TYPE,
      'label'          => t ('Player'),
      'description'    => t ('The player that the stat applies to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_PLAYER_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

/// Creates the Game field for the Player Game Stat content type.
function soccer_boss_create_pgs_game_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_pgs_game',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PGS_TYPE,
      'label'          => t ('Game'),
      'description'    => t ('The game that the stat applies to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_GAME_TYPE),
      'weight'         => 1,
      'visible'        => true
  ));
}

/// Creates the Value field for the Player Game Stat content type.
function soccer_boss_create_pgs_value_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_pgs_value',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PGS_TYPE,
      'label'       => t ('Value'),
      'description' => t ('The stat value.'),
      'cardinality' => 1,
      'weight'      => 2,
      'visible'     => true
  ));
}

// ----- IX. Defines the Player Performance Stat fields. -----

/// Creates the Player field for the Player Performance Stat (PPS) content type.
function soccer_boss_create_pps_player_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_pps_player',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PPS_TYPE,
      'label'          => t ('Player'),
      'description'    => t ('The player that the stat applies to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_PLAYER_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

/// Creates the Value field for the Player Performance Stat (PPS) content type.
function soccer_boss_create_pps_value_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_pps_value',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PPS_TYPE,
      'label'       => t ('Value'),
      'description' => t ('The stat value.'),
      'cardinality' => 1,
      'weight'      => 1,
      'visible'     => true
  ));
}

/// Creates the Year field for the Player Performance Stat (PPS) content type.
function soccer_boss_create_pps_year_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_pps_year',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PPS_TYPE,
      'label'       => t ('Year'),
      'description' => t ('The year that this stat applies to.'),
      'cardinality' => 1, 
      'weight'      => 2,
      'visible'     => true
  ));
}

// ----- X. Defines the Team Stat (TS) fields. -----

/// Creates the Team field for the Team Stat (TS) content type.
function soccer_boss_create_ts_team_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_ts_team',
      'entity'         => 'node',
      'bundle'         => soccer_boss_TS_TYPE,
      'label'          => t ('Team'),
      'description'    => t ('The team that the stat applies to.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_TEAM_TYPE),
      'weight'         => 0,
      'visible'        => true
  ));
}

/// Creates the Value field for the Team Stat (TS) content type.
function soccer_boss_create_ts_value_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_ts_value',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TS_TYPE,
      'label'       => t ('Value'),
      'description' => t ('The stat value.'),
      'cardinality' => 1,
      'weight'      => 1,
      'visible'     => true
  ));
}

/// Creates the Year field for the Team Stat (TS) content type.
function soccer_boss_create_ts_year_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_ts_year',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TS_TYPE,
      'label'       => t ('Year'),
      'description' => t ('The year that this stat applies to.'),
      'cardinality' => 1,
      'weight'      => 2,
      'visible'     => true
  ));
}

// ----- XI. Field value functions -----

/**
  @brief Returns a date field value.
  @param $year (int) the year.
  @param $month (int) the month.
  @param $day (int) the day.
  @return (array) the field value.
*/
function soccer_boss_create_date_field_value ($year, $month, $day) {
  return array (
    'value' => "$year-$month-$day" . 'T05:00:00',
    'date_type' => 'date'
  );  
}
