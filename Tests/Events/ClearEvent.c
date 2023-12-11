/**
 * @file
 * @brief Test program for the event management and task execution in the operating system.
 *
 * This program initializes tasks, events, and the OS execution environment to test the functionality
 * of event management and task execution. It includes scenarios where events are set, cleared, and tasks are activated.
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
    // Define event mask and clear event mask for testing
    struct Event EventMask = {0b11111, 0b01010, 0b10101};
    uint64_t ClearEventMask = 0b10000;

    // Define tasks for testing
    struct Task T0 = {0, 0, 0, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask}; // normal extended task
    struct Task T1 = {0, 0, 1, WAITING, 5, 5, TASK_NON, 0, 0, 1, 0, 0, EventMask}; // not extended task
    struct Task IDLE = {0, 0, IDLE_TASK, SUSPENDED, 0, 0, TASK_FULL, 0, 0, 200, 0};

    // Initialize OS task PCB array
    OsTasksPCB[IDLE_TASK] = &IDLE;
    OsTasksPCB[0] = &T0;
    OsTasksPCB[1] = &T1;

    // Activate IDLE task
    OS_ActivateTask(IDLE.ID);

    // Test 1: Clear Event for T0
    OS_ActivateTask(T0.ID);
    StatusType st = ClearEvent(ClearEventMask);
    OS_TerminateTask();

    // Check results for Test 1
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 1\n\n");
        exit(1);
    }
    if (T0.EventMask.Event_State != 0b00101)
    {
        printf("Error Occurred in Clearing Test 1\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");

    // Test 2: Attempt to Clear Event for T1 (non-extended task)
    OS_ActivateTask(T1.ID);
    st = ClearEvent(ClearEventMask);
    OS_TerminateTask();

    // Check results for Test 2
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ACCESS Test 2\n\n");
        exit(1);
    }
    if (T1.EventMask.Event_State != 0b10101)
    {
        printf("Error Occurred in Clearing Test 2\n\n");
        exit(1);
    }
    printf("Test 2 Passed\n\n");

    printf("All tests Passed\n\n");

    return 0;
}
