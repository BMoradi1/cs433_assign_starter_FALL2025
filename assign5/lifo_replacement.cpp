/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Brynn Grofcsik  and Bijan Moradi (TODO: your name)
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

//total page count
int pageCountLIFO;
//total frame count (size of  table)
int frameCountLIFO;
//last replaced index
int lastReplacedIndexLIFO;


// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    //inputed page's frame number will be set to the next avaliable frame in stack (current frame pulled from replacement)
    page_table[page_num].frame_num = current_frame;
    //page_num now set valid since it's data is accessible now
    page_table[page_num].valid = true;  

    //push page to top of stack
    lifo_stack.push(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {

    //our victim page will be at the top of the lifo stack, so we'll pop it
    int victim_page = lifo_stack.top();
    lifo_stack.pop();

    //grab our victim frame for new page and set it's valid status to false
    int victim_frame = page_table[victim_page].frame_num;
    page_table[victim_page].valid = false;
    
    //replace victim page with new page
    page_table[page_num].frame_num = victim_frame;
    page_table[page_num].valid = true;

    //push new page to the top of stack
    lifo_stack.push(page_num);

    //return the victim page num
    return victim_page;
}