///////////////////////////////threadedBST.cpp file////////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// threadedBST class demonstrating data structure
// Can search a threadedBST and find items in O(log n) time.
// No duplicates are allowed.
// Assumptions: Will not contain 0 or negative numbers

#include <iostream>

#include "threadedBST.h"

using namespace std;

//-----------------------------------------------------------------------------
// iteratorBST: internal cursor for inorder traversal via thread links.
// Defined here rather than in the header because it is an implementation
// detail of operator<< and is not part of the public API.
class iteratorBST {
  friend ostream &operator<<(ostream &os, const threadedBST &bst);

  TNode *current;

public:
  explicit iteratorBST(TNode *root);
  bool next();
  bool hasNext() const;
  TNode *getCurrent() const;
  // Postfix ++ advances inorder by one; returns false when exhausted.
  bool operator++(int) { return next(); }
};

//-----------------------------------------------------------------------------
// Overloaded Operator <<
// Description: traverses tree inorder,
//              and prints each node's data as it passes
// PRE: threadedBST exists
// POST: All contained integers between 1 and n are printed to output
ostream &operator<<(ostream &os, const threadedBST &bst) {
  // return if the tree is empty
  if (bst.isEmpty()) {
    os << "empty tree";
    return os;
  }
  iteratorBST iterate(bst.root);
  os << iterate.getCurrent()->getData() << " ";

  while (iterate++) {
    os << iterate.getCurrent()->getData() << " ";
  }
  return os;
}

//-----------------------------------------------------------------------------
// TNode CONSTRUCTOR
// Description: creates a new TNode and sets its data value
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
// getData()
// Description: returns int value
// of the data field for this TNode object
// PRE: this TNode object does exist
// POST: returned int value of data field
int TNode::getData() const { return data; }

//-----------------------------------------------------------------------------
// getLeft()
// Description: returns left child of this TNode
// PRE: this TNode object does exist
// POST: returned this TNode's left child
//       OR returned nullptr if TNode has no left child
TNode *TNode::getLeft() const { return left; }

//-----------------------------------------------------------------------------
// getRight()
// Description: returns right child of this TNode
// PRE: this TNode object does exist
// POST: returned this TNode's right child
//       OR returned nullptr if TNode has no right child
TNode *TNode::getRight() const { return right; }



//-----------------------------------------------------------------------------
// getLeftThread()
// Description: returns thread status
//              of the left child of this TNode
// PRE: this TNode object does exist
// POST: returned this TNode's left child thread status
bool TNode::getLeftThread() const { return leftThread; }

//-----------------------------------------------------------------------------
// getRightThread()
// Description: returns thread status
//              of the right child of this TNode
// PRE: this TNode object does exist
// POST: returned this TNode's right child thread status
bool TNode::getRightThread() const { return rightThread; }

