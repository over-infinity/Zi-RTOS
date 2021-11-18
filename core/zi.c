/* 
* Zi-RTOS kernel V1.0
*
* this file is a part of Zi-RTOS project, https://github.com/over-infinity/Zi-RTOS
* Copyright (c) 2021, Over-Infinity 
*
*/

#include "core/zi.h"

DoubleLong_t Zi_TickCount;
static Byte_t Zi_ActiveScheduler = 0;

TCB_t Zi_TaskList[ZI_MAX_TASKS ];
TCB_t Zi_TaskSuspended[ZI_MAX_TASKS ];

void Zi_Init(void){ 
  
  for(int i=0; i < ZI_MAX_TASKS; i++){
    Zi_Remove_Task(i);
  }
  
  Zi_TickCount=0;
  
}  
  
void Zi_Dispath_Task(void){  
  
}


Int8_t Zi_Add_Task(TaskHandler_t handler, const Word_t delay, Word_t period, Byte_t priority){ 
  Byte_t taskId =0;  
  
  while((Zi_TaskList[taskId].task != NULL) && (taskId < ZI_MAX_TASKS))
    taskId++;
  
  if(taskId == ZI_MAX_TASKS)
    return ERROR_TWO_MANY_TASK;
  
  Zi_TaskList[taskId].task =handler;
  Zi_TaskList[taskId].delay=delay;
  Zi_TaskList[taskId].period=period;
  Zi_TaskList[taskId].priority=priority;
  Zi_TaskList[taskId].suspended=FALSE;
  
  return taskId;  
}

Int8_t Zi_Remove_Task(const Byte_t taskId){
  
  if(Zi_TaskList[taskId].task == NULL){ 
    // task is already has been deleted or no task to delete.
    return ERROR_DELETE_TASK;    
  }
  
  Zi_TaskList[taskId].task =NULL;
  Zi_TaskList[taskId].delay=0;
  Zi_TaskList[taskId].period=0;
  Zi_TaskList[taskId].priority=0;
  Zi_TaskList[taskId].suspended=FALSE;
  
  return NORMAL_RETURN;
}
    
void Zi_Suspend_Task(const Byte_t taskId){
  
  if(Zi_TaskList[taskId].task != NULL)(
     Zi_TaskList[taskId].suspended =TRUE;
    }
    
}

void Zi_Resume_Task(const Byte_t taskId){
  
  
}
   
void Zi_Delay(Long_t tick){  
  Long_t endTick=Zi_TickCount+tick;
  while(Zi_TickCount < endTick){
    ;
  }  
}


void Zi_Start(){
  
}

void Zi_Stop(){
  
}
  
DoubleLong_t Zi_GetTickCount(){  
  return Zi_TickCount;   
}
