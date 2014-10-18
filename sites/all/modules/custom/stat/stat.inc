<?php
/**
  @file
  @brief Defines the functions that create the
    Stat content type and the Unit vocabulary.
*/

// ----- I. Stat Types -----

/**
  @brief Creates a stat type.
  @param $stat_type (array) a stat type.
  @note Stat type arrays must have the following structure:
    array (
      'name'              => <the name of the stat type>
      'description'       => <a stat type description>
      'node_type'         => <the machine name of the node type used to represent stats>
      'subject_node_type' => <the machine name of the node type referenced by the subject field>
    )
*/
function stat_type_create ($stat_type) {
  drupal_write_record ('stat_stat_type', $stat_type);
  stat_type_create_node_type ($stat_type);
};

/**
  @brief Creates the given stat types.
  @param $stat_types (array) the stat types.
*/
function stat_type_create_multiple ($stat_types) {
  foreach ((array) $stat_types as $stat_type) {
    stat_type_create ($stat_type);
  }
}

/**
  @brief Returns a database query object that will retrieve stat type records.
  @return (SelectQuery) the query object.
*/
function stat_type_query_create () {
  return db_select ('{stat_stat_type}', 'tbl')
         ->fields  ('tbl', array ('name', 'description', 'node_type', 'subject_node_type'));
}

/**
  @brief Accepts a stat type select query and adds a node type filter.
  @param $query (SelectQuery) the query.
  @param $node_type (string) the node type.
*/
function stat_type_query_add_node_type_filter ($query, $node_type) {
  $query->condition ('node_type', $node_type);
  return $query;
}

/**
  @brief Accepts a stat type select query and adds a subject node type filter.
  @param $query (SelectQuery) the query.
  @param $subject_node_type (string) the subject node type.
*/
function stat_type_query_add_subject_node_type_filter ($query, $subject_node_type) {
  $query->condition ('subject_node_type', $subject_node_type);
  return $query;
}

/**
  @brief Accepts a stat type database record and returns a stat type array.
  @param $record (object) the record.
  @return (array) the stat type.
*/
function stat_type_from_record ($record) {
  return array (
    'name'              => $record->name,
    'description'       => $record->description,
    'node_type'         => $record->node_type,
    'subject_node_type' => $record->subject_node_type
  );
}

/**
  @brief Accepts stat type database records and returns the stat type arrays.
  @param $records (DatabaseConnection_mysql)
  @return (array) the stat types.
*/
function stat_type_from_records ($records) {
  $stat_types = array ();
  foreach ($records as $record) {
    $stat_types [] = stat_type_from_record ($record);
  }
  return $stat_types;
}

/**
  @brief Accepts a stat type query, executes the query, and returns the results.
  @param $query (SelectQuery) the query.
  @return (array) the stat types.
*/
function stat_type_query_execute ($query) {
  $results = $query->execute ();
  return stat_type_from_records ($results);
}

/**
  @brief Returns all of the stat types.
  @return (array) the stat types.
*/
function stat_type_get_all () {
  $query = stat_type_query_create ();
  return stat_type_query_execute ($query);
}

/**
  @brief Returns the stat types that use the given node type to represent stats.
  @param $node_type (string) the node type.
  @return (array) the stat types.
*/
function stat_type_get_by_node_type ($node_type) {
  $query = stat_type_query_create ();
  $query = stat_type_query_add_node_type_filter ($query, $node_type);
  return stat_type_query_execute ($query);
}

/**
  @brief Accepts a node type and returns those stat types that reference the given node type.
  @param $subject_node_type (string) the subject node type.
  @return (array) the stat types.
*/
function stat_type_get_by_subject_node_type ($subject_node_type) {
  $query = stat_type_query_create ();
  $query = stat_type_query_add_subject_node_type_filter ($query, $subject_node_type);
  return stat_type_query_execute ($query);
}

/**
  @brief Deletes the given stat type.
  @param $stat_type (array) the stat type.
*/
function stat_type_delete ($stat_type) {
  // I. Delete the stat type's node type and stat nodes.
  stat_type_delete_node_type ($stat_type);

  // II. Delete the stat type's database record.
  db_delete ('{stat_stat_type}')
  ->condition ('node_type', $stat_type ['node_type'])
  ->execute   ();
}

