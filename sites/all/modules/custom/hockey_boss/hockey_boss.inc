<?php
/**
  @file
  @brief This file defines the core content types
    and user roles used on the Hockey Boss site and
    provides an API for creating/modifying them.
*/

// ----- I. Vocabularies -----

/// The Player Position vocabulary name.
define ('hockey_boss_PLAYER_POSITION_VOCAB', 'hockey_boss_player_position');

/// The Team Age Group vocabulary name.
define ('hockey_boss_TEAM_AGE_GROUP_VOCAB', 'hockey_boss_team_age_group');

/// The Team Division vocabulary name.
define ('hockey_boss_TEAM_DIVISION_VOCAB', 'hockey_boss_team_division');

/// The Team Gender vocabulary.
define ('hockey_boss_TEAM_GENDER_VOCAB', 'hockey_boss_team_gender');

/// The core vocabularies.
function hockey_boss_vocabularies () {
  return array (
    array (
      'name'         => t ('Player Position'),
      'machine_name' => hockey_boss_PLAYER_POSITION_VOCAB,
      'description'  => t ('The player positions.')
    ),
    array (
      'name'         => t ('Team Age Group'),
      'machine_name' => hockey_boss_TEAM_AGE_GROUP_VOCAB,
      'description'  => t ('The team age group.')
    ),
    array (
      'name'         => t ('Team Division'),
      'machine_name' => hockey_boss_TEAM_DIVISION_VOCAB,
      'description'  => t ('The team division.')
    ),
    array (
      'name'         => t ('Team Gender'),
      'machine_name' => hockey_boss_TEAM_GENDER_VOCAB,
      'description'  => t ('The team gender.')
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
function hockey_boss_import_terms ($vid, $url) {
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
function hockey_boss_create_vocabulary ($vocab_array) {
  if (!taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name'])) {
    // I. create the vocabulary.
    taxonomy_vocabulary_save ((object) $vocab_array);
    
    // II. import the terms if given.
    if (isset ($vocab_array ['url'])) {
      $vocab = taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name']);
      hockey_boss_import_terms ($vocab->vid, $vocab_array ['url']);
    }
  }
}

/// Creates the core vocabularies.
function hockey_boss_create_vocabularies () {
  foreach (hockey_boss_vocabularies () as $vocab) {
    hockey_boss_create_vocabulary ($vocab);
  }
}

/// Deletes the core vocabularies.
function hockey_boss_delete_vocabularies () {
  foreach (hockey_boss_vocabularies () as $vocab_array) {  
    $vocab = taxonomy_vocabulary_machine_name_load ($vocab_array ['machine_name']);
    taxonomy_vocabulary_delete ($vocab->vid);
  }
}

// ----- II. Content Types -----

/// The Club Profile content type name.
define ('hockey_boss_CLUB_PROFILE_TYPE', 'hockey_boss_club_type');

/// The Coach Profile content type name.
define ('hockey_boss_COACH_PROFILE_TYPE', 'hockey_boss_coach_type');

/// The Game content type name.
define ('hockey_boss_GAME_TYPE', 'hockey_boss_game_type');

/// The Player Profile content type name.
define ('hockey_boss_PLAYER_PROFILE_TYPE', 'hockey_boss_player_type');

/// The Team Profile content type name.
define ('hockey_boss_TEAM_PROFILE_TYPE', 'hockey_boss_team_type');

/// The League Profile content type.
define ('hockey_boss_LEAGUE_PROFILE_TYPE', 'hockey_boss_league_type');

/**
  @brief Defines a content type.
  @param $name (string) the internal type name.
  @param $label (string) the human-readable type name.
  @param $description (string) a description of the type.
  @return (object) a content type.
*/
function hockey_boss_get_type ($name, $label, $description) {
  $t = get_t (); 
  return node_type_set_defaults (
    array (
      'type'        => $name,
      'name'        => $t ($label),
      'description' => $t ($description),
      'help'        => $t ($description),
      'has_title'   => true,
      'base'        => 'node_content',
      'custom'      => false,
      'modified'    => true,
      'locked'      => true,
      'module'      => 'stat'
  )); 
}

/// Defines the Club Profile content type.
function hockey_boss_club_profile_type () {
  return hockey_boss_get_type (hockey_boss_CLUB_PROFILE_TYPE, 'Club Profile', 'Represents clubs.');
}

/// Defines the Coach Profile content type.
function hockey_boss_coach_profile_type () {
  return hockey_boss_get_type (hockey_boss_COACH_PROFILE_TYPE, 'Coach Profile', 'Represents coach profiles.');
}

/// Defines the Game type.
function hockey_boss_game_type () {
  return hockey_boss_get_type (hockey_boss_GAME_TYPE, 'Game', 'Represents matches.');
}

/// Defines the League Profile content type.
function hockey_boss_league_profile_type () {
  return hockey_boss_get_type (hockey_boss_LEAGUE_PROFILE_TYPE, 'League Profile', 'Represents leagues.');
}

/// Defines the Player Profile content type.
function hockey_boss_player_profile_type () {
  return hockey_boss_get_type (hockey_boss_PLAYER_PROFILE_TYPE, 'Player Profile', 'Represents players.');
}

/// Defines the Team Profile content type.
function hockey_boss_team_profile_type () {
  return hockey_boss_get_type (hockey_boss_TEAM_PROFILE_TYPE, 'Team Profile', 'Represents teams.');
}

/// Returns the core content types.
function hockey_boss_types () {
  return array (
    hockey_boss_club_profile_type (),
    hockey_boss_coach_profile_type (),
    hockey_boss_game_type (),
    hockey_boss_league_profile_type (),
    hockey_boss_player_profile_type (),
    hockey_boss_team_profile_type ()
  );
}

/// Creates the core content types.
function hockey_boss_create_types () {
  foreach (hockey_boss_types () as $type) {
    node_type_save ($type);
  }
}

/**
  @brief Accepts a node type and deletes every node
    that belongs to the given type.
  @param $type (string) the node type.
*/
function hockey_boss_delete_type ($type)  {
  // I. Delete the node type nodes.
  foreach (hockey_boss_get_nodes ($type) as $nid) {
    node_delete ($nid);
  }
  // II. Delete the node type.
  node_type_delete ($type);
}

/// Deletes the core content types.
function hockey_boss_delete_types () {
  foreach (hockey_boss_types () as $type) {
    hockey_boss_delete_type ($type->type);
  }
}

// ----- III. Relations -----

/// The Club/League relation name.
define ('hockey_boss_CLUB_LEAGUE_RELATION', 'hockey_boss_club_league_rel');

/// The Coach/Team relation name.
define ('hockey_boss_COACH_TEAM_RELATION', 'hockey_boss_coach_team_rel');

/// The Game/Team relation name.
define ('hockey_boss_GAME_TEAM_RELATION', 'hockey_boss_game_team_rel');

/// The Player/Team relation name.
define ('hockey_boss_PLAYER_TEAM_RELATION', 'hockey_boss_player_team_rel');

/// The Team/Club relation name.
define ('hockey_boss_TEAM_CLUB_RELATION', 'hockey_boss_team_club_rel');

/// The User/Coach relation name.
define ('hockey_boss_USER_COACH_RELATION', 'hockey_boss_user_coach_rel');

/// The User/Player relation name.
define ('hockey_boss_USER_PLAYER_RELATION', 'hockey_boss_user_player_rel');

/**
  @brief Defines a relation type.
  @param $name (string) the internal type name.
  @param $label (string) the human-readable type name.
  @param $source_bundles (array) the source bundles.
  @param $directional (boolean) indicates whether
    or not the relation is directional.
  @param $reverse_label (string) the human-readable
    name of the reversed relation. Default $label.
  @param $target_bundles (array) the target bundles.
  @return (relation_type).
*/
function hockey_boss_get_relation ($name, $label, $source_bundles, $directional = false, $reverse_label = null, $target_bundles = array ()) {
  if (is_null ($reverse_label)) { $reverse_label = $label; }
  return relation_type_create (array (
    'relation_type'  => $name,
    'label'          => $label,
    'reverse_label'  => $reverse_label,
    'directional'    => $directional,
    'source_bundles' => $source_bundles,
    'target_bundles' => $target_bundles
  ));
}

/// Defines the club/league relation.
function hockey_boss_club_league_relation () {
  return hockey_boss_get_relation (hockey_boss_CLUB_LEAGUE_RELATION, 'Club League', array ('node:' . hockey_boss_CLUB_PROFILE_TYPE), true, 'League Club', array ('node:' . hockey_boss_LEAGUE_PROFILE_TYPE));
}

/// Defines the coach/team relation.
function hockey_boss_coach_team_relation () {
  return hockey_boss_get_relation (hockey_boss_COACH_TEAM_RELATION, 'Coach Team', array ('node:' . hockey_boss_COACH_PROFILE_TYPE), true, 'Team Coach', array ('node:' . hockey_boss_TEAM_PROFILE_TYPE));
}

/// Defines the game/team relation.
function hockey_boss_game_team_relation () {
  return hockey_boss_get_relation (hockey_boss_GAME_TEAM_RELATION, 'Game Team', array ('node:' . hockey_boss_GAME_TYPE), true, 'Team Game', array ('node:' . hockey_boss_TEAM_PROFILE_TYPE));
}

/// Defines the player/team relation.
function hockey_boss_player_team_relation () {
  return hockey_boss_get_relation (hockey_boss_PLAYER_TEAM_RELATION, 'Player Team', array ('node:' . hockey_boss_PLAYER_PROFILE_TYPE), true, 'Team Player', array ('node:' . hockey_boss_TEAM_PROFILE_TYPE));
}

/// Defines the team/club relation.
function hockey_boss_team_club_relation () {
  return hockey_boss_get_relation (hockey_boss_TEAM_CLUB_RELATION, 'Team Club', array ('node:' . hockey_boss_TEAM_PROFILE_TYPE), true, 'Club Team', array ('node:' . hockey_boss_CLUB_PROFILE_TYPE));
}

/// Defines the user/coach relation.
function hockey_boss_user_coach_relation () {
  return hockey_boss_get_relation (hockey_boss_USER_COACH_RELATION, 'User Coach Profile', array ('user:user'), true, 'Coach Profile User', array ('node:' . hockey_boss_COACH_PROFILE_TYPE)); 
}

/// Defines the user/player relation.
function hockey_boss_user_player_relation () {
  return hockey_boss_get_relation (hockey_boss_USER_PLAYER_RELATION, 'User Player Profile', array ('user:user'), true, 'Player Profile User', array ('node:' . hockey_boss_PLAYER_PROFILE_TYPE));
}

/// Returns the core relations.
function hockey_boss_relations () {
  return array (
    hockey_boss_club_league_relation (),
    hockey_boss_coach_team_relation (),
    hockey_boss_game_team_relation (),
    hockey_boss_player_team_relation (),
    hockey_boss_team_club_relation (),
    hockey_boss_user_coach_relation (),
    hockey_boss_user_player_relation ()
  );
}

/// Creates the core relations.
function hockey_boss_create_relations () {
  foreach (hockey_boss_relations () as $relation) {
    relation_type_save ($relation);
  }
}

/// Deletes the core relations.
function hockey_boss_delete_relations () {
  foreach (hockey_boss_relations () as $relation) {
    relation_type_delete ($relation->relation_type);
  }
}

// ----- IV. Create Fields. -----

/// Creates the game/team relation fields.
function hockey_boss_create_game_team_fields () {
  $relation = hockey_boss_game_team_relation ();
  simple_field_create_textfield ('relation', $relation->relation_type, $relation->relation_type . '_score', t ('Score'));
}

/// Creates the Club Profile fields.
function hockey_boss_create_club_profile_fields () {
  $type = hockey_boss_club_profile_type ();
  node_add_body_field ($type, 'Description');
  simple_field_create_relation_field ('node', $type->type, $type->type . '_league', t ('League'), hockey_boss_CLUB_LEAGUE_RELATION);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_teams', t ('Teams'), hockey_boss_TEAM_CLUB_RELATION . ':reverse');
}

/// Creates the Coach Profile fields. 
function hockey_boss_create_coach_profile_fields () {
  $type = hockey_boss_coach_profile_type ();
  node_add_body_field ($type, 'Bio');
  simple_field_create_relation_field ('node', $type->type, $type->type . '_user', t ('User Account'), hockey_boss_USER_COACH_RELATION . ':reverse', 1);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_team', t ('Team'), hockey_boss_COACH_TEAM_RELATION);
}

/// Creates the Game fields.
function hockey_boss_create_game_fields () {
  $type = hockey_boss_game_type ();
  node_add_body_field ($type, 'Recap');
  simple_field_create_date_field ('node', $type->type, $type->type . '_date', t ('Date'));
  simple_field_create_relation_field ('node', $type->type, $type->type . '_teams', t ('Teams'), hockey_boss_GAME_TEAM_RELATION, 2);
}

/// Creates the League Profile fields.
function hockey_boss_create_league_profile_fields () {
  $type = hockey_boss_league_profile_type ();
  node_add_body_field ($type, 'Description');
  simple_field_create_relation_field ('node', $type->type, $type->type . '_clubs', t ('Clubs'), hockey_boss_CLUB_LEAGUE_RELATION . ':reverse');
}

/// Creates the Player Profile fields.
function hockey_boss_create_player_profile_fields () {
  $type = hockey_boss_player_profile_type ();
  node_add_body_field ($type, 'Bio');
  simple_field_create_date_field ('node', $type->type, $type->type . '_birth', t ('Birth Date'));
  simple_field_create_textfield  ('node', $type->type, $type->type . '_height', t ('Height'));
  simple_field_create_textfield  ('node', $type->type, $type->type . '_weight', t ('Weight'));
  simple_field_create_term_reference ('node', $type->type, $type->type . '_position', t ('Position'), hockey_boss_PLAYER_POSITION_VOCAB);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_user', t ('User Account'), hockey_boss_USER_PLAYER_RELATION . ':reverse', 1);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_team', t ('Team'), hockey_boss_PLAYER_TEAM_RELATION);
}

/// Creates the Team Profile fields.
function hockey_boss_create_team_profile_fields () {
  $type = hockey_boss_team_profile_type ();
  node_add_body_field ($type, 'Description');
  simple_field_create_term_reference ('node', $type->type, $type->type . '_age_group', t ('Age Group'), hockey_boss_TEAM_AGE_GROUP_VOCAB);
  simple_field_create_term_reference ('node', $type->type, $type->type . '_division', t ('Division'), hockey_boss_TEAM_DIVISION_VOCAB);
  simple_field_create_term_reference ('node', $type->type, $type->type . '_gender', t ('Gender'), hockey_boss_TEAM_GENDER_VOCAB);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_coach', t ('Coach'), hockey_boss_COACH_TEAM_RELATION . ':reverse', 1);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_club', t ('Club'), hockey_boss_TEAM_CLUB_RELATION, 1);
  simple_field_create_relation_field ('node', $type->type, $type->type . '_players', t ('Players'), hockey_boss_PLAYER_TEAM_RELATION . ':reverse');
}

/// Creates the core fields.
function hockey_boss_create_fields () {
  hockey_boss_create_club_profile_fields ();
  hockey_boss_create_coach_profile_fields ();
  hockey_boss_create_game_team_fields ();
  hockey_boss_create_game_fields ();
  hockey_boss_create_league_profile_fields ();
  hockey_boss_create_player_profile_fields ();
  hockey_boss_create_team_profile_fields ();
}

// ----- V. Node operations -----

/**
  @brief Accepts a node type and returns the node
    id of every node that has the given type.
  @param $type (string) the node type.
  @return (array) the node ids.
*/
function hockey_boss_get_nodes ($type) {
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
  @brief Returns the node ids of the games ordered by date.
  @return (array) the node ids.
*/
function hockey_boss_get_game_nodes () {
  $game_nodes = array ();
  $game_nids = hockey_boss_get_nodes (hockey_boss_GAME_TYPE);
  foreach ($game_nids as $game_nid) {
    $game_node = node_load ($game_nid);
    $game_date = hockey_boss_get_game_date ($game_node);
    $game_nodes [$game_date] = $game_node;
  }
  ksort ($game_nodes);
  return $game_nodes;
}

/**
  @brief Accepts a player node and returns the user id of the user associated with it.
  @return (int) the user id.
*/
function hockey_boss_get_player_user_uid ($player_node) {
  return simple_field_get_relation_source_entity_id ($player_node, hockey_boss_PLAYER_PROFILE_TYPE . '_user');
}

/**
  @brief Accepts a player node and returns its team node id.
  @return (int) the team node id.
*/
function hockey_boss_get_player_team_nid ($player_node) {
  return simple_field_get_relation_target_entity_id ($player_node, hockey_boss_PLAYER_PROFILE_TYPE . '_team');
}

/**
  @brief Accepts a player node and returns its team node.
  @return (object) the team node.
*/
function hockey_boss_get_player_team_node ($player_node) {
  $team_nid = simple_field_get_relation_target_entity_id ($player_node, hockey_boss_PLAYER_PROFILE_TYPE . '_team');
  return is_null ($team_nid) ? null : node_load ($team_nid);
}

/**
  @brief Accepts a player profile node and returns its position term id.
  @param $player_node (node) the player profile node.
  @return (int) position term id.
*/
function hockey_boss_get_player_position_tid ($player_node) {
  $field = $player_node->{hockey_boss_PLAYER_PROFILE_TYPE . '_position'};
  return empty ($field) ? null : $field ['und'][0]['tid'];
}

/**
  @brief Accepts a player profile node and returns its position term.
  @param $player_node (node) the player profile node.
  @return (object) the position term.
*/
function hockey_boss_get_player_position_term ($player_node) {
  $position_tid = hockey_boss_get_player_position_tid ($player_node);
  return is_null ($position_tid) ? null : taxonomy_term_load ($position_tid);
}

/**
  @brief Accepts a team node and returns its coach node id.
  @return (int) the coach node id.
*/
function hockey_boss_get_team_coach_nid ($team_node) {
  return simple_field_get_relation_source_entity_id ($team_node, hockey_boss_TEAM_PROFILE_TYPE . '_coach');
}

/**
  @brief Accepts a team node and returns its coach node.
  @return (object) the team node.
*/
function hockey_boss_get_team_coach_node ($team_node) {
  $coach_nid = hockey_boss_get_team_coach_nid ($team_node);
  return is_null ($coach_nid) ? null : node_load ($coach_nid);
}

/**
  @brief Accepts a team node and returns its player node ids.
  @return (array) the player node ids.
*/
function hockey_boss_get_team_player_nids ($node) {
  return simple_field_get_relation_source_entity_ids ($node, hockey_boss_TEAM_PROFILE_TYPE . '_players');
}

/**
  @brief Accepts a team node id and returns the
    game/team relations associated with it.
  @param $team_nid (int) the team node id.
  @return (array) the relations.
*/
function hockey_boss_get_team_game_relations ($team_nid) {
  $query = relation_query ('node', $team_nid, 1);
  $query->entityCondition ('bundle', hockey_boss_GAME_TEAM_RELATION);
  $results = $query->execute ();
  $relations = array ();
  foreach ($results as $result) {
    $relations [] = relation_load ($result->rid);
  }
  return $relations;
}

/**
  @brief Accepts a team node id and returns an
    array describing the games that the team
    participated in.
  @param $team_nid (int) the team node id.
  @return (array) the game nodes sorted and keyed by date.
*/
function hockey_boss_get_team_games ($team_nid) {
  $game_nodes = array ();
  foreach (hockey_boss_get_team_game_relations ($team_nid) as $relation) {
    $entities = field_get_items ('relation', $relation, 'endpoints');
    $game_node = node_load ($entities [0]['entity_id']);
    $game_date = hockey_boss_get_game_date ($game_node);
    $game_nodes [$game_date] = $game_node;
  }
  asort ($game_nodes);
  return $game_nodes;
}

/**
  @brief Accepts a team node and returns its age term.
  @param $team_node (object) the team node.
  @return (int) the age term id.
*/
function hockey_boss_get_team_age_tid ($team_node) {
  $age_field_items = field_get_items ('node', $team_node, hockey_boss_TEAM_PROFILE_TYPE . '_age_group');
  return empty ($age_field_items) ? null : $age_field_items [0]['tid'];
}

/**
  @brief Accepts a team node and returns its age term.
  @param $team_node (object) the team node.
  @return (object) the age term.
*/
function hockey_boss_get_team_age_term ($team_node) {
  $age_tid  = hockey_boss_get_team_age_tid ($team_node);
  return is_null ($age_tid) ? null : taxonomy_term_load ($age_tid);
}

/**
  @brief Accepts a team node and returns its division term.
  @param $team_node (object) the team node.
  @return (int) the division term id.
*/
function hockey_boss_get_team_division_tid ($team_node) {
  $division_field_items = field_get_items ('node', $team_node, hockey_boss_TEAM_PROFILE_TYPE . '_division');
  return empty ($division_field_items) ? null : $division_field_items [0]['tid'];
}

/**
  @brief Accepts a team node and returns its division term.
  @param $team_node (object) the team node.
  @return (object) the division term.
*/
function hockey_boss_get_team_division_term ($team_node) {
  $division_tid = hockey_boss_get_team_division_tid ($team_node);
  return is_null ($division_tid) ? null : taxonomy_term_load ($division_tid);
}

/**
  @brief Accepts a team node and returns its gender term id.
  @param $team_node (object) the team node.
  @return (int) the gender term id.
*/
function hockey_boss_get_team_gender_tid ($team_node) {
  $gender_field_items = field_get_items ('node', $team_node, hockey_boss_TEAM_PROFILE_TYPE . '_gender');
  return empty ($gender_field_items) ? null : $gender_field_items [0]['tid'];
}

/**
  @brief Accepts a team node and returns its gender term.
  @param $team_node (object) the team node.
  @return (object) the gender term.
*/
function hockey_boss_get_team_gender_term ($team_node) {
  $gender_tid = hockey_boss_get_team_gender_tid ($team_node);
  return is_null ($gender_tid) ? null : taxonomy_term_load ($gender_tid);
}

/**
  @brief Accepts a team node and returns its club node id.
  @param $team_node (object) the team node.
  @return (int) the club node id.
*/
function hockey_boss_get_team_club_nid ($team_node) {
  return simple_field_get_relation_target_entity_id ($team_node, hockey_boss_TEAM_PROFILE_TYPE . '_club');
}

/**
  @brief Accepts a team node and returns its club node id.
  @param $team_node (object) the team node.
  @return (int) the club node id.
*/
function hockey_boss_get_team_club_node ($team_node) {
  $club_nid = hockey_boss_get_team_club_nid ($team_node);
  return is_null ($club_nid) ? null : node_load ($club_nid);
}

/**
  @brief Accepts a club node and returns its league node id.
  @param $team_node (object) the team node.
  @return (int) the league node id.
*/
function hockey_boss_get_club_league_nid ($club_node) {
  return simple_field_get_relation_target_entity_id ($club_node, hockey_boss_CLUB_PROFILE_TYPE . '_league');
}

/**
  @brief Accepts a club node and returns its league node id.
  @param $club_node (object) the club node.
  @return (int) the league node id.
*/
function hockey_boss_get_club_league_node ($club_node) {
  $league_nid = hockey_boss_get_club_league_nid ($club_node);
  return is_null ($league_nid) ? null : node_load ($league_nid);
}

/**
  @brief Accepts a club node and returns its team node ids.
  @param $club_node (object) the club node.
  @return (array int) the team node ids.
*/
function hockey_boss_get_club_team_nids ($club_node) {
  return simple_field_get_relation_source_entity_ids ($club_node, hockey_boss_CLUB_PROFILE_TYPE . '_teams');
}

/**
  @brief Accepts a league node and returns its club node ids.
  @param $league_node (object) the league node.
  @return (array) the club node ids.
*/
function hockey_boss_get_league_club_nids ($league_node) {
  return simple_field_get_relation_source_entity_ids ($league_node, hockey_boss_LEAGUE_PROFILE_TYPE . '_clubs');
}

/**
  @brief Accepts a coach node and returns its user id.
  @return (int) the coach user id.
*/
function hockey_boss_get_coach_user_uid ($node) {
  return simple_field_get_relation_source_entity_id ($node, hockey_boss_COACH_PROFILE_TYPE . '_user');
}

/**
  @brief Accepts a game node and returns the game date.
  @param $game_node (object) the game node.
  @return (string) the game date.
*/
function hockey_boss_get_game_date ($game_node) {
  return $game_node ? $game_node->{hockey_boss_GAME_TYPE . '_date'}['und'][0]['value'] : null;
}

/**
  @brief Accepts a game node and returns the node id of the teams.
  @return (array) the team node ids.
*/
function hockey_boss_get_game_team_nids ($node) {
  return simple_field_get_relation_target_entity_ids ($node, hockey_boss_GAME_TYPE . '_teams');
}

/**
  @brief Accepts a game node and returns the relations.
  @param $game_nid (int) the game node id.
  @return (object) the game team relations.
*/
function hockey_boss_get_game_team_relations ($game_nid) {
  $query = relation_query ('node', $game_nid, 0);
  $query->entityCondition ('bundle', hockey_boss_GAME_TEAM_RELATION);
  $results = $query->execute ();
  $relations = array ();
  foreach ($results as $result) {
    $relations [] = relation_load ($result->rid);
  }
  return $relations;
}

/**
  @brief Accepts a game node and returns the game date year.
  @param $game_node (object) the game node.
  @return (string) the game date year.
*/
function hockey_boss_get_game_year ($game_node) {
  $date_string = hockey_boss_get_game_date ($game_node);
  $date = date_create ($date_string);
  return date_format ($date, 'Y');
}

// ----- VI. User Roles -----

/// The Club Admin role name.
define ('hockey_boss_CLUB_ADMIN_ROLE', 'hockey_boss_club_admin_role');

/// The Coach role name. 
define ('hockey_boss_COACH_ROLE', 'hockey_boss_coach_role');

/// The League Admin role name.
define ('hockey_boss_LEAGUE_ADMIN_ROLE', 'hockey_boss_league_admin_role');

/// The Team Staff role name.
define ('hockey_boss_TEAM_STAFF_ROLE', 'hockey_boss_team_staff_role');

/// The Player role name.
define ('hockey_boss_PLAYER_ROLE', 'hockey_boss_player_role');

/**
  @brief Creates the given user role.
  @param $role_name (string) the role name.
  @return (boolean) returns true iff the role was 
    created successfully.
  @note This function will display and log an error
    message on failure.
*/
function hockey_boss_create_role ($role_name) {
  if (!user_role_load_by_name ($role_name)) {
    if (!user_role_save ((object) array ('name' => $role_name))) {
      $msg = "Error: an error occured while trying to create the $role_name role.";
      drupal_set_message ($msg, 'error');
      watchdog (
        'hockey_boss',
        '[hockey_boss_create_role] ' . $msg,
        array (), 
        WATCHDOG_ERROR
      );  
    }   
  }
}

/**
  @brief Returns a list of the core user roles and 
    their permissions.
  @return (array) the core user roles.
*/
function hockey_boss_roles () {
  return array (
    hockey_boss_CLUB_ADMIN_ROLE => array (),
    hockey_boss_COACH_ROLE => array (),
    hockey_boss_LEAGUE_ADMIN_ROLE => array (),
    hockey_boss_PLAYER_ROLE => array (),
    hockey_boss_TEAM_STAFF_ROLE => array ()
  );
}

/**
  @brief Creates the core user roles and assigns
    them their default permissions.
*/
function hockey_boss_create_roles () {
  foreach (hockey_boss_roles () as $role_name => $permissions) {
    hockey_boss_create_role ($role_name);
  }
}

/// Deletes the core user roles.
function hockey_boss_delete_roles () {
  foreach (array_keys (hockey_boss_roles ()) as $role_name) {
    user_role_delete ($role_name);
  }
}

// ----- VII. Permissions -----

/**
  @brief Grants the default permissions to the core
    user roles.
*/
function hockey_boss_grant_permissions () {
  foreach (hockey_boss_roles () as $role_name => $permissions) {
    $role = user_role_load_by_name ($role_name);
    user_role_grant_permissions ($role->rid, $permissions);
  }
}
