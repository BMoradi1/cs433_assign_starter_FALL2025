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
#include <tuple>
#include <algorithm>

std::vector<std::tuple<string, int, int>> finalList; //Process id, waittime, 
std::vector<PCB> prioritySchedule; //Our schedule, sorted through a maxheap by priority

SchedulerPriority::SchedulerPriority(){
    //TODO constructor
}

SchedulerPriority::~SchedulerPriority(){
    //TODO deconstructor 
}
void heapify(std::vector<PCB>& prioritySchedule, int count, int i){

    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < count && prioritySchedule[left].priority < prioritySchedule[largest].priority){
        largest = left;
    }

    if(right < count && prioritySchedule[right].priority < prioritySchedule[largest].priority){ 
        largest = right;
    }

    if(left < count && prioritySchedule[left].priority == prioritySchedule[largest].priority){ //if both the left and "largest" have the same burst time, prioritize the process with a smaller PID
        if(prioritySchedule[left].id > prioritySchedule[largest].id){
            largest = left;
        }
    }

     if(right < count && prioritySchedule[right].priority == prioritySchedule[largest].priority){ //if both the right and "largest" have the same burst time, prioritize the process with a smaller PID
        if(prioritySchedule[right].id > prioritySchedule[largest].id){
            largest = right;
        }
    }
    
    if(largest!=i){
        swap(prioritySchedule[i], prioritySchedule[largest]);
        heapify(prioritySchedule, count, largest);
    }
}

void SchedulerPriority::init(std::vector<PCB>& process_list){
    int count = process_list.size();
    int time = 0;

    string pid;
    int waitTime;
    int turnaroundTime; 
    
    prioritySchedule = process_list;

    for(int i = (count / 2) - 1; i >= 0; i--){
    heapify(prioritySchedule, count, i);
    }
        
    for (int i = count - 1; i > 0; i--){
            swap(prioritySchedule[0], prioritySchedule[i]);
            heapify(prioritySchedule, i, 0);
    }

    for (int i = 0; i < count; i++){
        cout << "Running Process " << prioritySchedule[i].name << " for " << prioritySchedule[i].burst_time << " time units" << endl;
        pid = prioritySchedule[i].name;
        waitTime = time;
        time = time + prioritySchedule[i].burst_time;
        turnaroundTime = time;
        finalList.push_back(tuple<string, int, int>(pid,waitTime,turnaroundTime));
    }
     sort(finalList.begin(), finalList.end(), [](const tuple<string,int,int> &a, const tuple<string,int,int> &b){ //resort our list by original PID
        return get<0>(a) < get<0>(b);
    });
}

void SchedulerPriority::print_results(){

    float averageWait = 0;
    float averageTurnaround = 0;
    int count = prioritySchedule.size();
    
    for (int i = 0; i < count; i++){
        averageTurnaround += get<2>(finalList[i]); //add each turnaround time to our average
        averageWait += get<1>(finalList[i]); //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / prioritySchedule.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / prioritySchedule.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerPriority::simulate(){

int count = prioritySchedule.size();

for (int i = 0; i < count; i++){
   cout << get<0>(finalList[i]) << " turnaround time = " << get<2>(finalList[i]) << ", waiting time = " << get<1>(finalList[i]) << endl;
   }
}

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here