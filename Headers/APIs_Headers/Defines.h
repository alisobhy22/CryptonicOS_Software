/**
 * @file
 * @brief Defines and configurations for the operating system components.
 *
 * This file contains various defines, enumerations, and structures related to the
 * operating system components such as tasks, resources, events, and interrupts.
 * It also provides configurations for error codes, hooks, and other OS-related parameters.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_Defines_H
#define Headers_APIs_Headers_Defines_H

#include <stdint.h>
#include "../../Configurations/TaskConfig.h"
#include "../../Configurations/OSExecutionControlConfig.h"
#include "../../Configurations/ResourceConfig.h"
#include "../../Configurations/AlarmsConfig.h"

/**
 * @brief Represents an invalid task ID.
 */
#define INVALID_TASK MAX_TASKS

/**
 * @brief Task states: Running, Ready, Waiting, Suspended.
 */
#define RUNNING 1
#define READY 2
#define WAITING 3
#define SUSPENDED 4

/**
 * @brief Task preemption flags: Non-preemptive, Full preemption.
 */
#define TASK_NON 0
#define TASK_FULL 1

/**
 * @brief Error codes used in the operating system.
 */
#define E_OK 0
#define E_OS_ACCESS 1
#define E_OS_CALLEVEL 2
#define E_OS_ID 3
#define E_OS_LIMIT 4
#define E_OS_NOFUNC 5
#define E_OS_RESOURCE 6
#define E_OS_STATE 7
#define E_OS_VALUE 8

/**
 * @brief Task activation states: Start, Stop.
 */
#define START_F 0
#define START_T 1

/**
 * @brief Represents an invalid resource ID.
 */
#define INVALID_RESOURCE MAX_RESOURCES

/**
 * @brief Default application mode and invalid application mode.
 */
#define OSDEFAULTAPPMODE 0
#define INVALID_APPMODE 255

/**
 * @brief Hook identifiers.
 */
#define Errorhook 1
#define PreTaskhook 2
#define PostTaskhook 3
#define Startuphook 4
#define Shutdownhook 5
#define INVALID_HOOK 0

/**
 * @brief Macro to save CPU context.
 */
#define SAVECTX __asm volatile();

/**
 * @brief Macro to save the stack pointer.
 */
#define SAVESP __asm volatile();

/**
 * @brief Macro to load CPU context.
 */
#define LOADCTX __asm volatile();

/**
 * @brief Macro to load CPU context for the first time.
 */
#define LOADCTX_FIRST __asm volatile();

/**
 * @brief Context switch flags.
 */
#define CS_ON 1
#define CS_OFF 0

/**
 * @brief Type definition for StatusType.
 */
typedef uint8_t StatusType;

/**
 * @brief Type definition for TaskType.
 */
typedef uint8_t TaskType;

/**
 * @brief Type definition for TaskRefType.
 */
typedef uint8_t *TaskRefType;

/**
 * @brief Type definition for TaskStateType.
 */
typedef uint8_t TaskStateType;

/**
 * @brief Type definition for TaskStateRefType.
 */
typedef uint8_t *TaskStateRefType;

/**
 * @brief Type definition for EventMaskType.
 */
typedef uint64_t EventMaskType;

/**
 * @brief Type definition for EventMaskRefType.
 */
typedef uint64_t *EventMaskRefType;

/**
 * @brief Type definition for ResourceType.
 */
typedef uint8_t ResourceType;

/**
 * @brief Type definition for AppModeType.
 */
typedef uint8_t AppModeType;

/**
 * @brief Structure representing an Event.
 */
struct Event {
    uint64_t Configured_Events; // 64 bit configured events
    uint64_t Event_Waiting;     // 64 bit event id
    uint64_t Event_State;       // 64 bit event state
};

/**
 * @brief Structure representing a Resource.
 */
struct Resource {
    ResourceType Res_ID;
    uint8_t Ceiling_Priority;
    ResourceType *Linked_Resource;
    ResourceType Resource_Property;
    TaskType Resource_Owner;
    ResourceType Prev_Resource;
};

// ISRs

/**
 * @brief Represents an invalid ISR ID.
 */
#define INVALID_ISR 255

/**
 * @brief Types of ISR disable.
 */
#define ISR_Disable_Type_NoDisable 0
#define ISR_Disable_Type_DisableAll 1
#define ISR_Disable_Type_SuspendAll 2
#define ISR_Disable_Type_SuspendOS 3

/**
 * @brief Type definition for ISRType.
 */
typedef uint32_t ISRType;

/**
 * @brief Structure representing an ISR.
 */
struct ISR {
    ISRType ID;        // id of ISR
    uint8_t Priority;  // current priority of ISR
    ISRType Category;
    struct Resource *Needed_Resources[MAX_RESOURCES];
    ResourceType Prev_Resource;
};

#endif
