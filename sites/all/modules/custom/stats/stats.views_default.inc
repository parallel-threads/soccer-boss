<?php
/**
  @file
  @brief Defines the Stat views.
*/

/// Implements hook_views_default_views (). 
function stats_views_default_views () {
  $views = array (); 
  foreach (array (
    stats_values_view (), 
    stats_node_stats_view () 
  ) as $view) {
    $views [$view->name] = $view;
  }
  return $views;
}

/// Deletes the Stat views.
function stats_delete_views () {
  foreach (stats_views_default_views () as $view) {
    views_delete_view ($view);
  }
}

// ===== The following section contains exported views bundled into functions =====

/// Returns the Stat Values view.
function stats_values_view () {
  $view = new view();
  $view->name = 'stat_values';
  $view->description = 'Lists the values associated with a given stat.';
  $view->tag = 'default';
  $view->base_table = 'stat_values';
  $view->human_name = 'Stat Values';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stat Values';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'content' => 'content',
    'date' => 'date',
  );
  $handler->display->display_options['style_options']['default'] = 'date';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
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
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'A collection of stat values.';
  $handler->display->display_options['style_options']['summary'] = 'A collection of stat values.';
  /* Field: Stat Value: Stat value ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'stat_values';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
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
  /* Contextual filter: Stat Value: Stat */
  $handler->display->display_options['arguments']['stat']['id'] = 'stat';
  $handler->display->display_options['arguments']['stat']['table'] = 'stat_values';
  $handler->display->display_options['arguments']['stat']['field'] = 'stat';
  $handler->display->display_options['arguments']['stat']['default_action'] = 'default';
  $handler->display->display_options['arguments']['stat']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['stat']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['stat']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['stat']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['stat']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'stat-values';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';

  return $view;
}

/// Returns the Node Stats view.
function stats_node_stats_view () {
  $view = new view();
  $view->name = 'node_stats';
  $view->description = 'Lists the stats associated with a given node.';
  $view->tag = 'default';
  $view->base_table = 'stat_values';
  $view->human_name = 'Node Stats';
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
      'field' => 'name',
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
  $handler->display->display_options['style_options']['default'] = 'date';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'content' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
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
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['date']['date_format'] = 'long';
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
  $handler->display->display_options['path'] = 'node-stats';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';

  return $view;
}
