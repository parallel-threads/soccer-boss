<?php
/**
  @file
  @brief Defines the primary views.
*/

/// Implements hook_views_default_views ().
function soccer_boss_views_default_views () {
  $views = array ();
  foreach (array (
    soccer_boss_player_game_stats_view (),
    soccer_boss_player_stats_view (),
    soccer_boss_player_vitals_view (),
    soccer_boss_team_games_view (),
    soccer_boss_team_roster_view ()
  ) as $view) {
    $views [$view->name] = $view;
  }
  return $views;
}

/// Deletes the primary views.
function soccer_boss_delete_views () {
  foreach (soccer_boss_views_default_views () as $view) {
    views_delete_view ($view);
  }
}

// ----- The following section contains the exported views bundled into functions -----

/// Returns the Player Game Stats view.
function soccer_boss_player_game_stats_view () {
  $view = new view();
  $view->name = 'player_game_stats';
  $view->description = 'Lists a player\'s game stats.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Player Game Stats';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Player Game Stats';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['soccer_boss_game_stats_game_target_id']['id'] = 'soccer_boss_game_stats_game_target_id';
  $handler->display->display_options['relationships']['soccer_boss_game_stats_game_target_id']['table'] = 'field_data_soccer_boss_game_stats_game';
  $handler->display->display_options['relationships']['soccer_boss_game_stats_game_target_id']['field'] = 'soccer_boss_game_stats_game_target_id';
  $handler->display->display_options['relationships']['soccer_boss_game_stats_game_target_id']['required'] = TRUE;
  /* Field: Content revision: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node_revision';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'soccer_boss_game_stats_game_target_id';
  $handler->display->display_options['fields']['title']['label'] = 'Match';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['soccer_boss_game_date']['id'] = 'soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['table'] = 'field_data_soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['field'] = 'soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['relationship'] = 'soccer_boss_game_stats_game_target_id';
  $handler->display->display_options['fields']['soccer_boss_game_date']['label'] = 'Match Date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Assists */
  $handler->display->display_options['fields']['soccer_boss_game_stats_assists']['id'] = 'soccer_boss_game_stats_assists';
  $handler->display->display_options['fields']['soccer_boss_game_stats_assists']['table'] = 'field_data_soccer_boss_game_stats_assists';
  $handler->display->display_options['fields']['soccer_boss_game_stats_assists']['field'] = 'soccer_boss_game_stats_assists';
  /* Field: Content: Goals */
  $handler->display->display_options['fields']['soccer_boss_game_stats_goals']['id'] = 'soccer_boss_game_stats_goals';
  $handler->display->display_options['fields']['soccer_boss_game_stats_goals']['table'] = 'field_data_soccer_boss_game_stats_goals';
  $handler->display->display_options['fields']['soccer_boss_game_stats_goals']['field'] = 'soccer_boss_game_stats_goals';
  /* Field: Content: Minutes */
  $handler->display->display_options['fields']['soccer_boss_game_stats_minutes']['id'] = 'soccer_boss_game_stats_minutes';
  $handler->display->display_options['fields']['soccer_boss_game_stats_minutes']['table'] = 'field_data_soccer_boss_game_stats_minutes';
  $handler->display->display_options['fields']['soccer_boss_game_stats_minutes']['field'] = 'soccer_boss_game_stats_minutes';
  /* Field: Content: Shots */
  $handler->display->display_options['fields']['soccer_boss_game_stats_shots']['id'] = 'soccer_boss_game_stats_shots';
  $handler->display->display_options['fields']['soccer_boss_game_stats_shots']['table'] = 'field_data_soccer_boss_game_stats_shots';
  $handler->display->display_options['fields']['soccer_boss_game_stats_shots']['field'] = 'soccer_boss_game_stats_shots';
  /* Field: Content: Shots On Goal */
  $handler->display->display_options['fields']['soccer_boss_game_stats_sog']['id'] = 'soccer_boss_game_stats_sog';
  $handler->display->display_options['fields']['soccer_boss_game_stats_sog']['table'] = 'field_data_soccer_boss_game_stats_sog';
  $handler->display->display_options['fields']['soccer_boss_game_stats_sog']['field'] = 'soccer_boss_game_stats_sog';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'soccer_boss_player_game_stats' => 'soccer_boss_player_game_stats',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  return $view;
}

