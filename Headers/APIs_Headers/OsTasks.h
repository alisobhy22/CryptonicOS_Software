/**
 * @file
 * @brief Declarations for operating system task management functions.
 *
 * This file contains declarations for functions related to managing tasks in the operating system.
 * The functions include activating a task, terminating the current task, scheduling tasks, inserting a new task,
 * deleting a task, and sorting tasks by priority.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Headers_APIs_Headers_OsTasks_H
#define Headers_APIs_Headers_OsTasks_H

#include "Defines.h"

/**
 * @brief Activate a task.
 *
 * This function changes a task from the suspended state to the ready state.
 *
 * @param[in] TaskID The ID of the task to be activated.
 */
void OS_ActivateTask(TaskType TaskID);

/**
 * @brief Terminate the current task.
 *
 * This function makes the currently running task transition from running to the suspended state.
 */
void OS_TerminateTask(void);

/**
 * @brief Schedule tasks.
 *
 * This function triggers the scheduling mechanism of the operating system.
 */
void OS_Schedule(void);

/**
 * @brief Insert a new task.
 *
 * This function inserts a new task into the system.
 *
 * @param[in] newTask Pointer to the structure representing the new task.
 */
void OS_Insert(struct Task* newTask);

/**
 * @brief Delete a task.
 *
 * This function deletes a task identified by its ID.
 *
 * @param[in] TaskID The ID of the task to be deleted.
 */
void OS_Delete(TaskType TaskID);

/**
 * @brief Sort tasks by priority.
 *
 * This function organizes tasks in the system based on their priority levels.
 */
void OS_SortByPriority(void);

#endif
