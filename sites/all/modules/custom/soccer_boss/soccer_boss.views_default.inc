<?php
/**
  @file
  @brief Defines the primary views.
*/

/// Implements hook_views_default_views ().
function soccer_boss_views_default_views () {
  $views = array ();
  foreach (array (
    soccer_boss_player_performance_stats_view (),
    soccer_boss_player_vital_stats_view (),
    soccer_boss_team_games_view (),
    soccer_boss_team_roster_view (),
    soccer_boss_team_staff_view ()
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

/// Returns the Player Performance Stats view.
function soccer_boss_player_performance_stats_view () {
  $view = new view();
  $view->name = 'player_performance_stats';
  $view->description = 'Displays stats summarizing a player\'s performance over a given season.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Player Performance Stats';
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
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'soccer_boss_pps_year',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'soccer_boss_pps_value' => 'soccer_boss_pps_value',
    'soccer_boss_pps_year' => 'soccer_boss_pps_year',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'soccer_boss_pps_value' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'soccer_boss_pps_year' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['soccer_boss_pps_player_target_id']['id'] = 'soccer_boss_pps_player_target_id';
  $handler->display->display_options['relationships']['soccer_boss_pps_player_target_id']['table'] = 'field_data_soccer_boss_pps_player';
  $handler->display->display_options['relationships']['soccer_boss_pps_player_target_id']['field'] = 'soccer_boss_pps_player_target_id';
  $handler->display->display_options['relationships']['soccer_boss_pps_player_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Value */
  $handler->display->display_options['fields']['soccer_boss_pps_value']['id'] = 'soccer_boss_pps_value';
  $handler->display->display_options['fields']['soccer_boss_pps_value']['table'] = 'field_data_soccer_boss_pps_value';
  $handler->display->display_options['fields']['soccer_boss_pps_value']['field'] = 'soccer_boss_pps_value';
  /* Field: Content: Year */
  $handler->display->display_options['fields']['soccer_boss_pps_year']['id'] = 'soccer_boss_pps_year';
  $handler->display->display_options['fields']['soccer_boss_pps_year']['table'] = 'field_data_soccer_boss_pps_year';
  $handler->display->display_options['fields']['soccer_boss_pps_year']['field'] = 'soccer_boss_pps_year';
  $handler->display->display_options['fields']['soccer_boss_pps_year']['label'] = '';
  $handler->display->display_options['fields']['soccer_boss_pps_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['soccer_boss_pps_year']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'soccer_boss_pps_player_target_id';
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
    'soccer_boss_pps' => 'soccer_boss_pps',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  return $view;
}

/// Returns the Player Vital Stats view.
function soccer_boss_player_vital_stats_view () {
  $view = new view();
  $view->name = 'player_vital_stats';
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
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['soccer_boss_player_team_target_id']['id'] = 'soccer_boss_player_team_target_id';
  $handler->display->display_options['relationships']['soccer_boss_player_team_target_id']['table'] = 'field_data_soccer_boss_player_team';
  $handler->display->display_options['relationships']['soccer_boss_player_team_target_id']['field'] = 'soccer_boss_player_team_target_id';
  $handler->display->display_options['relationships']['soccer_boss_player_team_target_id']['label'] = 'Content entity referenced from soccer_boss_player_team';
  $handler->display->display_options['relationships']['soccer_boss_player_team_target_id']['required'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['soccer_boss_player_photo']['id'] = 'soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['table'] = 'field_data_soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['field'] = 'soccer_boss_player_photo';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['label'] = '';
  $handler->display->display_options['fields']['soccer_boss_player_photo']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Broken/missing handler */
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
  $handler->display->display_options['arguments']['nid']['relationship'] = 'soccer_boss_player_team_target_id';
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

/// Returns the Team Staff view.
function soccer_boss_team_staff_view () {
  $view = new view();
  $view->name = 'team_staff';
  $view->description = 'Lists the players on a given team.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Team Staff';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Team Staff';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['soccer_boss_staff_team_target_id']['id'] = 'soccer_boss_staff_team_target_id';
  $handler->display->display_options['relationships']['soccer_boss_staff_team_target_id']['table'] = 'field_data_soccer_boss_staff_team';
  $handler->display->display_options['relationships']['soccer_boss_staff_team_target_id']['field'] = 'soccer_boss_staff_team_target_id';
  $handler->display->display_options['relationships']['soccer_boss_staff_team_target_id']['required'] = TRUE;
  /* Field: Content: Photo */
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['id'] = 'soccer_boss_staff_photo';
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['table'] = 'field_data_soccer_boss_staff_photo';
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['field'] = 'soccer_boss_staff_photo';
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['label'] = '';
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['soccer_boss_staff_photo']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  /* Field: Content: Role */
  $handler->display->display_options['fields']['soccer_boss_staff_role']['id'] = 'soccer_boss_staff_role';
  $handler->display->display_options['fields']['soccer_boss_staff_role']['table'] = 'field_data_soccer_boss_staff_role';
  $handler->display->display_options['fields']['soccer_boss_staff_role']['field'] = 'soccer_boss_staff_role';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'soccer_boss_staff_team_target_id';
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
    'soccer_boss_staff' => 'soccer_boss_staff',
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
