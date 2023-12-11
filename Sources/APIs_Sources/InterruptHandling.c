
#include "../../Headers/APIs_Headers/InterruptHandling.h"
#include "../../Headers/APIs_Headers/Externs.h"
#include <stdio.h>






void EnableAllInterrupts(void)
{

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_DisableAll)
		{

			Active_ISR_Disable_Type = ISR_Disable_Type_NoDisable;
		}

	}

}

void DisableAllInterrupts(void)
{

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{
			Active_ISR_Disable_Type = ISR_Disable_Type_DisableAll;
		}

	}



	

}

void ResumeAllInterrupts(void)
{

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_SuspendAll || Active_ISR_Disable_Type == ISR_Disable_Type_SuspendOS )
		{
			ISR_Suspend_Counter--;

			if(ISR_Suspend_Counter == 0)
			{
				Active_ISR_Disable_Type =  ISR_Disable_Type_NoDisable;
			}
			else
			{
				Active_ISR_Disable_Type = ISR_Disable_Type_SuspendAll;

			}

		}

	}
}

void SuspendAllInterrupts(void)
{

	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{

			Active_ISR_Disable_Type = ISR_Disable_Type_SuspendAll;
			ISR_Suspend_Counter =  1;
		}
		else
		{
			{
				ISR_Suspend_Counter++;
			}

		}

	}
}

void ResumeOSInterrupts(void)
{


	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_SuspendAll || Active_ISR_Disable_Type == ISR_Disable_Type_SuspendOS )
		{
			for(int i =0;i<MAX_ISRs;i++)
			{

			}

			ISR_Suspend_Counter--;

			if(ISR_Suspend_Counter == 0)
			{
				Active_ISR_Disable_Type =  ISR_Disable_Type_NoDisable;
				
			}
			else
			{
				Active_ISR_Disable_Type = ISR_Disable_Type_SuspendOS;

			}

		}

	}

}

void SuspendOSInterrupts (void)
{


	if(Active_Hooks == INVALID_HOOK)
	{
		if(Active_ISR_Disable_Type == ISR_Disable_Type_NoDisable)
		{

			Active_ISR_Disable_Type = ISR_Disable_Type_SuspendOS;
			ISR_Suspend_Counter =  1;
		}
		else
		{
			{
				ISR_Suspend_Counter++;
			}

		}

	}



}



bool CheckPending(void)
{
	return false;
}