/**
  @brief Deletes the given stat types.
  @param $stat_types (array) the stat types.
*/
function stat_type_delete_multiple ($stat_types) {
  foreach ((array) $stat_types as $stat_type) {
    stat_type_delete ($stat_type);
  }
}

/// Deletes all of the stat types.
function stat_type_delete_all () {
  stat_type_delete_multiple (
    stat_type_get_all ());
}

// ----- II. Stat Type Node Types -----

/**
  @brief Defines a stat type's node type.
  @param $stat_type (array) a stat type.
  @return (object) a content type.
*/
function stat_type_get_node_type ($stat_type) {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => $stat_type ['node_type'],
      'name'        => t ($stat_type ['name']),
      'description' => t ($stat_type ['description']),
      'help'        => t ($stat_type ['description']),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'stat'
  )); 
}

/**
  @brief Accepts a stat type and deletes its node type.
  @param $stat_type (array) the stat type.
*/
function stat_type_delete_node_type ($stat_type) {
  stat_delete_node_type ($stat_type ['node_type']);
}

/**
  @brief Creates a stat type.
  @details This function creates a stat type node type and defines the core stat fields.
  @param $stat_type (array) the stat type.
*/
function stat_type_create_node_type ($stat_type) {
  // I. Create the content type.
  $stat_type_node_type = stat_type_get_node_type ($stat_type);
  node_type_save ($stat_type_node_type);

  // II. Create core fields.
  simple_field_create_textfield        ('node', $stat_type ['node_type'], $stat_type ['node_type'] . '_value',   t ('Value'));
  simple_field_create_textfield        ('node', $stat_type ['node_type'], $stat_type ['node_type'] . '_unit',    t ('Units'));
  simple_field_create_entity_reference ('node', $stat_type ['node_type'], $stat_type ['node_type'] . '_subject', t ('Subject'), is_null ($stat_type ['subject_node_type']) ? array () : array ($stat_type ['subject_node_type']), 'node', 1);
  simple_field_create_date_field       ('node', $stat_type ['node_type'], $stat_type ['node_type'] . '_date',    t ('Date'));

  // III. Call hook_stat_create_<stat_type_node_type>_stat_type_node_type () to add custom fields.
  $hook = 'stat_create_' . $stat_type ['node_type'] . '_stat_type_node_type';
  module_invoke_all ($hook, $stat_type_node_type);

  // IV. Return the type definition.
  return $stat_type_node_type;
}

/**
  @brief Accepts a set of stat types and
    creates content types that represent each.
  @param $stat_types (array) the stat types.
*/
function stat_type_create_node_types ($stat_types) {
  foreach ((array) $stat_types as $stat_type) {
    stat_type_create_node_type ($stat_type);
  }
}

/**
  @brief Accepts a set of stat types and deletes them.
  @param $stat_types (array) the stat types.
*/
function stat_type_delete_node_types ($stat_types) {
  foreach ((array) $stat_types as $stat_type) {
    stat_type_delete_node_type ($stat_type);
  }
}

/**
  @brief Deletes every node that belongs to a given type and the type itself.
  @param $type (string) the node type.
*/
function stat_delete_node_type ($node_type) {
  // I. Delete the node type nodes.
  stat_node_delete_all ($node_type);

  // II. Delete the node type.
  node_type_delete ($node_type);
}

// ----- III. Stats -----

/**
  @brief Creates a stat object.
  @param $name (string) the human readable stat name.
  @param $node_type (string) the stat node type.
  @param $value (string) the stat value.
  @param $unit  (string) the units of measure.
  @param $date  (string) the stat date.
  @param $subject_nid (int) the stat subject.
  @return (node) the stat node with core fields set.
*/
function stat_create ($name, $node_type, $value, $unit, $date, $subject_nid) {
  return array (
    'name'        => $name,
    'node_type'   => $node_type,
    'value'       => $value,
    'unit'        => $unit,
    'date'        => $date,
    'subject_nid' => $subject_nid
  );
}

