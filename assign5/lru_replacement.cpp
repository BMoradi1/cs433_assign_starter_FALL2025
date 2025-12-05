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
    free_frames = num_frames;
  /*   //unordered_map<int, Node*> Map;
    Node *head;
    Node *tail;

    capacity = num_pages;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head-> next = tail;
    tail-> prev = head;
 */
    }

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    // TODO: Add necessary code here
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    //printf("hello");
    for(auto it = lruList.begin(); it != lruList.end(); it++) //find where the page is inside our LRU order tracker
    {
        lruList.splice(lruList.begin(), lruList, it); //since we accessed it we move it to the top
        break;
    }
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
//inputed page's frame number will be set to the next avaliable frame in stack (current frame pulled from replacement)
    page_table[page_num].frame_num = current_frame;
    //page_num now set valid since it's data is accessible now
    page_table[page_num].valid = true;  
    // TODO: Update your data structure LRU replacement}
    lruList.push_front(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) 
{
    int victim = lruList.back();
    // TODO: Update your data structure LRU replacement and pagetable
    lruList.push_front(page_num);
    lruList.pop_back();
    return victim;
}