/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Bijan Moradi, Bryn Grofcsik 
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"
#include <vector>

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) 
{
    
   // TODO: add your code here
    table = new std::vector<PCB*> ; //allocate our vector of PCB pointers
    tableSize = size;
    count = 0;

}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() 
{
   // TODO: add your code here
   // Delete all the PCBs in the table
   while(!table -> empty())
   {
        delete table -> back(); //delete the object at the back of the table vector
        table -> pop_back(); //remove the pointer from the table vectro
   }
   table -> clear(); //deallocates the table
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) 
{
    
    return (*table)[idx];
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // TODO: add your code here
    // Add a PCB pointer to the PCBTable at index idx.
    table -> insert(table -> begin() + idx, pcb);
    count++;
}
