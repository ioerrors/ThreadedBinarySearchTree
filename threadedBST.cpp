////////////////////////////////  skiplist.cpp file  //////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice on 02/19/2021.
//
// skiplist class demonstrating data structure
// Can search a skiplist and find items in O(log n) time.
// No duplicates are allowed.
// modified by mashhadi on 14th feb to add an alternative op<<

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

bool isEmpty(){
if(root == nullptr){
return true;
}

return false;
}

bool clear(TNode* subTreePtr){
if(subTreePtr != nullptr){
clear(subTreePtr->leftChild);
clear(subTreePtr->rightChild);
subTreePtr->leftChild = nullptr;
subTreePtr->rightChild = nullptr:
delete subTreePtr;
}
}

bool contains(int target, TNode* root){

//check if root's value is target
if(target == root->value){
return true;
}

if(root->value < target  && root->rightChild !=null && root->rightThread == false){
root = root->rightChild;
contains(target,root);
}

if(root->value > target && root->leftChild !=null && root->leftThread == false){
root = root->leftChild;
contains(target,root);
}

return false; 
}
