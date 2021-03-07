////////////////////////////////  threadedBST.h file  ////////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice & Bruce Nguyen on 03/04/2021.
//
// threadedBST class header demonstrating data structure
// Can search a threadedBST and find items in O(log n) time. 
// No duplicates are allowed.

#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <iostream>

using namespace std;

// only threadedBST class can create TNode objects

class threadedBST;

//-----------------------------------------------------------------------------
class TNode {
  friend class threadedBST;
  friend ostream &operator<<(ostream &out, const threadedBST &bst);

private:
  // constructor
  explicit TNode(int data);

  // data contained in the object
  int data;

  // link to left TNode child
  TNode *left;

  // link to right TNode child
  TNode *right;

  // true if left child pointer is actually a thread
  bool leftThread; 
  
  // true if right child pointer is actually a thread
  bool rightThread;

  // true if node is a leaf
  bool isLeaf();

  //print out node's data
  void display();

};

//-----------------------------------------------------------------------------
class threadedBST {
  // display with level
  friend ostream &operator<<(ostream &os, const threadedBST &list);

private:
  // O(n) Traverses in order threadedBST, calls display
  void inOrderTraversal();

  // addHelper()
  bool addHelper(int data, TNode* node);
  
  // removeHelper()
  bool removeHelper(int data, TNode* node);
  
  // containsHelper()
  bool containsHelper(int target, TNode* node) const;

  // constructorHelper()
  void constructorHelper(int start, int end);

  /*
  traverse through tree inorder
  calls display() at each node to print out data
  */
  void printInOrder(TNode* treePtr);

  //places threads where applicable
  void addThread(TNode* treePtr);

  /*
  searches tree for node with target data
  returns pointer to target findNode
  returns nullptr if not found
  */
  TNode* findNode(int target, TNode* treePtr);

public:
  // default threadedBST is empty
  explicit threadedBST(int n);

  // root node
  TNode* root;
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

  // return true if threadedBST
  bool isEmpty();

  // clear, destroys 
  void clear(TNode* subTreePtr);

};

#endif //ASS5_THREADEDBST_H
