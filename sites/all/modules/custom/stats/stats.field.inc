<?php
/**
  @file
  @brief Defines the fields attached to the Stat
    and Stat Value entities.
*/

/// Creates the Name field for Stat entities.
function stats_create_name_field () {
  field_create_field (array (
    'field_name'   => 'stats_name',
    'type'         => 'text',
    'entity_type'  => 'stat',
  ));

  field_create_instance (array (
    'field_name'   => 'stats_name',
    'entity_type'  => 'stat',
    'bundle'       => 'stat',
    'label'        => t ('Name'),
    'description'  => t ('The stat name.'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Subject field for Stat entities.
function stats_create_subject_field () {
  field_create_field (array (
    'field_name'   => 'stats_subject',
    'type'         => 'entityreference',
    'entity_type'  => 'stat'
  ));

  field_create_instance (array (
    'field_name'   => 'stats_subject',
    'entity_type'  => 'stat',
    'bundle'       => 'stat',
    'label'        => t ('Subject'),
    'description'  => t ('The subject that this stat applies to.'),
    'required'     => true,
    'widget'       => array ('type' => 'entityreference_autocomplete'),
    'display'      => array (
      'default' => array (
        'label' => 'Subject',
        'type'  => 'entityreference_entity_view'
    ))
  ));
}

/// Creates the Stat field for the Stat Value entities.
function stats_create_stat_field () {
  field_create_field (array (
    'field_name'   => 'stats_value_stat',
    'type'         => 'entityreference',
    'entity_type'  => 'stat_value',
    'settings'     => array (
      'target_type' => 'stat'
    )
  ));

  field_create_instance (array (
    'field_name'   => 'stats_value_stat',
    'entity_type'  => 'stat_value',
    'bundle'       => 'stat_value',
    'label'        => t ('Stat'),
    'description'  => t ('The stat that this value applies to.'),
    'required'     => true,
    'widget'       => array ('type' => 'entityreference_autocomplete'),
    'display'      => array (
      'default' => array (
        'label' => 'Stat',
        'type'  => 'entityreference_entity_view'
    ))
  ));
}

/// Creates the Value field for the Stat Value entities.
function stats_create_value_field () {
  field_create_field (array (
    'field_name'   => 'stats_value_content',
    'type'         => 'text',
    'entity_type'  => 'stat_value',
  ));

  field_create_instance (array (
    'field_name'   => 'stats_value_content',
    'entity_type'  => 'stat_value',
    'bundle'       => 'stat_value',
    'label'        => t ('Value'),
    'description'  => t ('The stat value.'),
    'required'     => true,
    'widget'       => array ('type' => 'text_textfield')
  ));
}

/// Creates the Date field for the Stat Value entities.
function stats_create_date_field () {
  field_create_field (array (
    'field_name'   => 'stats_value_date',
    'type'         => 'datestamp',
    'entity_type'  => 'stat_value',
  ));

  field_create_instance (array (
    'field_name'  => 'stats_value_date',
    'entity_type' => 'stat_value',
    'bundle'      => 'stat_value',
    'label'       => t ('Date'),
    'description' => t ('The date on which the value was measured or reported.'),
    'required'    => true,
    'widget'      => array ('type' => 'date_select')
  ));
}
