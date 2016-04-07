<?php

function tfa_nudge_admin_settings_form($form, $form_state, $nid = 0){
  $form = array();
  $form['subject'] = array(
    '#title' => t('Subject Line'),
    '#descirption' => t('Default email subject line.'),
    '#type' => 'textfield',
    '#size' => '50',
    '#required' => TRUE,
    '#default_value' => variable_get('subject', 'You have not yet enabled TFA'),
  );
  $form['body'] = array(
    '#title' => t('Body Text'),
    '#descirption' => t('Default email body.'),
    '#type' => 'textarea',
    '#size' => '20',
    '#default_value' => variable_get('body', 'Dear [user:name],
    You have not yet enabled TFA! Please do so in the interest of our site\'s security.  ---[site:name] team'),
  );

  return system_settings_form($form);
}
