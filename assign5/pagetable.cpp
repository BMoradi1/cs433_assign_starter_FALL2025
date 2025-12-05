/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author ??? (TODO: your name)
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

PageTable::PageTable(int num_pages) {
    // Initialize the underlying vector to hold `num_pages` entries
    pages.resize(num_pages);
}

// Destructor: rely on vector's automatic cleanup. Do NOT delete the vector's address.
PageTable::~PageTable() {
}