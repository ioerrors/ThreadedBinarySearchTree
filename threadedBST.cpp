////////////////////////////////  threadedBST.cpp file
/////////////////////////////
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
ostream &operator<<(ostream &os, const threadedBST &threadA) {
  // return if the tree is empty
  if (threadA.root == nullptr) {
    return os;
  }
  if (threadA.root->isLeaf()) {
    os << threadA.root->data << ", "; // out
    return os;
  }
  //TODO: Fix this.
  os << threadA.root->left << ", ";  // a
  os << threadA.root->data << ", ";           // b
  os << threadA.root->right << ", "; // c
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
  // indexes
  int start = 1;
  int end = n;
  int mid = (end + start) / 2;

  // test this!
  /*
  if (n % 2 != 0) {
    mid++;
  }
  */
  // create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid);
  constructorHelper(mid + 1, end);

  // add threads
}

void threadedBST::constructorHelper(int start, int end) {
  if (start <= end) {
    // pick middle index
    int mid = (start + end) / 2;
    if (mid != root->data) {
      // add middle index
      add(mid);
    }
    if (start != end) {
      if (end > 2) {
        // call on sub array left
        constructorHelper(start, mid - 1);
      }
      constructorHelper(mid + 1, end);
    }
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

// WIP MICAH CODE:

//-----------------------------------------------------------------------------
// return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int value, TNode *node) {
  if (value < node->data) {
    return removeHelper(value, node->left);
  } else if (value > node->data) {
    return removeHelper(value, node->right);
  } else {
    // at this point data === node->data
    // check if leaf, if so, remove.
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
    }
    // check if right child only
    else if (node->left == nullptr && node->right != nullptr) {
      TNode *deleteMe = node->right;
      node->right = deleteMe->right;
      node->data = deleteMe->data;
      delete deleteMe;
    }
    // check if left child only
    else if (node->left != nullptr && node->right == nullptr) {
      TNode *deleteMe = node->left;
      node->left = deleteMe->left;
      node->data = deleteMe->data;
      delete deleteMe;
    }
    // oh no; has both
    else {
      // take right subtree
      TNode *subTreeParent = node;
      TNode *subTreePtr = node->right;

      // move to leftmost child
      while (subTreePtr->left != nullptr) {
        subTreeParent = subTreePtr;
        subTreePtr = subTreePtr->left;
      }
      // copy over the data
      node->data = subTreePtr->data;

      // if leaf, sets parent->left to nullptr
      // if right child only, sets parent->left to that branch
      subTreeParent->left = subTreePtr->right;
      // now delete subTreePtr
      delete subTreePtr;
    }
  }
  return true;
}

//
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
bool threadedBST::addHelper(int value, TNode *node) {
  if (value < node->data) {
    if (node->left != nullptr) { // goes down left branch
      return addHelper(value, node->left);
    } else { // found leaf
      TNode *newNode = new TNode(value);
      node->left = newNode;
    }
  }
  if (value > node->data) {
    if (node->right != nullptr) { // goes down right branch
      return addHelper(value, node->right);
    } else {                             // found leaf
      TNode *newNode = new TNode(value); // create node directly before use
      node->right = newNode;
    }
  }
  return true;
}
bool threadedBST::threadedBST::add(int value) {
  // would like to just say contains(value)
  if (contains(value)) { // maybe include containsHelper(data, this->root);
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

bool threadedBST::containsHelper(int target, TNode *node) const {
  // check if node's data is target
  if (target == node->data) {
    return true;
  }
  if (node->data < target && node->right != nullptr &&
      node->rightThread == false) {
    node = node->right;
    return containsHelper(target, node);
  }
  if (node->data > target && node->left != nullptr &&
      node->leftThread == false) {
    node = node->left;
    return containsHelper(target, node);
  }
  return false;
}

// comment these
bool threadedBST::isEmpty() {
  if (this->root == nullptr) {
    return true;
  }
  return false;
}

void threadedBST::clear(TNode *subTreePtr) {
  if (subTreePtr != nullptr) {
    clear(subTreePtr->left);
    clear(subTreePtr->right);
    subTreePtr->left = nullptr;
    subTreePtr->right = nullptr;
    delete subTreePtr;
  }
}

//-----------------------------------------------------------------------------
void threadedBST::addThread(TNode *treePtr) {
  if (treePtr->isLeaf()) {
    if (contains(treePtr->data + 1)) {
      treePtr->right = findNode(treePtr->data + 1, this->root); // r
      treePtr->rightThread = true;
      return;
    }
    if (contains(treePtr->data - 1)) {
      treePtr->left = findNode(treePtr->data - 1, this->root); // r
      treePtr->leftThread = true;
      return;
    }
  }

  if (treePtr->left != nullptr) {
    addThread(treePtr->left); // a
  }

  if (treePtr->right == nullptr) {
    if (contains(treePtr->data + 1)) {
      treePtr->right = findNode(treePtr->data + 1, this->root); // t
      treePtr->rightThread = true;
      return;
    }
  }
  if (treePtr->left == nullptr) {
    if (contains(treePtr->data - 1)) {
      treePtr->left = findNode(treePtr->data - 1, this->root); // d
      treePtr->leftThread = true;
      return;
    }
  }

  if (treePtr->right != nullptr) {
    addThread(treePtr->right); // b
  }
  return;
}

//-----------------------------------------------------------------------------
TNode *threadedBST::findNode(int target, TNode *treePtr) {
  if (target == treePtr->data) {
    return treePtr;
  }
  if (treePtr->data > target && treePtr->left != nullptr &&
      treePtr->leftThread == false) {
    return findNode(target, treePtr->left);
  }
  if (treePtr->data < target && treePtr->left != nullptr &&
      treePtr->leftThread == false) {
    return findNode(target, treePtr->right);
  }
  return nullptr;
}

//-----------------------------------------------------------------------------
// returns true if node is a leaf
bool TNode::isLeaf() {
  if ((this->left == nullptr && this->rightThread == true) ||
      (this->right == nullptr && this->leftThread == true) ||
      (this->leftThread == true && this->rightThread == true)) {
    return true;
  }
  return false;
}


//-----------------------------------------------------------------------------
// threadedBST copy constructor
// PRE: None
// POST: a new threadedBST is made, separate but identical to original threadedBST
threadedBST::threadedBST(const threadedBST& oldBST) {
  // indexes
  int start = 1;
  TNode* n = oldBST.getRoot();
  int end = copyConstHelper(n);
  int mid = (end + start) / 2;

  // create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid);
  constructorHelper(mid + 1, end);
}

//-------------------------------------------------------------------------------
// traverses through right branches
// returns largest integer in tree
int threadedBST::copyConstHelper(TNode* treePtr) {
  while(treePtr->right != nullptr){
    treePtr=treePtr->right;
  }
  return (treePtr->data);
}

//---------------------------------------------------------------------------------
TNode* threadedBST::getRoot() const{
  return this->root;
}
/*
//-----------------------------------------------------------------------------
ostream TNode::display(ostream &os) { 
  return << this->data << ", "; 
}

//-----------------------------------------------------------------------------
void threadedBST::printInOrder(TNode *treePtr) {
  if (treePtr->isLeaf()) {
    treePtr->display(ostream &os); // out
    return;
  }
  printInOrder(treePtr->left);  // a
  treePtr->display();           // b
  printInOrder(treePtr->right); // c
}
*/

