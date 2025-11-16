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
*/

#include "buffer.h"
#include <queue>
#include <iostream>
using namespace std;


//Buffer Object and Global Variables
buffer_item *OurBuffer;
int bufferCount = 0;
int bufferSize = 0;
int in = 0;
int out = 0;

 //Constructor
Buffer::Buffer(int size)
{
   OurBuffer = new buffer_item[size];
   bufferSize = size;
}

//Deconstructor
Buffer::~Buffer()
{
    delete [] OurBuffer; 
}

buffer_item Buffer::getBufferFront(){
   return OurBuffer[0];
}

//Returns size of the buffer; how many items it can hold
int Buffer::get_size()
{
 return bufferSize;
}

//Returns the count of the number of items currently in buffer
int Buffer::get_count()
{
   return bufferCount;
}

//Checks if buffer is empty
bool Buffer::is_empty()
{
   if(bufferCount <= 0)
   {
      return true;
   }
return false;
}

//Checks if buffer is full
bool Buffer::is_full()
{
   if(bufferCount == bufferSize)
   {
      return true;
   }
return false;
}
//Inserts an item into the buffer, On successful insertion return true.
bool Buffer::insert_item(buffer_item item)
{
   if(is_full() == false)
   {
      OurBuffer[bufferCount] = item; //if the count is zero, then the first index is zero
      bufferCount++;
      //cout << "Added item!" << endl;
      return true;
   }
   return false;
}

//Removes an item from the buffer, On successful deletion return true.
bool Buffer::remove_item(buffer_item *item)
{
   if(!is_empty())
   { 
      *item = OurBuffer[0]; //set item pointer to removed item as per zybook.
      for(int i = 0; i < bufferCount - 1; i++) {
         OurBuffer[i] = OurBuffer[i + 1]; //shift everything to keep FIFO order
      }
      bufferCount--; // keep track of our count
      return true;
   }
   return false; //shouldn't come here
}


//Prints a list of items in the buffer
void Buffer::print_buffer()
{
   std::string arrayPrint;
   arrayPrint.append("Buffer: [");
   for(int i = 0; i < bufferCount; i++)
   {
      
         arrayPrint.append(std::to_string(OurBuffer[i]));
         if(i < bufferCount-1)
            arrayPrint.append(", ");
      
   }
   //arrayPrint.erase(arrayPrint.size() - 2); //removes the last comma and space
   arrayPrint.append("]");
   std::cout << arrayPrint << std::endl;
}

