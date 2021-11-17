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
    Zi_Resume_Task(i);
  }
  
  Zi_TickCount=0;
  
}  
  
void Zi_Dispath_Task(void){  
  
}


Byte_t Zi_Add_Task(TaskHandler_t handler, const Word_t delay, Word_t period, Byte_t priority){ 
  
  
}

Byte_t Zi_Remove_Task(Byte_t){
  
}
    
void Zi_Suspend_Task(Byte_t taskId){
  
  
}

void Zi_Resume_Task(Byte_t taskId){
  
  
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
