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


LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    for (int i = num_frames - 1; i >= 0; i--)
    {
        free_frames.push_back(i); 
    }//free frame vector initialization

}


LRUReplacement::~LRUReplacement()
{
    //clear our datastructures
    lruList.clear();
    lruMap.clear();
    free_frames.clear();
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
     page_table[page_num].valid = true; //set the new page as valid

     auto it = lruMap.find(page_num); //search thtough our LRU hash map and check if its in the map. Used because map allows a o(1) search 
     if(it == lruMap.end()) //we didn't find it, so return
        return;
    
    lruList.splice(lruList.begin(), lruList, it->second); //we need to move the element at location page_num (corrisponding iterator) to the front of the LRU tracking list
    lruMap[page_num] = lruList.begin();

}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) 
{
    page_table[page_num].valid = false;

    int frame = free_frames.back(); //grab  a free frame
    free_frames.pop_back(); //remove it from the free frame vector as its now in use

    page_table[page_num].frame_num = frame; //set our new page entry as valid and assign it a frame number
    page_table[page_num].valid = true;

    lruList.push_front(page_num); //put it in the front because it is the most recently used page entry.
    lruMap[page_num] = lruList.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) 
{

    int victim = lruList.back(); //victim is the tail of the LRU linked list
    int frame = page_table[victim].frame_num;

    lruList.pop_back(); //remove it from the LRUList
    lruMap.erase(victim); //remove the victim from our hashmap as it is no longer loaded into our memory

    page_table[victim].valid = false;  //no longer a valid page entry
    page_table[victim].frame_num = -1;

    page_table[page_num].frame_num = frame; //new page entry assigned its framenumber
    page_table[page_num].valid = true; //page entry is now valid

    lruList.push_front(page_num); //since it was just added, its now the most recently used so it goes to the top of our LRU linked
    lruMap[page_num] = lruList.begin();

    return victim;
}