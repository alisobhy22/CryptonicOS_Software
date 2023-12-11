#include "../../Headers/APIs_Headers/Tasks.h"
#include "../../Sources/APIs_Sources/Tasks.c"
#include "../../Sources/APIs_Sources/OsTasks.c"
#include "../../Sources/APIs_Sources/Hooks.c"
#include <stdio.h>

TaskType RunningTaskID=INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
struct Task* OsTasksPCB[MAX_TASKS];


struct Task IDLE = {0, 0, IDLE_TASK, SUSPENDED, 0, 0, TASK_FULL, 0, 0, 200, 0};
struct Task T1 = {10, 0, 0, SUSPENDED, 5, 5, TASK_FULL, 0, 0, 1, 1};
struct Task T2 = {20, 0, 1, SUSPENDED, 1, 1, TASK_NON, 0, 0, 1, 1};
struct Task T3 = {30, 0, 2, SUSPENDED, 2, 2, TASK_FULL, 0, 0, 1, 1};

void fill_pcbtable();

void print_ready_queue();

void print_PCB_Table();

int main()
{
    RunningTaskID = INVALID_TASK;
    // Testing Scheduler with tasks that are non preemptive and preemptive with different priorities

    fill_pcbtable();
    StatusType st = ActivateTask(IDLE_TASK);
    print_ready_queue();
    if (st != E_OK)
    {
        printf("Error Occured in START OS EX1 \n\n");
        exit(1);
    }
    if (RunningTaskID != IDLE_TASK)
    {
        printf("Error Occured in START OS EX2 \n\n");
        exit(1);
    }

    print_PCB_Table();
    print_ready_queue();

    st = ActivateTask(2);
    print_ready_queue();
    if (st != E_OK)
    {
        printf("Error Occured in T1 E_OK \n\n");
        exit(1);
    }
    if (T3.State != RUNNING && IDLE.State != READY)
    {
        printf("Error Occured in T1 Act \n\n");
        exit(1);
    }

    ActivateTask(1);
    print_ready_queue();
    if (st != E_OK)
    {
        printf("Error Occured in T1 E_OK \n\n");
        exit(1);
    }
    if (T3.State != RUNNING && T2.State != READY && IDLE.State != READY)
    {
        printf("Error Occured in T1 Act \n\n");
        exit(1);
    }

    ActivateTask(0);
    print_ready_queue();
    if (st != E_OK)
    {
        printf("Error Occured in T1 E_OK \n\n");
        exit(1);
    }
    if (T3.State != READY && T1.State != RUNNING && T2.State != READY && IDLE.State != READY)
    {
        printf("Error Occured in T1 Act \n\n");
        exit(1);
    }

    printf("\n\n ALL tests passed \n\n");
    return 0;
}

void fill_pcbtable()
{
    OsTasksPCB[IDLE_TASK] = &IDLE;
    OsTasksPCB[0] = &T1;
    OsTasksPCB[1] = &T2;
    OsTasksPCB[2] = &T3;
}

void print_ready_queue()
{
    printf("Ready Queue: ");
    struct Ready_Entry *current = Ready_Queue.Head;
    while (current != NULL)
    {
        printf("%d ", current->task->ID);

        current = current->Next;
    }
    printf("\n");
}
void print_PCB_Table()
{
    printf("PCB Table: \n");
    for (int i = 0; i < 3; i++)
    {
        printf("id: %d, state: %d \n", OsTasksPCB[i]->ID, OsTasksPCB[i]->State);
    }
    printf("id: %d, state: %d \n", OsTasksPCB[IDLE_TASK]->ID, OsTasksPCB[IDLE_TASK]->State);
    printf("\n\n\n");
}
