#ifndef Configurations_TaskConfig_H
#define Configurations_TaskConfig_H

#define MAX_TASKS 200 //IDS = 0-199

#define IDLE_TASK MAX_TASKS-1

/**
 * @brief The highest priority a task can get.
 */
#define TASK_MAX_PRIO_NUM 5

/**
 * @brief The  lowest  priority a task can get.
 */
#define TASK_MIN_PRIO_NUM 0

/**
 * @brief The  number of tasks that share the same prio
 */
#define MAX_TASK_PER_PRIO 3

#define MAX_EVENTS 5
#endif
