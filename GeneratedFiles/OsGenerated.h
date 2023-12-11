
#ifndef _OSGENERATED_H_
#define _OSGENERATED_H_
#include "../Configurations/TaskConfig.h"
#include "../Configurations/ResourceConfig.h"
#include "../Configurations/OSExecutionControlConfig.h"
#include "../Configurations/ISRConfig.h"
#include "../Headers/APIs_Headers/Defines.h"

TaskType RunningTaskID=INVALID_TASK;
TaskType PreTaskID = INVALID_TASK;
uint8_t Queue_Size;
struct Ready_List Ready_Queue;
struct Ready_Entry Ready_Entries[MAX_TASKS];
AppModeType ActiveAppMode;
uint8_t Active_Hooks = INVALID_HOOK;
ISRType Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
uint8_t ISR_Suspend_Counter = 0;
ISRType Running_ISR_Count = 0;
struct Task* OsTasksPCB[MAX_TASKS];
struct Resource *OsResourcesPCB[MAX_RESOURCES];
#define Event1 1

#define Event2 2

#define Event3 4

#define R1 0

#define R2 1

#define Task1 0

#define Task2 1

#define Task3 2

#define TaskTRNG 3

#define TaskEncrypt_Decrypt 4


void Task1Func();
void Task2Func();
void Task3Func();
void TRNG();
void Encrypt_Decrypt();
void IdleFunc();
#endif