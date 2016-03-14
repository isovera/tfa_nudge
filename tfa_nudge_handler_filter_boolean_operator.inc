<?php

/**
 * @file
 * Definition of tfa_nudge_handler_filter_boolean_operator.
 */
class tfa_nudge_handler_filter_boolean_operator extends views_handler_filter_boolean_operator {
  // Accept NULL as a false value
  var $accept_null = TRUE;
}
