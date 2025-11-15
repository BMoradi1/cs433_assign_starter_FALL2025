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
      OurBuffer[in] = item; //if the count is zero, then the first index is zero
      bufferCount++;
      in = (in + 1)%bufferSize;
      //cout << "Added item!" << endl;
      return true;
   }
   return false;
}

//Removes an item from the buffer, On successful deletion return true.
bool Buffer::remove_item(buffer_item *item)
{
   /*
   cout << "Removing item: "<< *item<<endl;
   if(is_empty() == false)
   {
      for(int i = bufferCount - 1; i >= 0; i--)
      {
         cout << "Checking Buffer: " << OurBuffer[i] << "Against Removal Item: " << *item << " WITH BUFFER COUNT " << bufferCount <<endl;
         if(OurBuffer[i] == *item)
         {
            cout << "Consumed item!" << endl;
            bufferCount--;
            OurBuffer[i] = NULL;
            return true;
         }
      }
   */
   if(!is_empty())
   {
      *item = OurBuffer[out]; //pass item out as parameter as per zybook
      out = (out + 1)%bufferSize;
      bufferCount--;
      return true;
   }
      
   
   return false;
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

