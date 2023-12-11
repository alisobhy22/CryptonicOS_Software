#include "../../Headers/APIs_Headers/OSExecutionControl.h"
#include "../../Headers/APIs_Headers/Externs.h"
#include "../../Headers/APIs_Headers/OsTasks.h"
#include "../../Headers/APIs_Headers/Hooks.h"
// #include "../../Headers/APIs_Headers/Globels.h"
// #include "Tasks.c"
AppModeType GetActiveApplicationMode(void)
{
  return ActiveAppMode;
}

void StartOS (AppModeType Mode)
{
if ((Active_Hooks & Startuphook) != 0)
	{
		//StartupHook();
	}
  if(Mode == OSDEFAULTAPPMODE)
  {
	  OS_ActivateTask(199);


  }
}



void ShutDownOS (StatusType Error)
{
  if ((Active_Hooks & Shutdownhook) != 0)
	{
		ShutdownHook(E_OK);
	}

  for(;;)
  {
    
  }
}
