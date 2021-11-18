/* 
* this file is a part of Zi-RTOS project, https://github.com/over-infinity/Zi-RTOS
* Copyright (c) 2021, Over-Infinity 
*
*/
#ifndef INC_ZI_H
#define INC_ZI_H

#ifndef __cplusplus
extern "C" {
#endif

 #include "core/ziconfig.h"
  
typedef unsigned char Byte_t;
typedef unsigned int  Word_t;
typedef unsigned long Long_t;
typedef unsigned long long DoubleLong_t;
typedef signed char Int8_t;

  
#ifndef TRUE
  #define FALSE 0
  #define TRUE (!FALSE)
#endif

 #ifndef NULL
  #define NULL (void*)0
#endif
 
#define NORMAL_RETURN          (0)
#define ERROR_GENRAL           (-1)    // genral error
#define ERROR_TWO_MANY_TASK    (-2)    // task list add error, task list is already full
#define ERROR_DELETE_TASK      (-3)    // delete task error

typedef void(*TaskHandler_t)(void);
  
/* Task Control Block  */
typedef struct{
  TaskHandler_t task;
  Word_t delay;
  Word_t period;
  Byte_t priority;
  Byte_t run_freq;
  Byte_t suspended;
}TCB_t;  

  /* Public APIs prototypes */
  
  void Zi_Init(void);
  
  /* Task APIs */
  void Zi_Dispath_Task(void);
  Int8_t Zi_Add_Task(TaskHandler_t handler, const Word_t delay, Word_t period, Byte_t priority);
  Int8_t Zi_Remove_Task(const Byte_t);
  void Zi_Suspend_Task(const Byte_t taskId);
  void Zi_Resume_Task(const Byte_t taskId);
 
 void Zi_Scheduler(void);
   
  void Zi_Delay(Long_t tick);
  void Zi_Start();
  void Zi_Stop();
  
  DoubleLong_t Zi_GetTickCount();

#ifndef __cplusplus
}
#endif
#endif /* INC_ZI_H */
