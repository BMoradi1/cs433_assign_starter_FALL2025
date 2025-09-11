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

    PCB* current = heaparray[index];
    PCB* parent = heaparray[getParent(index)];
 
    int currPrior = current->priority;
    int parentPrior = parent->priority;

    if(currPrior > parentPrior && getParent(index) >= 0){
      swap(index, getParent(index));

      percolateUp(getParent(index));
    }
 }

 void ReadyQueue::percolateDown(int index){

   PCB* current = heaparray[index];
   PCB* left = heaparray[getLeft(index)];
   PCB* right = heaparray[getRight(index)];

   int currPrior = current->priority;
   int leftPrior = left->priority;
   int rightPrior = right->priority;

     if (currPrior < leftPrior && leftPrior > rightPrior && getRight(index) <= count){ //if the index's value is less that its left child, and the left is greater than the right, and the left is not out of bounds, swap.
  swap(index, getLeft(index));
    percolateDown(index);
  }

  else if(currPrior < rightPrior && getRight(index) <= count){
    swap(index, getRight(index));
    percolateDown(index);
  }
 }  

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
       if(count == capacity) //array is full, we need to resize
    {
        PCB** newHeap = new PCB*[capacity + 1]; //add a slot for the element
        for (int i = 0; i < count; i++)//loop to copy elements to new array
        {
            newHeap[i] = heaparray[i];
        }
        delete[] heaparray; //delete old heap array
        heaparray = newHeap; 
        capacity = capacity + 1; //account for the new slot
    }
    heaparray[count] = pcbPtr; //insert the value
    count++; //increment the count since we have a new element
    percolateUp(count - 1); // restore heap structure
  // TODO: resize the Heap array if neccessary and insert the value into the
  // heap.
  // TODO: percolate the Heap to rearange after th
}

void ReadyQueue::swap(int index1, int index2){
    PCB* temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
    if (count == 0){
      return NULL;
    }
    PCB* min = heaparray[0];

    heaparray[0] = heaparray[count - 1];
    count--;
    if(count > 1){
      percolateDown(0);
    }
    min -> setState(ProcState::RUNNING);
    return min;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count;
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