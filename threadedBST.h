////////////////////////////////threadedBST.h file  ///////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice & Bruce Nguyen on 03/04/2021.
//
// threadedBST class demonstrating data structure
// Can search a threadedBST and find items in O(log n) time.
// No duplicates are allowed.
// Assumptions: Will not contain 0 or negative numbers

#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <iostream>

using namespace std;

// only threadedBST class can create TNode objects
class threadedBST;

//-----------------------------------------------------------------------------
class TNode {
  friend class threadedBST;

  //---------------------------------------------------------------------------
  // Overloaded Operator <<
  // Description: traverses tree inorder, 
  //              and prints each node's data as it passes
  // PRE: threadedBST exists
  // POST: All contained integers between 1 and n are printed to output
  friend ostream &operator<<(ostream &os, const threadedBST &list);

private:
  //---------------------------------------------------------------------------
  // TNode CONSTRUCTOR
  // Description: creates a new TNode and sets its data value
  // PRE: this TNode does not exist
  // POST: this TNode is created and data is set
  //       next/prev/upLevel/downLevel are nullptr
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

  //---------------------------------------------------------------------------
  // isLeaf()
  // Description: returns true if this TNode object is a leaf
  // PRE: this TNode object does exist
  // POST: returned true if TNode is leaf
  //       OR returned false if TNode is not a leaf
  bool isLeaf() const;

public:
  //---------------------------------------------------------------------------
  // getData()
  // Description: returns int value 
  // of the data field for this TNode object
  // PRE: this TNode object does exist
  // POST: returned int value of data field
  int getData() const;

  //---------------------------------------------------------------------------
  // getLeft()
  // Description: returns left child of this TNode
  // PRE: this TNode object does exist
  // POST: returned this TNode's left child
  //       OR returned nullptr if TNode has no left child
  TNode* getLeft() const;

  //---------------------------------------------------------------------------
  // getRight()
  // Description: returns right child of this TNode
  // PRE: this TNode object does exist
  // POST: returned this TNode's right child
  //       OR returned nullptr if TNode has no right child
  TNode* getRight() const;


  //---------------------------------------------------------------------------
  // getLeftThread()
  // Description: returns thread status 
  //              of the left child of this TNode
  // PRE: this TNode object does exist
  // POST: returned this TNode's left child thread status
  bool getLeftThread() const;
  
  //---------------------------------------------------------------------------
  // getRightThread()
  // Description: returns thread status 
  //              of the right child of this TNode
  // PRE: this TNode object does exist
  // POST: returned this TNode's right child thread status
  bool getRightThread() const;

};

class iteratorBST {
  friend class threadedBST;
  friend class TNode;

  //---------------------------------------------------------------------------
  // Overloaded Operator <<
  // Description: traverses tree inorder, 
  //              and prints each node's data as it passes
  // PRE: threadedBST exists
  // POST: All contained integers between 1 and n are printed to output
  friend ostream &operator<<(ostream &os, const threadedBST &list);


  //---------------------------------------------------------------------------
  // Overloaded Operator ++
  // Description: calls next() to traverse tree inorder by one, 
  //              by moving the TNode* current by one in order
  // PRE: threadedBST exists and this iterator exists
  // POST: returned true if successfully moved inorder by one
  //       OR returned false if there is no next Node in order
  friend bool operator++(iteratorBST &iterator, int);
  
private:
  //Iterator pointer node tracks current position
  TNode* current;

public:

  //---------------------------------------------------------------------------
  // iteratorBST CONSTRUCTOR
  // Description: constructs an iterator object 
  //              for traversing through the threadedBST using threads
  // PRE: this TNode does not exist
  // POST: this TNode is created and data is set
  //       next/prev/upLevel/downLevel are nullptr  
  explicit iteratorBST(TNode* root);

  //---------------------------------------------------------------------------
  // next()
  // Description: traverses tree inorder by one, 
  //              by moving the TNode* current
  // PRE: threadedBST exists and this iterator exists
  // POST: returned true if successfully moved inorder by one
  //       OR returned false if there is no next Node in order
  bool next();

  //---------------------------------------------------------------------------
  // hasNext()
  // Description: checks if current is 
  //              not yet at max value of the threadedBST
  // PRE: threadedBST exists and this iterator exists
  // POST: returned true if current is not at the max value
  //       OR returned false if current is at max value
  bool hasNext() const;

  //---------------------------------------------------------------------------
  // getCurrent()
  // Description: returns TNode* current
  // PRE: threadedBST exists and this iterator exists
  // POST: returned TNode* current
  TNode* getCurrent() const;
};


//-----------------------------------------------------------------------------
class threadedBST {

  //---------------------------------------------------------------------------
  // Overloaded Operator <<
  // Description: traverses tree inorder, 
  //              and prints each node's data as it passes
  // PRE: threadedBST exists
  // POST: All contained integers between 1 and n are printed to output
  friend ostream &operator<<(ostream &os, const threadedBST &list);

private:
 
  // root node pointer
  TNode* root;

  //---------------------------------------------------------------------------
  // addHelper()
  // Description: recursive helper function for add() --> addHelper()
  //              return true if successfully added, no duplicates
  // PRE: data may or may not already exist in threadedBST
  // POST: if data did not exist in threadedBST,
  //       TNode is created with data and added to threadedBST
  //       OR if data did exist in threadedBST, returned false
  //       (no duplicates allowed)
  bool addHelper(int data, TNode* node);
  
