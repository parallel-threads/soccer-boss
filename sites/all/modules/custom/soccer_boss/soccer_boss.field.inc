<?php
/**
  @file
  @brief Defines the functions that create the
    fields associated with the core content types.
*/

// ----- I. Defines generic field creation functions. -----

/**
  @brief Creats a photo field that has the given properties.
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
    'widget'        => array ('type' => 'text_textfield')
  ));
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
      'default' => array (
        'label' => $description ['label'],
        'type'  => 'entityreference_entity_view'
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
    'widget'       => array ('type' => 'date_text')
  ));
}


// ----- II. Defines the Coach fields. -----

/// Creates the Photo field for the Coach content type.
function soccer_boss_create_coach_photo_field () {
  soccer_boss_create_photo_field (
    array (
      'name'        => 'soccer_boss_coach_photo',
      'entity'      => 'node',
      'bundle'      => soccer_boss_COACH_TYPE,
      'label'       => t ('Photo'),
      'description' => t ('A photo of the coach.'),
      'cardinality' => 1
  ));
}

/// Creates the First Name field for the Coach content type.
function soccer_boss_create_coach_first_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_coach_first_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_COACH_TYPE,
      'label'       => t ('First Name'),
      'description' => t ('The coach\'s first name.'),
      'cardinality' => 1
  ));
}

/// Creates the Last Name field for the Coach content type.
function soccer_boss_create_coach_last_name_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_coach_last_name',
      'entity'      => 'node',
      'bundle'      => soccer_boss_COACH_TYPE,
      'label'       => t ('Last Name'),
      'description' => t ('The coach\'s last name.'),
      'cardinality' => 1
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
      'target_bundles' => array (soccer_boss_TEAM_TYPE)
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
      'cardinality' => 1
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
      'cardinality' => 1
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
      'cardinality' => 1
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
      'cardinality' => 1
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
      'cardinality' => 1
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
      'target_bundles' => array (soccer_boss_TEAM_TYPE)
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
      'vocabulary'  => 'soccer_boss_position'
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
      'cardinality' => 1
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
      'cardinality' => 1
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
      'cardinality' => 1
  ));
}

// ----- V. Defines the Player Game Stats fields. -----

/// Creates the Player field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_player_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_game_stats_player',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'          => t ('Player'),
      'description'    => t ('The player.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_PLAYER_TYPE)
  ));
}

/// Creates the Game field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_game_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'           => 'soccer_boss_game_stats_game',
      'entity'         => 'node',
      'bundle'         => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'          => t ('Game'),
      'description'    => t ('The match.'),
      'cardinality'    => 1,
      'target_bundles' => array (soccer_boss_GAME_TYPE)
  ));
}

/// Creates the Minutes field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_minutes_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_stats_minutes',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'       => t ('Minutes'),
      'description' => t ('The number of minutes that the player participated in the match.'),
      'cardinality' => 1
  ));
}

/// Creates the Goals field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_goals_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_stats_goals',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'       => t ('Goals'),
      'description' => t ('The number of goals scored by the player during the match.'),
      'cardinality' => 1
  ));
}

/// Creates the Assists field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_assists_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_stats_assists',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'       => t ('Assists'),
      'description' => t ('The number of assists made by the player during the match.'),
      'cardinality' => 1
  ));
}

/// Creates the Shots field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_shots_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_stats_shots',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'       => t ('Shots'),
      'description' => t ('The number of shots made by the player during the match.'),
      'cardinality' => 1
  ));
}

/// Creates the Shots on Goal (SOG) field for the Player Game Stats content type.
function soccer_boss_create_player_game_stats_sog_field () {
  soccer_boss_create_text_field (
    array (
      'name'        => 'soccer_boss_game_stats_sog',
      'entity'      => 'node',
      'bundle'      => soccer_boss_PLAYER_GAME_STATS_TYPE,
      'label'       => t ('Shots On Goal'),
      'description' => t ('The number of shots on the goal made by the player during the match.'),
      'cardinality' => 1
  ));
}

// ----- VI. Defines the Team fields. -----

/// Creates the Logo field for the Team content type.
function soccer_boss_create_team_logo_field () {
  soccer_boss_create_photo_field (
    array (
      'name'        => 'soccer_boss_team_logo',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Logo'),
      'description' => t ('The Team\'s logo.'),
      'cardinality' => 1
  ));
}

/// Creates the Coach field for the Team content type.
function soccer_boss_create_team_coach_field () {
  soccer_boss_create_entity_reference_field (
    array (
      'name'        => 'soccer_boss_team_coach',
      'entity'      => 'node',
      'bundle'      => soccer_boss_TEAM_TYPE,
      'label'       => t ('Coach'),
      'description' => t ('The Team\'s coach.'),
      'cardinality' => FIELD_CARDINALITY_UNLIMITED
  ));
}
