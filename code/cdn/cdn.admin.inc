<?php
// $Id$

/**
 * @file
 * Settings administration UI.
 */


//----------------------------------------------------------------------------
// Form API callbacks.

/**
 * Form definition; settings.
 */
function cdn_admin_settings_form() {
  $form['settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Settings'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );

  $form['settings'][CDN_STATUS_VARIABLE] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#description' => t(
      "If you don't want to use the CDN to serve files to your visitors yet,
      but you do want to see if it's working well for your site, then enable
      debug mode.<br />It will only serve files from the CDN if they have the
      %cdn-debug-mode-permission permission.",
      array('%cdn-debug-mode-permission' => 'access files on CDN when in debug mode')
    ),
    '#options' => array(
      CDN_DISABLED => t('Disabled'),
      CDN_ENABLED  => t('Enabled'),
      CDN_DEBUG    => t('Debug'),
    ),
    '#default_value' => variable_get(CDN_STATUS_VARIABLE, CDN_DISABLED),
  );

  $form['settings'][CDN_MODE_VARIABLE] = array(
    '#type' => 'radios',
    '#title' => t('Mode'),
    '#description' => t(
      "<strong>Basic mode</strong> will simply prepend another URL to the
      complete file URL. Therefor, it only works for CDNs that support the
      Origin Pull technique.<br />
      <strong>Advanced mode</strong> uses the daemon to synchronize files and
      can be used with both Origin Pull and Push CDNs. If you've got an Origin
      Pull CDN and want to process files before they're synced to the CDN, it
      is also recommended to use this mode."
    ),
    '#options' => array(
      CDN_MODE_BASIC    => t('Basic'),
      CDN_MODE_ADVANCED => t('Advanced'),
    ),
    '#default_value' => variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC),
  );


  $form['basic'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Settings for basic mode'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['basic'][CDN_BASIC_URL_VARIABLE] = array(
    '#type'          => 'textfield',
    '#title'         => t('CDN URL'),
    '#description'   => t('The CDN URL prefix that should be used. Only works
                         for CDNs that support Origin Pull.'),
    '#default_value' => variable_get(CDN_BASIC_URL_VARIABLE, ''),
  );
  
  $form['basic'][CDN_BASIC_EXTENSIONS_VARIABLE] = array(
    '#type'          => 'textfield',
    '#title'         => t('Allowed extensions'),
    '#description'   => t('Only files with these extensions will be synced.'),
    '#default_value' => variable_get(CDN_BASIC_EXTENSIONS_VARIABLE, CDN_BASIC_EXTENSIONS_DEFAULT),
  );


  $form['advanced'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Settings for advanced mode'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );
  
  $form['advanced'][CDN_ADVANCED_SYNCED_FILES_DB_VARIABLE] = array(
    '#type' => 'textfield',
    '#title' => t('Synced files database'),
    '#description' => t('Enter the full path to the daemon\'s synced files database file.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => variable_get(CDN_ADVANCED_SYNCED_FILES_DB_VARIABLE, ''),
  );


  $form['other'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Other settings'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['other'][CDN_STATS_VARIABLE] = array(
    '#type' => 'radios',
    '#title' => t('Show statistics for the current page'),
    '#description' => t(
      'Shows the CDN integration statistics of the current page, to users with
      the %access-per-page-statistics permission.',
      array('%access-per-page-statistics' => 'access per-page statistics')
    ),
    '#options' => array(
      CDN_DISABLED => t('Disabled'),
      CDN_ENABLED  => t('Enabled'),
    ),
    '#default_value' => variable_get(CDN_STATS_VARIABLE, CDN_DISABLED),
  );

  return system_settings_form($form);
}