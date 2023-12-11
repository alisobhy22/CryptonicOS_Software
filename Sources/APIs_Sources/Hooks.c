#include "../../Headers/APIs_Headers/Hooks.h"
#include "../../Headers/APIs_Headers/Externs.h"


void ErrorHook (StatusType Error)
{
    //printf("ErrorHook Called");
}

void PreTaskHook (void)
{
//printf("PreTaskHook Called");
}

void PostTaskHook (void)
{
//printf("PostTaskHook Called");
}

void StartupHook (void)
{
//printf("StartupHook Called");
}

void ShutdownHook (StatusType Error)
{
//printf("ShutdownHook Called");
}