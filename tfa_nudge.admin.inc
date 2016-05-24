<?php

function tfa_nudge_admin_settings_form($form, $form_state){
  $form = array();
  $form['tfan_reminder_email_subject'] = array(
    '#title' => t('Subject Line'),
    '#descirption' => t('Default email subject line.'),
    '#type' => 'textfield',
    '#size' => '50',
    '#required' => TRUE,
    '#default_value' => variable_get('tfan_reminder_email_subject', 'You have not yet enabled two factor authentication on [site:name]'),
  );
  $form['tfan_reminder_email_body'] = array(
    '#title' => t('Body Text'),
    '#descirption' => t('Default email body.'),
    '#type' => 'textarea',
    '#size' => '20',
    '#required' => TRUE,
    '#default_value' => variable_get('tfan_reminder_email_body', 'Dear [user:name],' . "\r\n" . 'You have not yet enabled TFA! Please do so in the interest of [site:name] security.'),
  );
  $form['tokens'] = array(
    '#theme' => 'token_tree_link',
    '#token_types' => array('user'),
    '#global_types' => TRUE,
    '#click_insert' => TRUE,
  );
  return system_settings_form($form);
}

