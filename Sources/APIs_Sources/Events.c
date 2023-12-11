#include "../../Headers/APIs_Headers/Events.h"
#include "../../Headers/APIs_Headers/Externs.h"
#include "../../Headers/APIs_Headers/Hooks.h"
#include "../../Headers/APIs_Headers/OsTasks.h"
#include <string.h>


EventMaskType GlobalEventMask;
StatusType SetEvent(TaskType TaskID, EventMaskType ActivatedEvents)
{

    if (TaskID >= MAX_TASKS) // Invalid task ID
    {
        // error msg

        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_ID);
        }
        return E_OS_ID;
    }
    if (OsTasksPCB[TaskID]->Extended == 0)
    {

        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_ACCESS);
        }
        return E_OS_ACCESS;
    }
    if (OsTasksPCB[TaskID]->State == SUSPENDED)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_STATE);
        }
        return E_OS_STATE;
    }

    OsTasksPCB[TaskID]->EventMask.Event_State = OsTasksPCB[TaskID]->EventMask.Event_State | ActivatedEvents; // set the activated events
    uint64_t condition = OsTasksPCB[TaskID]->EventMask.Configured_Events & OsTasksPCB[TaskID]->EventMask.Event_State & OsTasksPCB[TaskID]->EventMask.Event_Waiting;
    if (condition != 0) // if there is a match between configured and activated events
    {
        OsTasksPCB[TaskID]->State = READY; // set to ready state
        OS_Insert(OsTasksPCB[TaskID]);     // insert to ready queue
        OsTasksPCB[TaskID]->EventMask.Event_Waiting = OsTasksPCB[TaskID]->EventMask.Event_Waiting & ~OsTasksPCB[TaskID]->EventMask.Event_State;
        return E_OK; // clear the activated events
    }
    return E_OK;
}

StatusType WaitEvent(EventMaskType EventMask)
{
	GlobalEventMask = EventMask;
    SAVECTX;
    SAVESP;
	EventMask = GlobalEventMask;
	StatusType StatusMsg = E_OK;
    if (OsTasksPCB[RunningTaskID]->Extended == 0)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_STATE);
        }

        StatusMsg = E_OS_ACCESS;
    }

    if (OsTasksPCB[RunningTaskID]->Reasourses_Occupied > 0)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_RESOURCE);
        }
        StatusMsg = E_OS_RESOURCE;
    }

    // E_OS_CALLEVEL
    if ((OsTasksPCB[RunningTaskID]->EventMask.Configured_Events & EventMask) != 0)
    {
        if (EventMask & OsTasksPCB[RunningTaskID]->EventMask.Event_State)
        {
        	StatusMsg = E_OK;
        }
        else
        {
            OsTasksPCB[RunningTaskID]->State = WAITING;                                                                                                                                     // set to waititng state
            OsTasksPCB[RunningTaskID]->EventMask.Event_Waiting = (OsTasksPCB[RunningTaskID]->EventMask.Configured_Events & EventMask) | OsTasksPCB[RunningTaskID]->EventMask.Event_Waiting; // set waiting events
            OS_Delete(RunningTaskID);
            RunningTaskID = INVALID_TASK;
            OS_Schedule();
        }
    }
    // delete from ready queue
     // schedule next task
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

StatusType GetEvent(TaskType TaskID, EventMaskRefType Event)
{

    if (TaskID >= MAX_TASKS) // max number of active tasks
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_ID);
        }
        // error msg
        return E_OS_ID;
    }

    if (OsTasksPCB[TaskID]->Extended == 0)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_ACCESS);
        }
        return E_OS_ACCESS;
    }

    if (OsTasksPCB[TaskID]->State == SUSPENDED)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_STATE);
        }
        return E_OS_STATE;
    }

    *Event = OsTasksPCB[TaskID]->EventMask.Event_State;

    return E_OK;
}

StatusType ClearEvent(EventMaskType Mask)
{
    if (OsTasksPCB[RunningTaskID]->Extended == 0)
    {
        if ((Active_Hooks & Errorhook) != 0)
        {
            ErrorHook(E_OS_ACCESS);
        }
        return E_OS_ACCESS;
    }
    // E_OS_CALLEVEL
    OsTasksPCB[RunningTaskID]->EventMask.Event_State = OsTasksPCB[RunningTaskID]->EventMask.Event_State & ~Mask; // clear the activated events

    return E_OK;
}