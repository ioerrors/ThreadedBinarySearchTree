#include <cassert>
#include <climits>
#include <iostream>

#include "skiplist.h"

//test comment 
using namespace std;

void test1() {

  SkipList skp(5);

  skp.add(3);
  skp.add(5);
  skp.add(9);
  skp.add(14304);
  skp.add(-19394);
  skp.add(0);

  // cannot add existing
  assert(!skp.add(3));

  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;

  // contains INT_MAX or INT_MIN, but cannot remove or add as intended
  cout << "contains INT_MAX ? " << skp.contains(INT_MAX) << endl;
  cout << "remove INT_MAX ? " << skp.remove(INT_MAX) << endl;
  cout << "contains INT_MIN ? " << skp.contains(INT_MIN) << endl;
  cout << "remove INT_MIN ? " << skp.remove(INT_MIN) << endl;
  cout << "add INT_MAX ? " << skp.add(INT_MAX) << endl;
  cout << "add INT_MIN ? " << skp.add(INT_MIN) << endl;

  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}

void test04() {
  SkipList s(5);
  for (int i = 0; i < 20; ++i) {
    int number = rand() % 100;
    s.add(number);
    cout << "After adding " << number << endl;
    cout << s << endl;
    cout << " " << endl;
  }
}

int main() {
  test1();
  test04();
  cout << "Done." << endl;
  return 0;
}
