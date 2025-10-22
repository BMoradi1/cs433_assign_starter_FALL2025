/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

//References: https://www.geeksforgeeks.org/dsa/heap-sort/

#include "scheduler_sjf.h"

vector<int> waitTimes; //A vector to hold our wait times
vector<int> turnaroundTimes; //A vector to hold our turnaround times
std::vector<PCB> sjfSchedule; //Our schedule, sorted through a maxheap by burst time

SchedulerSJF::SchedulerSJF(){
    //TODO Constructor
}

SchedulerSJF::~SchedulerSJF(){
    //TODO Deconstructor
}

void heapify(std::vector<PCB>& sjfSchedule, int count, int i){

    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < count && sjfSchedule[left].burst_time > sjfSchedule[largest].burst_time){
        largest = left;
    }
    if(right < count && sjfSchedule[right].burst_time > sjfSchedule[largest].burst_time){
        largest = right;
    }
    
    if(largest!=i){
       // cout << "Swapping: " << sjfSchedule[i].name << " and " << sjfSchedule[largest].name << endl;
        swap(sjfSchedule[i], sjfSchedule[largest]);
        heapify(sjfSchedule, count, largest);
    }
}

void SchedulerSJF::init(std::vector<PCB>& process_list){
    int count = process_list.size();
    int time = 0;

    sjfSchedule = process_list;

    for(int i = count / 2 - 1; i >= 0; i--){
    heapify(sjfSchedule, count, i);
    }
        
    for (int i = count - 1; i > 0; i--){
            swap(sjfSchedule[0], sjfSchedule[i]);
            heapify(sjfSchedule, i, 0);
    }

    for (int i = 0; i < count; i++){
        cout << "Running Process " << sjfSchedule[i].name << " for " << sjfSchedule[i].burst_time << " time units" << endl;
        waitTimes.push_back(time);
        time = time + sjfSchedule[i].burst_time;
        turnaroundTimes.push_back(time); 
    }
}

void SchedulerSJF::print_results(){

    float averageWait = 0;
    float averageTurnaround = 0;
    int count = sjfSchedule.size();
    
    for (int i = 0; i < count; i++){
        averageTurnaround += turnaroundTimes[i]; //add each turnaround time to our average
        averageWait += waitTimes[i]; //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / sjfSchedule.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / sjfSchedule.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerSJF::simulate(){

int count = sjfSchedule.size();

//TODO: fix re-sort by PID

for (int i = 0; i < count; i++){
   cout << sjfSchedule[i].name << " turnaround time = " << turnaroundTimes[i] << ", waiting time = " << waitTimes[i] << endl;
   }
}
// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here
