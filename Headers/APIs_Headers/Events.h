/**
 * @file
 * @brief Event-related API declarations and macros.
 *
 * This file contains declarations for APIs related to events in the operating system.
 * Events are mechanisms for task synchronization and communication.
 * The APIs include operations such as setting, clearing, getting, and waiting for events.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_Events_H
#define Headers_APIs_Headers_Events_H

#include "Defines.h"

/**
 * @brief Sets the specified events for a given task.
 *
 * This function sets the events specified by the ActivatedEvents parameter for the task identified by TaskID.
 *
 * @param TaskID The ID of the task for which events should be set.
 * @param ActivatedEvents The bitmask representing the events to be set.
 * @return StatusType E_OK if successful, an error code otherwise.
 */
StatusType SetEvent(TaskType TaskID, EventMaskType ActivatedEvents);

/**
 * @brief Clears the specified events based on the provided mask.
 *
 * This function clears the events specified by the Mask parameter.
 *
 * @param Mask The bitmask representing the events to be cleared.
 * @return StatusType E_OK if successful, an error code otherwise.
 */
StatusType ClearEvent(EventMaskType Mask);

/**
 * @brief Gets the currently set events for a given task.
 *
 * This function retrieves the events currently set for the task identified by TaskID.
 *
 * @param TaskID The ID of the task for which events should be retrieved.
 * @param Event A reference to the variable where the retrieved events will be stored.
 * @return StatusType E_OK if successful, an error code otherwise.
 */
StatusType GetEvent(TaskType TaskID, EventMaskRefType Event);

/**
 * @brief Waits for the specified events to be set.
 *
 * This function causes the calling task to wait until the specified events are set.
 *
 * @param EventMask The bitmask representing the events to wait for.
 * @return StatusType E_OK if successful, an error code otherwise.
 */
StatusType WaitEvent(EventMaskType EventMask);

#endif
