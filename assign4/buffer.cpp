/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author ??? (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 *
 *
 * Zybooks Skeleton Code:
 * -------------------------
 /* 1. Get command line arguments argv[1],argv[2],argv[3] */
 /* 2. Initialize buffer */
 /* 3. Create producer thread(s) */
 /* 4. Create consumer thread(s) */
 /* 5. Sleep */
 /* 6. Exit */

#include "buffer.h"
#include <iostream>
//using namespace std;


//Buffer Object and Global Variables
buffer_item **OurBuffer;
int bufferCount = 0;
int bufferSize = 0;

 //Constructor
Buffer::Buffer(int size)
{
   OurBuffer = new buffer_item*[size];
   bufferSize = size;
}

//Deconstructor
Buffer::~Buffer()
{
   for(int i = 0; i < bufferSize;i++)
   {
      delete OurBuffer[i];
   }
   delete OurBuffer;
}

//Inserts an item into the buffer, On successful insertion return true.
bool insert_item(buffer_item *item)
{
   if(!is_full())
   {
      OurBuffer[bufferCount - 1] = item;
      bufferCount++;
      return true;
   }
   return false;
}
//Removes an item from the buffer, On successful deletion return true.
bool remove_item(buffer_item *item)
{
   if(!is_empty())
   {
      delete OurBuffer[bufferCount - 1];
      OurBuffer[bufferCount - 1] = NULL;
      bufferCount--;
      return true;
   }
   return false;
}

//Returns size of the buffer; how many items it can hold
int get_size()
{
 return bufferSize;
}

//Returns the count of the number of items currently in buffer
int get_count()
{
   return bufferCount;
}

//Checks if buffer is empty
bool is_empty()
{
   if(bufferCount <= 0)
   {
      return true;
   }
return false;
}

//Checks if buffer is full
bool is_full()
{
   if(bufferCount >= bufferSize)
   {
      return true;
   }
return false;
}

//Prints a list of items in the buffer
void print_buffer()
{
   std::string arrayPrint;
   arrayPrint.append("Buffer: [");
   for(int i = 0; i < bufferCount; i++)
   {
      arrayPrint.append(std::to_string((int)OurBuffer[i]));
      arrayPrint.append(", ");
   }
   arrayPrint.erase(arrayPrint.size() - 2); //removes the last comma and space
   arrayPrint.append("]");
   std::cout << arrayPrint << std::endl;
}
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

// TODO: Add your implementation of the buffer class here