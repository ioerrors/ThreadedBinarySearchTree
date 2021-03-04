////////////////////////////////  threadedBST.h file  ////////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice & Bruce Nguyen on 03/04/2021.
//
// threadedBST class header demonstrating data structure
// Can search a threadedBST and find items in O(log n) time. 
// No duplicates are allowed.

#ifndef ASS4_THREADEDBST_H
#define ASS4_THREADEDBST_H

#include <iostream>

using namespace std;

// only threadedBST class can create TNode objects

class threadedBST;

class TNode {
  friend class threadedBST;
  friend ostream &operator<<(ostream &out, const threadedBST &bst);

private:
  // constructor
  explicit TNode(int data);

  // data contained in the object
  int data;

  // link to Next TNode 
  TNode *leftChild;

  // link to Prev TNode
  TNode *rightChild;

  // true if left child pointer is actually a thread
  bool leftThread; 
  
  // true if right child pointer is actually a thread
  bool rightThread;

};

class threadedBST {
  // display with level
  friend ostream &operator<<(ostream &os, const threadedBST &list);

private:
  // current number of levels
  int height = 1;


public:
  // default threadedBST has only 1 level, just one doubly-linked list
  explicit threadedBST(int height = 1);

  //copy constructor
  threadedBST(const threadedBST&);

  // destructor
  virtual ~threadedBST();

  // return true if successfully added, no duplicates allowed
  bool add(int data);

  // return true if successfully removed
  bool remove(int data);

  // return true if found in threadedBST
  bool contains(int data) const;

};


