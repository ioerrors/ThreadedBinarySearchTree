////////////////////////////////  threadedBST.cpp file  //////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// threadedBST class demonstrating data structure
// Can search a threadedBST and find items in O(log n) time.
// No duplicates are allowed.
// Assumptions: Will not contain 0 or negative numbers 


#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>

#include "threadedBST.h"

using namespace std;

//-----------------------------------------------------------------------------
// << operator
// display all the elements of the threadedBST
// PRE: threadedBST &list exists
// POST: ostream has formatted output of threadedBST, example:
ostream &operator<<(ostream &os, const threadedBST &threadB) {
  // return if the tree is empty
  if (threadB.root == nullptr) {
      return os;
  }
  // print the threadB.root node
  os << threadB.root->data << " ";
  // create two empty queues and enqueue threadB.root's left and
  // right child, respectively
  queue<TNode*> q1, q2;
  q1.push(threadB.root->left);
  q2.push(threadB.root->right);
  // loop till queue is empty
  while (!q1.empty()) {
    // calculate the total number of TNodes at the current level
    int n = q1.size();
    // process every TNode of the current level
    while (n--) {
      // dequeue front TNode from the first queue and print it
      TNode* x = q1.front();
      q1.pop();
      os << x->data << " ";
      // enqueue left and right child of `x` to the first queue
      if (x->left) {
          q1.push(x->left);
      }
      if (x->right) {
          q1.push(x->right);
      }
      // dequeue front TNode from the second queue and print it
      TNode* y = q2.front();
      q2.pop();
      os << y->data << " ";
      // enqueue right and left child of `y` to the second queue
      if (y->right) {
          q2.push(y->right);
      }
      if (y->left) {
          q2.push(y->left);
      }
    }
  }
  return os;
}


//-----------------------------------------------------------------------------
// TNode CONSTRUCTOR
// PRE: this TNode does not exist
// POST: this TNode is created and data is set
//       next/prev/upLevel/downLevel are nullptr
TNode::TNode(int data) : data{data} {
  left = nullptr;
  right = nullptr;
  rightThread = false;
  leftThread = false;
}

//-----------------------------------------------------------------------------
// threadedBST CONSTRUCTOR
// default threadedBST has data of 1, one doubly-linked list
// PRE: this threadedBST does not exist
// POST: threadedBST is created with data specified,
//       frontGuards and RearGaurds are dynamically allocated
//       at each level special TNode* objects created to be guards
//       and all the TNode objects are tied together
threadedBST::threadedBST(int n) {
  //indexes
  int start = 0;
  int end = n; 
  int mid = (end + start) / 2; 
  max = n;
  //test this!
  if (n % 2 != 0) {
    mid++;
  }

  //create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid - 1);
  constructorHelper(mid + 1, end);
}


void threadedBST::constructorHelper(int start, int end) {
  //pick middle index
  int mid = (start + end) / 2; 
  //add middle index
  add(mid);  

  if (start != end) {
    if (end > 2) {
    // call on sub array left
      constructorHelper(start, mid - 1); 
    }
    constructorHelper(mid + 1, end);
  }
}



//-----------------------------------------------------------------------------
// destructor
// PRE: threadedBST exists
// POST: threadedBST is deleted, all memory deallocated, no leaks
threadedBST::~threadedBST() {
  // need to delete individual nodes
  clear(this->root);
}

//WIP MICAH CODE:


//-----------------------------------------------------------------------------
// return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int value, TNode* node) {
  if (value < node->data) {
    return removeHelper(value, node->left);
  }
  else if (value > node->data) {
    return removeHelper(value, node->right);
  }
  else {
    //at this point data === node->data
    //check if leaf, if so, remove.
    if (node->left == nullptr && node->right == nullptr)  {
      delete node;
    }
    //locate easier to remove node
    //node should be at node to remove
    TNode *findLeaf = node->left;
    //rightmost leaf of node's left child
    while (findLeaf->right->left != nullptr 
        && findLeaf->right->right != nullptr) {
      findLeaf = findLeaf->right;
    }
    node->data = findLeaf->right->data;
    delete findLeaf->right;
    findLeaf->right = nullptr;
  }
  return true;
}

bool threadedBST::remove(int value) {
  if (!contains(value)) {
    return false;
  }
  return removeHelper(value, this->root);
}


//-----------------------------------------------------------------------------
// add()
// return true if successfully added, no duplicates
// PRE: data may or may not already exist in threadedBST
// POST: if data did not exist in threadedBST,
//       TNode is created with data and added to threadedBST
//       OR if data did exist in threadedBST, returned false
//       (no duplicates allowed)
// recursive helper function for add() --> addHelper()
bool threadedBST::addHelper(int value, TNode* node) {
  if (value < node->data) {
    if (node->left != nullptr) { //goes down left branch
      return addHelper(value, node->left);
    }
    else { // found leaf
      TNode* newNode = new TNode(value); 
      node->left = newNode;
    }
  }
  if (value > node->data) {
    if (node->right != nullptr) { //goes down right branch
      return addHelper(value, node->right);
    }
    else { // found leaf
      TNode* newNode = new TNode(value); //create node directly before use
      node->right = newNode;
    }
  }
  return true;
}
bool threadedBST::threadedBST::add(int value) {
  //would like to just say contains(value)
  if (contains(value)) { //maybe include containsHelper(data, this->root);
    cout << "Duplicates are not allowed: " << value << endl;
    return false;
  }
  return addHelper(value, this->root);
}



// BRUCE CODE:

//-----------------------------------------------------------------------------
// Checks to see whether or not a data data exists in the list
// Returns true if the data exists in the threadedBST.
// Returns false otherwise
// PRE: data may or may exist in threadedBST
// POST: if data exists in threadedBST, returned true
//       OR if data does not exist in list, returned false
bool threadedBST::contains(int target) const {
  return containsHelper(target, this->root);
}

bool threadedBST::containsHelper(int target, TNode* node) const {
  //check if node's data is target
  if(target == node->data) {
    return true;
  }
  if(node->data < target  && node->right != nullptr 
                           && node->rightThread == false) {
    node = node->right; 
    containsHelper(target, node); 
  }
  if(node->data > target && node->left != nullptr 
                          && node->leftThread == false) {
    node = node->left; 
    containsHelper(target, node); 
  }
  return false; 
}


//comment these
bool threadedBST::isEmpty() {
  if (this->root == nullptr){
    return true;
  }
  return false;
}

void threadedBST::clear(TNode* subTreePtr) {
  if(subTreePtr != nullptr){
  clear(subTreePtr->left);
    clear(subTreePtr->right);
    subTreePtr->left = nullptr;
    subTreePtr->right = nullptr;
    delete subTreePtr;
  }
}
