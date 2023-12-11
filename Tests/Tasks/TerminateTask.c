#include "../../Headers/APIs_Headers/Tasks.h"
#include "../../Sources/APIs_Sources/Tasks.c"
#include "../../Sources/APIs_Sources/OsTasks.c"
#include "../../Sources/APIs_Sources/Hooks.c"
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
    {0,0, 0,SUSPENDED,5,5,TASK_NON,0,0,1,0 };
    

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
        printf("Error Occured in START OS EX2\n\n");
        exit(1);
    }

    OsTasksPCB[0] = &T1;
    //test E_OK
    st = ActivateTask(T1.ID);
    st = TerminateTask();

    if(st != E_OK)
    {
        printf("Error Occured in E_OK EX1\n\n");
        exit(1);
    }
    if (RunningTaskID != IDLE_TASK)
    {
        printf("Error Occured in E_OK EX2\n\n");
        exit(1);
    }
    if (T1.State != SUSPENDED)
    {
        printf("Error Occured in E_OK EX3\n\n");
        exit(1);
    }
    printf("Test 1 Passed\n\n");
    //test E_OS_RESOURCE
    //E_OS_CALLEVEL
    exit(0);
}
