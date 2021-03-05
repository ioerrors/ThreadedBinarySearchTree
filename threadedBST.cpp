////////////////////////////////  threadedBST.cpp file  //////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// threadedBST class demonstrating data structure
// Can search a threadedBST and find items in O(log n) time.
// No duplicates are allowed.
// modified by mashhadi on 14th feb to add an alternative op<<

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "threadedBST.h"

using namespace std;

//-----------------------------------------------------------------------------
// << operator
// display all the elements of the threadedBST
// PRE: threadedBST &list exists
// POST: ostream has formatted output of threadedBST, example:
// Level: 4 -- -2147483648, 2147483647,
// Level: 3 -- -2147483648, 93, 2147483647,
// Level: 2 -- -2147483648, 93, 2147483647,
// Level: 1 -- -2147483648, 3, 23, 67, 93, 2147483647,
// Level: 0 -- -2147483648, 3, 7, 23, 35, 67, 68, 72, 87, 93, 2147483647,
ostream &operator<<(ostream &os, const threadedBST &list) {
  for (int index = list.depth - 1; index >= 0; index--) {
    os << "Level: " + to_string(index) + " -- ";
    TNode *curr = list.frontGuards[index];
    while (curr != nullptr) {
      os << to_string(curr->data) + ", ";
      curr = curr->next;
    }
    os << "\n";
  }
  return os;
}

//-----------------------------------------------------------------------------
// TNode CONSTRUCTOR
// PRE: this TNode does not exist
// POST: this TNode is created and data is set
//       next/prev/upLevel/downLevel are nullptr
TNode::TNode(int data) : data{data} {
  next = nullptr;
  prev = nullptr;
  upLevel = nullptr;
  downLevel = nullptr;
}

//-----------------------------------------------------------------------------
// threadedBST CONSTRUCTOR
// default threadedBST has depth of 1, one doubly-linked list
// PRE: this threadedBST does not exist
// POST: threadedBST is created with depth specified,
//       frontGuards and RearGaurds are dynamically allocated
//       at each level special TNode* objects created to be guards
//       and all the TNode objects are tied together
threadedBST::threadedBST(int depth) : depth{depth} {
  assert(depth > 0);
  frontGuards = new TNode *[depth];
  rearGuards = new TNode *[depth];
  for (int index = depth - 1; index >= 0; index--) {
    frontGuards[index] = new TNode(INT_MIN);
    rearGuards[index] = new TNode(INT_MAX);
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
// PRE: threadedBST exists
// POST: returned true 50% of time
//       returned false 50% of time
bool threadedBST::alsoHigher() const {
  srand(time(0) + rand());
  return ((rand() % 100) <= 50);
}



//-----------------------------------------------------------------------------
// destructor
// PRE: threadedBST exists
// POST: threadedBST is deleted, all memory deallocated, no leaks
threadedBST::~threadedBST() {
  // need to delete individual nodes
  for (int index = depth - 1; index >= 0; index--) {
    TNode *curr = frontGuards[index];
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
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int data, TNode* node) {
  if (data < node->data) {
    return addHelper(data, node->left);
  }
  else if (data > node->data) {
    return addHelper(data, node->right);
  }
  else {
    TNode *
  }
  return true;






  TNode *curr = frontGuards[index];
  while (curr->next != nullptr && curr->next->data < data) {
    curr = curr->next;
  }
  if (curr->next != nullptr && curr->next->data == data) {
    curr = curr->next;
    TNode *previous = curr->prev;
    TNode *nextNode = curr->next;
    nextNode->prev = previous;
    previous->next = nextNode;
    delete curr;
  }
  return true;
}

bool threadedBST::remove(int data) {
  if (!contains(data)) {
    return false;
  }
  return removeHelper(data, root);
}


//-----------------------------------------------------------------------------
// add()
// return true if successfully added, no duplicates
// PRE: data may or may not already exist in threadedBST
// POST: if data did not exist in threadedBST,
//       TNode is created with data and added to threadedBST
//       OR if data did exist in threadedBST, returned false
//       (no duplicates allowed)
bool add(int data) {
  //would like to just say contains(data)
  if (contains(data, root)) { //maybe include containsHelper(data, root);
    cout << "Duplicates are not allowed: " << data << endl;
    return false;
  }
  return addHelper(data, root);
}
// recursive helper function for add() --> addHelper()
bool addHelper(int data, TNode* node) {
  if (data < node->data) {
    if (node->left != null) { //goes down left branch
      return addHelper(data, node->left);
    }
    else { // found leaf
      TNode* newNode = new TNode(data); 
      node->left = newNode;
    }
  }
  if (data > node->data) {
    if (node->right != null) { //goes down right branch
      return addHelper(data, node->right);
    }
    else { // found leaf
      TNode* newNode = new TNode(data); //create node directly before use
      node->right = newNode;
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the threadedBST.
// Returns false otherwise
// PRE: data may or may exist in threadedBST
// POST: if data exists in threadedBST, returned true
//       OR if data does not exist in list, returned false
bool threadedBST::contains(int target, TNode* root) const {
  //check if root's value is target
  if(target == root->value){
    return true;
  }
  if(root->value < target  && root->rightChild !=null && root->rightThread == false){
    root = root->rightChild; //changes root?
    contains(target, root); 
  }
  if(root->value > target && root->leftChild !=null && root->leftThread == false){
    root = root->leftChild; //changes root?
    contains(target, root); 
  }
  return false; 
}
