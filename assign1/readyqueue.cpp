#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code

int capacity;
/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     //TODO: add your code here
    capacity = 100;
    heaparray = new PCB*[capacity];
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
    printf("Constructor\n");
    this->capacity = length;
    this->heaparray = values;
    this->count = count;

      for(int i = 0; i < length; i++)
  {
    this->heaparray[i] = values[i];
  }

  this -> heapify(); //restore the heap property.
 }

void ReadyQueue::heapify() 
{
  // TODO: Organize the heap values by percolating through the heap
  for(int i = (count/2) - 1; i >= 0; i-- ) //start from last non leaf node
  {
    percolateDown(i); //pecholate the heap 
  }
}

 void ReadyQueue::percolateUp(int index){
  //  printf("PercolateUP\n");
    if(index == 0) //we hit the root
  {
    return; //break out of recursion
  }

   if(index < 0 || index >= count)
  { 
    throw out_of_range("Index is out of range");
  }

    if(heaparray[index]->getPriority() > heaparray[(index-1)/2]->getPriority()){

      swap(index, (index-1)/2);
      percolateUp((index-1)/2);
    } 
 }

 void ReadyQueue::percolateDown(int index){
//  printf("PercolateDown");
  // TODO: check the values at index in the heap and decide whether they need to
  // be swapped. Run recursively until the current node is bigger than its
  // children

  if(index < 0 || index >= count)
  { 
    throw out_of_range("Index is out of akerange");
  }

  int largestChildIndex = index;

  if(2*index+1 < count && heaparray[2*index+1] -> getPriority() > heaparray[largestChildIndex] -> getPriority()) //check if its within heap bounds, then check if its larger than parent
  {
    largestChildIndex = 2*index+1; //its bigger so set the largest child index
  } 
  if(2*index+2 < count &&  heaparray[2*index+2] -> getPriority() > heaparray[largestChildIndex] -> getPriority()) //now we check it with the right child
  {
    largestChildIndex = 2*index+2; //right child bigger than left child and bigger than index. set it
  }
  if(largestChildIndex != index) //check if index and children were in the right order. if largest child index change then they were not. Recurse.
  {
    swap(index, largestChildIndex); //its smaller, lets swap
    percolateDown(largestChildIndex); //recursive call
  }
 }  

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
   //printf("Addding PCB With Priority:");
   //cout << pcbPtr -> getPriority() << endl;
      pcbPtr -> setState(ProcState::READY);
       if(count == capacity) //array is full, we need to resize
    {
        PCB** newHeap = new PCB*[capacity * 2]; //add a slot for the element
        for (int i = 0; i < count; i++)//loop to copy elements to new array
        {
            newHeap[i] = heaparray[i];
        }
        delete[] heaparray; //delete old heap array
        heaparray = newHeap; 
        capacity = capacity * 2; //account for the new slot
    }
    heaparray[count] = pcbPtr; //insert the value
    count++; //increment the count since we have a new element
    percolateUp(count - 1); // restore heap structure
  // TODO: resize the Heap array if neccessary and insert the value into the
  // heap.
  // TODO: percolate the Heap to rearange after th
}

void ReadyQueue::swap(int index1, int index2){
 // printf("swap\n");
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
  //  printf("remove\n");
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
  cout << "Display Processes in ReadyQueue: " << endl;
  int i;
  //cout << "[ ";
  for (i = 0; i < count; i++)
  {
    //cout << " ";
    heaparray[i] -> display();
  }
  //cout << "]\n";
}