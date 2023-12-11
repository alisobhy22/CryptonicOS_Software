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
    struct Task T1 = { 10,0,0,SUSPENDED,5,5,TASK_NON,0,0,1,0 };
    struct Task T2 = { 20,0,1,SUSPENDED,5,5,TASK_FULL,0,0,1,0 };
    struct Task T3 = { 30,0,2,SUSPENDED,6,6,TASK_FULL,0,0,1,0 };
    struct Task T4 = { 40,0,3,SUSPENDED,6,6,TASK_NON,0,0,1, 0 };
    struct Task T5 = { 50,0,4,SUSPENDED,8,8,TASK_FULL,0,0,1, 0 };



    void fill_pcbtable();

    void print_ready_queue();

    void print_PCB_Table();


    int main()
    {
        //Testing Scheduler with tasks that are non preemptive and preemptive with same priorities of each pair of tasks to make sure that eveything working when 
        //they have the same priorities in scheduling non preemptive and preemptive tasks together
        RunningTaskID = INVALID_TASK;
        fill_pcbtable();



        StatusType st = ActivateTask(IDLE_TASK); // T_idle
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


        st = ActivateTask(0); // T1 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T1 E_OK \n\n");
            exit(1);
        }
        if (T1.State != RUNNING && IDLE.State != READY)
        {
            printf("Error Occured in T1 Act \n\n");
            exit(1);
        }

        st = ActivateTask(1); // T1 T2 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T2 E_OK \n\n");
            exit(1);
        }
        if (T1.State != RUNNING && T1.State != READY && IDLE.State != READY)
        {
            printf("Error Occured in T2 Act \n\n");
            exit(1);
        }


    st = ActivateTask(2); // T1 T3 T2 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T3 E_OK \n\n");
            exit(1);
        }
        if (T1.State != RUNNING && T2.State != READY && T3.State != READY && IDLE.State != READY)
        {
            printf("Error Occured in T3 Act \n\n");
            exit(1);
        }
    
        st = TerminateTask(); // T3 T2 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T1 E_OK_2 \n\n");
            exit(1);
        }
        if (T3.State != RUNNING && T2.State != READY && IDLE.State != READY)
        {
            printf("Error Occured in T1 Terminate\n\n");
            exit(1);
        }



        st = ActivateTask(3); // T3 T4 T2 T_idle
        print_ready_queue();

        if (st != E_OK)
        {
            printf("Error Occured in T4 E_OK \n\n");
            exit(1);
        }
        if (T3.State != RUNNING && T2.State != READY && T4.State != READY  && IDLE.State != READY)
        {
            printf("Error Occured in T4 Act \n\n");
            exit(1);
        }




        st = ActivateTask(4); // T5 T3 T4 T2 T_idle
        print_ready_queue();

        if (st != E_OK)
        {
            printf("Error Occured in T5 E_OK \n\n");
            exit(1);
        }
        if (T5.State != RUNNING && T2.State != READY && T3.State != READY && T4.State != READY  && IDLE.State != READY)
        {
            printf("Error Occured in T5 Act \n\n");
            exit(1);
        }



        st = TerminateTask(); // T3 T4 T2 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T5 E_OK_2 \n\n");
            exit(1);
        }
        if (T3.State != RUNNING && T2.State != READY && T4.State != READY && IDLE.State != READY)
        {
            printf("Error Occured in T5 Terminate\n\n");
            exit(1);
        }

        
        st = TerminateTask(); // T4 T2 T_idle
        print_ready_queue();
        if (st != E_OK)
        {
            printf("Error Occured in T3 E_OK_2 \n\n");
            exit(1);
        }
        if (T4.State != RUNNING && T2.State != READY &&  IDLE.State != READY)
        {
            printf("Error Occured in T3 Terminate\n\n");
            exit(1);
        }


    


        print_PCB_Table();
        printf("\n\n ALL tests passed \n\n");

        return 0;
    }




    void fill_pcbtable()
    {



        OsTasksPCB[0] = &T1;
        OsTasksPCB[1] = &T2;
        OsTasksPCB[2] = &T3;
        OsTasksPCB[3] = &T4;
        OsTasksPCB[4] = &T5;

        OsTasksPCB[IDLE_TASK] = &IDLE;
        //OsTasksPCB[5] = &T6;
        //OsTasksPCB[6] = &T7;
        //OsTasksPCB[7] = &T8;
        //OsTasksPCB[8] = &T9;
        //OsTasksPCB[9] = &T10;

    }

    void print_ready_queue()
    {
        printf("Ready Queue: ");
        struct Ready_Entry* current = Ready_Queue.Head;
        while(current!=NULL)
        {
            printf("%d ",current->task->ID);

            current=current->Next;
        }
        printf("\n");
    }
    void print_PCB_Table()
    {
        printf("PCB Table: \n");
        for (int i = 0; i < 5; i++)
        {
            printf("id: %d, state: %d \n", OsTasksPCB[i]->ID, OsTasksPCB[i]->State);
        }
    }
