<?php
/**
  @file
  @brief Defines the functions that create the
    fields associated with the Player content type.
*/

/// Creates the Photo field for Player content type.
function player_create_player_photo_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_photo',
    'type'         => 'image',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'        => 'player_player_photo',
    'entity_type'       => 'node',
    'bundle'            => player_PLAYER_TYPE,
    'label'             => t ('Photo'),
    'description'       => t ('A photo of the player.'),
    'instance_settings' => array (
      'file_extensions' => 'jpg jpeg',
      'alt_field'       => 1,
      'title_field'     => 1
  )));
}

/// Creates the First Name field for Player content type.
function player_create_player_first_name_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_first_name',
    'type'         => 'text',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'   => 'player_player_first_name',
    'entity_type'  => 'node',
    'bundle'       => player_PLAYER_TYPE,
    'label'        => t ('First Name'),
    'description'  => t ('The player\'s first name.'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Last Name field for Player content type.
function player_create_player_last_name_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_last_name',
    'type'         => 'text',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'   => 'player_player_last_name',
    'entity_type'  => 'node',
    'bundle'       => player_PLAYER_TYPE,
    'label'        => t ('Last Name'),
    'description'  => t ('The player\'s last name.'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Position field the Player content type.
function player_create_player_position_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_position',
    'type'         => 'taxonomy_term_reference',
    'entity_types' => array ('node'),
    'settings' => array (
      'allowed_values' => array (
        array ('vocabulary' => 'player_position', 'parent' => 0)
      ),
    )
  )); 

  field_create_instance (array (
    'field_name'  => 'player_player_position',
    'entity_type' => 'node',
    'bundle'      => player_PLAYER_TYPE,
    'label'       => t ('Position'),
    'description' => t ('The Player\'s position.'),
    'widget' => array (
      'type' => 'options_select',
    ),  
    'settings' => array (
      'text_processing' => true
    )
  ));
}

/// Creates the Height field for Player content type.
function player_create_player_height_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_height',
    'type'         => 'text',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'   => 'player_player_height',
    'entity_type'  => 'node',
    'bundle'       => player_PLAYER_TYPE,
    'label'        => t ('Height'),
    'description'  => t ('The player\'s height in feet and inches (<feet>\' <inches>").'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Weight field for Player content type.
function player_create_player_weight_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_weight',
    'type'         => 'text',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'   => 'player_player_weight',
    'entity_type'  => 'node',
    'bundle'       => player_PLAYER_TYPE,
    'label'        => t ('Weight'),
    'description'  => t ('The player\'s weight in lbs.'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Birth Date field for Player content type.
function player_create_player_birth_date_field () {
  module_load_include ('inc', 'player');

  field_create_field (array (
    'field_name'   => 'player_player_birth_date',
    'type'         => 'date',
    'entity_type'  => array ('node')
  ));

  field_create_instance (array (
    'field_name'   => 'player_player_birth_date',
    'entity_type'  => 'node',
    'bundle'       => player_PLAYER_TYPE,
    'label'        => t ('Birth Date'),
    'description'  => t ('The player\'s date of birth.'),
    'required'     => true,
    'widget'       => array ('type' => 'date_text')
  ));
}
