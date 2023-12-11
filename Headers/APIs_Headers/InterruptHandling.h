/**
 * @file
 * @brief Declarations for interrupt handling functions.
 *
 * This file contains declarations for functions related to interrupt handling in the operating system.
 * The functions provide capabilities to enable, disable, suspend, and resume interrupts at different levels.
 * Additionally, there's a function to check if there are pending interrupts.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_InterruptHandling_H
#define Headers_APIs_Headers_InterruptHandling_H

#include "Defines.h"
#include <stdbool.h>

/**
 * @brief Enable all interrupts.
 *
 * This function enables all interrupts globally.
 */
void EnableAllInterrupts(void);

/**
 * @brief Disable all interrupts.
 *
 * This function disables all interrupts globally.
 */
void DisableAllInterrupts(void);

/**
 * @brief Resume all interrupts.
 *
 * This function resumes all interrupts globally.
 */
void ResumeAllInterrupts(void);

/**
 * @brief Suspend all interrupts.
 *
 * This function suspends all interrupts globally.
 */
void SuspendAllInterrupts(void);

/**
 * @brief Resume OS interrupts.
 *
 * This function resumes operating system-related interrupts.
 */
void ResumeOSInterrupts(void);

/**
 * @brief Suspend OS interrupts.
 *
 * This function suspends operating system-related interrupts.
 */
void SuspendOSInterrupts(void);

/**
 * @brief Check for pending interrupts.
 *
 * This function checks if there are any pending interrupts.
 *
 * @return true if there are pending interrupts, false otherwise.
 */
bool CheckPending(void);

#endif