/**
  Accepts a stat node and returns a stat object.
  @param $stat_node (node) a stat node.
  @return (array) the stat.
*/
function stat_from_stat_node ($stat_node) {
  return array (
    'nid'         => $stat_node->nid,
    'name'        => $stat_node->title,
    'node_type'   => $stat_node->type,
    'value'       => stat_node_get_value ($stat_node),
    'unit'        => stat_node_get_unit ($stat_node),
    'date'        => stat_node_get_date ($stat_node),
    'subject_nid' => stat_node_get_subject_nid ($stat_node)
  );
}

// ----- IV. Stat Nodes -----

/**
  @brief Accepts a information about a stat and returns a node object with the core fields set.
  @param $stat_type (array) the stat type.
  @param $name (string) the human readable stat name.
  @param $value (string) the stat value.
  @param $unit  (string) the units of measure.
  @param $date  (string) the stat date.
  @param $subject_nid (int) the stat subject.
  @return (node) the stat node with core fields set.
*/
function stat_node_create ($stat_type, $name, $value, $unit, $date, $subject_nid) {
  // I. Create the stat node and set the core fields.
  $stat_node = new stdClass ();
  $stat_node->type = $stat_type ['node_type'];
  node_object_prepare ($stat_node);
  $stat_node->title = $name;
  stat_node_set_value    ($stat_node, $value);
  stat_node_set_unit     ($stat_node, $unit);
  stat_node_set_date     ($stat_node, $date);
  stat_node_set_subject  ($stat_node, $subject_nid);

  // II. Call hook_stat_create_<stat_type_node_type>_stat_node () to set custom field values.
  module_invoke_all ('stat_create_' . $stat_type ['node_type'] . '_stat_node', $stat_node);

  // III. Saves the newly created stat node.
  node_save ($stat_node);
  return $stat_node;
}

/**
  @brief Returns an EntityFieldQuery that selects
    stat nodes of the given type.
  @param $stat_node_type (string)
  @return (EntityFieldQuery) the query.
*/
function stat_node_query_create ($stat_node_type) {
  $query = new EntityFieldQuery (); 
  return $query->entityCondition ('entity_type', 'node')
               ->entityCondition ('bundle', $stat_node_type);
}

/**
  @brief Executes the given stat node select query.
  @param $query (EntityFieldQuery) the query.
  @return (array) the stat nodes. 
*/
function stat_node_query_execute ($query) {
  $stat_nodes = array ();
  $result = $query->execute ();
  if (isset ($result ['node'])) {
    foreach ((array) $result ['node'] as $stat_node) {
      $stat_nodes [] = node_load ($stat_node->nid);
    }
  }
  return $stat_nodes;
}

/**
  @brief Accepts a stat node select query and adds a title filter.
  @param $query (EntityFieldQuery) the query.
  @param $title (string) the title.
  @return (EntityFieldQuery).
*/
function stat_node_query_add_title_filter ($query, $title) {
  $query->propertyCondition ('title', $title);
  return $query;
}

/**
  @brief Accepts a stat node select query and adds a date filter.
  @param $query (EntityFieldQuery) the query.
  @param $date (string) the date.
  @return (EntityFieldQuery).
  @example '2013-04-13 00:00:00'.
*/
function stat_node_query_add_date_filter ($query, $date) {
  $stat_node_type = $query->entityConditions ['bundle']['value'];
  $query->fieldCondition ($stat_node_type . '_date', 'value', $date, '=');
  return $query;
}

/**
  @brief Accepts a stat node select query and adds a date year filter.
  @param $query (EntityFieldQuery) the query.
  @param $year (int) the year.
  @return (EntityFieldQuery).
*/
function stat_node_query_add_year_filter ($query, $year) {
  $stat_node_type = $query->entityConditions ['bundle']['value'];
  $query->fieldCondition ($stat_node_type . '_date', 'value', "%$year%", 'like');
  return $query;
}

