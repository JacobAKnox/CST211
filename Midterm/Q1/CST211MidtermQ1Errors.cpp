// CST211MidtermQ1Errors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include "array2d.h"
#include <string>
using std::string;
using std::cout;
using std::endl;

void IntegerTest();
void StringTest();
void ConstTest(const Array2D<int>& mantaray);
void ExceptionTest();

int main()
{	
	// windows memory leak detection disabled
	// I'm on linux, uncomment if you want to use on windows
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Array2D<int>test(3, 6);

	test.setRow(2);
	test.setColumn(9);
	// name(ROWS, COLS)
	cout << "*** TESTING A MULTIDIMENSIONAL ARRAY OF INTEGERS ***" << endl;
	IntegerTest();

	cout << "*** TESTING A MULTIDIMENSIONAL ARRAY OF STRINGS ***" << endl;
	StringTest();

	cout << "*** TESTING A CONSTANT MULTIDIMENSIONAL ARRAY OF INTEGERS ***" << endl;
	Array2D<int> mantaray(5, 6);
	for (int i = 0; i < mantaray.getRow(); ++i)
	{
		for (int j = 0; j < mantaray.getColumn(); ++j)
		{
			mantaray[i][j] = (i + j);
		}
	}
	ConstTest(mantaray);

	cout << "*** TESTING EXCEPTION CONDITIONS ***" << endl;
	ExceptionTest();

}

void IntegerTest()
{
	cout << " Creating an Array with the default constructor." << endl;
	Array2D<int> simba;
	cout << " Creating an Array with the 2-arg constructor: 5 rows, 6 columns." << endl;
	Array2D<int> nala(5, 6);
	cout << "      " << nala.getRow() << ' ' << nala.getRow() << endl;
	cout << " Testing the setColumn method." << endl;
	simba.setColumn(3);
	cout << "      simba now has " << simba.getColumn() << " columns." << endl;
	cout << " Testing the setRow method." << endl;
	simba.setRow(7);
	cout << "      simba now has " << simba.getRow() << " rows." << endl;
	cout << "      simba's row/column value is: " << endl;
	cout << "      " << simba.getRow() << ' ' << simba.getColumn() << endl;

	cout << " Testing assigning values using the [x][y] method." << endl;
	Array2D<int> mufasa;
	mufasa.setColumn(6);
	mufasa.setRow(3);
	for (int i = 0; i < mufasa.getRow(); ++i)
	{
		for (int j = 0; j < mufasa.getColumn(); ++j)
		{
			mufasa[i][j] = (i * j);
		}
	}
	cout << "      mufasa's value is: " << endl;

	for (int i = 0; i < mufasa.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < mufasa.getColumn(); ++j)
		{
			cout << mufasa[i][j] << ' ';
		}
		cout << endl;
	}

	cout << " Testing the op=. Assigning simba with mufasa's values." << endl;
	simba = mufasa;
	cout << "      simba's value is now:" << endl;
	for (int i = 0; i < simba.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < simba.getColumn(); ++j)
		{
			cout << simba[i][j] << ' ';
		}
		cout << endl;
	}
	cout << " Testing the copy constructor." << endl;
	Array2D<int> pumba(4, 7);
	cout << "      pumba's row/column value is: " << endl;
	cout << "      " << pumba.getRow() << ' ' << pumba.getColumn() << endl;
	Array2D<int>timon = pumba;
	cout << "      timon's row/column value is: " << endl;
	cout << "      " << timon.getRow() << ' ' << timon.getColumn() << endl;
	cout << " Testing the 1-arg constructor." << endl;
	Array2D<int>rafiki(5);
	cout << "      rafiki's row/column value is: " << endl;
	cout << "      " << rafiki.getRow() << ' ' << rafiki.getColumn() << endl;


	cout << " Testing reducing timon's columns to 3." << endl;
	timon.setColumn(3);
	cout << "      timon's row/column value is: " << endl;
	cout << "      " << timon.getRow() << ' ' << timon.getColumn() << endl;

}


