/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Brynn Grofcsik, Bijan Moradi
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
   //TODO Constructor
}

SchedulerFCFS::~SchedulerFCFS(){
   //TODO Deconstructor
}

void SchedulerFCFS::init(std::vector<PCB>& process_list){

fcfsSchedule = process_list; //store our process list within our schedule

}

void SchedulerFCFS::print_results(){

float averageWait = 0;
float averageTurnaround = 0;

for (int i = 0; i < fcfsSchedule.size(); i++){
    averageTurnaround += turnaroundTimes[i]; //add each turnaround time to our average
    averageWait += waitTimes[i]; //add each wait time to our average
   }    
   averageTurnaround = averageTurnaround / fcfsSchedule.size(); //divide our total turnaround by the amount of PCBs
   averageWait = averageWait / fcfsSchedule.size(); // divide our total wait by the amout of PCBs

   cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerFCFS::simulate(){

   int time = 0; //Acts as a clock, tracks current time units

   for (int i = 0; i < fcfsSchedule.size(); i++){

   cout << "Running Process " << fcfsSchedule[i].name << " for " << fcfsSchedule[i].burst_time << " time units" << endl;
   waitTimes.push_back(time); //pushes back the time before execution to our list of wait times, this serves as the processes wait
   time = time + fcfsSchedule[i].burst_time; //"runs" the process, adds its burst time to the clock
   turnaroundTimes.push_back(time); //pushes back the turnaround time to our list of turnaround times

   }

for (int i = 0; i < fcfsSchedule.size(); i++){ //prints each process' name, turnaround time and wait time. Since theyre all in order already we can cycle through "i"
   cout << fcfsSchedule[i].name << " turnaround time = " << turnaroundTimes[i] << ", waiting time = " << waitTimes[i] << endl; 
   }
}
