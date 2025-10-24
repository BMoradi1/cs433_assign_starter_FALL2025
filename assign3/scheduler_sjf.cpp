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
#include <tuple>
#include <algorithm>


std::vector<std::tuple<string, int, int>> finalList; //Process id, waittime, turnaround time
std::vector<PCB> sjfSchedule; //Our schedule, sorted through a maxheap by burst time

SchedulerSJF::SchedulerSJF(){
    //TODO Constructor
}

SchedulerSJF::~SchedulerSJF(){
    //TODO Deconstructor
}

void heapify(std::vector<PCB>& sjfSchedule, int count, int i){

    int shortest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < count && sjfSchedule[left].burst_time > sjfSchedule[shortest].burst_time){
        shortest = left;
    }
   if(right < count && sjfSchedule[right].burst_time > sjfSchedule[shortest].burst_time){
        shortest = right;
    }

     if(left < count && sjfSchedule[left].burst_time == sjfSchedule[shortest].burst_time){ //if both the left and "shortest" have the same burst time, prioritize the process with a smaller PID
           shortest = left;
        }

     if(right < count && sjfSchedule[right].burst_time == sjfSchedule[shortest].burst_time){ //if both the right and "shortest" have the same burst time, prioritize the process with a smaller PID
        if(sjfSchedule[right].id > sjfSchedule[shortest].id){
            shortest = right;
        }
    }
    
    if(shortest!=i){
       // cout << "Swapping: " << sjfSchedule[i].name << " and " << sjfSchedule[largest].name << endl;
        swap(sjfSchedule[i], sjfSchedule[shortest]);
        heapify(sjfSchedule, count, shortest);
    }
}

void SchedulerSJF::init(std::vector<PCB>& process_list){
    int count = process_list.size();
    int time = 0;

    string pid;
    int waitTime;
    int turnaroundTime; 
    
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
        pid = sjfSchedule[i].name;
        waitTime = time;
        time = time + sjfSchedule[i].burst_time;
        turnaroundTime = time;
        finalList.push_back(tuple<string, int, int>(pid,waitTime,turnaroundTime));
    }
     sort(finalList.begin(), finalList.end(), [](const tuple<string,int,int> &a, const tuple<string,int,int> &b){ //resort our list by original PID
        return get<0>(a) < get<0>(b);
    });
}

void SchedulerSJF::print_results(){

    float averageWait = 0;
    float averageTurnaround = 0;
    int count = sjfSchedule.size();
    
    for (int i = 0; i < count; i++){
        averageTurnaround += get<2>(finalList[i]); //add each turnaround time to our average
        averageWait += get<1>(finalList[i]); //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / sjfSchedule.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / sjfSchedule.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerSJF::simulate(){

int count = sjfSchedule.size();

for (int i = 0; i < count; i++){
   cout << get<0>(finalList[i]) << " turnaround time = " << get<2>(finalList[i]) << ", waiting time = " << get<1>(finalList[i]) << endl;
   }
}
// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here