//-----------------------------------------------------------------------------
// isLeaf()
// Description: returns true if this TNode object is a leaf
// PRE: this TNode object does exist
// POST: returned true if TNode is leaf
//       OR returned false if TNode is not a leaf
bool TNode::isLeaf() const {
  if ((this->left == nullptr && this->right == nullptr) ||
      (this->left == nullptr && this->rightThread == true) ||
      (this->right == nullptr && this->leftThread == true) ||
      (this->leftThread == true && this->rightThread == true)) {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------
// iteratorBST CONSTRUCTOR
// Description: constructs an iterator object
//              for traversing through the threadedBST using threads
// PRE: this TNode does not exist
// POST: this TNode is created and data is set
//       next/prev/upLevel/downLevel are nullptr
iteratorBST::iteratorBST(TNode *root) {
  current = root;
  if (current == nullptr) { return; }
  while (current->getLeft() != nullptr && !current->getLeftThread()) {
    current = current->getLeft();
  }
}

//-----------------------------------------------------------------------------
// next()
// Description: traverses tree inorder by one,
//              by moving the TNode* current
// PRE: threadedBST exists and this iterator exists
// POST: returned true if successfully moved inorder by one
//       OR returned false if there is no next Node in order
bool iteratorBST::next() {
  if (!hasNext()) { return false; }
  if (!current->getRightThread()) {
    // Real right child: descend to the leftmost node of the right subtree.
    current = current->getRight();
    while (current->getLeft() != nullptr && !current->getLeftThread()) {
      current = current->getLeft();
    }
  } else {
    // Successor thread: follow it directly to the inorder successor.
    current = current->getRight();
  }
  return true;
}


//-----------------------------------------------------------------------------
// hasNext()
// Description: checks if current is
//              not yet at max value of the threadedBST
// PRE: threadedBST exists and this iterator exists
// POST: returned true if current is not at the max value
//       OR returned false if current is at max value
bool iteratorBST::hasNext() const { return current->getRight() != nullptr; }

//-----------------------------------------------------------------------------
// getCurrent()
// Description: returns TNode* current
// PRE: threadedBST exists and this iterator exists
// POST: returned TNode* current
TNode *iteratorBST::getCurrent() const { return current; }


//-----------------------------------------------------------------------------
// threadedBST CONSTRUCTOR
// Description: creates threadedBST with n-number of nodes
//              calls constructorHelper() for actual construction process
// PRE: n is > 0
// POST: balanced threadedBST of size-n is created with nodes 1....n
threadedBST::threadedBST(int n) {
  // indexes
  int start = 1;
  int end = n;
  int mid = (end + start) / 2;

  // create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid);
  constructorHelper(mid + 1, end);

  // add threads
  addThreads(this->root);
}

//-----------------------------------------------------------------------------
// constructorHelper()
// Description: recursive helper function for threadedBST CONSTRUCTOR
//              recursively adds root and subroots
// PRE: threadedBST exists with a root node already instantiated
// POST: threadedBST is constructed in full after all recursive calls finish
void threadedBST::constructorHelper(int start, int end) {
  if (start <= end) {
    int mid = (start + end) / 2;
    if (mid != root->data) {
      add(mid);
    }
    if (start != end) {
      // The start <= end guard above makes the end > 2 check redundant:
      // constructorHelper(start, mid-1) returns immediately when mid == start.
      constructorHelper(start, mid - 1);
      constructorHelper(mid + 1, end);
    }
  }
}

//-----------------------------------------------------------------------------
// threadedBST COPY CONSTRUCTOR
// Description: creates exact copy of given TBST by cloning real child links
//              and then rebuilding thread links explicitly by inorder traversal
// PRE: oldBST may be empty or non-empty
// POST: an exact structural and threaded copy of oldBST is constructed
threadedBST::threadedBST(const threadedBST &oldBST) {
  this->root = cloneRealChildren(oldBST.root);
  rebuildAllThreads(this->root);
}

TNode *threadedBST::cloneRealChildren(const TNode *source) {
  if (source == nullptr) {
    return nullptr;
  }

  TNode *clone = new TNode(source->data);
  if (source->left != nullptr && !source->leftThread) {
    clone->left = cloneRealChildren(source->left);
  }
  if (source->right != nullptr && !source->rightThread) {
    clone->right = cloneRealChildren(source->right);
  }
  return clone;
}

void threadedBST::rebuildThreadsInorder(TNode *node, TNode *&prev) {
  if (node == nullptr) {
    return;
  }

  TNode *leftChild = node->left;
  TNode *rightChild = node->right;

  rebuildThreadsInorder(leftChild, prev);

  if (node->left == nullptr) {
    node->left = prev;
    node->leftThread = (prev != nullptr);
  } else {
    node->leftThread = false;
  }

  if (prev != nullptr && prev->right == nullptr) {
    prev->right = node;
    prev->rightThread = true;
  }

  node->rightThread = false;
  prev = node;

  rebuildThreadsInorder(rightChild, prev);
}

void threadedBST::rebuildAllThreads(TNode *rootNode) {
  if (rootNode == nullptr) {
    return;
  }

  TNode *prev = nullptr;
  rebuildThreadsInorder(rootNode, prev);
}

//-----------------------------------------------------------------------------
// threadedBST COPY ASSIGNMENT OPERATOR
// Description: assigns rhs to this, replacing current content
// PRE: both objects exist (rhs may be empty)
// POST: this is an exact deep copy of rhs; previous content is freed
threadedBST &threadedBST::operator=(const threadedBST &rhs) {
  if (this != &rhs) {
    clear(this->root);
    this->root = nullptr;
    threadedBST tmp(rhs);
    this->root = tmp.root;
    tmp.root = nullptr; // prevent tmp destructor from freeing the adopted tree
  }
  return *this;
}

//------------------------------------------------------------------------------
// threadedBST DESTRUCTOR
// Description: destroys threadedBST object
//              calls clear() as helper function
//              to delete nodes from memory
// PRE: threadedBST exists
// POST: threadedBST is destroyed, deleted;
//       all allocated memory for the threadedBST is freed
threadedBST::~threadedBST() {
  clear(this->root);
}

//-----------------------------------------------------------------------------
// clear()
// Description: deletes all nodes in threadedBST
//              traverses and delete in postorder fashion
// PRE: threadedBST exists
// POST: threadedBST is deletedd from memory
//       all allocated memory for the threadedBST is freed
void threadedBST::clear(TNode *subTreePtr) {
  if (subTreePtr != nullptr) {
    if (subTreePtr->left != nullptr && !subTreePtr->leftThread) {
      clear(subTreePtr->left);
    }
    if (subTreePtr->right != nullptr && !subTreePtr->rightThread) {
      clear(subTreePtr->right);
    }
    subTreePtr->left = nullptr;
    subTreePtr->right = nullptr;
    delete subTreePtr;
  }
}

//---------------------------------------------------------------------------
// remove()
// Description: return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       calls removeHelper for actual removal process
bool threadedBST::remove(int value) {
  if (!contains(value)) {
    return false;
  }
  return removeHelper(value, this->root, this->root);
}

TNode *threadedBST::inorderPredecessor(TNode *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->leftThread) {
    return node->left;
  }

  TNode *walk = node->left;
  while (walk != nullptr && !walk->rightThread && walk->right != nullptr) {
    walk = walk->right;
  }
  return walk;
}

TNode *threadedBST::inorderSuccessor(TNode *node) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->rightThread) {
    return node->right;
  }

  TNode *walk = node->right;
  while (walk != nullptr && !walk->leftThread && walk->left != nullptr) {
    walk = walk->left;
  }
  return walk;
}

