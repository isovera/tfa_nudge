<?php

function tfa_nudge_settings($nid, $subject, $body){
  $value = array(
    'nid' => $nid,
    'subject' => $subject,
    'body' => $body,
  );

  drupal_write_record('tfa_nudge', $value);
}

function tfa_nudge_admin_settings_form(){
  $form = array();
  $form['tfan_email_subject'] = array(
    '#title' => t('Subject Line'),
    '#descirption' => t('TFAN Subject Line'),
    '#type' => 'textfield',
    '#size' => '50',
  );
  $form['tfan_email_body'] = array(
    '#title' => t('Body Text'),
    '#descirption' => t('TFAN Body'),
    '#type' => 'textarea',
    '#size' => '20',
  );

  return system_settings_form($form);
}
