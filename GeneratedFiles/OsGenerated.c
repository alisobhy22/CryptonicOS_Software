/**
 * @file
 * @brief Initialization and configuration for the generated operating system components.
 *
 * This file contains the initialization function and configuration data structures
 * for the generated operating system components based on the provided specifications.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#ifndef Generated
#define Generated


#include <stdio.h>



#include "OsGenerated.h"

/**
 * @brief Initialize and configure the operating system components.
 *
 * This function initializes and configures the operating system components, including
 * tasks, resources, and other necessary parameters based on the specified requirements.
 */
void Init(){


 RunningTaskID=INVALID_TASK;
 PreTaskID = INVALID_TASK;
 Active_Hooks = INVALID_HOOK;
 Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
 ISR_Suspend_Counter = 0;
 Running_ISR_Count = 0;

struct Resource resource0={
    .Res_ID = 0,
    .Ceiling_Priority = 7,
    .Linked_Resource = 0,
    .Resource_Property = 0,
    .Resource_Owner = INVALID_TASK,
    .Prev_Resource = INVALID_RESOURCE
};

struct Resource resource1={
    .Res_ID = 1,
    .Ceiling_Priority = 5,
    .Linked_Resource = 0,
    .Resource_Property = 0,
    .Resource_Owner = INVALID_TASK,
    .Prev_Resource = INVALID_RESOURCE
};



OsResourcesPCB[0]=&resource0;
OsResourcesPCB[1]=&resource1;



struct Task task0 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task1Func,
    .current_pc = &Task1Func,
    .ID = 0,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 4,
    .Priority = 4,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event1 | Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};
task0.stack[99] = (uint32_t) task0.current_pc;

struct Task task1 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task2Func,
    .current_pc = &Task2Func,
    .ID = 1,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 6,
    .Priority = 6,
    .F_PREEM = TASK_NON,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 0,
    .EventMask = { (Event1 | Event2 | Event3),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};
task1.stack[99] = (uint32_t) task1.current_pc;


struct Task task2 = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Task3Func,
    .current_pc = &Task3Func,
    .ID = 2,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 1,
    .Priority = 1,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event3|Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};
task2.stack[99] = (uint32_t) task2.current_pc;




struct Task TRNG_Task = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &TRNG,
    .current_pc = &TRNG,
    .ID = 3,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 5,
    .Priority = 5,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event3|Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};
TRNG_Task.stack[99] = (uint32_t) TRNG_Task.current_pc;

struct Task Encrypt_Decrypt_Task = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &Encrypt_Decrypt,
    .current_pc = &Encrypt_Decrypt,
    .ID = 4,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 10,
    .Priority = 10,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 1,
    .Reasourses_Occupied = 0,
    .Extended = 1,
    .EventMask = { (Event3|Event2),0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { &resource0,&resource1 }
};
Encrypt_Decrypt_Task.stack[99] = (uint32_t) Encrypt_Decrypt_Task.current_pc;

struct Task idle = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &IdleFunc ,
    .current_pc = &IdleFunc,
    .ID = IDLE_TASK,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 0,
    .Priority = 0,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 200,
    .Reasourses_Occupied = 0,
    .Extended = 0,
    .EventMask = {0,0 , 0},
};
idle.stack[99] = (uint32_t) idle.current_pc;
OsTasksPCB[0]=&task0;
OsTasksPCB[1]=&task1;
OsTasksPCB[2]=&task2;
OsTasksPCB[3]=&TRNG_Task;
OsTasksPCB[4]=&Encrypt_Decrypt_Task;
OsTasksPCB[IDLE_TASK]=&idle;

}


#endif