void threadedBST::retargetAdjacentThreads(TNode *removedNode) {
  if (removedNode == nullptr) {
    return;
  }

  TNode *predecessor = inorderPredecessor(removedNode);
  TNode *successor = inorderSuccessor(removedNode);

  if (predecessor != nullptr && predecessor->rightThread &&
      predecessor->right == removedNode) {
    predecessor->right = successor;
  }
  if (successor != nullptr && successor->leftThread &&
      successor->left == removedNode) {
    successor->left = predecessor;
  }
}

bool threadedBST::hasRealLeft(const TNode *node) const {
  return node->left != nullptr && !node->leftThread;
}

bool threadedBST::hasRealRight(const TNode *node) const {
  return node->right != nullptr && !node->rightThread;
}

void threadedBST::removeLeafNode(TNode *node, TNode *parent) {
  retargetAdjacentThreads(node);

  if (parent == node) {
    root = nullptr;
  }
  if (parent->right == node) {
    parent->right = node->right;
    parent->rightThread = node->rightThread;
  } else {
    parent->left = node->left;
    parent->leftThread = node->leftThread;
  }
  delete node;
}

void threadedBST::removeNodeWithOnlyRightChild(TNode *node) {
  TNode *deleteMe = node->right;
  retargetAdjacentThreads(deleteMe);

  node->right = deleteMe->right;
  node->rightThread = deleteMe->rightThread;
  if (!deleteMe->leftThread) {
    node->left = deleteMe->left;
    TNode *findThread = deleteMe;
    while (!findThread->leftThread) {
      findThread = findThread->left;
    }
    findThread->leftThread = false;
    findThread->left = nullptr;
  } else {
    node->left = nullptr;
    node->leftThread = false;
  }
  node->data = deleteMe->data;
  delete deleteMe;
}

void threadedBST::removeNodeWithOnlyLeftChild(TNode *node) {
  TNode *deleteMe = node->left;
  retargetAdjacentThreads(deleteMe);

  node->left = deleteMe->left;
  node->leftThread = deleteMe->leftThread;
  if (!deleteMe->rightThread) {
    node->right = deleteMe->right;
    TNode *findThread = deleteMe;
    while (!findThread->rightThread) {
      findThread = findThread->right;
    }
    findThread->rightThread = false;
    findThread->right = nullptr;
  } else {
    node->right = nullptr;
    node->rightThread = false;
  }
  node->data = deleteMe->data;
  delete deleteMe;
}

void threadedBST::removeNodeWithTwoChildren(TNode *node) {
  TNode *subTreeParent = node;
  TNode *subTreePtr = node->right;
  if (subTreePtr != nullptr) {
    if (!subTreePtr->leftThread && subTreePtr->left != nullptr) {
      while (!subTreePtr->leftThread && subTreePtr->left != nullptr) {
        subTreeParent = subTreePtr;
        subTreePtr = subTreePtr->left;
      }

      node->data = subTreePtr->data;

      if (subTreePtr->isLeaf()) {
        subTreeParent->left = nullptr;
      } else {
        subTreeParent->left = subTreePtr->right;
      }
    } else {
      node->data = subTreePtr->data;
      subTreeParent->right = subTreePtr->right;
      subTreeParent->rightThread = subTreePtr->rightThread;
    }
    retargetAdjacentThreads(subTreePtr);
  }
  delete subTreePtr;
}

