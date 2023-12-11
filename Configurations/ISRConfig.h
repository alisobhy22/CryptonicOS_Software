/**
 * @file
 * @brief Configuration file for Interrupt Service Routines (ISRs).
 */

#ifndef Configurations_ISRConfig_H
#define Configurations_ISRConfig_H

/**
 * @def ISR_CAT_1
 * @brief Category 1 Interrupt Service Routine.
 *
 * Category 1 ISRs are synchronous and non-reentrant.
 */
#define ISR_CAT_1 1

/**
 * @def ISR_CAT_2
 * @brief Category 2 Interrupt Service Routine.
 *
 * Category 2 ISRs are asynchronous and reentrant.
 */
#define ISR_CAT_2 2

/**
 * @def MAX_ISRs
 * @brief Maximum number of supported Interrupt Service Routines.
 *
 * This defines the maximum number of ISRs that can be configured in the system.
 */
#define MAX_ISRs 85

#endif
