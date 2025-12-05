/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"


// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
  
    // TODO: Add additional implementation code
}

FIFOReplacement::~FIFOReplacement() {
    while (!fifo_queue.empty()) {   
        fifo_queue.pop();  
    }
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    //set new page's frame num to the next currently avaliable (current_frame pulled from replacement)
    page_table[page_num].frame_num = current_frame; 
    //set valid status to true
    page_table[page_num].valid = true; 

    //push page num into the back of the fifo queue 
    fifo_queue.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    //since this is FIFO, our victim page is the first in queue
    int victim_page = fifo_queue.front();
    fifo_queue.pop();

    //grab our victim page's frame num since we'll be using it and set its valid status to false
    int victim_frame = page_table[victim_page].frame_num;
    page_table[victim_page].valid = false;

    //set our page's frame num as the victim's frame num and set its valid status to true
    page_table[page_num].frame_num = victim_frame;
    page_table[page_num].valid = true;

    //push new page to back of stack
    fifo_queue.push(page_num);

    return victim_page;
}