//---------------------------------------------------------------------------
// removeHelper()
// Description: recursive helper function for remove() --> removeHelper()
//              return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int value, TNode *node, TNode *parent) {
  if (value < node->data) {
    return removeHelper(value, node->left, node);
  } else if (value > node->data) {
    return removeHelper(value, node->right, node);
  }

  if (!hasRealLeft(node) && !hasRealRight(node)) {
    removeLeafNode(node, parent);
  } else if (!hasRealLeft(node) && hasRealRight(node)) {
    removeNodeWithOnlyRightChild(node);
  } else if (hasRealLeft(node) && !hasRealRight(node)) {
    removeNodeWithOnlyLeftChild(node);
  } else {
    removeNodeWithTwoChildren(node);
  }

  return true;
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
bool threadedBST::add(int value) {
  if (root == nullptr) {
    root = new TNode(value);
    return true;
  }
  if (contains(value)) {
    cout << "Duplicates are not allowed: " << value << endl;
    return false;
  }
  return addHelper(value, this->root);
}

//-----------------------------------------------------------------------------
// addHelper()
// Description: recursive helper function for add() --> addHelper()
//              return true if successfully added, no duplicates
// PRE: data may or may not already exist in threadedBST
// POST: if data did not exist in threadedBST,
//       TNode is created with data and added to threadedBST
//       OR if data did exist in threadedBST, returned false
//       (no duplicates allowed)
bool threadedBST::addHelper(int value, TNode *node) {
  if (value < node->data) {
    if (node->left != nullptr) {
      return addHelper(value, node->left);
    } else {
      node->left = new TNode(value);
    }
  } else if (value > node->data) {
    if (node->right != nullptr) {
      return addHelper(value, node->right);
    } else {
      node->right = new TNode(value);
    }
  }
  return true;
}


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

//-----------------------------------------------------------------------------
  // containsHelper()
  // Description: Checks to see whether or not a data data exists in the list
  //              recursive helper function for contains() --> containsHelper()
  //              Returns true if the data exists in the threadedBST.
  //              Returns false otherwise
  // PRE: data may or may exist in threadedBST
  // POST: if data exists in threadedBST, returned true
  //       OR if data does not exist in list, returned false
bool threadedBST::containsHelper(int target, TNode *node) const {
  if (node == nullptr) { return false; }
  if (target == node->data) { return true; }
  if (target > node->data && node->right != nullptr && !node->rightThread) {
    return containsHelper(target, node->right);
  }
  if (target < node->data && node->left != nullptr && !node->leftThread) {
    return containsHelper(target, node->left);
  }
  return false;
}

//-----------------------------------------------------------------------------
  // addThreads()
  // Description: iterates through a built threadedBST
  //              and places threads where needed
  // PRE: a non-empty threadedthreadedBST exists
  // POST: nodes with nullptr children are given either predecessor,
  //       successor, OR both threads where applicable
void threadedBST::addThreads(TNode *treePtr) {
  if (treePtr != nullptr) {
    if (treePtr->isLeaf()) {
      if (contains(treePtr->data + 1)) {
        treePtr->right = findNode(treePtr->data + 1, this->root); // r
        treePtr->rightThread = true;
      }
      if (contains(treePtr->data - 1)) {
        treePtr->left = findNode(treePtr->data - 1, this->root); // r
        treePtr->leftThread = true;
      }
      return;
    }

    if (treePtr->left != nullptr && !treePtr->leftThread) {
      addThreads(treePtr->left); // a
    }

    if (treePtr->right == nullptr) {
      if (contains(treePtr->data + 1)) {
        treePtr->right = findNode(treePtr->data + 1, this->root); // t
        treePtr->rightThread = true;
      }
    }
    if (treePtr->left == nullptr) {
      if (contains(treePtr->data - 1)) {
        treePtr->left = findNode(treePtr->data - 1, this->root); // d
        treePtr->leftThread = true;
      }
    }
    if (treePtr->right != nullptr && !treePtr->rightThread) {
      addThreads(treePtr->right); // b
    }
  }
}

//-----------------------------------------------------------------------------
  // findNode()
  // Description: calls contains() to check if target node exists in,
  //              traverses through threadedthreadedBST at log(n) speed
  //              returns target node's pointer if found, nullptr if not
  // PRE: a non-empty threadedthreadedBST exists
  // POST: returned a pointer
TNode *threadedBST::findNode(int target, TNode *treePtr) const {
  if (target < treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->left);
  }
  if (target > treePtr->data && treePtr->right != nullptr) {
    return findNode(target, treePtr->right);
  }
  return treePtr;
}

bool threadedBST::isEmpty() const {
  return this->root == nullptr;
}
