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

#include <iosfwd>

// Forward declarations — iteratorBST is an implementation detail defined in
// threadedBST.cpp; it is forward-declared here only so TNode can grant it
// friendship.
class threadedBST;
class iteratorBST;

//-----------------------------------------------------------------------------
// TNode: internal node of threadedBST. Not part of the public interface;
// all members are private, accessible only to threadedBST, iteratorBST,
// and operator<<.
class TNode {
  friend class threadedBST;
  friend class iteratorBST;
  friend std::ostream &operator<<(std::ostream &os, const threadedBST &bst);

private:
  explicit TNode(int data);

  int   data;
  TNode *left;
  TNode *right;
  bool  leftThread;   // true when left pointer is a predecessor thread
  bool  rightThread;  // true when right pointer is a successor thread

  bool isLeaf() const;
  int  getData() const;

  TNode *getLeft()  const;
  TNode *getRight() const;

  bool getLeftThread()  const;
  bool getRightThread() const;
};


//-----------------------------------------------------------------------------
class threadedBST {

  //---------------------------------------------------------------------------
  // Overloaded Operator <<
  // Description: traverses tree inorder, 
  //              and prints each node's data as it passes
  // PRE: threadedBST exists
  // POST: All contained integers between 1 and n are printed to output
  friend std::ostream &operator<<(std::ostream &os, const threadedBST &list);

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

  bool hasRealLeft(const TNode* node) const;
  bool hasRealRight(const TNode* node) const;

  void removeLeafNode(TNode* node, TNode* parent);
  void removeNodeWithOnlyRightChild(TNode* node);
  void removeNodeWithOnlyLeftChild(TNode* node);
  void removeNodeWithTwoChildren(TNode* node);

  TNode* inorderPredecessor(TNode* node) const;
  TNode* inorderSuccessor(TNode* node) const;
  void retargetAdjacentThreads(TNode* removedNode);
  
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
  TNode* findNode(int target, TNode* treePtr) const;

  // Destroys all nodes in the subtree rooted at subTreePtr.
  // Private: callers outside the class must not invoke this directly.
  void clear(TNode* subTreePtr);

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

  threadedBST &operator=(const threadedBST &rhs);

  virtual ~threadedBST();

  bool add(int data);
  bool remove(int data);
  bool contains(int data) const;
  bool isEmpty() const;
};

#endif //ASS5_THREADEDBST_H
