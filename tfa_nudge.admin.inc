<?php

function tfa_nudge_admin_settings_form($form, $form_state, $nid = 0){
  $form = array();
  $form['subject'] = array(
    '#title' => t('Subject Line'),
    '#descirption' => t('Default email subject line.'),
    '#type' => 'textfield',
    '#size' => '50',
    '#required' => TRUE,
  );
  $form['body'] = array(
    '#title' => t('Body Text'),
    '#descirption' => t('Default email body.'),
    '#type' => 'textarea',
    '#size' => '20',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}
