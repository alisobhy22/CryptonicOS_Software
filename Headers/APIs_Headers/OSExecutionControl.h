/**
 * @file
 * @brief Declarations for operating system execution control functions.
 *
 * This file contains declarations for functions related to the execution control of the operating system.
 * The functions include obtaining the active application mode, starting the operating system, and shutting it down.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_OSExecutionControl_H
#define Headers_APIs_Headers_OSExecutionControl_H

#include "Defines.h"

/**
 * @brief Get the active application mode.
 *
 * This function retrieves the currently active application mode.
 *
 * @return The active application mode.
 */
AppModeType GetActiveApplicationMode(void);

/**
 * @brief Start the operating system.
 *
 * This function initiates the execution of the operating system in a specified application mode.
 *
 * @param Mode The application mode in which the operating system should start.
 */
void StartOS(AppModeType Mode);

/**
 * @brief Shut down the operating system.
 *
 * This function shuts down the operating system and handles any associated errors.
 *
 * @param Error The status type indicating any error that occurred during shutdown.
 */
void ShutDownOS(StatusType Error);

#endif
