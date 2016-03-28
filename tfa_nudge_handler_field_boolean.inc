<?php

class tfa_nudge_handler_field_boolean extends views_handler_field_boolean {

  function init(&$view, &$options) {
    parent::init($view, $options);

    $default_formats = array(
      'lock-icon' => array(t('Lock icon')),
      'warning-icon' => array(t('Warning icon')),
      'yes-no' => array(t('Yes'), t('No')),
      'true-false' => array(t('True'), t('False')),
      'on-off' => array(t('On'), t('Off')),
      'enabled-disabled' => array(t('Enabled'), t('Disabled')),
      'boolean' => array(1, 0),
      'unicode-yes-no' => array('✔', '✖'),
    );
    $output_formats = isset($this->definition['output formats']) ? $this->definition['output formats'] : array();
    $custom_format = array('custom' => array(t('Custom')));
    $this->formats = array_merge($default_formats, $output_formats, $custom_format);
  }

  function render($values) {
    $value = $this->get_value($values);
    if (!empty($this->options['not'])) {
      $value = !$value;
    }

    if ($this->options['type'] == 'lock-icon') {
      global $user;
      $lock_icon = array(
        '#title' => 'TFA enabled',
        '#theme' => 'image',
        '#alt' => 'TFA enabled',
        '#path' => drupal_get_path('module', 'tfa_nudge') . '/images/lock_icon.svg',
      );
      if(user_access('access user profiles', $user)) {
        $lock_icon = drupal_render($lock_icon);
        $lock_icon = l($lock_icon, "user/$values->uid/security/tfa", array('attributes'=>array('title'=>'Two-factor authentication enabled'), 'html'=>TRUE));
      }
      return $value ? $lock_icon : NULL;
    }

    if ($this->options['type'] == 'warning-icon') {
      global $user;
      $warning_icon = array(
        '#title' => 'TFA not enabled',
        '#theme' => 'image',
        '#alt' => 'TFA not enabled',
        '#path' => drupal_get_path('module', 'tfa_nudge') . '/images/warning_icon.svg',
      );
      if(user_access('access user profiles', $user)) {
        $warning_icon = drupal_render($warning_icon);
        $warning_icon = l($warning_icon, "user/$values->uid/security/tfa", array('attributes'=>array('title'=>'Two-factor authentication not enabled'), 'html'=>TRUE));
      }
      return $value ? NULL : $warning_icon;
    }
    if ($this->options['type'] == 'custom') {
      return $value ? filter_xss_admin($this->options['type_custom_true']) : filter_xss_admin($this->options['type_custom_false']);
    }
    else if (isset($this->formats[$this->options['type']])) {
      return $value ? $this->formats[$this->options['type']][0] : $this->formats[$this->options['type']][1];
    }
    else {
      return $value ? $this->formats['yes-no'][0] : $this->formats['yes-no'][1];
    }
  }
}
