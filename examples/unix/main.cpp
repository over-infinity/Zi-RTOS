
/* 
* *
* this file is a part of Zi-RTOS project, https://github.com/over-infinity/Zi-RTOS
* Copyright (c) 2021, Over-Infinity 
*
*/

#include <iostream>
#include "core/zi.h"

void Task_1(void){
	std::cout << "Execute Task 1" << std::endl;
}

void Task_2(void){
	std::cout << "Execute Task 2" << std::endl;	
}

int main(int argc, char** argv){
	
	Zi_Init();

	int task1Id = Zi_Add_Task(Task_1,10000000,10000000,2);
	int task2Id = Zi_Add_Task(Task_2,5000000,5000000,1);
	/*executing frequency of task 2 is twice of task 1. 
	for exit from program press ctrl+z in linux*/

	Zi_Start();

	while(true){

		Zi_Scheduler();
		Zi_Dispath_Task();

	}

	Zi_Stop();

	return 0;
}
