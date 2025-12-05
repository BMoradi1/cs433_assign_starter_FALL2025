/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Brynn Grofcsik  and Bijan Moradi (TODO: your name)
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
    // TODO: Add necessary code here
    lruList.clear();
    lruMap.clear();
    free_frames.clear();
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    //printf("hello");
     page_table[page_num].valid = true;

     auto it = lruMap.find(page_num);
     if(it == lruMap.end())
        return;
    
    lruList.splice(lruList.begin(), lruList, it->second);
    lruMap[page_num] = lruList.begin();

}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    page_table[page_num].valid = false;

    int frame = free_frames.back();
    free_frames.pop_back();

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    lruList.push_front(page_num);
    lruMap[page_num] = lruList.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) 
{

    int victim = lruList.back();
    int frame = page_table[victim].frame_num;

    lruList.pop_back();
    lruMap.erase(victim);

    page_table[victim].valid = false;
    page_table[victim].frame_num = -1;

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    lruList.push_front(page_num);
    lruMap[page_num] = lruList.begin();

    return victim;
}