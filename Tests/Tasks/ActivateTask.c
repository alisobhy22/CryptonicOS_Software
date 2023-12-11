#include "../../Headers/APIs_Headers/Tasks.h"
#include "../../Sources/APIs_Sources/Tasks.c"
#include "../../Sources/APIs_Sources/OsTasks.c"
#include "../../Sources/APIs_Sources/Hooks.c"
#include "../../Sources/Hardware_Dep_Sources/ContextSwitch.c"

#include <stdlib.h>
#include <stdio.h>

TaskType RunningTaskID=INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
struct Task* OsTasksPCB[MAX_TASKS];


int main()
{
    RunningTaskID = INVALID_TASK;
    struct Task T1 =
    {0,0,0,SUSPENDED,5,5,TASK_NON,0,0,1,0 };//normal task
     struct Task T2 =
    {0,0,1,SUSPENDED,5,5,TASK_NON,0,5,5,0 }; //max activations
     struct Task T3 =
    {0,0,MAX_TASKS,SUSPENDED,5,5,TASK_NON,0,0,0,0 }; //invalid task


    OsTasksPCB[0] = &T1;
    OsTasksPCB[1] = &T2;
    OsTasksPCB[2] = &T3;


    struct Task IDLE = { 0,0,IDLE_TASK,SUSPENDED,0,0,TASK_FULL,0,0,200,0 };
    OsTasksPCB[IDLE_TASK] = &IDLE;
    //startos
    StatusType st = ActivateTask(IDLE.ID);
    if(st != E_OK)
    {
        printf("Error Occured in START OS EX1\n\n");
        exit(1);
    }
    if(RunningTaskID != IDLE_TASK)
    {
        //print RunningTaskID
        printf("RunningTaskID = %d\n\n",RunningTaskID);
        printf("Error Occured in START OS EX2\n\n");
        exit(1);
    }


    //test E_OK normal activate
    st = ActivateTask(T1.ID);
    if(st != E_OK)
    {
        printf("Error Occured in E_OK EX1\n\n");
        exit(1);
    }

    if (T1.State != RUNNING)
    {
        printf("Error Occured in E_OK EX2\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");
    //test E_OS_LIMIT (TO many activations of <TaskID>)
     st = ActivateTask(T2.ID);
    if (st != E_OS_LIMIT)
    {
        printf("Error Occured in E_OS_LIMIT EX1\n\n");
        exit(1);
    }
    if (T2.State != SUSPENDED)
    {
        printf("Error Occured in E_OS_LIMIT EX2\n\n");
        exit(1);
    }
    printf("Test 2 Passed\n\n");
    //test E_OS_ID (Invalid Task ID)
     st = ActivateTask(T3.ID);
    if (st != E_OS_ID)
    {
        printf("Error Occured in E_OS_ID EX1\n\n");
        exit(1);
    }
    if (T3.State != SUSPENDED)
    {
        printf("Error Occured in E_OS_ID EX2\n\n");
        exit(1);
    }
    printf("Test 3 Passed\n\n");
    exit(0);
}
