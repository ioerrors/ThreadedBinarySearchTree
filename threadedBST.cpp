////////////////////////////////  threadedBST.cpp file
/////////////////////////////
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

// returns data
int TNode::getData() { return data; }

// returns left child
TNode *TNode::getLeft() {
  if (left == nullptr) {
    return nullptr;
  }
  return left;
}

// returns right child
TNode *TNode::getRight() {
  if (right == nullptr) {
    return nullptr;
  }
  return right;
}

// returns thread status of right child
bool TNode::getRightThread() { return rightThread; }

// returns thread status of left child
bool TNode::getLeftThread() { return leftThread; }

//-----------------------------------------------------------------------------
// Iterator CONSTRUCTOR
// PRE: this Iterator does not exist
// POST: this Iterator is created and is set
//       to leftmost node
iteratorBST::iteratorBST(TNode *root) {
  current = root;
  while (current->getLeft() != nullptr) {
    current = current->getLeft();
  }
}

//-----------------------------------------------------------------------------
// inorder traversal by one step
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
// postorder traversal by one step
bool iteratorBST::prev() {
  if (current != nullptr && current->getLeft() != nullptr) {
    if (current->getRight() != nullptr && current->getLeft() != nullptr &&
        !current->getLeftThread() && !current->getRightThread()) {
      current = current->getLeft();
      while (!current->getRightThread() && current->getRight() != nullptr) {
        current = current->getRight();
      }
      return true;
    } else {
      current = current->getLeft();
    }
  } else {
    return false;
  }
  return true;
}

// check if at max of tree
bool iteratorBST::hasNext() {
  if (current == nullptr) {
    return false;
  } else {
    return current->getRight() != nullptr;
  }
}

TNode *iteratorBST::getCurrent() const {
  if (current != nullptr) {
    return current;
  }
  return nullptr;
}

//-----------------------------------------------------------------------------
// << operator
// display all the elements of the threadedBST
// PRE: threadedBST &bst exists
// POST: ostream has formatted output of threadedBST, example:
ostream &operator<<(ostream &os, const threadedBST &bst) {
  // return if the tree is empty
  if (bst.getRoot() == nullptr) {
    os << "empty tree";
    return os;
  }
  iteratorBST iterate(bst.getRoot());
  os << iterate.getCurrent()->getData() << " ";
  // use iteratorBST?
  while (iterate.hasNext()) {
    iterate++;
    os << iterate.getCurrent()->getData() << " ";
  }
  return os;
}

//-----------------------------------------------------------------------------
// ++ operator
// move iterator by one inorder
// PRE: threadedBST &bst exists, iterator exists
// POST: iterator now points at next node inorder:
bool operator++(iteratorBST &itty, int) { return itty.next(); }

//-----------------------------------------------------------------------------
// -- operator
// move iterator by one postorder
// PRE: threadedBST bst exists, iterator exists
// POST: iterator now points at next node postorder (prev node inorder):
bool operator--(iteratorBST &itty) { return itty.prev(); }

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

  // create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid);
  constructorHelper(mid + 1, end);

  // add threads
  addThread(this->root);
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
// threadedBST copy constructor
// PRE: None
// POST: a new threadedBST is made, separate but identical to original
// threadedBST
threadedBST::threadedBST(const threadedBST &oldBST) {
  // indexes
  int start = 1;
  TNode *n = oldBST.getRoot();
  int end = copyConstHelper(n);
  int mid = (end + start) / 2;

  // create node, attach to this->root
  this->root = new TNode(mid);
  constructorHelper(start, mid);
  constructorHelper(mid + 1, end);

  // add threads
  addThread(this->root);

  // for loop removing nodes not in oldBST
  for (int i = 1; i < end; i++) {
    if (!oldBST.contains(i)) {
      this->remove(i);
    }
  }
}

//-------------------------------------------------------------------------------
// traverses through right branches
// returns largest integer in tree
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

//-----------------------------------------------------------------------------
// destructor
// PRE: threadedBST exists
// POST: threadedBST is deleted, all memory deallocated, no leaks
threadedBST::~threadedBST() {
  // need to delete individual nodes
  clear(this->root); // 9
}

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

//-----------------------------------------------------------------------------
// return true if successfully removed
// PRE: data may or may exist in threadedBST
// POST: data removed from threadedBST, returned true
//       if data already did not exist in list returned false
bool threadedBST::removeHelper(int value, TNode *node, TNode *parent) {
  if (node != nullptr && parent != nullptr) {
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
  return false;
}

//
bool threadedBST::remove(int value) {
  if (!contains(value)) {
    return false;
  }
  return removeHelper(value, this->root, this->root);
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
  if (node != nullptr) {
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
  return false;
}
bool threadedBST::threadedBST::add(int value) {
  // would like to just say contains(value)
  if (contains(value)) { // maybe include containsHelper(data, this->root);
    cout << "Duplicates are not allowed: " << value << endl;
    return false;
  }
  return addHelper(value, this->root);
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

// comment these
bool threadedBST::isEmpty() {
  if (this->root == nullptr) {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------
void threadedBST::addThread(TNode *treePtr) {
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
      addThread(treePtr->left); // a
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
      addThread(treePtr->right); // b
    }
  }
}

//-----------------------------------------------------------------------------
TNode *threadedBST::findNode(int target, TNode *treePtr) {
  if (target == treePtr->data) {
    return treePtr;
  }
  if (target < treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->left);
  }
  if (target > treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->right);
  }
  return nullptr;
}

//-----------------------------------------------------------------------------
// returns true if node is a leaf
bool TNode::isLeaf() const {
  if ((this->left == nullptr && this->right == nullptr) ||
      (this->left == nullptr && this->rightThread == true) ||
      (this->right == nullptr && this->leftThread == true) ||
      (this->leftThread == true && this->rightThread == true)) {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------
TNode *threadedBST::getRoot() const { return this->root; }

//-----------------------------------------------------------------------------
void TNode::display(int x) { cout << x << ", "; }
