/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <tuple>
#include <algorithm>

// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here

int time_quantum = 0;

std::vector<PCB> RRSchedule; //Our schedule
std::vector<PCB> RRScheduleSaved; //Holds our original, unaltered values
std::vector<std::tuple<PCB, int, int>> finalList; //Process id, waittime, and turnaround time

SchedulerRR::SchedulerRR(int tq)
{
   //TODO Constructor
   time_quantum = tq;
}

SchedulerRR::~SchedulerRR()
{
   //TODO Deconstructor
}


void SchedulerRR::init(std::vector<PCB>& process_list)
{
    RRSchedule = process_list; //store our process list within our schedule
    RRScheduleSaved = process_list;
}

void SchedulerRR::print_results()
{

    float averageWait = 0;
    float averageTurnaround = 0;
    int count = RRScheduleSaved.size();


   for (int i = 0; i < count; i++){
   cout << get<0>(finalList[i]).name << " turnaround time = " << get<2>(finalList[i]) << ", waiting time = " << get<1>(finalList[i]) << endl;
   }

     for (int i = 0; i < count; i++){
        averageTurnaround += get<2>(finalList[i]); //add each turnaround time to our average
        averageWait += get<1>(finalList[i]); //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / RRScheduleSaved.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / RRScheduleSaved.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerRR::simulate()
{
    int time = 0;
    int count = RRSchedule.size();
    int test = count;
    int waitTime; //stores a temporary wait time
    PCB running = RRSchedule.front();
    while(count > 0) //we loop until we exaust all processes
    {
        running = RRSchedule.front(); //get the first element in our schedule
        if(running.burst_time > time_quantum) //check if its runtime excedes the tq
        {
            cout << "Running Process " << running.name << " for " << time_quantum << " time units" << endl;
            RRSchedule.erase(RRSchedule.begin());//remove it from the front, we will have to run it again
            running.burst_time = running.burst_time - time_quantum; //new burt time because it raun for time quantum time units
            RRSchedule.push_back(running); //add to back of schedule
            time += time_quantum;        
        }
        else
        {
            cout << "Running Process " << running.name <<" for " << running.burst_time << " time units" << endl;
            RRSchedule.erase(RRSchedule.begin());//remove it from the queue. execution is finished
            time += running.burst_time;
            waitTime = time - RRScheduleSaved[running.id].burst_time; //In round robin, turnaround time - burst time = wait time.
            finalList.push_back(tuple<PCB, int, int>(running,waitTime,time));
            count--;
        }
     }
  sort(finalList.begin(), finalList.end(), [](const tuple<PCB,int,int> &a, const tuple<PCB,int,int> &b){ //resort our list by original PID
        return get<0>(a).id < get<0>(b).id;
    });
}