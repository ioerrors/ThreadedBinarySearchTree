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
  iteratorBST iterate(bst.getRoot());
  os << iterate.getCurrent()->getData() << " ";
  // use iteratorBST?

  while (iterate++) {
    // iterate++;
    os << iterate.getCurrent()->getData() << " ";
  }
  return os;
}

//-----------------------------------------------------------------------------
// Overloaded Operator ++
// Description: calls next() to traverse tree inorder by one,
//              by moving the TNode* current by one in order
// PRE: threadedBST exists and this iterator exists
// POST: returned true if successfully moved inorder by one
//       OR returned false if there is no next Node in order
bool operator++(iteratorBST &itty, int) { return itty.next(); }



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
TNode *TNode::getLeft() const {
  if (left == nullptr) {
    return nullptr;
  }
  return left;
}

//-----------------------------------------------------------------------------
// getRight()
// Description: returns right child of this TNode
// PRE: this TNode object does exist
// POST: returned this TNode's right child
//       OR returned nullptr if TNode has no right child
TNode *TNode::getRight() const {
  if (right == nullptr) {
    return nullptr;
  }
  return right;
}



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
  while (current->getLeft() != nullptr) {
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
  if (hasNext()) {
    if (current->getRight() != nullptr && current->getLeft() != nullptr &&
        !current->getLeftThread() && !current->getRightThread()) {
      current = current->getRight();
      while (!current->getLeftThread() && current->getLeft() != nullptr) {
        current = current->getLeft();
      }
    } else if (current != nullptr && current->getRight() != nullptr) {
      current = current->getRight();
    }
  } else {
    return false;
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
// threadedBST COPY CONSTRUCTOR
// Description: creates exact copy of given TBST
//              calls copyConstHelper() to determine largest integer value n
//              calls constructorHelper() to create full n-sized tree
//              calls remove() on integers not contained in original
//              calls addThreads to add threads to applicables nodes
// PRE: oldBST is non-empty
// POST: an exact copy of oldBST is constructed
threadedBST::threadedBST(const threadedBST &oldBST) {
  // indexes
  int start = 1;
  TNode *n = oldBST.getRoot();
  int end = copyConstHelper(n);
  if (end != 0) {
    int mid = (end + start) / 2;

    // create node, attach to this->root
    this->root = new TNode(mid);
    constructorHelper(start, mid);
    constructorHelper(mid + 1, end);

    // add threads
    addThreads(this->root);

    // for loop removing nodes not in oldBST
    for (int i = 1; i < end; i++) {
      if (!oldBST.contains(i)) {
        this->remove(i);
      }
    }
  } else {
    this->root = nullptr;
  }
}

//-----------------------------------------------------------------------------
// copyConstructorHelper()
// Description: recursive helper function for constructor
//              iterates through right branches of original tree
//              and returns largest integer in original tree
// PRE: threadedthreadedBST exists with at least single node
// POST: returned integer of maximum doata value to the right of treePtr
//       OR returned 0 if tree is isEmpty
int threadedBST::copyConstHelper(TNode *treePtr) {
  if (treePtr != nullptr) {
    while (treePtr->right != nullptr) {
      treePtr = treePtr->right;
    }
    return (treePtr->data);
  } else {
    return 0;
  }
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
  // need to delete individual nodes
  clear(this->root); // 9
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
  } else {
    // at this point data === node->data
    // check if leaf, if so, remove.
    if (node->isLeaf()) {
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
    // check if right child only
    else if ((node->left == nullptr || node->leftThread) &&
             (node->right != nullptr && !node->rightThread)) {
      TNode *deleteMe = node->right;
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
    // check if left child only
    else if ((node->right == nullptr || node->rightThread) &&
             (node->left != nullptr && !node->leftThread)) {
      TNode *deleteMe = node->left;
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
    // oh no; has both
    else {
      // take right subtree
      TNode *subTreeParent = node;
      TNode *subTreePtr = node->right;
      // check if we have left children
      if (subTreePtr != nullptr) {
        if (!subTreePtr->leftThread && subTreePtr->left != nullptr) {
          // if so move to leftmost child
          while (!subTreePtr->leftThread && subTreePtr->left != nullptr) {
            subTreeParent = subTreePtr;
            subTreePtr = subTreePtr->left;
          }

          // copy over the data
          if (subTreePtr != nullptr) {
            node->data = subTreePtr->data;
          }

          // if leaf, sets parent->left to nullptr
          if (subTreePtr->isLeaf()) {
            subTreeParent->left = nullptr;
          } else {
            // if right child only, sets parent->left to that branch
            subTreeParent->left = subTreePtr->right;
          }
        } else {
          node->data = subTreePtr->data;
          subTreeParent->right = subTreePtr->right;
          subTreeParent->rightThread = subTreePtr->rightThread;
        }
      }
      // now delete subTreePtr
      delete subTreePtr;
    }
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
bool threadedBST::threadedBST::add(int value) {
  if (root == nullptr) {
    root = new TNode(value);
    return true;
  }
  // would like to just say contains(value)
  if (contains(value)) { // maybe include containsHelper(data, this->root);
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
  if (node != nullptr) {
    // check if node's data is target
    if (target == node->data) {
      return true;
    }
    if (target > node->data && node->right != nullptr &&
        node->rightThread == false) {
      node = node->right;
      return containsHelper(target, node);
    }
    if (target < node->data && node->left != nullptr &&
        node->leftThread == false) {
      node = node->left;
      return containsHelper(target, node);
    }
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
  if (target > treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->right);
  }
  return treePtr;
}

// comment these
bool threadedBST::isEmpty() const {
  if (this->root == nullptr) {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------
  // getRoot()
  // Description: returns root pointer
  // PRE: threadedBST exists
  // POST: root pointer is returned
TNode *threadedBST::getRoot() const { return this->root; }
