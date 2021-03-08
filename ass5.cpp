#include <cassert>
#include <climits>
#include <iostream>

#include "threadedBST.h"

// test comment
using namespace std;

void test1() {
  cout << endl << "Test1: N = 7 " << endl;
  threadedBST threaded1(7);
  cout << threaded1 << endl;
  cout << "Test 2: N = 19 " << endl;
  threadedBST threaded2(19);
  cout << threaded2 << endl;
  cout << "Test 3: N = 8 " << endl;
  threadedBST threaded3(8);
  cout << threaded3 << endl;
}

void test2(){
  cout << endl << "Creating original tree of N = 7" << endl;
  threadedBST threaded1(7);
  cout << "Creating copy of original tree" << endl;
  threadedBST threaded2 = threaded1; 
  cout << "Print out of original tree: " << threaded1 << endl;
  cout << "Print out of copy tree: " << threaded2 << endl;
}

int main() {
  cout << "Performing test1" << endl;
  test1();
  cout << endl << endl << "Performing test2" <<endl;
  test2();
  cout << "Done." << endl;
  return 0;
}
