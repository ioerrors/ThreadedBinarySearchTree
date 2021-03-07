#include <cassert>
#include <climits>
#include <iostream>

#include "threadedBST.h"

//test comment 
using namespace std;

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
}


int main() {
  test1();
  cout << "Done." << endl;
  return 0;
}
