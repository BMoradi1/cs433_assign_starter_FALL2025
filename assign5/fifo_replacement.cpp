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
int lastReplacedIndex = 0;
//total page count
int pageCount;
//total frame count (size of  table)
int frameCount;


// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    pageCount = num_pages;
    frameCount = num_frames;
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    //load_page(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    PageEntry firstIn = page_table[0];
    PageEntry newPage;

    newPage.dirty = true;
    newPage.valid = false;
    newPage.frame_num = page_num;
    page_table[0] = newPage;

    for(int i = 0; i < frameCount - 1; i++){
        page_table[i] = page_table[i + 1];
    }
    if (lastReplacedIndex == frameCount - 1){
        lastReplacedIndex = 0;
    }
    else{
        lastReplacedIndex++;
    }
    return firstIn.frame_num;
}