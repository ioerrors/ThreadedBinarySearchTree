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

#include "threadedBST.h"

using namespace std;

//-----------------------------------------------------------------------------
// << operator
// display all the elements of the threadedBST
// PRE: threadedBST &list exists
// POST: ostream has formatted output of threadedBST, example:
ostream &operator<<(ostream &os, const threadedBST &list) {
  int sposition = 40
  TNode* curr = root;
  for (int j = 0; j < sposition; j++) {
    out << " ";
  }
  out << "      " << curr->data << endl;
  for (int k = 0; k < sposition; k++) {
    out << " ";
  }
  out << "   " << curr->left->data << "   " << curr->right->data << endl;
  for (int l = 0; l < sposition - 4; l++) {
    out << " ";
  }

  os << "Level: " + to_string(index) + " -- ";
  TNode *curr = list.frontGuards[index];
  while (curr != nullptr) {
    os << to_string(curr->data) + ", ";
    curr = curr->next;
  }
  os << "\n";
  return os;
}

//-----------------------------------------------------------------------------
// TNode CONSTRUCTOR
// PRE: this TNode does not exist
// POST: this TNode is created and data is set
//       next/prev/upLevel/downLevel are nullptr
TNode::TNode(int data) : data{data} {
  leftChild = nullptr;
  rightChild = nullptr;
  rightThread = nullptr;
  leftThread = nullptr;
}

//-----------------------------------------------------------------------------
// threadedBST CONSTRUCTOR
// default threadedBST has value of 1, one doubly-linked list
// PRE: this threadedBST does not exist
// POST: threadedBST is created with value specified,
//       frontGuards and RearGaurds are dynamically allocated
//       at each level special TNode* objects created to be guards
//       and all the TNode objects are tied together
threadedBST::threadedBST(int n) : n{n} { 
  //indexes
  int start = 0;
  int end = n; 
  int mid = (end + start) / 2; 
  max = n;
  //test this!
  if (n % 2 != 0) {
    mid++;
  }

  //create node, attach to root
  root = new TNode(mid);
  constructorHelper(start, mid - 1, 0); 
  constructorHelper(mid + 1, end, end); 
}


void threadedBST::constructorHelper(int start, int end, int max) {
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
  clear();
}

//WIP MICAH CODE:


//-----------------------------------------------------------------------------
// return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int data, TNode* node) {
  if (data < node->data) {
    return removeHelper(data, node->left);
  }
  else if (data > node->data) {
    return removeHelper(data, node->right);
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
    while (findleaf->right->left != nullptr 
        && findleaf->right->right != nullptr) {
      findleaf = findLeaf->right;
    }
    node->data = findLeaf->right->data;
    delete findLeaf->right;
    findLeaf->right = nullptr;
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


// BRUCE CODE:

//-----------------------------------------------------------------------------
// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the threadedBST.
// Returns false otherwise
// PRE: data may or may exist in threadedBST
// POST: if data exists in threadedBST, returned true
//       OR if data does not exist in list, returned false
bool threadedBST::constains(int target) {
  return containsHelper(target, root);
}

bool threadedBST::containsHelper(int target, TNode* node) const {
  //check if node's value is target
  if(target == node->value) {
    return true;
  }
  if(node->value < target  && node->rightChild !=null 
                           && node->rightThread == false) {
    node = node->rightChild; 
    containsHelpert, node); 
  }
  if(node->value > target && node->leftChild !=null 
                          && node->leftThread == false) {
    node = node->leftChild; 
    containsHelpert, node); 
  }
  return false; 
}


//comment these
bool isEmpty() {
  if(root == nullptr){
    return true;
  }
  return false;
}

void clear(TNode* subTreePtr){
  if(subTreePtr != nullptr){
  clear(subTreePtr->leftChild);
    clear(subTreePtr->rightChild);
    subTreePtr->leftChild = nullptr;
    subTreePtr->rightChild = nullptr:
    delete subTreePtr;
  }
}