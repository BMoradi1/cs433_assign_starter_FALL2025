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
//total page count
int pageCount;
//total frame count (size of  table)
int frameCount;
int totalFrames;


// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    pageCount = num_pages;
    totalFrames = num_frames;
    frameCount = 0;
    // TODO: Add additional implementation code
    frameCount = 0;
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    PageEntry newPage = PageEntry();

    newPage.dirty = true;
    newPage.valid = false;
    newPage.frame_num = frameCount;

    page_table[frameCount] = newPage;
    frameCount++;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    PageEntry firstIn = page_table[0];
    PageEntry newPage;

    newPage.dirty = true;
    newPage.valid = false;
    newPage.frame_num = 0;

    for(int i = 0; i < frameCount - 1; i++){
        page_table[i] = page_table[i + 1];
    }

    page_table[frameCount - 1] = newPage;

    return firstIn.frame_num;
}