void StringTest()
{
	cout << " Creating an Array with the default constructor." << endl;
	Array2D<string> steve;
	cout << " Creating an Array with the 2-arg constructor: 5 rows, 6 columns." << endl;
	Array2D<string> ironman(5, 6);
	cout << "      " << ironman.getRow() << ' ' << ironman.getRow() << endl;
	cout << " Testing the setColumn method." << endl;
	steve.setColumn(3);
	cout << "      steve now has " << steve.getColumn() << " columns." << endl;
	cout << " Testing the setRow method." << endl;
	steve.setRow(7);
	cout << "      steve now has " << steve.getRow() << " rows." << endl;
	cout << "      steve's row/column value is: " << endl;
	cout << "      " << steve.getRow() << ' ' << steve.getColumn() << endl;

	cout << " Testing assigning values using the [x][y] method." << endl;
	Array2D<string> thor;
	thor.setColumn(6);
	thor.setRow(3);
	for (int i = 0; i < thor.getRow(); ++i)
	{
		for (int j = 0; j < thor.getColumn(); ++j)
		{
			thor[i][j] = "AVENGERS!";
		}
	}
	cout << "      thor's value is: " << endl;

	for (int i = 0; i < thor.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < thor.getColumn(); ++j)
		{
			cout << thor[i][j] << ' ';
		}
		cout << endl;
	}

	cout << " Testing the op=. Assigning simba with mufasa's values." << endl;
	steve = thor;
	cout << "      steve's value is now:" << endl;
	for (int i = 0; i < steve.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < steve.getColumn(); ++j)
		{
			cout << steve[i][j] << ' ';
		}
		cout << endl;
	}
	cout << " Testing the copy constructor." << endl;
	Array2D<string> hawkeye(4, 7);
	cout << "      hawkeye's row/column value is: " << endl;
	cout << "      " << hawkeye.getRow() << ' ' << hawkeye.getColumn() << endl;
	Array2D<string>widow = hawkeye;
	cout << "      widow's row/column value is: " << endl;
	cout << "      " << widow.getRow() << ' ' << widow.getColumn() << endl;
	cout << " Testing the 1-arg constructor." << endl;
	Array2D<string>hulk(5);
	cout << "      hulk's row/column value is: " << endl;
	cout << "      " << hulk.getRow() << ' ' << hulk.getColumn() << endl;


	cout << " Testing reducing timon's columns to 3." << endl;
	widow.setColumn(3);
	cout << "      widow's row/column value is: " << endl;
	cout << "      " << widow.getRow() << ' ' << widow.getColumn() << endl;

	cout << "      widow has been assigned steve's value, " << endl
		<< "      but her row value is reduced to 2, and " << endl
		<< "      her column value has been increasedto 7:" << endl;
	widow = steve;
	widow.setRow(2);
	widow.setColumn(7);
	for (int i = 0; i < widow.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < widow.getColumn(); ++j)
		{
			cout << widow[i][j] << ' ';
		}
		cout << endl;
	}
}


void ConstTest(const Array2D<int>& mantaray)
{
	cout << " Testing mantaray's value as a constant Array2D object." << endl
		<< "      mantaray's value is:" << endl;
	for (int i = 0; i < mantaray.getRow(); ++i)
	{
		cout << "      ";
		for (int j = 0; j < mantaray.getColumn(); ++j)
		{
			cout << mantaray[i][j] << ' ';
		}
		cout << endl;
	}
	cout << " Testing the Select method for a const object. Accessing (3, 3)." << endl
		<< "      The value at (3, 3) is: " << endl << "      " << mantaray.Select(3, 3) << endl;
}

