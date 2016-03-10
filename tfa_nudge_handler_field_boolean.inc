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
      $lock_icon = array(
        '#title' => 'TFA enabled',
        '#alt' => 'TFA enabled',
        '#path' => '/images/lock_icon.svg'
      );
      if(user_access('access user profiles', $user)) {
        $lock_icon = l($lock_icon, "user/$values->uid/security/tfa", array('attributes'=>array('title'=>'Two-factor authentication enabled'), 'html'=>TRUE));
      }
      return $value ? $lock_icon : NULL;
    }

    if ($this->options['type'] == 'warning-icon') {
      global $user;
      $warning_icon = array(
        '#title' => 'TFA not enabled',
        '#alt' => 'TFA not enabled',
        '#path' => '/images/warning_icon.svg'
      );
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
