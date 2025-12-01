/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author ??? (TODO: your name)
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
int lastReplacedIndexLIFO = pageCountLIFO - 1;


// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    frameCountLIFO = num_frames;
    pageCountLIFO = num_pages;
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    load_page(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    PageEntry lastOut = page_table[lastReplacedIndexLIFO];
    PageEntry newPage;

    newPage.dirty = true;
    newPage.valid = false;
    newPage.frame_num = page_num;

    page_table[lastReplacedIndexLIFO] = newPage;

    for(int i = 0; i < frameCountLIFO - 1; i++){
        page_table[i] = page_table[i + 1];
    }  
    if (lastReplacedIndexLIFO == 0){
        lastReplacedIndexLIFO = frameCountLIFO - 1;
    }
    else{
        lastReplacedIndexLIFO--;
    }
    return lastOut.frame_num;
}