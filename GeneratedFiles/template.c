#ifndef Generated
#define Generated


#include <stdio.h>
#include "../Headers/APIs_Headers/Defines.h"
#include "../Configurations/TaskConfig.h"
//#include "../Configurations/AlarmConfig.h"
#include "../Configurations/ResourceConfig.h"
#include "../Configurations/OSExecutionControlConfig.h"

ISRType Running_ISR_ID;

TaskType RunningTaskID=INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
uint8_t Active_Hooks = INVALID_HOOK;
ISRType Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
uint8_t ISR_Suspend_Counter = 0;
ISRType Running_ISR_Count = 0;

{% for e in events %}
#define {{e.name}} {{e.mask}}
{% endfor %}




{% for r in resources %}
#define {{r.OSResourceName}} {{loop.index-1}}
struct Resource resource{{loop.index-1}}={
    .Res_ID = {{loop.index-1}},
    .Ceiling_Priority = {{r.OSResourceCeilingPriority}},
    .Linked_Resource = 0,
    .Resource_Property = {{r.OSResourceProperty}},
    .Resource_Owner = INVALID_TASK,
    .Prev_Resource = INVALID_RESOURCE
};
{% endfor %}


struct Resource *OsResourcesPCB[MAX_RESOURCES]={
    {% for r in resources %}
    &resource{{loop.index-1}},
    {% endfor %}
};

{% for task in tasks %}
#define {{task.OSTaskName}} {{loop.index-1}}
void {{task.OSTaskName}}Func();
struct Task task{{loop.index-1}} = {
    .stack = {},
    .sp = NULL,
    .first = 0,
    .address = &{{task.OSTaskName}}Func,
    .current_pc = {{task.OSTaskName}}Func,
    .ID = {{loop.index-1}},
    .State = SUSPENDED,
    .CONFIG_PRIORITY = {{task.OsTaskPriority}},
    .Priority = {{task.OsTaskPriority}},
    .F_PREEM = {{task.OsTaskSchedule}},
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = {{task.OsTaskActivation}},
    .Reasourses_Occupied = 0,
    .Extended = {{task.OsTaskType}},
    .EventMask = { {{task.OsTaskEventRef}},0 , 0},
    .Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = { {% for r in task.OsTaskResourceRef %}&resource{{loop.index-1}}{% if not loop.last %},{% endif %}{% endfor %} }
};
{% endfor %}


void IdleFunc();
struct Task idle = {
	.stack = {},
	.sp = NULL,
	.first = 0,
    .address = &IdleFunc,
    .current_pc = &IdleFunc,
    .ID = IDLE_TASK,
    .State = SUSPENDED,
    .CONFIG_PRIORITY = 0,
    .Priority = 0,
    .F_PREEM = TASK_FULL,
    .Preeimpted = 0,
    .Activation_Record = 0,
    .Activation_Request = 200,
    .Reasourses_Occupied = 0,
    .Extended = 0,
    .EventMask = {0,0 , 0},
	.Last_Running_Resource = INVALID_RESOURCE,
    .Needed_Resources = INVALID_RESOURCE
};

struct Task* OsTasksPCB[MAX_TASKS]={
    {% for task in tasks %}
    &task{{loop.index-1}},
    {% endfor %}
    [MAX_TASKS-1]=&idle
};


{% for Interrupt in Interrupts %}
struct ISR isr{{loop.index-1}} = {
    .ID = {{Interrupt.OsInterruptID}},
    .Priority = {{Interrupt.OsInterruptPriority}},
    .Category = {{Interrupt.OsInterruptCategory}},
    .Needed_Resources = { {% for r in Interrupt.OsInterruptResourceRef %}&resource{{loop.index-1}}{% if not loop.last %},{% endif %}{% endfor %} },
    .Prev-Resoure = INVALID_RESOURCE
}

{% endfor %}

struct ISR* ISRPCB[MAX_ISR]={
    {% for Interrupt in Interrupts %}
    [{{Interrupt.OsInterruptID}}] = &isr{{loop.index-1}},
    {% endfor %}
};

#endif
