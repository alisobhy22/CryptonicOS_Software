HSM_CryptonicOS
=================

Lightweight AUTOSAR-OSEK/VDX-compliant OS for HSM on **MCU TC387QP**

# Project Definition

Our project provides a fully functioning Operating System intended to be flashed on the Hardware Security Module (HSM). The primary motivation is to enhance productivity for developers working on the HSM by providing a cleaner environment for interacting with HSM accelerators. Our OS is designed to be portable and lightweight, ensuring implementation on various HSM cores without limitations. It supports task definition, event triggering, resource claiming, and interrupt management.

## Importance

The automotive industry's shift towards incorporating more Electronic Control Units (ECUs) has increased cybersecurity threats. HSMs address these challenges by providing specific accelerators for secure cryptographic operations. Our OS, when flashed on the HSM, enables developers to write efficient code for the automotive industry, meeting the increasing demands.

## Testing

We tested the software portion using Continuous Integration with GitHub Actions. Hardware testing involved ensuring the OS ran correctly on the HSM. For the software, we tested each API separately, verifying correct interactions and return messages.

## Implementation

Our OS is implemented on the TC387QP microcontroller's HSM core. We tested True Random Number Generator, Encryption, and Decryption peripherals. Additionally, we ported the OS to the STM32FE303E open-source microcontroller, testing portability and minimal code changes for context switching and interrupts.

## Intended Usage

Developers should use our OS to port to an HSM core. It supports single-core usage and is not intended for multicore systems. The documentation specifies steps for developers, including an example port to the STM32FE303 microcontroller.

## Provided APIs

### Task Management
- ActivateTask(TaskType TaskID)
- TerminateTask()
- ChainTask(TaskType TaskID)
- Schedule()
- GetTaskID(TaskRefType TaskID)
- GetTaskState(TaskType TaskID, TaskStateRefType State)

### Events
- SetEvent(TaskType TaskID, EventMaskType ActivatedEvents)
- WaitEvent(EventMaskType EventMask)
- GetEvent(TaskType TaskID, EventMaskRefType Event)
- ClearEvent(EventMaskType Mask)

### Resources
- GetResource(ResourceType ResID)
- ReleaseResource(ResourceType ResID)

### Interrupts
- EnableAllInterrupts()
- DisableAllInterrupts()
- ResumeAllInterrupts()
- SuspendAllInterrupts()
- ResumeOSInterrupts()
- SuspendOSInterrupts()

### Execution Control
- GetActiveApplicationMode()
- StartOS(AppModeType Mode)
- ShutDownOS(StatusType Error)

## Porting To Target

Before using the operating system, developers need to write certain macros that our operating system intends to use. These macros are hardware-dependent and vary from target to target, requiring developers to write them for porting to the target. This section outlines the required macros, how they should be written, and provides an example for an open-source microcontroller (STM32FE303) for reference.

While different architectures exist for various cores, the example provided may need to be implemented differently. However, the functionalities remain similar. Developers must ensure that macros are written as intended and verify that startup and linker scripts function correctly. Debugging and resolving errors in our OS may require logic changes, but we've attempted to minimize this through our modular structure.

### Context Switch Macros

Three macros must be defined by the developer to enable the core to perform context switching from task to task. These macros ensure task context is saved and loaded correctly with the correct context. To perform this, the following macros are required to be written in the `Defines.h` file located in the headers folder using assembly instructions:

#### SaveCtx(Indent):

- Add the value of `Indent` to the Stack pointer (SP)
- Push the value of LR register to Stack pointer
- Assign the value of SP to the Running Tasks SP attribute
- Subtract the value of SP by 4

   Example:

   ```c
   #define SAVECTX(indent) __asm volatile( "ADD sp, %1;" "PUSH {lr};" "MOV %0, sp \n\t" "SUB r7 , #4" :"=r" (OsTasksPCB[RunningTaskID]->sp) :"r" (indent) )

   ```

   *Note that the value 4 may differ from architecture to another and will need to be properly replaced by the user with the correct number based on the core’s implementation. Also Note that some Architectures may need extra steps like pushing off extra registers and developers should refer to their architecture to identify exactly what needs to be done.*


 ####  LoadCtx:

- Load the RunningTaskID’s SP to SP register
- Pop the LR register from the Stack
- Add 8 to the SP register
- Save the return status to RunningTaskID’s retstatus attribute
- Branch to LR register

 Example:
```c
#define LOADCTX __asm volatile( "MOV sp, %0 \n\t" "POP {lr};" "ADD sp,#8;" "MOV r7,sp;" "MOV r0,%1;" "BX lr;": : "r" (OsTasksPCB[RunningTaskID]->sp),"r" (OsTasksPCB[RunningTaskID]->retStatus) : "memory");
```

*Note that the value 8  may differ from architecture to another and will need to be properly replaced by the user with the correct number based on the core’s implementation. Also note that in this case the return status was always stored in the R0 register, which may not be the case. Also note that extra steps may need to be added, like popping of extra registers for example and developers should refer to their target architecture for an extra steps.*


 #### LoadCtx_First:

- Assign the SP register to RunningTaskID’s SP
- Branch to RunningTaskID’s Address

