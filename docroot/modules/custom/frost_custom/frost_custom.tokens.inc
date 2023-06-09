<?php

/**
 * @file
 * Tokens for the frost_custom module.
 */

use Drupal\Core\Render\BubbleableMetadata;

/**
 * Implements hook_token_info_alter().
 */
function frost_custom_token_info_alter(&$info) {
  // Add referringId to entities that are referenced.
  $info['tokens']['media']['refId'] = [
    'name' => t('Referring entity ID'),
    'description' => t('The entity ID of the referencing parent'),
    'module' => 'frost_custom',
  ];
}

/**
 * Implements hook_tokens().
 */
function frost_custom_tokens($type, $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata) {
  $replacements = [];

  if ($type === 'entity') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'refId':
          // @todo Make this safer with conditions.
          $bubbleable_metadata->setCacheTags([])->setCacheMaxAge(0);
          $replacements[$original] = $data["entity"]->_referringItem->getParent()
            ->getParent()
            ->getEntity()
            ->id();

          break;
      }
    }
  }

  return $replacements;
}
