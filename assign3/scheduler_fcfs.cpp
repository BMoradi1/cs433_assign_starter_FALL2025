/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

vector<int> waitTimes; //A vector to hold our wait times
vector<int> turnaroundTimes; //A vector to hold our turnaround times
std::vector<PCB> fcfsSchedule; //Our schedule, unaltered for a FCFS as the processes will be executed in order

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
SchedulerFCFS::SchedulerFCFS(){

}

SchedulerFCFS::~SchedulerFCFS(){
}

void SchedulerFCFS::init(std::vector<PCB>& process_list){

int time = 0;

fcfsSchedule = process_list;

for (int i = 0; i < process_list.size(); i++){

cout << "Running Process " << process_list[i].name << " for " << process_list[i].burst_time << " time units" << endl;

waitTimes.push_back(time);

time = time + process_list[i].burst_time;
turnaroundTimes.push_back(time);

   }
}

void SchedulerFCFS::print_results(){

float averageWait = 0;
float averageTurnaround = 0;

for (int i = 0; i < fcfsSchedule.size(); i++){
    averageTurnaround += turnaroundTimes[i];
    averageWait += waitTimes[i];
   }    
   averageTurnaround = averageTurnaround / fcfsSchedule.size();
   averageWait = averageWait / fcfsSchedule.size();

   cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerFCFS::simulate(){
for (int i = 0; i < fcfsSchedule.size(); i++){
   cout << fcfsSchedule[i].name << " turnaround time = " << turnaroundTimes[i] << ", waiting time = " << waitTimes[i] << endl;
   }
}
// member functions init, print_results, and simulate here
