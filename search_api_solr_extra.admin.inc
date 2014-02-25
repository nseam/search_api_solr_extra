<?php
/**
 * @file
 * search_api_solr_extra admin functions.
 * Implements Admin functions for Search API Solr Extra module.
 */

/**
 * Generates form to configure interface.
 */
function search_api_solr_extra_settings_form() {

  $form['search_api_solr_extra_solr'] = array(
    '#type' => 'fieldset',
    '#title' => t('Solr'),
    '#description' => t('General solr settings.'),
  );

  $form['search_api_solr_extra_solr']['search_api_solr_extra_solr_cache_results'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable solr caching on search pages.'),
    '#default_value' => variable_get('search_api_solr_extra_solr_cache_results', TRUE),
  );

  $form['search_api_solr_extra_solr']['search_api_solr_extra_solr_cache_results_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('How long the results are cached.'),
    '#size' => 6,
    '#description' => t('In format: "1h" or "5min 30s" OR "2 days"'),
    '#default_value' => variable_get('search_api_solr_extra_solr_cache_results_timeout', '1min 30s'),
  );

  $form['search_api_solr_extra_settings_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Interface'),
  );

  $form['search_api_solr_extra_settings_ui']['static_minmax'] = array(
    '#type' => 'fieldset',
    '#title' => t('Salary slider'),
  );

   $form['search_api_solr_extra_settings_score_thresholding'] = array(
    '#type' => 'fieldset',
    '#title' => t('Score Thresholding'),
  );

  $form['search_api_solr_extra_settings_score_thresholding']['search_api_solr_extra_score_thresholding_threshold_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#default_value' => variable_get('search_api_solr_extra_score_thresholding_threshold_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_score_thresholding']['search_api_solr_extra_score_thresholding_threshold_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum score for records to be displayed'),
    '#field_suffix' => t('%'),
    '#size' => 3,
    '#maxlength' => 3,
    '#default_value' => variable_get('search_api_solr_extra_score_thresholding_threshold_value', '20'),
    '#description' => t('Minimum score threshold is a score scaled to 0 - 100 range.'),
  );

  $form['search_api_solr_extra_settings_spellchecking'] = array(
    '#type' => 'fieldset',
    '#title' => t('Spell Checking'),
  );

  $form['search_api_solr_extra_settings_spellchecking']['search_api_solr_extra_settings_debugging_build_spellcheck'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild spellchecker data'),
    '#executes_submit_callback' => TRUE,
    '#submit' => array('search_api_solr_extra_rebuild_spellchecker_data'),
  );

  $form['search_api_solr_extra_settings_debugging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
    '#description' => t('Debug messages will be displayed in status area of the current view.'),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_queries_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr queries'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_queries_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_results_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr results'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_results_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_results_process_time'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr result processing time'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_results_process_time', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_result_boosts_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr result boosts'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_result_boosts_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_result_boosts_expand'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr result boosts - Show expanded'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_result_boosts_expand', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_result_spellcheck_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr result spellchecker data'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_result_spellcheck_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_debugging']['search_api_solr_extra_settings_debugging_result_full_response_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Solr result full response'),
    '#default_value' => variable_get('search_api_solr_extra_settings_debugging_result_full_response_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_logging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logging'),
    '#description' => t('Watchdog logging.'),
  );

  $form['search_api_solr_extra_settings_logging']['search_api_solr_extra_settings_logging_queries_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log Solr queries'),
    '#default_value' => variable_get('search_api_solr_extra_settings_logging_queries_enabled', FALSE),
  );

  $form['search_api_solr_extra_settings_logging']['search_api_solr_extra_settings_logging_responses_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log Solr responses'),
    '#default_value' => variable_get('search_api_solr_extra_settings_logging_responses_enabled', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Validate form submission.
 */
function search_api_solr_extra_settings_form_validate($form, &$form_state) {
   if (!is_numeric($form_state['values']['search_api_solr_extra_score_thresholding_threshold_value'])
       || $form_state['values']['search_api_solr_extra_score_thresholding_threshold_value'] == ''
       || $form_state['values']['search_api_solr_extra_score_thresholding_threshold_value'] < 0
       || $form_state['values']['search_api_solr_extra_score_thresholding_threshold_value'] > 100) {
    form_set_error('wrapper][options][search_api_solr_extra_score_thresholding_threshold_value', t('Invalid score threshold'));
   }
}

/**
 * Generates form to configure boosts per field.
 */
function search_api_solr_extra_boosts_settings_form() {

  // @TODO: Move it to settings page.
  $index             = search_api_index_load('ads_adverts');
  $fields            = $index->getFields();
  $job_search_fields = array();


  /**
   * Phrase based boosts
   */

  $form['search_api_solr_extra_boosts_phrase'] = array(
    '#type' => 'fieldset',
    '#title' => t('Phrase boosts'),
    '#weight' => 0,
  );

  $header = array(
    'name' => t('Boost name'),
    'type' => t('Type'),
    'boost' => t('Boost value'),
  );

  $rows = array();

  $phrase_fields = array();

  // Keyword in title

  $phrase_fields[] = array(
    'name' => t('Keywords in any field'),
    'type' => t('Single word'),
    'key' => 'search_api_solr_extra_boost_value_keywords_any_s',
  );

  $phrase_fields[] = array(
    'name' => t('Keywords in any field'),
    'type' => t('All words match'),
    'key' => 'search_api_solr_extra_boost_value_keywords_any_fm',
  );

  $phrase_fields[] = array(
    'name' => t('Keywords in title field'),
    'type' => t('Single word'),
    'key' => 'search_api_solr_extra_boost_value_keywords_t_s_nf',
  );

  $phrase_fields[] = array(
    'name' => t('Keywords in title field'),
    'type' => t('All words match'),
    'key' => 'search_api_solr_extra_boost_value_keywords_t_fm_nf',
  );


  foreach ($phrase_fields as $field) {

    $boost_value = number_format(variable_get($field['key'], '0.0'), 1, '.', '');

    $boost = array(
      '#type' => 'textfield',
      '#value' => $boost_value,
      '#size' => '3',
      '#name' => 'phrase_boosts[' . $field['key'] . ']',
      '#id' => 'phrase_boosts[' . $field['key'] . ']',
      '#attributes' => array('style' => 'text-align: right'),
    );

    $rows[] = array(
      'name' => $field['name'],
      'type' => $field['type'],
      'boost' => drupal_render($boost),
    );
  }

  $form['search_api_solr_extra_boosts_phrase']['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#weight' => 0,
  );


  /**
   * Generic boosts. Idexed ones.
   */

  $form['search_api_solr_extra_boosts_generic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Generic field boosts'),
    '#weight' => 1,
  );

  foreach ($fields as $key => $field) {
    $job_search_fields[$field['name']] = $field;
    $job_search_fields[$field['name']]['indexed_name'] = $key;
  }

  ksort($job_search_fields);

  $header = array(
    'name' => t('Field name'),
    'type' => t('Type'),
    'boost' => t('Boost value'),
    'indexed_name' => t('Field indexed name'),
  );

  $rows = array();

  foreach ($job_search_fields as $field) {

    $boost = array(
      '#type' => 'textfield',
      '#value' => number_format($field['boost'], 1, '.', ''),
      '#size' => '3',
      '#name' => 'generic_boosts[' . $field['indexed_name'] . ']',
      '#id' => 'generic_boosts[' . $field['indexed_name'] . ']',
      '#attributes' => array('style' => 'text-align: right'),
    );

    $rows[] = array(
      'name' => $field['name'],
      'type' => $field['type'],
      'boost' => drupal_render($boost),
      'indexed_name' => $field['indexed_name'],
    );
  }

  $form['search_api_solr_extra_boosts_generic']['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#prefix' => '<div>',
    '#suffix' => '<div>',
  );

  $form['search_api_solr_extra_bf_expressions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom filters'),
    '#weight' => 3,
  );

  $form['search_api_solr_extra_bf_expressions']['search_api_solr_extra_boost_expr_date'] = array(
    '#name' => 'search_api_solr_extra_boost_expr_date',
    '#title' => t('Date filter expression'),
    '#type' => 'textfield',
    '#size' => 60,
    '#weight' => 4,
    '#default_value' => variable_get('search_api_solr_extra_boost_expr_date', '')
  );

  $form['#submit'][] = 'search_api_solr_extra_boosts_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Implements hook_form_validate().
 */
