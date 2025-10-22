/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

vector<int> waitTimes; //A vector to hold our wait times
vector<int> turnaroundTimes; //A vector to hold our turnaround times
std::vector<PCB> prioritySchedule; //Our schedule, altered to be in order by priority

void heapify(std::vector<PCB>& sjfSchedule, int count, int i){

    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < count && prioritySchedule[left].burst_time > prioritySchedule[largest].burst_time){
        largest = left;
    }
    if(right < count && prioritySchedule[right].burst_time > prioritySchedule[largest].burst_time){
        largest = right;
    }
    
    if(largest!=i){
       // cout << "Swapping: " << sjfSchedule[i].name << " and " << sjfSchedule[largest].name << endl;
        swap(prioritySchedule[i], prioritySchedule[largest]);
        heapify(prioritySchedule, count, largest);
    }
}

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here