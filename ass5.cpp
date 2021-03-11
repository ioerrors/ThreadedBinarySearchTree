#include <cassert>
#include <iostream>

#include "threadedBST.h"

// test comment
using namespace std;

void removeEvens(threadedBST &threadedCopy) {
  iteratorBST itty(threadedCopy.getRoot());
  int cur;
  while (itty.hasNext()) {
    cur = itty.getCurrent()->getData();
    if (cur % 2 == 0) {
      threadedCopy.remove(cur);
    }
    itty++;
  }
  cur = itty.getCurrent()->getData();
  if (cur % 2 == 0) {
    threadedCopy.remove(cur);
  }
}

int input() {
  int n;
  string prompt = "Please enter a non-zero positive integer: ";
  cout << prompt;
  cin >> n;
  while (n < 0) {
    cout << prompt;
    cin >> n;
  }
  return n;
}

void bigTest() {
  string exitPrompt = "To exit, enter 0.";
  cout << exitPrompt << endl;
  int n = input();
  while (n != 0) {
    threadedBST threaded(n);
    threadedBST threadedCopy(threaded);
    removeEvens(threadedCopy);
    //<< operator uses the iterator class
    cout << threadedCopy;
    cout << endl << exitPrompt << endl;
    n = input();
  }
}

int main() {
  // testConstructors();
  // testRemoves();
  bigTest();
  cout << "Done." << endl;
  return 0;
}

/*
void testConstructors() {
  cout << "Test1: N = 7 " << endl;
  threadedBST threaded1(7);
  cout << threaded1 << endl;
  cout << "Test 2: N = 19 " << endl;
  threadedBST threaded2(19);
  cout << threaded2 << endl;
  cout << "Test 3: N = 8 " << endl;
  threadedBST threaded3(8);
  cout << threaded3 << endl;
  cout << "Test copy 1: N = 7 " << endl;
  threadedBST threadedCopy(threaded1);
  cout << threadedCopy << endl;
  cout << "Test copy 2: N = 19 " << endl;
  threadedBST threadedCopy2(threaded2);
  cout << threadedCopy2 << endl;
  cout << "Test copy 3: N = 8" << endl;
  threadedBST threadedCopy3(threaded3);
  cout << threadedCopy3 << endl;
}


void testRemoves() {
  cout << "Test1: N = 7 " << endl;
  threadedBST threaded1(7);
  cout << threaded1 << endl;
  cout << "Test copy 1: N = 7 " << endl;
  threadedBST threadedCopy(threaded1);
  cout << threadedCopy << endl;
  cout << "Delete all evens from copy 1, N = 7:" << endl;
  removeEvens(threadedCopy);
  cout << threadedCopy << endl;

  cout << "Test 2: N = 19 " << endl;
  threadedBST threaded2(19);
  cout << threaded2 << endl;
  cout << "Test copy 2: N = 19 " << endl;
  threadedBST threadedCopy2(threaded2);
  cout << threadedCopy2 << endl;
  cout << "Delete all evens from copy 2, N = 19:" << endl;
  removeEvens(threadedCopy2);
  cout << threadedCopy2 << endl;

  cout << "Test 3: N = 8 " << endl;
  threadedBST threaded3(8);
  cout << threaded3 << endl;
  cout << "Test copy 3: N = 8" << endl;
  threadedBST threadedCopy3(threaded3);
  cout << threadedCopy3 << endl;
  cout << "Delete all evens from copy 3, N = 8:" << endl;
  removeEvens(threadedCopy3);
  cout << threadedCopy3 << endl;

  cout << "Test 4: N = 30 " << endl;
  threadedBST threaded4(30);
  cout << threaded4 << endl;
  cout << "Test copy 3: N = 30" << endl;
  threadedBST threadedCopy4(threaded4);
  cout << threadedCopy4 << endl;
  cout << "Delete all evens from copy 4, N = 30:" << endl;
  removeEvens(threadedCopy4);
  cout << threadedCopy4 << endl;
}
*/