function search_api_solr_extra_boosts_settings_form_validate($form, &$form_state) {

  foreach ($form_state['input']['phrase_boosts'] as $key => $value) {
    if (substr($key, 0, 27) == 'search_api_solr_extra_boost_value_') {
      if (!is_numeric($value) || $value < 0 || $value > 1000000) {
        drupal_set_message(t('Invalid value for one of the boosts "@value". Boost reverted to the previous value.', array('@value' => $value)), 'error');
        form_set_error('');
        return;
      }
    }
  }

  // @TODO: Move it to the settings page.
  $index  = search_api_index_load('ads_adverts', TRUE);
  $fields = $index->getFields();

  foreach ($form_state['input']['generic_boosts'] as $key => $value) {
    if (array_key_exists($key, $fields)) {
      if (!is_numeric($value) || $value < 0 || $value > 1000000) {
        drupal_set_message(t('Invalid value for one of the boosts "@value". Boost reverted to the previous value.', array('@value' => $value)), 'error');
        form_set_error('');
        return;
      }
    }
  }
}

/**
 * Implements hook_form_submit().
 */
function search_api_solr_extra_boosts_settings_form_submit($form, &$form_state) {

  foreach ($form_state['input'] as $key => $value) {
    if (strpos($key, 'search_api_solr_extra_boost_expr_') === 0) {
      variable_set($key, $value);
    }
  }

  foreach ($form_state['input']['phrase_boosts'] as $key => $value) {
    if ((is_numeric($value) && substr($key, 0, 38) == 'search_api_solr_extra_boost_value_')) {
      variable_set($key, (float)$value);
    }
  }

  // @TODO: Move it to the settings page.
  $index  = search_api_index_load('ads_adverts', TRUE);
  $fields = $index->getFields();

  foreach ($form_state['input']['generic_boosts'] as $key => $value) {
    if (array_key_exists($key, $fields)) {
      $fields[$key]['boost'] = (float)$value;
    }
  }

  $options = $index->options;
  $options['fields'] = $fields;
  $index->update(array('options' => $options));
}

/**
 * Rebuilds Solr's spellchecker data
 */
function search_api_solr_extra_rebuild_spellchecker_data($form, &$form_state) {

  // @TODO: Move it to settings page.
  $query = search_api_query('ads_adverts');

  $query->keys('__REBUILD_SPELLCHECK_DATA__');

  // Query will be caught in the search_api_solr_extra_search_api_solr_query_alter hook.
  $result = $query->execute();
}
