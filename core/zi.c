/*
 * this file is a part of Zi-RTOS project, https://github.com/over-infinity/Zi-RTOS
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Over-Infinity
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* zi.c */

#include "core/zi.h"

DoubleLong_t Zi_TickCount;
static Byte_t Zi_ActiveScheduler = FALSE;

TCB_t Zi_TaskList[ZI_MAX_TASKS];

void Zi_Init(void){ 
  
  for(int i=0; i < ZI_MAX_TASKS; i++){
    Zi_Remove_Task(i);
  }
  
  Zi_TickCount=0;
  
}  
/****************************************************************
 * @name i_Add_Task
 * @brief     :add new task to the Zi_TaskList if there is not any 
               empty entry in the Zi_TaskList, it return error.
 * @param  handle pointer to function task.
 * @param  delay this param indicate that  delay before executing task
 * @param  period indicate period frequency of executing task. if task is one-shot runing set
 *                period to zero
 * @param  priority task priority (high value more priority).
 * @return    return taskId of recently added task or error code(ERROR_TWO_MANY_TASK)
 * @author    :over-infinity
 * @date      :18-11-2021
 ****************************************************************/
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

/****************************************************************
 * @function  :Zi_Suspend_Task
 * @brief     :suspended task by getting taskId we simply
 *             set a suspended field in the task TCB.
 * @input     :taskId, taskId will return by Zi_Add_Task function.
 * @author    :over-infinity
 * @date      :18-11-2021
 ****************************************************************/ 
void Zi_Suspend_Task(const Byte_t taskId){
  
  if(Zi_TaskList[taskId].task != NULL){
     Zi_TaskList[taskId].suspended =TRUE;
    }   
}

void Zi_Resume_Task(const Byte_t taskId){
  
  if(Zi_TaskList[taskId].task != NULL){
     Zi_TaskList[taskId].suspended =FALSE;
    }
}

void Zi_Delay(Long_t tick){  
  Long_t endTick=Zi_TickCount+tick;
  while(Zi_TickCount < endTick){
    ;
  }  
}

void Zi_Start(){
  if(!Zi_ActiveScheduler)
    Zi_ActiveScheduler=TRUE;
}

void Zi_Stop(){
  if(Zi_ActiveScheduler)
    Zi_ActiveScheduler=FALSE;
}
  
DoubleLong_t Zi_GetTickCount(){  
  return Zi_TickCount;   
}

/**  Return taskId of the most high priority task to execute **/
static Int8_t Zi_GetNextTaskId(void){  
  
  Int8_t taskIndex=-1;
  
  for(int i = 0; i < ZI_MAX_TASKS ; i++){
    if(Zi_TaskList[i].run_freq > 0 && Zi_TaskList[i].suspended == FALSE){
      
      if(taskIndex < 0){
        taskIndex=i;
      }else if(Zi_TaskList[i].priority > Zi_TaskList[taskIndex].priority){
        taskIndex=i;        
      }   
    }    
  }  
  return taskIndex; 
}

void Zi_Dispath_Task(void){  
  
  Int8_t taskId = Zi_GetNextTaskId();
  
  if(taskId >= 0){
    /* execute task with high priority */
    (*Zi_TaskList[taskId].task)();
    
    Zi_TaskList[taskId].run_freq -=1;
    
    if(Zi_TaskList[taskId].period ==0)
      Zi_Remove_Task(taskId);       
  }  
}

/* Zi_Scheduler : increment tick count and update internal tasks state  */
void Zi_Scheduler(void){  
  Zi_TickCount++;
  if(Zi_ActiveScheduler){
    for(int i=0; i< ZI_MAX_TASKS; i++){
      if(Zi_TaskList[i].task !=  NULL)
        if(Zi_TaskList[i].delay == 0 ){
          Zi_TaskList[i].run_freq +=1;
          if(Zi_TaskList[i].period)
            Zi_TaskList[i].delay=Zi_TaskList[i].period;          
        }else{
          Zi_TaskList[i].delay -=1;
        }      
    } // end for    
  }  //end if(Zi_ActiveScheduler)
} // end Zi_Scheduler function




