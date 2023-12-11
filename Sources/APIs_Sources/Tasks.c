#include "../../Headers/APIs_Headers/Tasks.h"
#include "../../Headers/APIs_Headers/Externs.h"
#include "../../Headers/APIs_Headers/OsTasks.h"
#include "../../Headers/APIs_Headers/Hooks.h"
#include <stdio.h>

TaskType GlobalID;
StatusType ActivateTask(TaskType TaskID)
{
	GlobalID = TaskID;

	SAVECTX;
	SAVESP;
	TaskID = GlobalID;
	StatusType StatusMsg = E_OK;
	if (TaskID >= MAX_TASKS)
	{

		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}
	}
	if ((OsTasksPCB[TaskID]->State == SUSPENDED) && (OsTasksPCB[TaskID]->Activation_Request != OsTasksPCB[TaskID]->Activation_Record)) 
	{
		OS_ActivateTask(TaskID);
		StatusMsg = E_OK;
	}
	else
	{
		StatusMsg = E_OS_LIMIT;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}
	}
	OsTasksPCB[PreTaskID]->retStatus = StatusMsg;
	if(OsTasksPCB[RunningTaskID]->first ==0)
						{
							OsTasksPCB[RunningTaskID]->first = 1;
							LOADCTX_FIRST;
						}
						else
						{
							LOADCTX;
						}
	return E_OK;
}

StatusType TerminateTask(void)
{
	

	StatusType StatusMsg = E_OK;

	if (OsTasksPCB[RunningTaskID]->Reasourses_Occupied != 0)
	{
		StatusMsg = E_OS_RESOURCE;
	}
	else
	{
		OS_TerminateTask();
	}
	if ((Active_Hooks & Errorhook) != 0 && StatusMsg != E_OK)
	{
		ErrorHook(StatusMsg);
	}
	return StatusMsg;
}

StatusType ChainTask(TaskType TaskID)
{
	StatusType StatusMsg = E_OK;

	if (RunningTaskID >= INVALID_TASK) 
	{
		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}

	}
	if (OsTasksPCB[RunningTaskID]->Reasourses_Occupied != 0)
	{
		StatusMsg = E_OS_RESOURCE;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}

	}
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

	if (TaskID >= INVALID_TASK)
	{
		StatusMsg = E_OS_ID;
		if ((Active_Hooks & Errorhook) != 0)
		{
			ErrorHook(StatusMsg);
		}

	}

	if (OsTasksPCB[TaskID]->State == SUSPENDED)
	{
		if (OsTasksPCB[TaskID]->Activation_Request == OsTasksPCB[TaskID]->Activation_Record)
		{
			StatusMsg = E_OS_LIMIT;
			if ((Active_Hooks & Errorhook) != 0)
			{
				ErrorHook(StatusMsg);
			}

		}
		OS_ActivateTask(TaskID);
		StatusMsg = E_OK;

	}
	OsTasksPCB[PreTaskID]->retStatus = StatusMsg;
	if(OsTasksPCB[RunningTaskID]->first ==0)
						{
							OsTasksPCB[RunningTaskID]->first = 1;
							LOADCTX_FIRST;
						}
						else
						{
							LOADCTX;
						}
	return StatusMsg;
}

StatusType Schedule(void)
{

	StatusType StatusMsg = E_OK;

	if (RunningTaskID == INVALID_TASK)
	{

		// fetch highest priority task from ready queue
		RunningTaskID = Ready_Queue.Head->task->ID;

		Ready_Queue.Head->task->State = RUNNING;

		StatusMsg = E_OK;
	}
	else
	{
		if (OsTasksPCB[RunningTaskID]->F_PREEM == TASK_FULL)
		{
			if (Ready_Queue.Head->task->Priority > OsTasksPCB[RunningTaskID]->Priority)
			{

				OsTasksPCB[RunningTaskID]->State = READY;
				RunningTaskID = Ready_Queue.Head->task->ID;
				Ready_Queue.Head->task->State = RUNNING;
				// context switch
			}
			else // running task still highest prio
			{
				// do nothing
				StatusMsg = E_OK;
			}
		}
		else // non preinmteable running task
		{
			// do nothing
			StatusMsg = E_OK;
		}
	}

	return StatusMsg;
}

StatusType GetTaskID(TaskRefType TaskID)
{
	StatusType StatusMsg = E_OK;

	if (RunningTaskID == INVALID_TASK) 
	{
		*TaskID = INVALID_TASK;
	}
	else
	{
		*TaskID = OsTasksPCB[RunningTaskID]->ID;
	}
	return StatusMsg;
}

StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	StatusType StatusMsg = E_OK;

	if (TaskID >= MAX_TASKS)
	{
		StatusMsg = E_OS_ID;
	}
	else
	{
		*State = OsTasksPCB[TaskID]->State; 
	}
	if ((Active_Hooks & Errorhook) != 0 && StatusMsg !=E_OK)
		{
			ErrorHook(StatusMsg);
		}
	return StatusMsg;
}
