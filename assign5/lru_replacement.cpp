/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Brynn Grofcsik  and Bijan Moradi 
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//https://www.geeksforgeeks.org/dsa/lru-cache-implementation-using-double-linked-lists/

#include "lru_replacement.h"
//#include <bits/stdc++.h>
int capacity;


// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    for (int i = num_frames - 1; i >= 0; i--){
        free_frames.push_back(i);
    }

}

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    //deconstructor for our lists and map
    lruList.clear();
    lruMap.clear();
    free_frames.clear();
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    //printf("hello");
     page_table[page_num].valid = true;

     //finds the page in the map
     auto it = lruMap.find(page_num);
     if(it == lruMap.end())
        return;
    
    //Moves the found page to the front of the list
    lruList.splice(lruList.begin(), lruList, it->second);
    //Updates page number's position in the map
    lruMap[page_num] = lruList.begin();

}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {

    //grab a free frame and remove it from the free frame list
    int frame = free_frames.back();
    free_frames.pop_back();
    
    //set incoming page's frame num and valid status
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    //add page to front of list and map
    lruList.push_front(page_num);
    lruMap[page_num] = lruList.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) 
{
    //victim is the least recently used page at the back of the list
    int victim = lruList.back();
    int frame = page_table[victim].frame_num;

    //removes victim from list and map
    lruList.pop_back();
    lruMap.erase(victim);

    //sets victim page to invalid and frame num to -1
    page_table[victim].valid = false;
    page_table[victim].frame_num = -1;

    //sets new page's frame num to victim's frame num and valid status to true
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    //adds new page to front of list and map
    lruList.push_front(page_num);
    lruMap[page_num] = lruList.begin();

    return victim;
}