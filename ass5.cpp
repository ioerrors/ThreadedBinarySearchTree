#include <cassert>
#include <climits>
#include <iostream>

#include "threadedBST.h"

//test comment 
using namespace std;

void test1() {
	cout << "Test1: " << endl;
	//crashes on this line --> threadedBST threaded(7);
	//cout << threaded;
}


int main() {
  test1();
  cout << "Done." << endl;
  return 0;
}
