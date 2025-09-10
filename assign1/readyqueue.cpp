#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue(int size)  {
     //TODO: add your code here
    capacity = size;
    heaparray = new PCB*[size];
    count = 0;
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    //TODO: add your code to release dynamically allocate memory
    delete[] heaparray;
}

/**
 * @brief constructor to build a heap from the table
 */

 ReadyQueue::ReadyQueue(PCB **values, int count, int length){
    this->capacity = length;
    this->heaparray = values;
    this->count = count;
 }

 void ReadyQueue::percolateUp(int index){
   
 }

 void ReadyQueue::percolateDown(int index){

   PCB* current = heaparray[index];
   PCB* left = heaparray[leftChild(index)];
   PCB* right = heaparray[rightChild(index)];

   int currPrior = current->priority;
   int leftPrior = left->priority;
   int rightPrior = right->priority;

     if (currPrior < leftPrior && leftPrior > rightPrior && leftChild(index) <= count){ //if the index's value is less that its left child, and the left is greater than the right, and the left is not out of bounds, swap.
  swap(index, leftChild(index));
    percolateDown(index);
  }
 }  

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    //TODO: add your code here
}

void ReadyQueue::swap(int index1, int index2){
    PCB* temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
int i;
  cout << "[ ";
  for (i = 0; i < count; i++)
  cout << heaparray[i] << " ";
  cout << "]\n";
}