/// Returns the Player Stats view.
function soccer_boss_player_stats_view () {
  $view = new view();
  $view->name = 'player_stats';
  $view->description = 'Lists the stats associated with a given node.';
  $view->tag = 'default';
  $view->base_table = 'stat_values';
  $view->human_name = 'Player Stats';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stats';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'date',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'name' => 'name',
    'content' => 'content',
    'date' => 'date',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'content' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date' => array(
      'sortable' => 0,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  /* Relationship: Stat Values: Stat Values to Stat */
  $handler->display->display_options['relationships']['stat_values_related_stat']['id'] = 'stat_values_related_stat';
  $handler->display->display_options['relationships']['stat_values_related_stat']['table'] = 'stat_values';
  $handler->display->display_options['relationships']['stat_values_related_stat']['field'] = 'stat_values_related_stat';
  $handler->display->display_options['relationships']['stat_values_related_stat']['required'] = TRUE;
  /* Relationship: Stats: Stats to Node */
  $handler->display->display_options['relationships']['stats_related_node']['id'] = 'stats_related_node';
  $handler->display->display_options['relationships']['stats_related_node']['table'] = 'stats';
  $handler->display->display_options['relationships']['stats_related_node']['field'] = 'stats_related_node';
  $handler->display->display_options['relationships']['stats_related_node']['relationship'] = 'stat_values_related_stat';
  $handler->display->display_options['relationships']['stats_related_node']['required'] = TRUE;
  /* Field: Stat Value: Stat value ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'stat_values';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Stat: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'stats';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'stat_values_related_stat';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Stat Value: Content */
  $handler->display->display_options['fields']['content']['id'] = 'content';
  $handler->display->display_options['fields']['content']['table'] = 'stat_values';
  $handler->display->display_options['fields']['content']['field'] = 'content';
  $handler->display->display_options['fields']['content']['label'] = 'Value';
  $handler->display->display_options['fields']['content']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['content']['alter']['path'] = 'stat/value/[id]/view';
  /* Field: Stat Value: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'stat_values';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['label'] = '';
  $handler->display->display_options['fields']['date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['date']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date']['custom_date_format'] = 'Y';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'stats_related_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'player-stats';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';

  return $view;
}

/// Returns the Player Vitals view.
function soccer_boss_player_vitals_view () {
  $view = new view();
  $view->name = 'player_vitals';
  $view->description = 'Displays the vitals of the referenced player.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Player Vitals';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Birth Date */
  $handler->display->display_options['fields']['soccer_boss_player_birth_date']['id'] = 'soccer_boss_player_birth_date';
  $handler->display->display_options['fields']['soccer_boss_player_birth_date']['table'] = 'field_data_soccer_boss_player_birth_date';
  $handler->display->display_options['fields']['soccer_boss_player_birth_date']['field'] = 'soccer_boss_player_birth_date';
  $handler->display->display_options['fields']['soccer_boss_player_birth_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Height */
  $handler->display->display_options['fields']['soccer_boss_player_height']['id'] = 'soccer_boss_player_height';
  $handler->display->display_options['fields']['soccer_boss_player_height']['table'] = 'field_data_soccer_boss_player_height';
  $handler->display->display_options['fields']['soccer_boss_player_height']['field'] = 'soccer_boss_player_height';
  /* Field: Content: Weight */
  $handler->display->display_options['fields']['soccer_boss_player_weight']['id'] = 'soccer_boss_player_weight';
  $handler->display->display_options['fields']['soccer_boss_player_weight']['table'] = 'field_data_soccer_boss_player_weight';
  $handler->display->display_options['fields']['soccer_boss_player_weight']['field'] = 'soccer_boss_player_weight';
  /* Field: Content: Position */
  $handler->display->display_options['fields']['soccer_boss_player_position']['id'] = 'soccer_boss_player_position';
  $handler->display->display_options['fields']['soccer_boss_player_position']['table'] = 'field_data_soccer_boss_player_position';
  $handler->display->display_options['fields']['soccer_boss_player_position']['field'] = 'soccer_boss_player_position';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'soccer_boss_player' => 'soccer_boss_player',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  return $view;
}

/// Returns the Team Games view.
function soccer_boss_team_games_view () {
  $view = new view();
  $view->name = 'team_games';
  $view->description = 'Displays a list of the games that the given team has participated in.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Team Games';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Team Games';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['soccer_boss_game_teams_target_id']['id'] = 'soccer_boss_game_teams_target_id';
  $handler->display->display_options['relationships']['soccer_boss_game_teams_target_id']['table'] = 'field_data_soccer_boss_game_teams';
  $handler->display->display_options['relationships']['soccer_boss_game_teams_target_id']['field'] = 'soccer_boss_game_teams_target_id';
  $handler->display->display_options['relationships']['soccer_boss_game_teams_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['soccer_boss_game_date']['id'] = 'soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['table'] = 'field_data_soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['field'] = 'soccer_boss_game_date';
  $handler->display->display_options['fields']['soccer_boss_game_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Teams */
  $handler->display->display_options['fields']['soccer_boss_game_teams']['id'] = 'soccer_boss_game_teams';
  $handler->display->display_options['fields']['soccer_boss_game_teams']['table'] = 'field_data_soccer_boss_game_teams';
  $handler->display->display_options['fields']['soccer_boss_game_teams']['field'] = 'soccer_boss_game_teams';
  $handler->display->display_options['fields']['soccer_boss_game_teams']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['soccer_boss_game_teams']['delta_offset'] = '0';
  $handler->display->display_options['fields']['soccer_boss_game_teams']['separator'] = ' vs ';
  /* Field: Content: Score */
  $handler->display->display_options['fields']['soccer_boss_game_score']['id'] = 'soccer_boss_game_score';
  $handler->display->display_options['fields']['soccer_boss_game_score']['table'] = 'field_data_soccer_boss_game_score';
  $handler->display->display_options['fields']['soccer_boss_game_score']['field'] = 'soccer_boss_game_score';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'soccer_boss_game_teams_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'soccer_boss_game' => 'soccer_boss_game',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'team-games';

  return $view;
}

/// Returns the Team Roster view.
function soccer_boss_team_roster_view () {
  $view = new view();
  $view->name = 'team_roster';
  $view->description = 'Lists the players on a given team.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Team Roster';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Team Roster';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Photo */
  $handler->display->display_options['fields']['soccer_boss_player_photo']['id'] = 'soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['table'] = 'field_data_soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['field'] = 'soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['label'] = '';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['soccer_boss_player_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Position */
  $handler->display->display_options['fields']['soccer_boss_player_position']['id'] = 'soccer_boss_player_position';
  $handler->display->display_options['fields']['soccer_boss_player_position']['table'] = 'field_data_soccer_boss_player_position';
  $handler->display->display_options['fields']['soccer_boss_player_position']['field'] = 'soccer_boss_player_position';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'soccer_boss_player' => 'soccer_boss_player',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'team-roster';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'team-roster.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'page' => 'page',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';

  return $view;
}
