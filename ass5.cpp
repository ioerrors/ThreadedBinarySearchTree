#include <cassert>
#include <iostream>

#include "threadedBST.h"

// test comment
using namespace std;

// calls .remove() on all evens
void removeEvens(threadedBST &threadedCopy) {
  int i = 2;
  while (threadedCopy.remove(i)) {
    i += 2;
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
  while (n > 0) {
    threadedBST threaded(n);
    assert(!threaded.isEmpty());
    threadedBST threadedCopy(threaded);
    //<< operator uses the iterator class
    cout << "original threadedBST, N = " << n << endl;
    cout << threaded;
    cout << endl << "Copy of threadedBST, N = " << n << endl;
    cout << threadedCopy;
    removeEvens(threadedCopy);
    cout << endl
         << "Copy of threadedBST, N = " << n
         << ", with evens removed: " << endl;
    cout << threadedCopy;
    cout << endl
         << "original threadedBST, N = " << n << ", unaltered: " << endl;
    cout << threaded;
    cout << endl << endl << exitPrompt << endl;
    cout << endl << endl;
    n = input();
  }
}

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
  threadedBST threaded(7);
  cout << threaded << endl;
  for (int i = 1; i < 8; i++) {
    if (i != 5) {
      threaded.remove(i);
    }
  }
  cout << "Test1: N = 7, removed everything except 5" << endl;
  cout << threaded << endl;

  cout << "Test 2: N = 7 " << endl;
  threadedBST threaded1(7);
  cout << threaded1 << endl;
  cout << "Test copy 2: N = 7 " << endl;
  threadedBST threadedCopy(threaded1);
  cout << threadedCopy << endl;
  cout << "Delete all evens from copy 2, N = 7:" << endl;
  removeEvens(threadedCopy);
  cout << threadedCopy << endl;

  cout << "Test 3: N = 19 " << endl;
  threadedBST threaded2(19);
  cout << threaded2 << endl;
  cout << "Test copy 3: N = 19 " << endl;
  threadedBST threadedCopy2(threaded2);
  cout << threadedCopy2 << endl;
  cout << "Delete all evens from copy 3, N = 19:" << endl;
  removeEvens(threadedCopy2);
  cout << threadedCopy2 << endl;

  cout << "Test 4: N = 8 " << endl;
  threadedBST threaded3(8);
  cout << threaded3 << endl;
  cout << "Test copy 4: N = 8" << endl;
  threadedBST threadedCopy3(threaded3);
  cout << threadedCopy3 << endl;
  cout << "Delete all evens from copy 4, N = 8:" << endl;
  removeEvens(threadedCopy3);
  cout << threadedCopy3 << endl;

  cout << "Test 5: N = 30 " << endl;
  threadedBST threaded4(30);
  cout << threaded4 << endl;
  cout << "Test copy 5: N = 30" << endl;
  threadedBST threadedCopy4(threaded4);
  cout << threadedCopy4 << endl;
  cout << "Delete all evens from copy 5, N = 30:" << endl;
  removeEvens(threadedCopy4);
  cout << threadedCopy4 << endl;
}

int main() {
  testConstructors();
  testRemoves();
  // bigTest();
  cout << "Done." << endl;
  return 0;
}