Example:
```c
#define LOADCTX_FIRST __asm volatile( "MOV sp, %0 \n\t" "BX %1;": : "r" (&OsTasksPCB[RunningTaskID]->sp), "r"(OsTasksPCB[RunningTaskID]->address) : "memory");
```


### Interrupt Macros:

To Handle interrupts, the user needs to modify mapping of the request handler (IRQ) to the service routine (ISR) by making the IRQ point to a defined function inside the code.

Example: 

```c
g_pfnVectors:
```
```c
.word EXI0_Config
```

*Note that depending on the architecture, there can be either a function for each IRQ or one function for all IRQs depending on whether the hardware allows the user to know the fired IRQ or not*

1. Inside the new function defined:
2. Save context of the calling task (running task).
3. Call the required ISR.
4. Initiate scheduling.
5. Load context of the currently running task
	
	Example:
```c

void EXI0_Config()
{
   SAVECTX(0);
   EXI0_IRQHandler();
   OS_Schedule();
   if(OsTasksPCB[RunningTaskID]->first == 0)
      {
         OsTasksPCB[RunningTaskID]->first = 1;
         LOADCTX_FIRST;
      }
      else
      {
         LOADCTX;
      }

```
Following the osek-standard, inside the ISR, differentiating between CAT1 and CAT2 interrupts is a must; in addition to keeping the count of active interrupts to disable scheduling inside CAT2 interrupts.

For the ISR:
1. Increase the count of active interrupts.
2. If the interrupt is a CAT2 interrupt, call the user-defined function.
3. Decrease the number of active interrupts
4. Clear the interrupt request.

	Example:

```c
void EXI0_IRQHandler(void)
{
   Running_ISR_Count++;
   if(ISRPCB[EXIT0_IRQn]->Category ==  ISR_CAT_2)
         EXI0_ISR();
   else
      {
      //CAT 1 body
      }
   Running_ISR_Count--;
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
```
## Configurations

After writing the required hardware functions and macros for setting up the operating system to port on their specific target, configurations now need to be made in order to define their OS. In Order to do this, we offer a tool in our repo which the user can use to transform an XML containing the OS configurations into the required files for compilation. All tools and files regarding the configurations should be found in the folder “GeneratedFiles”. The user should modify the XML called “Config.xml”, and after he/she finishes modifying the XML, should run the “jinja.py” script which will transfer the Config.xml to output the required C files. 
The documentation for how to use the configurations follows the Autosar SWS Specifications for configurations, but below we document exactly what and how to configure different properties in our OS.
 
## Hooks
   In terms of Hooks, the user can only trigger certain hooks and whether they are used in the OS or not. The user should simply navigate to the <Hooks> attribute and write either true or false to the sub attributes to activate the respective hook routine.
## Interrupts
   For interrupts, the user should navigate to the <Interrupts> attribute in XML and the user can add interrupts to the os. An example interrupt is already added to the config file for reference. The user should provide the <OsInterruptID> which refers to the exact name of the interrupt handler that they are configuring, user should note that the input id should be an interrupt that is already supported by the target. The user should now define whether the interrupt is of type Category 1 or Category 2, provide the priority number for the interrupt, and reference the allocated resources. 
## Events
   For Events, the user should navigate to the <Events> attribute in the XML and the user simply has to add an Event and give it a name by adding an attribute <OsEventName> containing the name of the event that he/she will reference in their code. Three events have already been added as default for reference.
## Resources
   For Resources, the user should navigate to the <Resources> attribute in the XML and the user can add the resources he wishes to add in his OS. the user will need to provide the  name of the resource to be referenced in their code, along with the ceiling priority, and the resource property which should always be 0, since we only support the standard property. We already provide two examples of resources in our OS.
## Tasks
   For Tasks, the user should navigate to the <Tasks> attribute in the XML and the user can add a task by adding the Task name <OsTaskName> which will be the name of the function in the code, <OsTaskActivation> which refers to how many times a task can be activated, <OsTaskPriority> for the priority of the task, <OsTaskSchedule> for weather the task is preemptable or not which should be either “Full” or “Task_NON”, <OsTaskType> which refers to whether the task is “Extended” or “Standard” , <OsTaskEventRef> and <OsTaskResourceRef> which refers to the events and resources allocated to the task, and finally <OsTaskAutostart> which is either true or false which will define whether the task will activate when booting the OS or not.

Example Code:

   Here is an example of code that showcase how the functions should look like, how the main should look like and the overall look of the main.c. Please note that the following code sample is on the STM32FE303E Microcontroller.


   ```c
#include "OS.h"
#include "OsGenerated.h"
void Task1Func()
{
	x = 12;
	y = 5;
	delayMs();
	uint8_t st;
	st = WaitEvent(Event1);
	delayMs();
	z = x * y;
	st = TerminateTask();
	return;
}

void Task2Func()
{
	delayMs();
	uint8_t st;
	ActivateTask(Task3);
	SetEvent(Task1,Event1);
	st = TerminateTask();
}
void Task3Func()
{
	uint8_t st;
	delayMs();
	st = TerminateTask();
}

void IdleFunc()
{
	while(1)
	{
	}
	return;
}
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_USART3_UART_Init();
 __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
  StartOS(OSDEFAULTAPPMODE);
  while (1)
  {
  }
}
```