void ExceptionTest()
{
	cout << ">> 1) Attempting to create a negative array." << endl;
	try
	{
		Array2D<int> shame(-1, -3);
	}
	catch (Exception msg)
	{
		cout << "      " << msg << endl;
	}

	cout << "2) Setting a Row to a negative value after creation." << endl;
	try
	{
		Array2D<int> howdare(2, 2);
		howdare.setRow(-4);
	}
	catch (Exception msg)
	{
		cout << "      " << msg << endl;
	}

	cout << "3) Setting a Column to a negative value after creation." << endl;
	try
	{
		Array2D<int> shun(5, 5);
		shun.setColumn(-3);
	}
	catch (Exception msg)
	{
		cout << "      " << msg << endl;
	}

	cout << "4) Selecting an element outside the bounds of the Array." << endl;
	try
	{
		Array2D<int> stopthat(1, 3);
		stopthat.Select(6, 4);
	}
	catch (Exception msg)
	{
		cout << "      " << msg << endl;
	}
}

//Expected results:
//
// ***TESTING A MULTIDIMENSIONAL ARRAY OF INTEGERS***
// Creating an Array with the default constructor.
// Creating an Array with the 2 - arg constructor : 5 rows, 6 columns.
// 5 5
// Testing the setColumn method.
// simba now has 3 columns.
// Testing the setRow method.
// simba now has 7 rows.
// simba's row/column value is:
// 7 3
// Testing assigning values using the[x][y] method.
// mufasa's value is:
// 0 0 0 0 0 0
// 0 1 2 3 4 5
// 0 2 4 6 8 10
// Testing the op = .Assigning simba with mufasa's values.
// simba's value is now:
// 0 0 0 0 0 0
// 0 1 2 3 4 5
// 0 2 4 6 8 10
// Testing the copy constructor.
// pumba's row/column value is:
// 4 7
// timon's row/column value is:
// 0 0
// Testing the 1 - arg constructor.
// rafiki's row/column value is:
// 5 0
// Testing reducing timon's columns to 3.
// timon's row/column value is:
// 0 3
// * **TESTING A MULTIDIMENSIONAL ARRAY OF STRINGS * **
// Creating an Array with the default constructor.
// Creating an Array with the 2 - arg constructor : 5 rows, 6 columns.
// 5 5
// Testing the setColumn method.
// steve now has 3 columns.
// Testing the setRow method.
// steve now has 7 rows.
// steve's row/column value is:
// 7 3
// Testing assigning values using the[x][y] method.
// thor's value is:
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// Testing the op = .Assigning simba with mufasa's values.
// steve's value is now:
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// Testing the copy constructor.
// hawkeye's row/column value is:
// 4 7
// widow's row/column value is:
// 0 0
// Testing the 1 - arg constructor.
// hulk's row/column value is:
// 5 0
// Testing reducing timon's columns to 3.
// widow's row/column value is:
// 0 3
// widow has been assigned steve's value,
// but her row value is reduced to 2, and
// her column value has been increasedto 7:
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!AVENGERS!
// ***TESTING A CONSTANT MULTIDIMENSIONAL ARRAY OF INTEGERS * **
// Testing mantaray's value as a constant Array2D object.
// mantaray's value is:
// 0 1 2 3 4 5
// 1 2 3 4 5 6
// 2 3 4 5 6 7
// 3 4 5 6 7 8
// 4 5 6 7 8 9
// Testing the Select method for a const object.Accessing(3, 3).
// The value at(3, 3) is:
// 6
// * **TESTING EXCEPTION CONDITIONS***
// >> 1) Attempting to create a negative array.
// EXCEPTION: Cannot have a row or column of a negative value!

// 2) Setting a Row to a negative value after creation.
// EXCEPTION: You cannot change the row value to a negative number.

// 3) Setting a Column to a negative value after creation.
// EXCEPTION: You cannot change the column value to a negative number.

// 4) Selecting an element outside the bounds of the Array.
// EXCEPTION: Out of bounds of the 2D Array.
