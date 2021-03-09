#include <cassert>
#include <iostream>

#include "threadedBST.h"

// test comment
using namespace std;

void visiting(const int x) {
  cout << "this is visit:" << endl;
  cout << x << endl;
}

void test1() {
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
  cout << "Test copy 1: N = 19 " << endl;
  threadedBST threadedCopy2(threaded2);
  cout << threadedCopy2 << endl;
  cout << "Test copy 1: N = 8" << endl;
  threadedBST threadedCopy3(threaded3);
  cout << threadedCopy3 << endl;
}

int main() {
  test1();
  cout << "Done." << endl;
  return 0;
}
