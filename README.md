Assignment5 CSS 342 C University of Washington
by Micah Rice and Bruce Nguyen
OUR NOTES:
-- use create-output.sh to compile and run

-- output.txt contains the output of a typical create-output.sh run

-- compile with: C++11 or C++14, either should work

-- in using create-output.sh, if terminal shell seems to stop during a stage after clang-tidy, it is waiting for input
-- during create-output.sh it will do this during the 2 memory checks (g++ and valgrind) and the code coverage test,
-- since it runs the program independently each time, and each time the program is asking for input under the hood
-- even though no prompt will show, you can enter as many integers as desired for that memory or code coverage check,
-- then enter 0 to finish that run of the program and continue execution of the create-output.sh.

-- comment out userDefinedTest to avoid user input during create-output.sh execution, testComprehensive() will show memory/code coverage correctly
-- testComprehsive() does not show the original tree after the removeEvens() on the copied tree
-- as that was done in userDefinedTest(), and testComprehensive was for making sure to test everything else in the program not otherwise covered 

-- No changes made to clang-tidy file given in Assignment 3 starter files



Threaded Binary Search Tree
Since a binary search tree with N nodes has N + 1 NULL pointers, half the space allocated in a binary search tree for pointer information is wasted. Suppose that if a node has a NULL left child, we make its left child pointer link to its inorder predecessor, and if a node has a NULL right child, we make its right child pointer link to its inorder successor. This is known as a threaded tree and the extra links are called threads.

Note: Your threadedBST doesn't need to be Complete or Self-balancing but it requires to be balanced. You can achieve that at the point of tree creation by the order you assemble the tree.

Some extra clarifications: You are welcome to use AVT or self balancing functions if you like to practice your coding skills. However as I mentioned before your tree does not have to have that functionality.

To achieve balanced tree for input 1....n you can take n/2 to be the root. then the mid point of the left subarray (1...n/2) would be the left child and the mid point of the right subarray (n/2.....n) would be the right child of the root. You repeat this process until all nodes are inserted.

Building a Threaded Binary Search Tree

Start with the BST code from the Carrano textbook and augment it so that it correctly implements a ThreadedBST. You may do this by either modifying the existing code or by creating new classes derived from the TreeNode and BinarySearchTree classes in Carrano. Make sure that all of the public methods of BinarySearchTree are either correct as-is (when operating on a ThreadedBST) or are replaced (if you are modifying the existing classes) or overridden (if you are creating subclasses) by correct ThreadedBST methods. You may use a KeyType of int during your development process.

The threads can be used to make non-recursive inorder, preorder, and postorder traversals (or iterators without internal stacks). Implement an Inorder iterator class for your ThreadedBST. Your iterator should not use a stack; instead, it should use the thread links.

To test:

Implement your ThreadedBST and Inorder classes as described above. Then, write a program that uses these classes as follows. Your program should take a single command line argument: an integer, n, specifying the number of nodes to create in your tree. Your program should then create a ThreadedBST with KeyType being int and insert the numbers 1,2,…,n into that container in NON INCREMENTAL order (see above). It should then make a copy of that tree and delete all the even numbers from the copy. Finally, it should use iterators to perform an inorder traversal of each tree, outputting to cout each node’s contents (just put a single space between each node’s contents).

Unlike other assignments no initial code is given to you but you are free to use and/or modify any code from the Carrano textbook for this assignment from this repository https://github.com/pisanuw/books/tree/master/Carrano7

Hint: Make sure you think about the followings before you start on your implementation):

How can we distinguish threads from real child pointers?
What are the potential advantages of using threaded trees?
What is your implementation? What are the sequence of steps you will go 
through to change the BST implementation to a Threaded BST? 
Which BST methods need to be modified/overridden and which will work as is?
Pair Programming
Pair programming refers to the practice whereby two programmers work together at one computer, collaborating on the same design, algorithm, code, or test. The pair is made up of a driver, who actively types at the computer or records a design; and a navigator, who watches the work of the driver and attentively identifies problems, asks clarifying questions, and makes suggestions.

Rules you must follow in CSS 342:
-- Partners must be of "equal" ability and experience. For example, do not partner if one person knows C++ well and the other does not. Do not partner if one person has a self-perception of being a strong programmer and the other has a self-perception of being a weak programmer.

My biggest concern is that if one person is a stronger programmer currently, the other person may believe they are understanding, but are not. Note that "strong" changes with experience. Also note that I am not concerned about one person cheating off another. If you don't understand, you WILL do poorly on my exams.

-- Be sure you have comparable work habits and schedules. For example, early-starters don't work well with last-minute workers. If your schedule is such that you do all homework on the weekends and you plan to pair with someone who works weekends, that won't work well.

-- At least 70% of the work must be done working live together so you get the benefit of discussion.

-- I will ask you to write the name of your pair in thisform (Links to an external site.)
-- If pairing isn't working, contact me immediately.

-- One person will do the electronic turn-in, or if you both want to submit (using it for storage), I must be able to grab either one.

The DOs of Pair programming (summary from video)
Talk to each other, but be respectful.
Listen to each other - either person should be able to do anything on the program at any point in time.
Change roles of driver/navigator periodically.
Be patient - be able to explain your work to your partner (or professor).
Respect your partner.
Take breaks.
Be prepared; be ready to work on arrival and don't be late.
The DON'Ts of Pair programming (summary from video posted on the main page)
Don't be a keyboard hog; don't be bossy.
Don't be intimidated; you're not alone if you don't understand.
Don't be quiet; speak up if you disagree.
Don't suffer in silence; talk to the professor if the pairing isn't working out.
