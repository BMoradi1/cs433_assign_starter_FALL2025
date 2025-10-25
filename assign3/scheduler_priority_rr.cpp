/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Brynn Grofcsik, Bijan Moradi
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_priority_rr.h"
#include <tuple>
#include <algorithm>

// TODO: add implementation of SchedulerPriorityRR constructor, destrcutor and 
// member functions init, print_results, and simulate here

int time_quantum = 0;

std::vector<PCB> RRSchedule; //Our schedule
std::vector<PCB> RRScheduleSaved; //Holds our original, unaltered values
std::vector<std::tuple<PCB, int, int>> finalList; //Process id, waittime, and turnaround time. Essential for storing our final values together

SchedulerPriorityRR::SchedulerPriorityRR(int tq)
{
   //TODO Constructor
   time_quantum = tq;
}

SchedulerPriorityRR::~SchedulerPriorityRR()
{
   //TODO Deconstructor
}


void SchedulerPriorityRR::init(std::vector<PCB>& process_list)
{
    RRSchedule = process_list; //store our process list within our schedule
    RRScheduleSaved = process_list; //store an unaltered list for calculating wait time later using original burst times
    sort(RRSchedule.begin(), RRSchedule.end(), [](const PCB &a, const PCB&b){ //resort our list by priority
        return a.priority > b.priority; //comparing priority
    });
}

void SchedulerPriorityRR::print_results()
{

    float averageWait = 0; //set to 0 as we'll be using a += to add all together
    float averageTurnaround = 0;  //set to 0 as we'll be using a += to add all together
    int count = RRScheduleSaved.size(); //Count of our PCBs


   for (int i = 0; i < count; i++){
   cout << get<0>(finalList[i]).name << " turnaround time = " << get<2>(finalList[i]) << ", waiting time = " << get<1>(finalList[i]) << endl; //print process name (get 0 represents the PCB), turnaround time (get2 is turnaround time) and waiting time (get1 is waiting time)
   }

     for (int i = 0; i < count; i++){
        averageTurnaround += get<2>(finalList[i]); //add each turnaround time to our average
        averageWait += get<1>(finalList[i]); //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / RRScheduleSaved.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / RRScheduleSaved.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerPriorityRR::simulate()
{
    int time = 0; //we need to store the amount of time passed per iteraion to calculate turnaround & wait
    int count = RRSchedule.size(); //amount of PCBs
    int waitTime; //stores a temporary wait time
    PCB running = RRSchedule.front(); //our first PCB in the queue
    while(count > 0) //we loop until we exaust all processes
    {
        running = RRSchedule.front(); //get the first element in our schedule

        if(( count == 1 && running.burst_time > time_quantum) || count > 1 && running.burst_time > time_quantum && running.priority > RRSchedule[1].priority)
        {
            cout << "Running Process " << running.name <<" for " << running.burst_time << " time units" << endl;
            RRSchedule.erase(RRSchedule.begin());//remove it from the queue. execution is finished
            time += running.burst_time; //add time passed to our clock
            waitTime = time - RRScheduleSaved[running.id].burst_time; //In round robin, turnaround time - burst time = wait time.
            finalList.push_back(tuple<PCB, int, int>(running,waitTime,time)); //Store our PCB, wait time and turnaround time in the final list for later reference
            count--;
        }
        else if(running.burst_time > time_quantum) //check if its runtime excedes the tq
        {
            cout << "Running Process " << running.name << " for " << time_quantum << " time units" << endl;
            RRSchedule.erase(RRSchedule.begin());//remove it from the front, we will have to run it again
            running.burst_time = running.burst_time - time_quantum; //new burt time because it raun for time quantum time units
            for(int i = 0; i < RRSchedule.size(); i++)
            {
                if(running.priority > RRSchedule[i].priority) //find where in the schedule to reinsert
                {
                    RRSchedule.insert(RRSchedule.begin()+i,running);
                    break;
                }
            }
            time += time_quantum; //add time passed to our clock
        }
        else
        {
            cout << "Running Process " << running.name <<" for " << running.burst_time << " time units" << endl;
            RRSchedule.erase(RRSchedule.begin());//remove it from the queue. execution is finished
            time += running.burst_time; //add time passed to our clock
            waitTime = time - RRScheduleSaved[running.id].burst_time; //In round robin, turnaround time - burst time = wait time.
            finalList.push_back(tuple<PCB, int, int>(running,waitTime,time)); //Store our PCB, wait time and turnaround time in the final list for later reference
            count--;
        }
     }
  sort(finalList.begin(), finalList.end(), [](const tuple<PCB,int,int> &a, const tuple<PCB,int,int> &b){ //resort our list by original Process ID, this will be used for printing
        return get<0>(a).id < get<0>(b).id; //compare process ids of the first item within the tuple (PCB)
    });
}