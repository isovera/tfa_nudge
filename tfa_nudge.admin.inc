<?php

/**
 * @param $form
 *  TFA Nudge admin settings form.
 * @param $form_state
 *  TFA Nudge admin settings form state.
 * @return array
 *  Populated TFA Nudge admin settings form.
 */

function tfa_nudge_admin_settings_form($form, $form_state){
  $form = array();
  $defaults = variable_get('tfan_settings');
  $form['#tree'] = TRUE;
  $form['tfan_settings'] = array(
    '#title' => t('TFA Nudge Settings'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
  );
  $form['tfan_settings']['subject'] = array(
    '#title' => t('Subject Line'),
    '#type' => 'textfield',
    '#size' => '50',
    '#required' => TRUE,
    '#default_value' => (!empty($defaults['subject'])) ? $defaults['subject'] : 'Please enable TFA',
  );
  $form['tfan_settings']['body'] = array(
    '#title' => t('Body Text'),
    '#type' => 'textarea',
    '#size' => '20',
    '#required' => TRUE,
    '#default_value' => (!empty($defaults['body'])) ? $defaults['body'] : 'Please enable TFA',
  );
  $form['tfan_settings']['auto_emails'] = array(
    '#title' => t('Enable automated reminder emails'),
    '#description' => t('Select whether or not to enable automated TFA Nudge reminder emails'),
    '#type' => 'radios',
    '#default_value' => (!empty($defaults['auto_emails'])) ? $defaults['auto_emails'] : 'no',
    '#options' => array(
      'yes' => 'yes',
      'no' => 'no',
    ),
  );
  $form['tfan_settings']['get_notifications'] = array(
    '#title' => t('Enable notifications upon login'),
    '#description' => t('Select whether or not to enable automated TFA Nudge post-login notifications'),
    '#type' => 'radios',
    '#default_value' => (!empty($defaults['get_notifications'])) ? $defaults['get_notifications'] : 'no',
    '#options' => array(
      'yes' => 'yes',
      'no' => 'no',
    ),
  );
  $form['tfan_settings']['interval'] = array(
    '#title' => t('Reminder email interval'),
    '#description' => t('Enter an interval in days for sending reminder emails. The first round of emails will be sent the next time cron runs. All entries will be rounded down to whole numbers.'),
    '#type' => 'textfield',
    '#default_value' => (!empty($defaults['interval'])) ? $defaults['interval'] : '1',
    '#states' => array(
      'visible' => array(
        ':input[name="tfan_settings[auto_emails]"]' => array('value' => 'yes'),
      ),
    ),
  );
  $form['tfan_settings']['roles'] = array(
    '#title' => t('Specify Roles'),
    '#description' => t('Select the roles that should recieve automated reminder emails'),
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => user_roles(TRUE),
    '#default_value' => (!empty($defaults['roles'])),
    '#states' => array(
      'visible' => array(
        ':input[name="tfan_settings[auto_emails]"]' => array('value' => 'yes'),
      ),
    ),
  );
  return system_settings_form($form);
}

/**
 * TFA Nudge validation handler.
 */
function tfa_nudge_admin_settings_form_validate($form, &$form_state){
  $interval = $form_state['input']['tfan_settings']['interval'];
  if (isset($interval) && is_numeric($interval)) {
    // Round any decimals to a whole number
    $interval = intval($interval);
    if ($interval < 1) {
      // Since we aren't alowing for decimals, we also don't want to round down
      // to 0 as that would cause emails to be sent on every cron run
      $interval = 1;
    }
    $form_state['input']['tfan_settings']['interval'] = $interval;
  } else {
    form_set_error('interval', t('Please enter a valid email interval'));
  }
}