/**
  @brief Accepts a stat node select query and adds a date filter.
  @param $query (EntityFieldQuery) the query.
  @param $subject_nid (int) the subject node id.
  @return (EntityFieldQuery).
*/
function stat_node_query_add_subject_filter ($query, $subject_nid) {
  $stat_node_type = $query->entityConditions ['bundle']['value'];
  $query->fieldCondition ($stat_node_type . '_subject', 'target_id', $subject_nid, '=');
  return $query;
}

/**
  @brief Accepts a node id and returns those stat
    nodes that reference the given node in their
    subject fields.
  @param $stat_node_type (string) the stat node type.
  @param $subject_nid (int) the subject node id.
  @return (array) the stat nodes.
*/
function stat_node_get_by_subject ($stat_node_type, $subject_nid) {
  $query = stat_node_query_create ($stat_node_type);
  $query = stat_node_query_add_subject_filter ($query, $subject_nid);
  return stat_node_query_execute ($query);
}

/**
  @brief Accepts a stat node type and returns every stat node that belongs to the given type.
  @param $stat_node_type (string) the stat node type.
  @return (array) the stat nodes.
*/
function stat_node_get_all ($stat_node_type) {
  $query = stat_node_query_create ($stat_node_type);
  return stat_node_query_execute ($query);
}

/**
  @brief Deletes every node that belongs to the given type.
  @param $type (string) the node type.
*/
function stat_node_delete_all ($stat_node_type) {
  foreach (stat_node_get_all ($stat_node_type) as $stat_node) {
    node_delete ($stat_node->nid);
  }
}

/**
  @brief Accepts a stat node and returns its subject.
  @param $stat_node (object) the stat node.
  @return (int) the subject entity id.
*/
function stat_node_get_subject_nid ($stat_node) {
  return $stat_node->{$stat_node->type . '_subject'}['und'][0]['target_id'];
}

/**
  @brief Accepts a stat node and a subject id and updates the stat value.
  @param $stat_node (object) the stat node.
  @param $subject_id (string) the subject entity id.
*/
function stat_node_set_subject ($stat_node, $subject_id) {
  $stat_node->{$stat_node->type . '_subject'}['und'][0]['target_id'] = $subject_id;
} 

/**
  @brief Accepts a stat node and returns its date.
  @param $stat_node (object) the stat node.
  @return (string) the date.
*/
function stat_node_get_date ($stat_node) {
  return $stat_node->{$stat_node->type . '_date'}['und'][0]['value'];
}

/**
  @brief Accepts a stat node and a date and updates the date value.
  @param $stat_node (object) the stat node.
  @param $date (string) the date value.
*/
function stat_node_set_date ($stat_node, $date) {
  $stat_node->{$stat_node->type . '_date'}['und'][0] = array (
    'value'     => $date,
    'date_type' => 'date'
  );
}

/**
  @brief Accepts a stat node and returns its year.
  @param $stat_node (object) the stat node.
  @return (int) the year.
*/
function stat_node_get_year ($stat_node) {
  $date = stat_node_get_date ($stat_node);
  $year = date ('Y', strtotime ($date));
  return $year + 1;
}

/**
  @brief Accepts a stat node and returns its value. 
  @param $stat_node (object) the stat node.
  @return (string) the stat value.
*/
function stat_node_get_value ($stat_node) {
  return $stat_node->{$stat_node->type . '_value'}['und'][0]['value'];
}

/**
  @brief Accepts a stat node and a value and updates the stats value.
  @param $stat_node (object) the stat node.
  @param $value (string) the stat value.
*/
function stat_node_set_value ($stat_node, $value) {
  $stat_node->{$stat_node->type . '_value'}['und'][0]['value'] = $value;
}

/**
  @brief Accepts a stat node and returns its units. 
  @param $stat_node (object) the stat node.
  @return (string) the stat units.
*/
function stat_node_get_unit ($stat_node) {
  return $stat_node->{$stat_node->type . '_unit'}['und'][0]['value'];
}

/**
  @brief Accepts a stat node and a unit and updates the stats unit.
  @param $node (object) the stat node.
  @param $unit (string) the stat unit.
*/
function stat_node_set_unit ($stat_node, $unit) {
  $stat_node->{$stat_node->type . '_unit'}['und'][0]['value'] = $unit;
}
