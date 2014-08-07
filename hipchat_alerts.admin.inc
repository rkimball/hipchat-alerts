<?php
/**
 * @file
 * Admin config pages
 * @author rkimball
 * @package hipchat_alerts
 * @version 0.0.1
 */

/**
 * Implements hook_form()
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hipchat_alerts_config_form($form, &$form_state) {

	$form['header'] = array(
		'#markup' => '<div style="padding:10px;border:1px solid #BEBFB9;margin-bottom:10px;"><p>The HipChat Alerts module allows Drupal to publish certain alerts to a HipChat room using the v1 API. This module requires a <a href="http://hipchat.com/account/api">HipChat API Key</a>. </p></div>',
	);

	$form['hipchat_api_version'] = array(
		'#type' => 'radios',
		'#title' => t('API Version'),
		'#description' => t('Please select which version of the HipChat API your lobby will use.'),
		'#default_value' => variable_get('hipchat_api_version', null),
		'#required' => TRUE,
		'#options' => array(
			t('v1'),
			t('v2'),
		),

	);

	$form['v1'] = array(
		'#type' => 'fieldset',
		'#states' => array(
			'visible' => array(
				':input[name="hipchat_api_version"]' => array('value' => 0),
			),
		),
	);

	$form['v1']['header'] = array(
		'#markup' => '<h2>HipChat API v1 Settings</h2>',
	);

	$form['v1']['hipchat_v1_api_token'] = array(
		'#type' => 'textfield',
		'#title' => t('API Token'),
		'#description' => t('To generate a HipChat API v1 token, you will need to be a group administrator'),
		'#default_value' => variable_get('hipchat_v1_api_token',''), // fe2e7baec2d954125ce22937ff4c4a
		'#size' => 60,
		'#maxlength' => 128,
		'#required' => FALSE,
	);


	$form['v2'] = array(
		'#type' => 'fieldset',
		'#states' => array(
			'visible' => array(
				':input[name="hipchat_api_version"]' => array('value' => 1),
			),
		),
	);

	$form['v2']['header'] = array(
		'#markup' => '<h2>HipChat API v2 Settings</h2> HipChat API v2 is not yet supported.',
	);

	$form['v2']['hipchat_v2_api_token'] = array(
		'#type' => 'textfield',
		'#title' => t('OAuth2 Token'),
		'#default_value' => variable_get('hipchat_v2_api_token',''),
		'#size' => 60,
		'#maxlength' => 128,
		'#required' => FALSE,
		'#disabled' => TRUE,
	);

	$form['v2']['hipchat_v2_api_key'] = array(
		'#type' => 'textfield',
		'#title' => t('OAuth2 Key'),
		'#default_value' => variable_get('hipchat_v2_api_key',''),
		'#size' => 60,
		'#maxlength' => 128,
		'#required' => FALSE,
		'#disabled' => TRUE,
	);

	$form['v2']['hipchat_v2_api_secret'] = array(
		'#type' => 'textfield',
		'#title' => t('OAuth2 Secret'),
		'#default_value' => variable_get('hipchat_v2_api_secret',''),
		'#size' => 60,
		'#maxlength' => 128,
		'#required' => FALSE,
		'#disabled' => TRUE,
	);

	$form['hipchat_room_id'] = array(
		'#type' => 'textfield',
		'#title' => t('Room ID'),
		'#default_value' => variable_get('hipchat_room_id',''),
		'#size' => 25,
		'#required' => TRUE,
		'#description' => t('All notifications sent from this module will be posted in this room.'),
	);

	$form['site_environment'] = array(
		'#type' => 'checkbox',
		'#title' => 'Development environment?',
		'#description' => t('HipChat Alerts will not send messages if this is checked. Alerts are only relevant from production environments.'),
		'#default_value' => variable_get('site_environment',null),
	);

	return system_settings_form($form);
}

function hipchat_alerts_config_info($apivers,$token,$room) {

	if(variable_get('site_environment') == 1) {
		drupal_set_message(t('The site environment is currently set to development. HipChat Alerts will not send any messages.'),'warning');
	}

	$content = '';
	$form = array();

	if(!is_null($apivers)) {

		$content .= '<h2>Group Users</h2>';
		$content .= hipchat_users();

		// test message
		$sender = 'HC-Alert';
		$msg = 'HipChat Alert System Test';

		$form['hipchat_test'] = array(
			'#type' => 'button',
			'#name' => 'Send a Test',
			'#value' => t('Send a Test'),
//			'#ajax' => array(
//				'callback' => hipchat_message($sender,$msg),
//				'wrapper' => 'test-wrapper',
//				'effect' => 'fade',
//			),
		);

//		hipchat_message($sender, $msg);

	} else {
		drupal_set_message(t('HipChat Alerts has not yet been configured. Please provide your API Key.'), 'error');
	}

	return $content;
	return system_settings_form($form);
}