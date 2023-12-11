/**
 * @file
 * @brief Test program for the GetEvent function in the operating system.
 *
 * This program tests the GetEvent function, which retrieves the current event state of a task.
 * It initializes tasks with different configurations to check the behavior of GetEvent in various scenarios.
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
    printf("Testing GetEvent\n\n");

    // Define event mask for testing
    struct Event EventMask = {0b11111, 0b01010, 0b01010};
    EventMaskType Event;

    // Define tasks for testing
    struct Task T0 = {0, 0, 0, READY, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask};    // normal extended task
    struct Task T1 = {0, 0, MAX_TASKS, SUSPENDED, 5, 5, TASK_NON, 0, 0, 0, 0, 0, EventMask}; // invalid task
    struct Task T2 = {0, 0, 2, READY, 5, 5, TASK_NON, 0, 0, 1, 0, 0, EventMask};  // not extended task
    struct Task T3 = {0, 0, 3, SUSPENDED, 5, 5, TASK_NON, 0, 0, 1, 0, 1, EventMask}; // suspended task

    // Initialize OS task PCB array
    OsTasksPCB[0] = &T0;
    OsTasksPCB[1] = &T1;
    OsTasksPCB[2] = &T2;
    OsTasksPCB[3] = &T3;

    // Test 1: GetEvent for T0
    printf("Before GetEvent\n\n");
    StatusType st = GetEvent(T0.ID, &Event);
    printf("After GetEvent\n\n");

    // Check results for Test 1
    if (st != E_OK)
    {
        printf("Error Occurred in E_OK Test 1\n\n");
        exit(1);
    }
    if (Event != 0b01010)
    {
        printf("Error Occurred in Event Test 1\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");

    // Test 2: GetEvent for T1 (invalid task)
    st = GetEvent(T1.ID, &Event);
    if (st != E_OS_ID)
    {
        printf("Error Occurred in E_OS_ID Test 2\n\n");
        exit(1);
    }
    printf("Test 2 Passed\n\n");

    // Test 3: GetEvent for T2 (not extended task)
    st = GetEvent(T2.ID, &Event);
    if (st != E_OS_ACCESS)
    {
        printf("Error Occurred in E_OS_ACCESS Test 3\n\n");
        exit(1);
    }
    printf("Test 3 Passed\n\n");

    // Test 4: GetEvent for T3 (suspended task)
    st = GetEvent(T3.ID, &Event);
    if (st != E_OS_STATE)
    {
        printf("Error Occurred in E_OS_STATE Test 4\n\n");
        exit(1);
    }
    printf("Test 4 Passed\n\n");

    printf("All Tests Passed\n\n");

    return 0;
}
