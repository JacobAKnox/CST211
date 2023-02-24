// CST211MidtermBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
#include "BinarySearchTree.h"
#include "Exception.h"

void Display(int& data);
void StringDisplay(string& data);
int main()
{
	// first testing with ints
	BinarySearchTree<int> t1;
	t1.Insert(20);
	t1.Insert(15);
	t1.Insert(25);
	t1.Insert(30);
	t1.Insert(18);
	t1.Insert(12);
	t1.Insert(11);
	cout << "IN ORDER" << endl;
	t1.InOrderTraversal(Display);
	cout << "PRE ORDER" << endl;
	t1.PreOrderTraversal(Display);
	cout << "POST ORDER" << endl;
	t1.PostOrderTraversal(Display);
	cout << "BREADTH FIRST" << endl;
	t1.BreadthFirstTraversal(Display);

	t1.Delete(11);
	cout << "BREADTH FIRST" << endl;
	t1.BreadthFirstTraversal(Display);
	t1.Insert(11);

	t1.Delete(25);
	cout << "BREADTH FIRST" << endl;
	t1.BreadthFirstTraversal(Display);


	BinarySearchTree<int> t2;
	t2.Insert(20);
	t2.Insert(15);
	t2.Insert(25);
	t2.Insert(30);
	t2.Insert(18);
	t2.Insert(12);
	t2.Insert(11);
	cout << "BREADTH FIRST" << endl;
	t2.BreadthFirstTraversal(Display);
	cout << "What is the height of the tree t2? " << t2.Height() << endl;
	cout << "Deleting a Node with two children..." << endl;
	t2.Delete(15);
	cout << "What is the height of the tree t2? " << t2.Height() << endl;
	cout << "BREADTH FIRST" << endl;
	t2.BreadthFirstTraversal(Display);

	cout << "COPY CONSTRUCTOR:" << endl;
	BinarySearchTree<int> t3 = t2;
	cout << "BREADTH FIRST" << endl;
	t2.BreadthFirstTraversal(Display);
	cout << "OP=:" << endl;
	t1 = t3;
	cout << "BREADTH FIRST" << endl;
	t1.BreadthFirstTraversal(Display);

	t1.Insert(65);
	t1.Insert(99);
	t1.Insert(2);
	t1.Insert(78);
	cout << "What is the height of the tree t1? " << t1.Height() << endl;


	cout << "Purging t2..." << endl;
	t2.Purge();

	// now testing with strings
	cout << "\n\nSTRINGS!!\n" << endl;
	BinarySearchTree<string> ts1;
	ts1.Insert("Binary");
	ts1.Insert("Search");
	ts1.Insert("Trees");
	ts1.Insert("need");
	ts1.Insert("to");
	ts1.Insert("stop");
	ts1.Insert("pls");
	cout << "IN ORDER" << endl;
	ts1.InOrderTraversal(StringDisplay);
	cout << "\nBREADTH FIRST" << endl;
	ts1.BreadthFirstTraversal(StringDisplay);
	cout << "\nPRE ORDER" << endl;
	ts1.PreOrderTraversal(StringDisplay);
	cout << "\nPOST ORDER" << endl;
	ts1.PostOrderTraversal(StringDisplay);
	cout << "\nCOPY CTOR:" << endl;
	BinarySearchTree<string> ts2 = ts1;
	cout << "\nDELETING pls AND Search: " << endl;
	ts2.Delete("pls");
	ts2.Delete("Search");
	cout << "\nBREADTH FIRST" << endl;
	ts2.BreadthFirstTraversal(StringDisplay);

	// error testing
	cout << "\n\nINTEGER ERROR TESTING\n" << endl;
	BinarySearchTree<int> itest;
	cout << "Delete from an empty tree..." << endl;
	try
	{
		itest.Delete(12);
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}
	cout << "Trying to Delete a node that doesn't exist..." << endl;
	itest.Insert(6);
	try
	{
		itest.Delete(2);
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}
	itest.Delete(6);
	cout << "Traverse an empty tree... " << endl;
	try
	{
		itest.BreadthFirstTraversal(Display);
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}

	cout << "\n\nSTRING ERROR TESTING\n" << endl;
	BinarySearchTree<string> stest;
	cout << "Delete from an empty tree..." << endl;
	try
	{
		stest.Delete("whoami");
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}
	cout << "Trying to Delete a node that doesn't exist..." << endl;
	stest.Insert("don't delete me");
	try
	{
		stest.Delete("muahahah");
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}
	stest.Delete("don't delete me");
	cout << "Traverse an empty tree... " << endl;
	try
	{
		stest.BreadthFirstTraversal(StringDisplay);
	}
	catch (Exception msg)
	{
		cout << msg << endl;
	}

}

void Display(int& data)
{
	cout << data << endl;
}
void StringDisplay(string& data)
{
	cout << data << endl;
}

//IN ORDER
//11
//12
//15
//18
//20
//25
//30
//PRE ORDER
//20
//15
//12
//11
//18
//25
//30
//POST ORDER
//11
//12
//18
//15
//30
//25
//20
//BREADTH FIRST
//20
//15
//25
//12
//18
//30
//11
//BREADTH FIRST
//20
//15
//25
//12
//18
//30
//BREADTH FIRST
//20
//15
//30
//12
//18
//11
//BREADTH FIRST
//20
//15
//25
//12
//18
//30
//11
//What is the height of the tree t2 ? 3
//Deleting a Node with two children...
//What is the height of the tree t2 ? 2
//BREADTH FIRST
//20
//12
//25
//11
//18
//30
//COPY CONSTRUCTOR :
//BREADTH FIRST
//20
//12
//25
//11
//18
//30
//OP = :
//BREADTH FIRST
//20
//12
//25
//11
//18
//30
//What is the height of the tree t1 ? 5
//Purging t2...
//
//
//STRINGS!!
//
//IN ORDER
//Binary
//Search
//Trees
//need
//pls
//stop
//to
//
//BREADTH FIRST
//Binary
//Search
//Trees
//need
//to
//stop
//pls
//
//PRE ORDER
//Binary
//Search
//Trees
//need
//to
//stop
//pls
//
//POST ORDER
//pls
//stop
//to
//need
//Trees
//Search
//Binary
//
//COPY CTOR :
//
//DELETING pls AND Search :
//
//BREADTH FIRST
//Binary
//Trees
//need
//to
//stop
//
//
//INTEGER ERROR TESTING
//
//Delete from an empty tree...
//ERROR: The tree is empty.
//
//Trying to Delete a node that doesn't exist...
//ERROR : Node not found.
//
//Traverse an empty tree...
//ERROR : Nothing in the tree.
//
//
//
//STRING ERROR TESTING
//
//Delete from an empty tree...
//ERROR: The tree is empty.
//
//Trying to Delete a node that doesn't exist...
//ERROR : Node not found.
//
//Traverse an empty tree...
//ERROR : Nothing in the tree.
//
//
