#include "../../Headers/APIs_Headers/OsTasks.h"
#include "../../Headers/APIs_Headers/Externs.h"

#include "../../Headers/APIs_Headers/Hooks.h"
#include "../../Headers/Hardware_Dep_Headers/ContextSwitch.h"

#include <stdio.h>

void OS_ActivateTask(TaskType TaskID)
{
	
	OsTasksPCB[TaskID]->State = READY;
	OsTasksPCB[TaskID]->Activation_Record++;
	OsTasksPCB[TaskID]->Started = START_F;
	OS_Insert(OsTasksPCB[TaskID]);
	OS_Schedule();



	return;
}

void OS_TerminateTask(void)
{


	if ((Active_Hooks & PostTaskhook) != 0)
	{
		PostTaskHook();
	}
	if (OsTasksPCB[RunningTaskID]->Activation_Record == 1)
	{
		OsTasksPCB[RunningTaskID]->State = SUSPENDED;
		OS_Delete(RunningTaskID);
		RunningTaskID = INVALID_TASK;
	}
	else
	{
		OsTasksPCB[RunningTaskID]->Activation_Record--;
		OsTasksPCB[RunningTaskID]->State = READY;
	}

	OS_Schedule();
	return;
}

void OS_Schedule(void)
{
	if(Running_ISR_Count!=0)
		return;
	PreTaskID=RunningTaskID;
	if (RunningTaskID == INVALID_TASK)
	{
		Ready_Queue.Head->task->Started = START_T;
		RunningTaskID = Ready_Queue.Head->task->ID;
		Ready_Queue.Head->task->State = RUNNING;


		if(OsTasksPCB[RunningTaskID]->first ==0)
					{
						OsTasksPCB[RunningTaskID]->first = 1;

						LOADCTX_FIRST;
					}
					else
					{
						LOADCTX;
					}

		return;
	}
	else if (OsTasksPCB[RunningTaskID]->F_PREEM == TASK_FULL)
	{
		if (Ready_Queue.Head->task->Priority > OsTasksPCB[RunningTaskID]->Priority)
		{
			if ((Active_Hooks & PreTaskhook) != 0 && OsTasksPCB[RunningTaskID]->Started != START_T)
			{
				PreTaskHook();
			}
			OsTasksPCB[RunningTaskID]->State = READY;
			RunningTaskID = Ready_Queue.Head->task->ID;
			Ready_Queue.Head->task->State = RUNNING;

		}

	}
return;
}


void OS_Insert(struct Task *newTask)
{
	Ready_Entries[newTask->ID] = (struct Ready_Entry){newTask, NULL, NULL};

	if (Ready_Queue.Queue_Size == 0)
	{

		Ready_Queue.Head = &Ready_Entries[newTask->ID];
		Ready_Queue.Tail = Ready_Queue.Head;
	}
	else
	{
		struct Ready_Entry *Current = Ready_Queue.Head;
		while (Current != NULL)
		{
			if (newTask->Priority > Current->task->Priority)
			{
				if (Ready_Queue.Head == Current)
				{
					Ready_Queue.Head = &Ready_Entries[newTask->ID];
				}
				else
				{
					Ready_Entries[newTask->ID].Prev = Current->Prev;
					Current->Prev->Next = &Ready_Entries[newTask->ID];
				}
				Ready_Entries[newTask->ID].Next = Current;
				Current->Prev = &Ready_Entries[newTask->ID];
				break;
			}
			if (Current->Next == NULL)
			{
				Current->Next = &Ready_Entries[newTask->ID];
				Ready_Entries[newTask->ID].Prev = Current;

				Ready_Queue.Tail = &Ready_Entries[newTask->ID];
				break;
			}
			Current = Current->Next;
		}
	}
	Ready_Queue.Queue_Size++;
}

void OS_Delete(TaskType TaskID)
{
	struct Ready_Entry *Current = Ready_Queue.Head;

	while (Current != NULL)
	{
		if (Current->task->ID == TaskID)
		{

			if (Ready_Queue.Head == Current)
			{
				Ready_Queue.Head = Current->Next;
				if (Ready_Queue.Head != NULL)
				{
					Ready_Queue.Head->Prev = NULL;
				}
			}
			else
			{
				Current->Prev->Next = Current->Next;
			}
			if (Ready_Queue.Tail == Current)
			{
				Ready_Queue.Tail = Current->Prev;
				if (Ready_Queue.Tail != NULL)
				{
					Ready_Queue.Tail->Next = NULL;
				}
			}
			else
			{
				Current->Next->Prev = Current->Prev;
			}
			Ready_Queue.Queue_Size--;
			break;
		}
		Current = Current->Next;
	}
}

void OS_SortByPriority(void) {
  
    int swapped;
    struct Ready_Entry *ptr1;
    struct Ready_Entry *lptr = NULL;


    if (Ready_Queue.Head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = Ready_Queue.Head;

        while (ptr1->Next != lptr) {
            if (ptr1->task->Priority < ptr1->Next->task->Priority) {

                struct Task *temp = ptr1->task;
                ptr1->task = ptr1->Next->task;
                ptr1->Next->task = temp;

                swapped = 1;
            }
            ptr1 = ptr1->Next;
        }
        lptr = ptr1;
    } while (swapped);
}