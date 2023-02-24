#ifndef ROW_H
#define ROW_H

template <typename T>
class Row;

#include "Exception.h"
#include "array2d.h"


/**********************************************************************
 *Class: Row
 *
 *Purpose:	Manages the rows for the 2D Array class, including the
 *			overloaded bracket operator for accessing a two dimensional
 *			array's elements.
 *
 *Member Functions:
 *	Row<T>();
 *		Default constructor for the templated Array class
 *	Row<T>(Array2D<T> & myarray, int row);
 *		2-arg constructor for the templated Array2D class. It takes a
 *		reference to a Array2D object as well as an integer for the
 *		number of rows there are.
 *	Row<T>(const Array2D<T> & myarray, int row);
 *		2-arg constructor for the templated Array2D class. It takes a
 *		reference to a const Array2D object as well as an integer for the
 *		number of rows there are.
 *Methods:
 *	T & operator[](int column);
 *		Accesses a multidimensional array's column value and returns it.
 *	T & operator[](int column) const;
 *		Accesses a constant multidimensional array's column value and
 *		returns it.
 *
 *
 **********************************************************************/
template <typename T>
class Row {
	friend class Array2D<T>;

 public:
  // removed <T> from these functions, it casuses a compiler error
  Row();
  Row(Array2D<T>& myarray, int row);
  Row(const Array2D<T>& myarray, int row);
  T& operator[](int column);
  T& operator[](int column) const;

 private:
  Array2D<T>& m_array2D;
  int m_row;
};

template <typename T>
Row<T>::Row() : m_array2D(Array2D<T>()), m_row(0) {}
/**********************************************************************
 *Row<T>::Row()
 *
 *Purpose:	Create an object where two parameters are passed into it.
 *Entry:		An object is being instantiated with two specified parameters.
 *Exit:		A Row<T> object with two values is constructed and
 *			instantiated.
 ***********************************************************************/
template <typename T>
Row<T>::Row(Array2D<T>& myarray, int row) : m_array2D(myarray), m_row(row) {}

/**********************************************************************
 *Row<T>::Row()
 *
 *Purpose:	Create an object where two parameters are passed into it. One
 *			of these parameters being a const Array2D<T> &.
 *Entry:		An object is being instantiated with two specified parameters.
 *Exit:		A Row<T> object with two values is constructed and
 *			instantiated.
 ***********************************************************************/
template <typename T>
Row<T>::Row(const Array2D<T>& myarray, int row)
    : m_array2D(const_cast<Array2D<T>&>(myarray)), m_row(row) {}

/**********************************************************************
 *T & Row<T>::operator[](int column)
 *
 *Purpose:	Accesses a multidimensional array's column value.
 *Entry:		This method is used for the case of: array[x][y]. This
 *			overloaded operator deals with the [y] portion of the statement.
 *			An Array2D object has been created and is now attempting
 *			to access the column value using the Select function.
 *Exit:		This returns a T by reference to the function that called
 *			it.
 ***********************************************************************/
template <typename T>
T& Row<T>::operator[](int column) {
  if (column < 0)  // if you try to access a negative column
    throw Exception("EXCEPTION: Cannot have a row value less then zero.");
  else
    return m_array2D.Select(m_row, column);  // pass back information from Select
}

/**********************************************************************
 *T & Row<T>::operator[](int column) const
 *
 *Purpose:	Accesses a constant multidimensional array's column value.
 *Entry:		This method is used for the case of: array[x][y]. This
 *			overloaded operator deals with the [y] portion of the statement.
 *			An Array2D object has been created and is now attempting
 *			to access the column value using the Select function.
 *Exit:		This returns a T by reference to the function that called
 *			it.
 ***********************************************************************/
template <typename T>
T& Row<T>::operator[](int column) const {
  if (column < 0)  // if you try to access a negative column
    throw Exception("EXCEPTION: Cannot have a row value less then zero.");
  else
    return m_array2D.Select(m_row, column);  // pass back information from const Select
}

#endif
