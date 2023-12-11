/**
 * @file
 * @brief Configuration file for Resources in the Operating System.
 */

#ifndef Configurations_ResourceConfig_H
#define Configurations_ResourceConfig_H

/**
 * @def MAX_RESOURCES
 * @brief Maximum number of resources in the system.
 *
 * This macro defines the maximum number of resources that can be configured in the system.
 * Users can adjust this value based on their system requirements.
 */
#define MAX_RESOURCES 10 // 0-9

/**
 * @def RESOURCE_STANDARD
 * @brief Identifier for a Standard Resource.
 *
 * This macro represents the identifier for a standard resource type.
 * Standard resources are commonly used and can be configured in the system.
 */
#define RESOURCE_STANDARD 0

/**
 * @def RESOURCE_INTERNAL
 * @brief Identifier for an Internal Resource.
 *
 * This macro represents the identifier for an internal resource type.
 * Internal resources may have special characteristics or behavior in the system.
 */
#define RESOURCE_INTERNAL 1

/**
 * @def RESOURCE_LINKED
 * @brief Identifier for a Linked Resource.
 *
 * This macro represents the identifier for a linked resource type.
 * Linked resources may have dependencies or associations with other resources.
 */
#define RESOURCE_LINKED 2

#endif