  //---------------------------------------------------------------------------
  // removeHelper()
  // Description: recursive helper function for remove() --> removeHelper()
  //              return true if successfully removed
  // PRE: data may or may exist in threadedBST
  // POST: data removed from threadedBST, returned true
  //       if data already did not exist in list returned false
  bool removeHelper(int data, TNode* node, TNode* parent);
  
  //---------------------------------------------------------------------------
  // containsHelper()
  // Description: Checks to see whether or not a data data exists in the list
  //              recursive helper function for contains() --> containsHelper()
  //              Returns true if the data exists in the threadedBST.
  //              Returns false otherwise
  // PRE: data may or may exist in threadedBST
  // POST: if data exists in threadedBST, returned true
  //       OR if data does not exist in list, returned false
  bool containsHelper(int target, TNode* node) const;

  //---------------------------------------------------------------------------
  // constructorHelper()
  // Description: recursive helper function for threadedBST CONSTRUCTOR 
  //              recursively adds root and subroots 
  // PRE: threadedBST exists with a root node already instantiated
  // POST: threadedBST is constructed in full after all recursive calls finish 
  void constructorHelper(int start, int end);

  //---------------------------------------------------------------------------
  // copyConstructorHelper()
  // Description: recursive helper function for constructor 
  //              iterates through right branches of original tree 
  //              and returns largest integer in original tree
  // PRE: threadedthreadedBST exists with at least single node
  // POST: returned integer of maximum doata value to the right of treePtr 
  //       OR returned 0 if tree is isEmpty
  int copyConstHelper(TNode* treePtr);

  //---------------------------------------------------------------------------
  // addThreads()
  // Description: iterates through a built threadedBST 
  //              and places threads where needed
  // PRE: a non-empty threadedthreadedBST exists
  // POST: nodes with nullptr children are given either predecessor,
  //       successor, OR both threads where applicable
  void addThreads(TNode* treePtr);

  //---------------------------------------------------------------------------
  // findNode()
  // Description: calls contains() to check if target node exists in,
  //              traverses through threadedthreadedBST at log(n) speed 
  //              returns target node's pointer if found, nullptr if not 
  // PRE: a non-empty threadedthreadedBST exists
  // POST: returned a pointer 
  TNode* findNode(int target, TNode* treePtr) const;

public:

  //---------------------------------------------------------------------------
  // threadedBST CONSTRUCTOR
  // Description: creates threadedBST with n-number of nodes 
  //              calls constructorHelper() for actual construction process
  // PRE: n is > 0
  // POST: balanced threadedBST of size-n is created with nodes 1....n
  explicit threadedBST(int n);


  //---------------------------------------------------------------------------
  // threadedBST COPY CONSTRUCTOR
  // Description: creates exact copy of given TBST
  //              calls copyConstHelper() to determine largest integer value n
  //              calls constructorHelper() to create full n-sized tree
  //              calls remove() on integers not contained in original
  //              calls addThreads to add threads to applicables nodes
  // PRE: oldBST is non-empty 
  // POST: an exact copy of oldBST is constructed 
  threadedBST(const threadedBST& oldBST);

  
  //---------------------------------------------------------------------------
  // getRoot()
  // Description: returns root pointer 
  // PRE: threadedBST exists
  // POST: root pointer is returned 
  TNode* getRoot() const;

  //---------------------------------------------------------------------------
  // threadedBST DESTRUCTOR
  // Description: destroys threadedBST object
  //              calls clear() as helper function 
  //              to delete nodes from memory 
  // PRE: threadedBST exists
  // POST: threadedBST is destroyed, deleted; 
  //       all allocated memory for the threadedBST is freed
  virtual ~threadedBST();

  //-----------------------------------------------------------------------------
  // add()
  // Description: return true if successfully added, no duplicates
  //              calls addHelper for actual adding process   
  // PRE: data may or may not already exist in threadedBST
  // POST: if data did not exist in threadedBST,
  //       TNode is created with data and added to threadedBST
  //       OR if data did exist in threadedBST, returned false
  //       (no duplicates allowed)
  bool add(int data);

  //---------------------------------------------------------------------------
  // remove()
  // Description: return true if successfully removed
  // PRE: data may or may exist in threadedBST
  // POST: data removed from threadedBST, returned true
  //       calls removeHelper for actual removal process
  bool remove(int data);

  //-----------------------------------------------------------------------------
  // contains()
  // Description: Checks to see whether or not a data data exists in the list
  //              Returns true if the data exists in the threadedBST.
  //              Returns false otherwise
  // PRE: data may or may exist in threadedBST
  // POST: if data exists in threadedBST, returned true
  //       OR if data does not exist in list, returned false
  bool contains(int data) const;

  //---------------------------------------------------------------------------
  // isEmpty()
  // Description: return true if tree has 0 nodes 
  //              by checking if root is nullptr
  // PRE: threadedBST exists
  // POST: returns true if root is a nullptr
  //       OR returns false if root is not a nullptr 
  bool isEmpty() const;

  //---------------------------------------------------------------------------
  // clear()
  // Description: deletes all nodes in threadedBST
  //              traverses and delete in postorder fashion
  // PRE: threadedBST exists
  // POST: threadedBST is deletedd from memory 
  //       all allocated memory for the threadedBST is freed
  void clear(TNode* subTreePtr);

};

#endif //ASS5_THREADEDBST_H
