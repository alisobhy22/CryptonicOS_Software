#ifndef Headers_APIs_Headers_Tasks_H
#define Headers_APIs_Headers_Tasks_H


#include "Defines.h"

/**
 * @brief User function changes a task from suspended to ready state
 *
 * This user function takes a task ID and changes a task from suspended to ready state.
 *
 * @param[in] TaskID The ID of the Task
 *
 * @return the error massege
 */
StatusType ActivateTask(TaskType TaskID);

/**
 * @brief User function changes a task from running to suspended state
 *
 * This user function makes the current running task changes from running to suspended state.
 *
 * @return the error massege
 */
StatusType TerminateTask(void); 

/**
 * @brief User function  terminates the current task and activate another in a chain
 *
 * This user function makes the current running task terminated while activating the task with the ID TaskID.
 *
 * @param[in] TaskID The ID of the Task
 *
 * @return the error massege
 */
StatusType ChainTask(TaskType TaskID);

/**
 * @brief User function schedules the tasks
 *
 * @return the error massege
 */
StatusType Schedule(void);

/**
 * @brief User function returns the information about the TaskID of the task which is currently running
 *
 * @return the error massege
 */
StatusType GetTaskID(TaskRefType TaskID);

/**
 * @brief User function returns the state of a taskat the time of calling GetTaskState.
 *
 * @return the error massege
 */
StatusType GetTaskState(TaskType TaskID, TaskStateRefType State);


#endif
