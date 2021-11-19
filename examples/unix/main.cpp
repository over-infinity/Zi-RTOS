
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

	int task1Id = Zi_Add_Task(Task_1,100000,100000,2);
	int task2Id = Zi_Add_Task(Task_2,200000,200000,2);


	return 0;
}
