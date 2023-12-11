/**
 * @file
 * @brief Test program for the WaitEvent function in the operating system.
 *
 * This program tests the WaitEvent function, which allows tasks to wait for specific events in the operating system.
 * It initializes tasks with different configurations, activates them, and checks the behavior of the WaitEvent function.
 * The test program checks for expected outcomes and prints error messages if any issues are detected.
 *
 * @author Your Name
 * @date YYYY-MM-DD HH:MM:SS
 */

#include "../../Sources/APIs_Sources/Events.c"
#include "../../Sources/APIs_Sources/OsTasks.c"
#include "../../Sources/APIs_Sources/Hooks.c"
#include "../../Headers/APIs_Headers/Events.h"
#include <stdlib.h>
#include <stdio.h>

TaskType RunningTaskID = INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
struct Task *OsTasksPCB[MAX_TASKS];

int main()
{
    // Initialize event mask and wait mask
    struct Event EventMask = {0b11111, 0, 0};
    EventMaskType WaitMask = 0b01010;

    // Define tasks for testing
    struct Task T0 = {0, 0, 0, WAITING, 3, 3, TASK_FULL, 0, 0, 1, 3, 1, EventMask}; // normal extended task with resources
    struct Task T1 = {0, 0, 1, WAITING, 4, 4, TASK_FULL, 0, 0, 1, 0, 0, EventMask}; // not extended task
    struct Task T2 = {0, 0, 2, WAITING, 5, 5, TASK_FULL, 0, 0, 1, 0, 1, EventMask}; // normal extended task
    struct Task IDLE = {0, 0, IDLE_TASK, SUSPENDED, 0, 0, TASK_FULL, 0, 0, 200, 0};

    // Initialize OS task PCB array
    OsTasksPCB[IDLE_TASK] = &IDLE;
    OsTasksPCB[0] = &T0;
    OsTasksPCB[1] = &T1;
    OsTasksPCB[2] = &T2;

    // Activate the IDLE task
    OS_ActivateTask(IDLE.ID);

    // Test 1: WaitEvent for T0
    OS_ActivateTask(T0.ID);
    StatusType st = WaitEvent(WaitMask);

    // Check results for Test 1
    if (st != E_OS_RESOURCE)
    {
        printf("Error Occurred in E_OS_RESOURCE Test 1\n\n");
        exit(1);
    }
    if (T0.EventMask.Event_Waiting != 0)
    {
        printf("Error Occurred in setting mask Test 1\n\n");
        exit(1);
    }
    if (T0.State == WAITING)
    {
        printf("Error Occurred in state Test 1\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");

    // Test 2: WaitEvent for T1
    OS_ActivateTask(T1.ID);
    st = WaitEvent(WaitMask);

    // Check results for Test 2
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ACCESS Test 2\n\n");
        exit(1);
    }
    if (T1.EventMask.Event_Waiting != 0)
    {
        printf("Error Occurred in setting mask Test 2\n\n");
        exit(1);
    }
    if (T1.State == WAITING)
    {
        printf("Error Occurred in state Test 2\n\n");
        exit(1);
    }
    printf("Test 2 Passed\n\n");

    // Test 3: WaitEvent for T2
    OS_ActivateTask(T2.ID);
    st = WaitEvent(WaitMask);

    // Check results for Test 3
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 3\n\n");
        exit(1);
    }
    if (T2.EventMask.Event_Waiting != WaitMask)
    {
        printf("Error Occurred in setting mask Test 3\n\n");
        exit(1);
    }
    if (T2.State != WAITING)
    {
        printf("Error Occurred in state Test 3\n\n");
        exit(1);
    }
    printf("Test 3 Passed\n\n");

    printf("All tests Passed\n\n");

    return 0;
}
