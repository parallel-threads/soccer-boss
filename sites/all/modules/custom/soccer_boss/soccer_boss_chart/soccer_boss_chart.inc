<?php
/**
  @file
  @brief Defines support functions for creating charts.
*/

/**
  @brief Accepts a chart value along with the
    minimum and maximum value displayed on the
    chart and returns the scaled equivalent of the
    given value.
  @param $min (float) the minimum chart value.
  @param $max (float) the maximum chart value.
  @param $value (float) the unscaled chart value.
  @return (float) the scaled chart value.
  @note Google Charts only allows values between
    0 - 100 inclusive.
*/
function _soccer_boss_chart_get_scaled_value ($min, $max, $value) {
  return $max - $min > 0 ? (($value - $min)/($max - $min)) * 100 : 0;
}

/**
  @brief Accepts a raw unscaled chart value and
    converts the value into a float that can be
    scaled.
  @param $value (string) the raw chart value.
  @return (float) the converted chart value.
  @note This function tries to convert time
    measures into second counts and strips units
    from unit measures.
*/
function _soccer_boss_chart_convert_value ($value) {
  if (preg_match ('/\s*(\d?\d):(\d\d)\s*/', $value, $matches)) {
    $value = $matches [1] * 60 + $matches [2];
  } else if (preg_match ('/^(\d+)/', $value, $matches)) { // strip units.
    $value = $matches [1];
  }
  return $value;
}

/**
  @brief Accepts raw unscaled chart values and
    converts the values into floats that can be
    scaled.
  @param $values (array) the raw chart values.
  @return (array) the converted chart values.
*/
function _soccer_boss_chart_convert_values ($values) {
  return array_map ('_soccer_boss_chart_convert_value', $values);
}

/**
  @brief Accepts an array of chart values and
    returns their scaled equivalents.
  @param $values (array) the values.
  @return (array) the scaled values.
*/
function _soccer_boss_chart_scale_chart_values ($values) {
  $scaled_values = array ();

  $min = min ($values);
  $max = max ($values);

  foreach ($values as $value) {
    $scaled_values [] = _soccer_boss_chart_get_scaled_value ($min, $max, $value);
  }

  return $scaled_values;
}

/**
  @brief Accepts an array of unscaled chart values
    and returns the chart value labels for the
    y-axis.
  @param $values (array) the unscaled values.
  @return (array) the chart labels.
*/
function _soccer_boss_chart_get_chart_value_labels ($values) {
  $labels = array ();

  $unique_values = array_unique ($values);  
  $min   = min ($unique_values);
  $max   = max ($unique_values);

  foreach ($unique_values as $unique_value) {
    $labels [] = chart_mixed_axis_label ($unique_value, _soccer_boss_chart_get_scaled_value ($min, $max, $unique_value));
  }

  return $labels;
}

/**
  @brief Returns a Chart that represents the given data.
  @param $data (array) the chart data array.
*/
function soccer_boss_chart ($data) {
  $y_axis_values = array_unique ($data ['values']);
  $x_axis_values = array_unique ($data ['x_axis_values']);

  return array (
    '#chart_id'           => $data ['chart_id'],
    '#title'              => $data ['title'],
    '#type'               => $data ['type'],
    '#size'               => $data ['size'],
    '#adjust_resolution'  => true,
    '#legends'            => array ($data ['legend']),
    '#mixed_axis_labels'  => array (
      CHART_AXIS_Y_LEFT   => array (
        _soccer_boss_chart_get_chart_value_labels ($y_axis_values),
        chart_mixed_axis_label ($data ['y_axis_label'], 50)
      ),
      CHART_AXIS_X_BOTTOM => array (
        array_map ('chart_mixed_axis_label', $x_axis_values),
        chart_mixed_axis_label ($data ['x_axis_label'], 50)
      )
    ),
    '#data'               => array (
      'values'            => _soccer_boss_chart_scale_chart_values (
                               _soccer_boss_chart_convert_values ($data ['values']))
  ));
}

/**
  @brief Accepts a player node and returns a chart
    that plots the player's fitness stats over time.
  @param $player (node) the player node.
  @return (array) the chart render array.
*/
function _soccer_boss_chart_pfs ($player) {
  module_load_include ('inc', 'soccer_boss');

  $stats = node_load_multiple (
    soccer_boss_get_references ($player->nid, 'node', 'soccer_boss_pfs_player'));

  $stat_names  = array ();
  $stat_values = array ();

  foreach ($stats as $stat) {
    if (!in_array ($stat->title, $stat_names)) {
      $stat_names [] = $stat->title;
    }
    $stat_values [$stat->title]
                 [$stat->soccer_boss_pfs_date ['und'][0]['value']] 
                 = $stat->soccer_boss_pfs_value ['und'][0]['value'];
  } 

  // II. Create the stat chart data arrays.

  $data_arrays = array ();

  foreach ($stat_values as $stat_name => $values) {
    
    $sorted_values = array_values ($values);
    sort ($sorted_values);

    ksort ($values);

    $dates = array ();
    foreach (array_keys ($values) as $date) {
      $dates [] = date ('D, d M Y', strtotime ($date));
    }

    $data_arrays [] = array (
      'chart_id'      => $stat_name,
      'title'         => $stat_name,
      'type'          => CHART_TYPE_LINE,
      'size'          => chart_size (700, 400),
      'legend'        => $stat_name,
      'y_axis_label'  => null,
      'x_axis_label'  => null,
      'x_axis_values' => $dates,
      'values'        => $values
    );
  }

  // III. return the chart form.

  return $data_arrays;
}
