////////////////////////////////  skiplist.h file  ////////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// skiplist class header demonstrating data structure
// Can search a skiplist and find items in O(log n) time. 
// No duplicates are allowed.
// modified by mashhadi on 14th feb to add an alternative op<<


#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  friend class SkipList;
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // constructor
  explicit SNode(int data);

  // data contained in the object
  int data;

  // link to Next SNode 
  SNode *next;

  // link to Prev SNode
  SNode *prev;
   
  //link to up node 
  SNode *upLevel;

  // link to down SNode
  SNode *downLevel;

};

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &os, const SkipList &list);

private:
  // maximum number of levels
  int depth = 1;

  // array of depth SNode* objects as frontGuards linking levels
  // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
  SNode **frontGuards;

  // array of depth SNode* objects as rearGuards linking levels
  SNode **rearGuards;

  // given a SNode, place it before the given nextNode
  void addBefore(SNode *newNode, SNode *nextNode);

  // return true 50% of time,
  // each node has a 50% chance of being at higher level
  bool alsoHigher() const;


public:
  // default SkipList has only 1 level, just one doubly-linked list
  explicit SkipList(int depth = 1);

  // destructor
  virtual ~SkipList();

  // copy not allowed
  SkipList(const SkipList &other) = delete;

  // move not allowed
  SkipList(SkipList &&other) = delete;

  // assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  // return true if successfully added, no duplicates allowed
  bool add(int data);

  // return true if successfully removed
  bool remove(int data);

  // return true if found in SkipList
  bool contains(int data) const;
};


