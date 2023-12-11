/**
 * @file
 * @brief Test program for the SetEvent function in the operating system.
 *
 * This program tests the SetEvent function, which sets events for tasks in the operating system.
 * It initializes tasks with different configurations, sets events, and checks the resulting task states and queue order.
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
    // Initialize event mask
    struct Event EventMask = {0b11111, 0b01010, 0b00000};
    uint64_t ActivatedEvents = 0b00000;

    // Define tasks for testing
    struct Task T0 = {0, 0, 0, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask};   // normal extended task
    struct Task T1 = {0, 0, 1, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 0, NULL};       // not extended task
    struct Task T2 = {0, 0, 2, SUSPENDED, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask}; // suspended task
    struct Task T3 = {0, 0, MAX_TASKS, SUSPENDED, 5, 5, TASK_NON, 0, 0, 0, 0, 0, NULL};
    struct Task T4 = {0, 0, 4, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask};

    // Initialize OS task PCB array
    OsTasksPCB[0] = &T0;
    OsTasksPCB[1] = &T1;
    OsTasksPCB[2] = &T2;
    OsTasksPCB[3] = &T3;
    OsTasksPCB[4] = &T4;

    // Test 1: SetEvent for T0
    // Set ActivatedEvents to be {0,1,0,1,0}
    ActivatedEvents = 0b01010;
    StatusType st = SetEvent(T0.ID, ActivatedEvents);

    // Check results for Test 1
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 1\n\n");
        exit(1);
    }
    if (T0.State != READY)
    {
        printf("Error Occurred in E_OK Test 2\n\n");
        exit(1);
    }
    if (Ready_Queue.Head->task->ID != 0)
    {
        printf("Error Occurred in E_OK Test 3\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");

    // Test 2: SetEvent for T4
    // Set ActivatedEvents to be {0,0,0,0,1}
    ActivatedEvents = 0b00001;
    st = SetEvent(T4.ID, ActivatedEvents);

    // Check results for Test 2
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 4\n\n");
        exit(1);
    }
    if (T4.State != WAITING)
    {
        printf("Error Occurred in E_OK Test 5\n\n");
        exit(1);
    }
    printf("Test 2 Passed\n\n");

    // Test 3: SetEvent for T1 (not extended task)
    st = SetEvent(T1.ID, ActivatedEvents);
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ID Test 1\n\n");
        exit(1);
    }
    printf("Test 3 Passed\n\n");

    // Test 4: SetEvent for T2 (suspended task)
    st = SetEvent(T2.ID, ActivatedEvents);
    if (st != E_OS_STATE)
    {
        printf("Error Occurred in E_OS_STATE Test 1\n\n");
        exit(1);
    }
    printf("Test 4 Passed\n\n");

    // Test 5: SetEvent for T3 (invalid task)
    st = SetEvent(T3.ID, ActivatedEvents);
    if (st != E_OS_ID)
    {
        printf("Error Occurred in E_OS_ID Test 2\n\n");
        exit(1);
    }

    printf("All Tests Passed\n\n");

    return 0;
}
