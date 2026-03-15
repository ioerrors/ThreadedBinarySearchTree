#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "threadedBST.h"

using namespace std;

static void removeEvens(threadedBST &threadedCopy) {
  int i = 2;
  while (threadedCopy.remove(i)) {
    i += 2;
  }
}

static string inorderString(const threadedBST &tree) {
  ostringstream out;
  out << tree;
  return out.str();
}

static void assertInorder(const threadedBST &tree,
                          const vector<int> &expectedValues) {
  if (expectedValues.empty()) {
    assert(inorderString(tree) == "empty tree");
    return;
  }

  ostringstream expected;
  for (int value : expectedValues) {
    expected << value << " ";
  }
  assert(inorderString(tree) == expected.str());
}

static void assertContainsSet(const threadedBST &tree,
                              const vector<int> &present,
                              const vector<int> &absent) {
  for (int value : present) {
    assert(tree.contains(value));
  }
  for (int value : absent) {
    assert(!tree.contains(value));
  }
}

static void testComprehensive() {
  cout << "=====================================================" << endl;
  cout << "====Comprehensive Tests with 100% Code Coverage======" << endl;
  cout << "=====================================================" << endl;
  cout << "Test 1: N = 7 " << endl;
  threadedBST threaded(7);
  cout << threaded << endl;
  for (int i = 1; i < 8; i++) {
    if (i != 5) {
      threaded.remove(i);
    }
  }
  cout << "Test 1: N = 7, removed everything, except for 5" << endl;
  cout << threaded << endl;

  cout << endl << "Test 2: N = 8 " << endl;
  threadedBST threadedRemoveAll(8);
  cout << threadedRemoveAll << endl;
  for (int i = 1; i < 9; i++) {
    threadedRemoveAll.remove(i);
  }
  cout << "Test 2: N = 8, removed everything" << endl;
  cout << threadedRemoveAll << endl;

  cout << endl << "Test 3: N = 7 " << endl;
  threadedBST threaded1(7);
  cout << threaded1 << endl;
  cout << "Test copy 3: N = 7 " << endl;
  threadedBST threadedCopy(threaded1);
  cout << threadedCopy << endl;
  cout << "Delete all evens from copy 3, N = 7:" << endl;
  removeEvens(threadedCopy);
  cout << threadedCopy << endl;

  cout << endl << "Test 4: N = 19 " << endl;
  threadedBST threaded2(19);
  cout << threaded2 << endl;
  cout << "Test copy 4: N = 19 " << endl;
  threadedBST threadedCopy2(threaded2);
  cout << threadedCopy2 << endl;
  cout << "Delete all evens from copy 4, N = 19:" << endl;
  removeEvens(threadedCopy2);
  cout << threadedCopy2 << endl;

  cout << endl << "Test 5: N = 8 " << endl;
  threadedBST threaded3(8);
  cout << threaded3 << endl;
  cout << "Test copy 5: N = 8" << endl;
  threadedBST threadedCopy3(threaded3);
  cout << threadedCopy3 << endl;
  cout << "Delete all evens from copy 5, N = 8:" << endl;
  removeEvens(threadedCopy3);
  cout << threadedCopy3 << endl;

  cout << endl << "Test 6: N = 30 " << endl;
  threadedBST threaded4(30);
  cout << threaded4 << endl;
  cout << "Test copy 6: N = 30" << endl;
  threadedBST threadedCopy4(threaded4);
  cout << threadedCopy4 << endl;
  cout << "Delete all evens from copy 6, N = 30:" << endl;
  removeEvens(threadedCopy4);
  cout << threadedCopy4 << endl;

  cout << endl
       << "Special Test: Make copy of a bst with evens already removed: "
       << endl
       << "Original evensRemoved N = 30" << endl;
  cout << threadedCopy4 << endl;
  threadedBST threadedSpecialCopy1(threadedCopy4);
  cout << "DeepCopy of evensRemoved N = 30: " << endl;
  cout << threadedSpecialCopy1 << endl;
  cout << "DeepCopy of evensRemoved N = 30, with extra removed number 5: "
       << endl;
  threadedSpecialCopy1.remove(5);
  cout << threadedSpecialCopy1 << endl;
  cout << "Original evensRemoved N = 30, showing 5 still exists" << endl;
  cout << threadedCopy4 << endl;

  cout << endl << "Special Test: Try to Copy an Empty Tree" << endl;
  threadedBST threadedSpecialCopy2(threadedRemoveAll);
  cout << threadedSpecialCopy2 << endl;
  cout << "DeepCopy of emptyTree: " << endl;
  cout << threadedSpecialCopy2 << endl;
  cout << "DeepCopy of emptyTree, with an added 3: " << endl;
  threadedSpecialCopy2.add(3);
  cout << threadedSpecialCopy2 << endl;
  cout << "Original emptyTree, showing still empty" << endl;
  cout << threadedRemoveAll << endl;

  cout << endl
       << "Special Test: N = 15 Delete nodes right to left, after remove(9), "
          "remove(8)"
       << endl;
  threadedBST threadedRightToLeft(15);
  threadedRightToLeft.remove(9);
  threadedRightToLeft.remove(8);
  cout << threadedRightToLeft << endl;
  for (int i = 15; i > 0; i--) {
    threadedRightToLeft.remove(i);
  }
  cout << "Special Test: N = 15, removed all nodes from right to left:" << endl;
  cout << threadedRightToLeft << endl;

  threadedRightToLeft.remove(4);
  threadedRightToLeft.add(4);

  cout << "Special Test: Attempting to add a value already contained in tree:"
       << endl;
  threadedRightToLeft.add(4);

  {
    threadedBST original(12);
    threadedBST copied(original);
    threadedBST assigned(1);
    assigned = original;

    copied.remove(6);
    copied.remove(7);
    assigned.remove(8);
    assigned.remove(9);

    assertContainsSet(original, {6, 7, 8, 9, 12}, {});
    assertContainsSet(copied, {8, 9, 12}, {6, 7});
    assertContainsSet(assigned, {6, 7, 12}, {8, 9});
    
    // intentional self-assignment test
    // NOLINTNEXTLINE(clang-diagnostic-self-assign-overloaded)
    assigned = assigned;
    
    assertContainsSet(assigned, {6, 7, 12}, {8, 9});
  }

  {
    threadedBST leafCase(7);
    assert(leafCase.remove(1));
    assertContainsSet(leafCase, {2, 7}, {1});

    threadedBST rightOnlyCase(15);
    assert(rightOnlyCase.remove(8));
    assert(rightOnlyCase.remove(9));
    assert(rightOnlyCase.remove(10));
    assertContainsSet(rightOnlyCase, {11, 12, 15}, {8, 9, 10});

    threadedBST leftOnlyCase(15);
    assert(leftOnlyCase.remove(8));
    assert(leftOnlyCase.remove(7));
    assert(leftOnlyCase.remove(6));
    assertContainsSet(leftOnlyCase, {1, 2, 5}, {6, 7, 8});

    threadedBST twoChildrenCase(15);
    assert(twoChildrenCase.remove(4));
    assertContainsSet(twoChildrenCase, {3, 5, 15}, {4});

    threadedBST rootCase(3);
    assert(rootCase.remove(2));
    assertContainsSet(rootCase, {1, 3}, {2});
    assertInorder(rootCase, {1, 3});
  }

  cout << "=====================================================" << endl;
  cout << "=======Finished Tests for 100% Code Coverage:========" << endl;
  cout << "=====================================================" << endl;
}

int main() {
  testComprehensive();
  return 0;
}
