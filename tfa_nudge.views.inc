<?php

/**
 * @file
 * Views data declarations.
 */

/**
 * Implements hook_views_data().
 */
function tfa_nudge_views_data() {
  // Basic table and data information.
  $data['tfa_user_settings']['table']['group'] = t('Two-Factor Authentication');
  $data['tfa_user_settings']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Two-Factor Authentication user settings table'),
    'help' => t('Contains user settings for two factor authentication.'),
    'weight' => -10,
  );
  // Reference to the users table
  $data['tfa_user_settings']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Base field.
  $data['tfa_user_settings']['uid'] = array(
    'title' => t('TFA User Settings'),
    'help' => t('Two-Factor Authenication settings referencing a user.'),
    'relationship' => array(
      'base' => 'user', // The name of the table to join with.
      'base field' => 'uid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => t('Two-Factor Authentication User Settings'),
      'title' => t('Two-Factor Authentication User Settings'),
      'help' => t('TFA settings'),
    ),
  );

  // TFA Saved.
  $data['tfa_user_settings']['saved'] = array(
    'title' => t('Saved Date'),
    'help' => t('The date the tfa user settings were last saved.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // TFA Status
  $data['tfa_user_settings']['status'] = array(
    'title' => t('Two-Factor Security'),
    'help' => t('The status of the users two-factor authentication setup'),
    'field' => array(
      'handler' => 'tfa_nudge_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'tfa_nudge_handler_filter_boolean_operator',
      'label' => t('Two-Factor Security'),
      'type' => 'enabled-disabled',
      'use equal' => TRUE,
    )
  );

  return $data;
}
