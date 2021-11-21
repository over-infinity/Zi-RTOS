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

#ifndef INC_ZI_H
#define INC_ZI_H

#ifdef __cplusplus
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
  #define NULL (void*)(0)
#endif
 
#define NORMAL_RETURN          (0)
#define ERROR_GENERAL           (-1)    // general error
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

#ifdef __cplusplus
}
#endif
#endif /* INC_ZI_H */
