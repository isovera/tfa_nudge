<?php

class tfa_nudge_handler_field_boolean extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['type'] = array('default' => 'lock-icon');
    $options['type_custom_true'] = array('default' => '', 'translatable' => TRUE);
    $options['type_custom_false'] = array('default' => '', 'translatable' => TRUE);
    $options['not'] = array('definition bool' => 'reverse');

    return $options;
  }

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

  function options_form(&$form, &$form_state) {
    foreach ($this->formats as $key => $item) {
      $options[$key] = implode('/', $item);
    }

    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Output format'),
      '#options' => $options,
      '#default_value' => $this->options['type'],
    );

    $form['type_custom_true'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom output for TRUE'),
      '#default_value' => $this->options['type_custom_true'],
      '#states' => array(
        'visible' => array(
          'select[name="options[type]"]' => array('value' => 'custom'),
        ),
      ),
    );

    $form['type_custom_false'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom output for FALSE'),
      '#default_value' => $this->options['type_custom_false'],
      '#states' => array(
        'visible' => array(
          'select[name="options[type]"]' => array('value' => 'custom'),
        ),
      ),
    );

    $form['not'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reverse'),
      '#description' => t('If checked, true will be displayed as false.'),
      '#default_value' => $this->options['not'],
    );
    parent::options_form($form, $form_state);
  }

  function render($values) {
    $value = $this->get_value($values);
    if (!empty($this->options['not'])) {
      $value = !$value;
    }

    if ($this->options['type'] == 'lock-icon') {
      global $user;
      $lock_icon = '<svg width="16" height="16" viewBox="0 0 220 220" xmlns="http://www.w3.org/2000/svg"><title>TFA enabled</title><path d="M40 100c0-5.523 4.484-10 10.002-10h-2.504 125.005-2.505C175.522 90 180 94.485 180 100v100c0 5.523-4.48 10-9.998 10H49.998C44.476 210 40 205.515 40 200V100z" stroke="#9B9B9B" stroke-width="20" fill="#D8D8D8"/><path d="M60 68s0-58 50-58 50 58 50 58v22h-22V68s2-36-28-36-28 36-28 36v22H60V68z" fill="#9B9B9B"/></svg>';
      if(user_access('access user profiles', $user)) {
        $lock_icon = l($lock_icon, "user/$values->uid/security/tfa", array('attributes'=>array('title'=>'Two-factor authentication enabled'), 'html'=>TRUE));
      }
      return $value ? $lock_icon : NULL;
    }

    if ($this->options['type'] == 'warning-icon') {
      global $user;
      $warning_icon = '&#x26a0;';
      if(user_access('access user profiles', $user)) {
        $lock_icon = l($warning_icon, "user/$values->uid/security/tfa", array('attributes'=>array('title'=>'Two-factor authentication not enabled'), 'html'=>TRUE));
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
