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

std::vector<std::tuple<string, int, int>> finalList; //Process id, waittime, and turnaroud time
std::vector<PCB> prioritySchedule; //Our schedule, sorted through a heap by priority

SchedulerPriority::SchedulerPriority(){
    //TODO constructor
}

SchedulerPriority::~SchedulerPriority(){
    //TODO deconstructor 
}
void heapify(std::vector<PCB>& prioritySchedule, int count, int i){

    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < count && prioritySchedule[left].priority < prioritySchedule[smallest].priority){ //store left if in bound and smaller
        smallest = left;
    }

    if(right < count && prioritySchedule[right].priority < prioritySchedule[smallest].priority){ //store right if in bound and smaller
        smallest = right;
    }

    if(left < count && prioritySchedule[left].priority == prioritySchedule[smallest].priority){ //if both the left and "smallest" have the same burst time, prioritize the process with a smaller PID
        if(prioritySchedule[left].id > prioritySchedule[smallest].id){
            smallest = left;
        }
    }

     if(right < count && prioritySchedule[right].priority == prioritySchedule[smallest].priority){ //if both the right and "smallest" have the same burst time, prioritize the process with a smaller PID
        if(prioritySchedule[right].id > prioritySchedule[smallest].id){
            smallest = right;
        }
    }
    
    if(smallest!=i){
        swap(prioritySchedule[i], prioritySchedule[smallest]); //swap smallest and original index
        heapify(prioritySchedule, count, smallest); //recursive send
    }
}

void SchedulerPriority::init(std::vector<PCB>& process_list){
    prioritySchedule = process_list; //save our original process list
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

    int time = 0;

    string name;
    int waitTime;
    int turnaroundTime; 
    
    for(int i = (count / 2) - 1; i >= 0; i--){ //heapifying our queue and sorting it by priority
    heapify(prioritySchedule, count, i);
    }
        
    for (int i = count - 1; i > 0; i--){
            swap(prioritySchedule[0], prioritySchedule[i]);
            heapify(prioritySchedule, i, 0);
    }

    for (int i = 0; i < count; i++){
        cout << "Running Process " << prioritySchedule[i].name << " for " << prioritySchedule[i].burst_time << " time units" << endl;
        name = prioritySchedule[i].name; //store our process name for printing purposes
        waitTime = time; //store our time before "execution', this acts as our wait time
        time = time + prioritySchedule[i].burst_time; //"execution", adds to clock
        turnaroundTime = time; //stores time after "execution", acts as our turnaround time
        finalList.push_back(tuple<string, int, int>(name,waitTime,turnaroundTime));
    }
     sort(finalList.begin(), finalList.end(), [](const tuple<string,int,int> &a, const tuple<string,int,int> &b){ //resort our list by original process name
        return get<0>(a) < get<0>(b); //comparing names (index 0 in get)
    });

for (int i = 0; i < count; i++){
   cout << get<0>(finalList[i]) << " turnaround time = " << get<2>(finalList[i]) << ", waiting time = " << get<1>(finalList[i]) << endl; //prints our processes by name, turnaround time and waiting time
   }
}

