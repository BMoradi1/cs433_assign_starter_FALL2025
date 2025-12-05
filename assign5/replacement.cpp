/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Brynn Grofcsik  and Bijan Moradi (TODO: your name)
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here


// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	//TODO: Add your implementation here
    numPageFaults = 0;
    numReplacements = 0;
    free_frames = num_frames;
    current_frame = 0;         
    numberOfReferences = 0;

}

// Destructor
Replacement::~Replacement()
{
    // TOOD: Add your code here
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    // TODO: Add your implementation here
    numberOfReferences++;
    // If the page is valid, it calls the touch_page function. 
    if(page_table[page_num].valid == true) 
    {
        touch_page(page_num);
        return false;
    }
    // If the page is not valid but free frames are available, it calls the load_page function.
    if(page_table[page_num].valid == false && free_frames > 0){
        load_page(page_num);

        page_table[page_num].frame_num = current_frame; //page loaded into frame and its now a valid page
        page_table[page_num].valid = true; //set as valid

        current_frame++;
        numPageFaults++;
        free_frames--;
        return true;
    }
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    if(page_table[page_num].valid == false && free_frames == 0)
    {
        replace_page(page_num);
        numReplacements++;
        numPageFaults++;
        return true;

    }
    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        //Print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: \t\t" << numberOfReferences << std::endl;
		std::cout << "Number of page faults: \t\t" << numPageFaults << std::endl;
		std::cout << "Number of page replacements: \t" << numReplacements << std::endl;
}