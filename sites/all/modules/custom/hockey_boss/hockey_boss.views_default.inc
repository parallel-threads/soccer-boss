<?php
/**
  @file
  @brief This file defines the primary views.
*/

/// Implements hook_views_default_views ().
function hockey_boss_views_default_views () {
  $views = array ();
  foreach (array (
    hockey_boss_leagues_view ()
  ) as $view) {
    $views [$view->name] = $view;
  }
  return $views;
}

/// Deletes the primary views.
function hockey_boss_delete_views () {
  foreach (hockey_boss_views_default_views () as $view) {
    views_delete_view ($view);
  }
}

// ----- The following section contains the exported views bundled into functions -----

/// Creates the Leagues view.
function hockey_boss_leagues_view () {
  $view = new view();
  $view->name = 'hockey_boss_leagues';
  $view->description = 'Displays a list of the leagues currently registered on the site.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Leagues';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Leagues';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'hockey_boss_league_type' => 'hockey_boss_league_type',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  return $view;
}
