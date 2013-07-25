<?php
/**
  @file
  @brief Defines the pages created by the Soccer
    Boss module.
*/

/**
  @brief Redirects the user to the Team page
    associated with the given coach node.
  @param $node (object) the coach node.
*/
function soccer_boss_coach_team_page ($node) {
  module_load_include ('inc', 'soccer_boss');

  watchdog (
    'soccer_boss',
    '[soccer_boss_coach_team_page]'
  );

  // I. Retrieve the team node ids.
  $ids = soccer_boss_get_references ($node->nid, 'node', 'soccer_boss_team_coach');

  watchdog (
    'soccer_boss',
    '[soccer_boss_coach_team_page] ids: <pre>@ids</pre>',
    array (
      '@ids' => print_r ($ids, true)
  ));

  // II. Retrieve the team node uri.
  if (empty ($ids)) {
    drupal_set_message ('This coach is not currently affiliated with any known teams.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($ids [0])); 
  }

  // III. Redirect the user.
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to the Player's Stats view.
  @param $node (object) the player node.
*/
function soccer_boss_player_stats_page ($node) {
  drupal_goto ("player-stats/$node->nid");
}

/**
  @brief Redirects the user to the Player's Team page.
  @param $node (object) the player node.
*/
function soccer_boss_player_team_page ($node) {
  if (empty ($node->soccer_boss_player_team ['und'])) {
    drupal_set_message ('This player is not associated with a team.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($node->soccer_boss_player_team ['und'][0]['target_id']));
  }
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to profile of the head
    coach associated with the given team.
  @param $node (object) the team node.
*/
function soccer_boss_team_coach_page ($node) {
  if (empty ($node->soccer_boss_team_coach ['und'])) {
    drupal_set_message ('This team does not have a Head Coach.');
    $uri = node_uri ($node);
  } else {
    $uri = node_uri (node_load ($node->soccer_boss_team_coach ['und'][0]['target_id']));
  }
  drupal_goto ($uri ['path']);
}

/**
  @brief Redirects the user to the Team Roster page.
  @param $node (object) the current team node.
*/
function soccer_boss_team_roster_page ($node) {
  drupal_goto ('team-roster/' . $node->nid);
}

/**
  @brief Redirects the user to the Team Games page.
  @param $node (object) the current team node.
*/
function soccer_boss_team_games_page ($node) {
  drupal_goto ('team-games/' . $node->nid);
}
