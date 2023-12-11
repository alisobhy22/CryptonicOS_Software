/**
 * @file
 * @brief Test program for the GetResource function in the operating system.
 *
 * This program tests the GetResource function, which allows tasks to acquire resources in the operating system.
 * It initializes resources and tasks with different configurations, activates them, and checks the behavior of the GetResource function.
 * The test program checks for expected outcomes and prints error messages if any issues are detected.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#include "../../Headers/APIs_Headers/Resources.h"
#include "../../Sources/APIs_Sources/Resources.c"
#include "../../Sources/APIs_Sources/Hooks.c"
#include "../../Sources/APIs_Sources/OsTasks.c"
#include <stdlib.h>
#include <stdio.h>

TaskType RunningTaskID = INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
struct Task *OsTasksPCB[MAX_TASKS];
struct Resource *OsResourcesPCB[MAX_RESOURCES];

int main()
{
    // Initialize resources
    struct Resource R0 = {0, 8, NULL, RESOURCE_STANDARD, INVALID_TASK, INVALID_RESOURCE};
    struct Resource R1 = {1, 8, NULL, RESOURCE_STANDARD, INVALID_TASK, INVALID_RESOURCE};
    struct Resource R2 = {MAX_RESOURCES, 5, NULL, RESOURCE_STANDARD, INVALID_TASK, INVALID_RESOURCE};
    struct Resource R3 = {3, 4, NULL, RESOURCE_STANDARD, INVALID_TASK, INVALID_RESOURCE};

    // Initialize OS resource PCB array
    OsResourcesPCB[0] = &R0;
    OsResourcesPCB[1] = &R1;
    OsResourcesPCB[2] = &R2;
    OsResourcesPCB[3] = &R3;

    // Initialize tasks for testing
    struct Task IDLE = {0, 0, IDLE_TASK, SUSPENDED, 0, 0, TASK_FULL, 0, 0, 200, 0};
    struct Task T0 = {0, 0, 0, WAITING, 5, 5, TASK_NON, 0, 0, 1, 1, 0, {0, 0, 0}, INVALID_RESOURCE, &(struct Resource[]){R0, R1}};
    struct Task T1 = {0, 0, 1, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 0, {0, 0, 0}, INVALID_RESOURCE, &(struct Resource[]){R2}};
    struct Task T2 = {0, 0, 2, SUSPENDED, 5, 5, TASK_NON, 0, 0, 1, 1, 0, {0, 0, 0}, INVALID_RESOURCE, &(struct Resource[]){R3}};
    struct Task T3 = {0, 0, MAX_TASKS, SUSPENDED, 5, 5, TASK_NON, 0, 0, 0, 0, 0, {0, 0, 0}, INVALID_RESOURCE, &(struct Resource[]){R0, R1, R2, R3}};
    struct Task T4 = {0, 0, 4, WAITING, 5, 5, TASK_NON, 0, 0, 1, 1, 0, {0, 0, 0}, INVALID_RESOURCE, &(struct Resource[]){R0, R1, R2, R3}};

    // Initialize OS task PCB array
    OsTasksPCB[IDLE_TASK] = &IDLE;
    OsTasksPCB[0] = &T0;
    OsTasksPCB[1] = &T1;
    OsTasksPCB[2] = &T2;
    OsTasksPCB[3] = &T3;
    OsTasksPCB[4] = &T4;

    StatusType st;

    // Activate IDLE task and T0 task
    OS_ActivateTask(IDLE.ID);
    OS_ActivateTask(T0.ID);

    // Test 1: GetResource for R0 and R1
    st = GetResource(R0.Res_ID);
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 1\n\n");
        exit(1);
    }
    if (T0.Priority != 8)
    {
        printf("Error Occurred in E_OK Test 2\n\n");
        exit(1);
    }
    if (T0.Last_Running_Resource != R0.Res_ID)
    {
        printf("Error Occurred in E_OK Test 3\n\n");
        exit(1);
    }
    if (R0.Resource_Owner != T0.ID)
    {
        printf("Error Occurred in E_OK Test 4\n\n");
        exit(1);
    }
    if (R0.Prev_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OK Test 5\n\n");
        exit(1);
    }
    st = GetResource(R1.Res_ID);
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 6\n\n");
        exit(1);
    }
    if (T0.Priority != 8)
    {
        printf("Error Occurred in E_OK Test 7\n\n");
        exit(1);
    }
    if (T0.Last_Running_Resource != R1.Res_ID)
    {
        printf("Error Occurred in E_OK Test 8\n\n");
        exit(1);
    }
    if (R1.Resource_Owner != T0.ID)
    {
        printf("Error Occurred in E_OK Test 9\n\n");
        exit(1);
    }
    if (R1.Prev_Resource != R0.Res_ID)
    {
        printf("Error Occurred in E_OK Test 10\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");

    //----------------------------
    // Terminate T0 task and activate T1 task
    OS_TerminateTask();
    OS_ActivateTask(T1.ID);

    // Test 2: GetResource for R2
    st = GetResource(R2.Res_ID);
    if (st != E_OS_ID)
    {
        printf("Error Occurred in E_OS_ID Test 1\n\n");
        exit(1);
    }
    if (T1.Priority != 5)
    {
        printf("Error Occurred in E_OS_ID Test 2\n\n");
        exit(1);
    }
    if (T1.Last_Running_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OS_ID Test 3\n\n");
        exit(1);
    }
    if (R2.Resource_Owner != INVALID_TASK)
    {
        printf("Error Occurred in E_OS_ID Test 4\n\n");
        exit(1);
    }
    if (R2.Prev_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OS_ID Test 5\n\n");
        exit(1);
    }

    printf("Test 2 Passed\n\n");

    //----------------------------
    // Terminate T1 task and activate T2 task
    OS_TerminateTask();
    OS_ActivateTask(T2.ID);

    // Test 3: GetResource for R1 and R3
    st = GetResource(R1.Res_ID);
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ACCESS Test 1\n\n");
        exit(1);
    }
    if (T2.Priority != 5)
    {
        printf("Error Occurred in E_OS_ACCESS Test 2\n\n");
        exit(1);
    }
    if (T2.Last_Running_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OS_ACCESS Test 3\n\n");
        exit(1);
    }
    if (R1.Resource_Owner != T0.ID)
    {
        printf("Error Occurred in E_OS_ACCESS Test 4\n\n");
        exit(1);
    }
    if (R1.Prev_Resource != R0.Res_ID)
    {
        printf("Error Occurred in E_OS_ACCESS Test 5\n\n");
        exit(1);
    }
    st = GetResource(R3.Res_ID);
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ACCESS Test 6\n\n");
        exit(1);
    }
    if (T2.Priority != 5)
    {
        printf("Error Occurred in E_OS_ACCESS Test 7\n\n");
        exit(1);
    }
    if (T2.Last_Running_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OS_ACCESS Test 8\n\n");
        exit(1);
    }
    if (R3.Resource_Owner != INVALID_TASK)
    {
        printf("Error Occurred in E_OS_ACCESS Test 9\n\n");
        exit(1);
    }
    if (R3.Prev_Resource != INVALID_RESOURCE)
    {
        printf("Error Occurred in E_OS_ACCESS Test 10\n\n");
        exit(1);
    }

    printf("Test 3 Passed\n\n");

    printf("All Tests Passed\n\n");

    return 0;
}
