/**
 * @file
 * @brief Declarations of hooks used in the operating system.
 *
 * This file contains declarations for various hooks that can be implemented in the operating system.
 * Hooks are functions that are called at specific points in the execution of the operating system.
 * Each hook serves a specific purpose and can be customized based on system requirements.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_Hooks_H
#define Headers_APIs_Headers_Hooks_H

#include "Defines.h"

/**
 * @brief Error hook function.
 *
 * This hook is called when functions return StatusType other than E_OK.
 * It is also triggered on events such as alarm expiration, failed task activation, and failed event setting.
 *
 * @param Error The error code indicating the cause of the hook invocation.
 */
void ErrorHook(StatusType Error);

/**
 * @brief Pre-task hook function.
 *
 * This hook is called after a new task moves to the running state.
 * It is specifically intended for new tasks.
 */
void PreTaskHook(void);

/**
 * @brief Post-task hook function.
 *
 * This hook is called before a finished task moves out of the running state.
 */
void PostTaskHook(void);

/**
 * @brief Startup hook function.
 *
 * This hook is called at the end of the system initialization, just before scheduling begins.
 */
void StartupHook(void);

/**
 * @brief Shutdown hook function.
 *
 * This hook is called during the system shutdown process.
 *
 * @param Error The error code indicating the cause of the shutdown.
 */
void ShutdownHook(StatusType Error);

#endif
