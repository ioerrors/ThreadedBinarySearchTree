////////////////////////////////  skiplist.cpp file  //////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// skiplist class demonstrating data structure
// Can search a skiplist and find items in O(log n) time.
// No duplicates are allowed.
// modified by mashhadi on 14th feb to add an alternative op<<

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

//-----------------------------------------------------------------------------
// << operator
// display all the elements of the SkipList
// PRE: SkipList &list exists
// POST: ostream has formatted output of SkipList, example:
// Level: 4 -- -2147483648, 2147483647,
// Level: 3 -- -2147483648, 93, 2147483647,
// Level: 2 -- -2147483648, 93, 2147483647,
// Level: 1 -- -2147483648, 3, 23, 67, 93, 2147483647,
// Level: 0 -- -2147483648, 3, 7, 23, 35, 67, 68, 72, 87, 93, 2147483647,
ostream &operator<<(ostream &os, const SkipList &list) {
  for (int index = list.depth - 1; index >= 0; index--) {
    os << "Level: " + to_string(index) + " -- ";
    SNode *curr = list.frontGuards[index];
    while (curr != nullptr) {
      os << to_string(curr->data) + ", ";
      curr = curr->next;
    }
    os << "\n";
  }
  return os;
}

//-----------------------------------------------------------------------------
// SNode CONSTRUCTOR
// PRE: this SNode does not exist
// POST: this SNode is created and data is set
//       next/prev/upLevel/downLevel are nullptr
SNode::SNode(int data) : data{data} {
  next = nullptr;
  prev = nullptr;
  upLevel = nullptr;
  downLevel = nullptr;
}

//-----------------------------------------------------------------------------
// SkipList CONSTRUCTOR
// default SkipList has depth of 1, one doubly-linked list
// PRE: this Skiplist does not exist
// POST: Skiplist is created with depth specified,
//       frontGuards and RearGaurds are dynamically allocated
//       at each level special SNode* objects created to be guards
//       and all the SNode objects are tied together
SkipList::SkipList(int depth) : depth{depth} {
  assert(depth > 0);
  frontGuards = new SNode *[depth];
  rearGuards = new SNode *[depth];
  for (int index = depth - 1; index >= 0; index--) {
    frontGuards[index] = new SNode(INT_MIN);
    rearGuards[index] = new SNode(INT_MAX);
    frontGuards[index]->next = rearGuards[index];
    rearGuards[index]->prev = frontGuards[index];
    if (index < depth - 1) {
      frontGuards[index]->upLevel = frontGuards[index + 1];
      rearGuards[index]->upLevel = rearGuards[index + 1];
      frontGuards[index + 1]->downLevel = frontGuards[index];
      rearGuards[index + 1]->downLevel = rearGuards[index];
    }
  }
}

//-----------------------------------------------------------------------------
// alsoHigher()
// return true 50% of time,
// each node has a 50% chance of being at higher level
// PRE: Skiplist exists
// POST: returned true 50% of time
//       returned false 50% of time
bool SkipList::alsoHigher() const {
  srand(time(0) + rand());
  return ((rand() % 100) <= 50);
}

//-----------------------------------------------------------------------------
// add()
// return true if successfully added, no duplicates
// PRE: data may or may not already exist in skiplist
// POST: if data did not exist in skiplist,
//       SNode is created with data and added to skiplist
//       OR if data did exist in skiplist, returned false
//       (no duplicates allowed)
bool SkipList::add(int data) {
  if (data == INT_MIN || data == INT_MAX) {
    return false;
  }
  SNode *nextNode = frontGuards[0]->next;
  while (nextNode->next != nullptr && nextNode->data < data) {
    nextNode = nextNode->next;
  }
  if (nextNode->data == data) {
    cout << "Duplicates are not allowed: " << data << endl;
    return false;
  }
  SNode *newNode = new SNode(data);
  addBefore(newNode, nextNode);
  nextNode = nextNode->prev;
  bool higher = alsoHigher();
  if (higher) {
    int x = 0;
    while (higher && ++x < depth) {
      // move up one level
      while (nextNode->upLevel == nullptr) {
        nextNode = nextNode->prev;
      }
      nextNode = nextNode->upLevel;

      // move to correct postion
      while (nextNode->next != nullptr && nextNode->data < data) {
        nextNode = nextNode->next;
      }

      // create upper node and link
      SNode *newUpper = new SNode(data);
      newNode->upLevel = newUpper;
      newUpper->downLevel = newNode;
      addBefore(newUpper, nextNode);

      // set situation for next level
      newNode = newUpper;
      higher = alsoHigher();
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
// destructor
// PRE: SkipList exists
// POST: SkipList is deleted, all memory deallocated, no leaks
SkipList::~SkipList() {
  // need to delete individual nodes
  for (int index = depth - 1; index >= 0; index--) {
    SNode *curr = frontGuards[index];
    while (curr->next != nullptr) {
      curr = curr->next;
      delete curr->prev;
    }
    delete curr;
  }
  delete[] frontGuards;
  delete[] rearGuards;
}

//-----------------------------------------------------------------------------
// return true if successfully removed
// PRE: data may or may exist in skiplist
// POST: data removed from skiplist, returned true
//       if data already did not exist in list
//       OR if data is INT_MAX(rearGuards value)
//       OR data is INT_MIN(frontGaurds value), returned false
bool SkipList::remove(int data) {
  if (!contains(data) || data == INT_MAX || data == INT_MIN) {
    return false;
  }
  for (int index = depth - 1; index >= 0; index--) {
    SNode *curr = frontGuards[index];
    while (curr->next != nullptr && curr->next->data < data) {
      curr = curr->next;
    }
    if (curr->next != nullptr && curr->next->data == data) {
      curr = curr->next;
      SNode *previous = curr->prev;
      SNode *nextNode = curr->next;
      nextNode->prev = previous;
      previous->next = nextNode;
      delete curr;
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
// Given a SNode, place it before the given NextNode
// PRE: SNode exists, and is not in Skiplist
// POST: SNode is placed before the given NextNode in SkipList
void SkipList::addBefore(SNode *newNode, SNode *nextNode) {
  // Link next to node in front
  newNode->next = nextNode;
  // Link prev to node behind
  newNode->prev = nextNode->prev;
  // Link node in back to new node
  nextNode->prev->next = newNode;
  // Link node in front to new node
  nextNode->prev = newNode;
}

//-----------------------------------------------------------------------------
// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise
// PRE: data may or may exist in skiplist
// POST: if data exists in skiplist, returned true
//       OR if data does not exist in list, returned false
bool SkipList::contains(int data) const {
  if (data == INT_MAX || data == INT_MIN) {
    return true;
  }
  for (int index = depth - 1; index >= 0; index--) {
    SNode *curr = frontGuards[index];
    while (curr->next != nullptr && curr->next->data < data) {
      curr = curr->next;
    }
    if (curr->next != nullptr && curr->next->data == data) {
      return true;
    }
  }
  return false;
}
