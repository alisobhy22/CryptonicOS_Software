/**
 * @file
 * @brief Global variables and structures used in the operating system.
 *
 * This file contains declarations for global variables and structures that are used throughout the operating system.
 * These include PCBs (Process Control Blocks), counters, and other essential elements for OS functionality.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_Globels_H
#define Headers_APIs_Headers_Globels_H

#include "Defines.h"
#include "../../Configurations/ISRConfig.h"
#include <stdint.h>

// Tasks Things
extern struct Task* OsTasksPCB[MAX_TASKS]; ///< Array holding PCBs (Process Control Blocks) for tasks.
extern struct ISR* ISRPCB[MAX_ISRs]; ///< Array holding PCBs for interrupts.
extern uint8_t Active_Hooks; ///< Variable indicating the active hooks.
extern TaskType RunningTaskID; ///< ID of the currently running task.
extern ISRType Running_ISR_ID; ///< ID of the currently running interrupt.
extern ISRType Running_ISR_Count; ///< Counter for the running interrupts.
extern ISRType Active_ISR_Disable_Type; ///< Type of active interrupt disable.
extern uint8_t ISR_Suspend_Counter; ///< Counter for suspended interrupts.

extern TaskType PreTaskID; ///< ID of the previously running task.
extern uint8_t Queue_Size; ///< Size of the ready queue.

extern struct Ready_List Ready_Queue; ///< Ready queue containing tasks ready to execute.
extern struct Ready_Entry Ready_Entries[MAX_TASKS]; ///< Array holding entries for the ready list.

// OS Execution Control Things
extern AppModeType ActiveAppMode; ///< Active application mode.

// Resource Things
extern struct Resource *OsResourcesPCB[MAX_RESOURCES]; ///< Array holding PCBs for resources.

#endif
