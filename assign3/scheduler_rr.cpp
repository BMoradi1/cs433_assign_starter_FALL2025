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

// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here
vector<int> waitTimes; //A vector to hold our wait times
vector<int> turnaroundTimes; //A vector to hold our turnaround times
int time_quantum = 0;
int time;
std::vector<PCB> RRSchedule; //Our schedule, unaltered for a FCFS as the processes will be executed in order
std::vector<PCB> RRScheduleSaved;
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

    time = 0; //Tracks current time units
    RRSchedule = process_list; //store our process list within our schedule
    RRScheduleSaved = process_list; //preserve for result printing
    
}
void SchedulerRR::print_results()
{

    float averageWait = 0;
    float averageTurnaround = 0;

    for (int i = 0; i < RRScheduleSaved.size(); i++)
    {
        cout << "T" << i+1 << " turnaround time = " << turnaroundTimes[i] << ", waiting time = " << waitTimes[i] << endl;
    }
    for (int i = 0; i < RRScheduleSaved.size(); i++){
        averageTurnaround += turnaroundTimes[i]; //add each turnaround time to our average
        averageWait += waitTimes[i]; //add each wait time to our average
    }    
    averageTurnaround = averageTurnaround / RRSchedule.size(); //divide our total turnaround by the amount of PCBs
    averageWait = averageWait / RRSchedule.size(); // divide our total wait by the amout of PCBs

    cout << "Average turn-around time = " << averageTurnaround <<", Average waiting time = " << averageWait << endl;
}

void SchedulerRR::simulate()
{
    PCB running = RRSchedule.front();
    while(RRSchedule.size() > 0) //we loop until we exaust all processes
    {
        running = RRSchedule.front(); //get the first element in our schedule
        if(running.burst_time > time_quantum) //check if its runtime excedes the tq
        {
            cout << "Running Process" << running.name<<" for" << time_quantum << "time units";
            RRSchedule.erase(RRSchedule.begin());//remove it from the front, we will have to run it again
            running.burst_time = running.burst_time - time_quantum; //new burt time because it raun for time quantum time units
            RRSchedule.push_back(running); //add to back of schedule
        }
        else
        {
            cout << "Running Process" << running.name<<" for" << running.burst_time << "time units";
            RRSchedule.erase(RRSchedule.begin());//remove it from the front, we will have to run it again
        }
    }
}