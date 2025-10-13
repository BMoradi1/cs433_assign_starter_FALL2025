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

vector<int> waitTimes;
vector<int> turnaroundTimes;
vector<PCB> FCFSschedule;

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
SchedulerFCFS::SchedulerFCFS(){

}

SchedulerFCFS::~SchedulerFCFS(){
}

void init(std::vector<PCB>& process_list){
//Doesnt need to be sorted since its FCFS
int time = 0;
int wait = 0;
for (int i = 0; i < process_list.size(); i++){
cout << "Running Process " << process_list[i].name << " for " << process_list[i].burst_time << " time units" << endl;

FCFSschedule[i] = process_list[i]; //accessibility for this class

wait = wait + time;
waitTimes[i] = wait;
time = time + process_list[i].burst_time;
turnaroundTimes[i] = time;

   }
}

void print_results(){

for (int i = 0; i < FCFSschedule.size(); i++){
   cout << FCFSschedule[i].name << " turnaround time = " << turnaroundTimes[i] << ", waiting time = " << waitTimes[i] << endl;
   }
}

void simulate(){
cout << "waht " << endl;
}
// member functions init, print_results, and simulate here
