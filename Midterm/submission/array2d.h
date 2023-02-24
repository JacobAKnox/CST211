#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <iostream>

template <typename T>
class Array2D;

#include "Exception.h"
#include "row.h"

/**********************************************************************
 *Class: Array2D
 *
 *Purpose:	Simulates a 2D Array based on the Array class.
 *
 *Manager Functions:
 *	Array2D<T>();
 *		Default constructor for the templated Array2D class
 *	Array2D<T>(int row, int col = 0);
 *		2-arg constructor for the templated Array2D class
 *	Array2D<T>(const Array2D<T> & copy);
 *		Copy constructor for the class.
 *	~Array2D<T>();
 *		Destructor for the templated Array2D class
 *	Array2D<T> & operator=(const Array2D<T> & rhs);
 *		Op= function for the templated Array2D class
 *Methods:
 *	Row<T> operator[](int index);
 *		Overloads the subscript operator to return a Row<T> object.
 *		This accesses the Array2D's row value.
 *	const Row<T> operator[](int row) const;
 *		Overloads the subscript operator to return a constant Row<T>
 *		object.	This accesses the Array2D's row value.
 *	int getRow() const;
 *		Returns the Array2D's row value.
 *	void setRow(int rows);
 *		Resize the Array2D object based on how many rows the user
 *		wants to increase/decrease it it based on the passed in row
 *		variable..
 *	int getColumn() const;
 *		Returns the Array2D's column value.
 *	void setColumn(int columns);
 *		Resize the Array2D object based on how many columns the user
 *		wants to increase/decrease it based on the passed in column
 *		variable.
 *	T & Select(int row, int column);
 *		Selects an Array2D element based on the row/column value passed
 *		into the method.
 *	T & Select(int row, int column) const;
 *		Selects an Array2D element based on the row/column value passed
 *		into the method. This method is for const Arraay2D objects.
 *
 *
 **********************************************************************/
template <typename T>
class Array2D {
 public:
  // removed <T> from these, is causes a compiler error
  Array2D();
  Array2D(int row, int col = 0);
  Array2D(const Array2D<T>& copy);
  Array2D(Array2D<T>&& move) noexcept;
  ~Array2D();
  Array2D<T>& operator=(const Array2D<T>& rhs);
  Row<T> operator[](int index);
  const Row<T> operator[](int row) const;

  int getRow() const;
  void setRow(int rows);
  int getColumn() const;
  void setColumn(int columns);
  T& Select(int row, int column);
  T& Select(int row, int column) const;

 private:
  T** m_array;
  int m_row;
  int m_col;
};

/**********************************************************************
 *Array2D<T>::Array2D()
 *
 *Purpose:	Create a default object when no parameters are passed.
 *Entry:		An object is being instantiated without specified parameters.
 *Exit:		An Array2D<T> object with default values is constructed and
 *			instantiated.
 ***********************************************************************/
template <typename T>
Array2D<T>::Array2D() : m_array(nullptr), m_row(0), m_col(0) {}

/**********************************************************************
 *Array2D<T>::Array2D()
 *
 *Purpose:	Create an object when 2 parameters are passed.
 *Entry:		An object is being instantiated with two specified parameters.
 *Exit:		An Array2D<T> object with two values is constructed and
 *			instantiated.
 ***********************************************************************/
template <typename T>
Array2D<T>::Array2D(int row, int col) : m_array(nullptr), m_row(row), m_col(col) {
  if (row < 0 || col < 0)  // if passed negative values
    throw Exception("EXCEPTION: Cannot have a row or column of a negative value!");
  else {
    m_array = new T*[row];         // create new rows
    for (int i = 0; i < row; ++i)  // create new columns for each riw
      m_array[i] = new T[col];
  }
}

/**********************************************************************
 *Array2D<T>::Array2D(Array2D<T> && move) noexcept
 *
 *Purpose:	Copies the contents of one Array2D object into a newly
 *			instantiated Array2D object.
 *Entry:		One object exists, and another is being instantiated
 *			upon entry. The object being copied will have its contents
 *			copied over into the newly created object.
 *Exit:		The new object contains all of the attributes of the object
 *			on the right hand side (that was copied).
 ***********************************************************************/
template <typename T>
Array2D<T>::Array2D(const Array2D<T>& copy) {
  m_array = new T*[copy.m_row];         // create new rows
  for (int i = 0; i < copy.m_row; ++i)  // create new collumns for each row
    m_array[i] = copy.m_array[i];
  // there was a bug here
  // row and col were not being copied
  m_row = copy.m_row;
  m_col = copy.m_col;
}

/**********************************************************************
 *Array2D<T>::Array2D(Array2D<T> && move) noexcept
 *
 *Purpose:	Moves the contents of one Array2D object into a newly
 *			instantiated Array2D object.
 *Entry:		One object has been created, and another is being instantiated
 *			upon entry. The object being moved will have its contents
 *			moved over into the newly created object.
 *Exit:		The new object contains all of the attributes of the object
 *			on the right hand side (that was moved).
 ***********************************************************************/
template <typename T>
Array2D<T>::Array2D(Array2D<T>&& move) noexcept {
  *this = move;  // implement the op=
}

/**********************************************************************
 *Array2D<T>::~Array2D()
 *
 *Purpose:	Deallocates used memory and returns objects to a default state.
 *Entry:		The program has reached the end of  main (return 0), and all
 *			objects that have been instantiated are going to be purged.
 *Exit:		Any object that allocated memory has given that memory back.
 *			all other private data members are returned to a deault state.
 ***********************************************************************/
template <typename T>
Array2D<T>::~Array2D() {
  for (int i = 0; i < m_row; ++i)  // delete contents of rows
    delete[] m_array[i];
  delete m_array;     // delete the rows
  m_array = nullptr;  // default state for all data
  m_row = 0;
  m_col = 0;
}

/**********************************************************************
 *Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
 *
 *Purpose:	Assigns one object's attributes and data to another object's.
 *Entry:		Two objects that have already been instantiated are set equal
 *			to one another. The object on the right of the = sign is the
 *			object whose data is being copied over to the object on the
 *			left of the = sign.
 *Exit:		The right object's attributes and data have been copied over
 *			to the left object's. Whatever old information has been
 *			deleted and re-initialized.
 ***********************************************************************/
template <typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D<T>& rhs) {
  if (this != &rhs) {
    for (int i = 0; i < m_row; ++i) {
      delete[] m_array[i];  // delete the contents of rows
    }
    delete m_array;  // delete the rows

    m_array = new T*[rhs.m_row];  // allocate a new set of rows

    for (int i = 0; i < rhs.m_row; i++)  // allocate new collumns
      m_array[i] = new T[rhs.m_col];

    for (int i = 0; i < rhs.m_row; ++i) {
      for (int j = 0; j < rhs.m_col; ++j) {
        m_array[i][j] = rhs.m_array[i][j];  // copy rhs' data
      }
    }

    m_row = rhs.m_row;  // reassign this' m_row's and m_col's
    m_col = rhs.m_col;
  }
  return *this;
}

/**********************************************************************
 *const Row<T> Array<T>::operator[](int index) const
 *
 *Purpose:	Overload the bracket operator to work with const Array2D objects.
 *Entry:		An Array2D has called a specific element and needs to access
 *			the information in it. The object has already been instantitated
 *			and has valid information inside of it
 *Exit:		Returns a Row object that has passed this Array2D's information
 *			as well as the row.
 ***********************************************************************/
template <typename T>
const Row<T> Array2D<T>::operator[](int row) const {
  if (row < 0)
    throw Exception("EXCEPTION: Cannot have a row value less then zero.");
  else if (row > m_row)
    throw Exception("EXCEPTION: Cannot exceed the bounds of the array.");
  else
    return Row<T>(*this, row);
}

/**********************************************************************
 *Row<T> Array<T>::operator[](int index)
 *
 *Purpose:	Overload the bracket operator to work with Array2D objects.
 *Entry:		An Array2D has called a specific element and needs to access
 *			the information in it. The object has already been instantitated
 *			and has valid information inside of it
 *Exit:		Returns a Row object that has passed this Array2D's information
 *			as well as the row.
 ***********************************************************************/
template <typename T>
Row<T> Array2D<T>::operator[](int row) {
  if (row < 0)  // if row is of negative value
    throw Exception("EXCEPTION: Cannot have a row value less then zero.");
  else if (row > m_row)  // if they attempt to access something out of bounds
    throw Exception("EXCEPTION: Cannot exceed the bounds of the array.");
  else
    return Row<T>(*this, row);
}

/**********************************************************************
 *int Array2D<T>::getRow() const
 *
 *Purpose:	Retrieve the number of rows of the Array2D object.
 *Entry:		The Array2D has been created an initialized.
 *Exit:		An integer is returned that represents the row value of the
 *			Array2D.
 ***********************************************************************/
template <typename T>
int Array2D<T>::getRow() const {
  return m_row;
}

/**********************************************************************
 *void Array<T>::setRows(int rows)
 *
 *Purpose:	Resize the Array2D object based on how many rows the user
 *			wants to increase/decrease it it based on the passed in row
 *			variable.
 *Entry:		The Array2D has been created and initialized. The length is
 *			being changed via this method, as well as the number of rows.
 *Exit:		The data member for the Array2D's rows has been modified
 *			to the value passed into the method.
 ***********************************************************************/
template <typename T>
void Array2D<T>::setRow(int rows) {
  if (rows < 0)
		throw Exception("EXCEPTION: Cannot have a row value less then zero.");
	else if (rows == m_row)
		return;
	else {
		T** temp = new T*[rows];  // allocate a new set of rows

		for (int i = 0; i < rows; i++)  // allocate new collumns
			temp[i] = new T[m_col];

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < m_col; ++j) {
        if (i < m_row)
          temp[i][j] = m_array[i][j];  // copy this' data
        else
          temp[i][j] = T();  // initialize new data to 0
      }
		}

		for (int i = 0; i < m_row; ++i) {
			delete[] m_array[i];  // delete the contents of rows
		}
		delete m_array;  // delete the rows

		m_array = temp;  // reassign this' m_array
		m_row = rows;    // reassign this' m_row
	}
}

/**********************************************************************
 *int Array2D<T>::getColumn() const
 *
 *Purpose:	Retrieve the number of columns of the Array2D object.
 *Entry:		The Array2D has been created an initialized.
 *Exit:		An integer is returned that represents the column value of the
 *			Array2D.
 ***********************************************************************/
template <typename T>
int Array2D<T>::getColumn() const {
  return m_col;
}

/**********************************************************************
 *void Array<T>::setColumn(int columns)
 *
 *Purpose:	Resize the Array2D object based on how many columns the user
 *			wants to increase/decrease it it based on the passed in column
 *			variable.
 *Entry:		The Array2D has been created and initialized. The length is
 *			being changed via this method, as well as the number of columns.
 *Exit:		The data member for the Array2D's rows has been modified
 *			to the value passed into the method.
 ***********************************************************************/
template <typename T>
void Array2D<T>::setColumn(int columns) {
  if (columns < 0)
		throw Exception("EXCEPTION: Cannot have a column value less then zero.");
	else if (columns == m_col)
		return;
	else {
    T** temp = new T*[m_row];  // allocate a new set of rows
    for (int i = 0; i < m_row; i++)  // allocate new collumns
      temp[i] = new T[columns];
    
    for (int i = 0; i < m_row; ++i) {
      for (int j = 0; j < columns; ++j) {
        if (j < m_col)
          temp[i][j] = m_array[i][j];  // copy this' data
        else
          temp[i][j] = T();  // initialize new data to default
      }
    }

    for (int i = 0; i < m_row; ++i) {
      delete[] m_array[i];  // delete the contents of rows
    }
    delete m_array;  // delete the rows

    m_array = temp;  // reassign this' m_array
    m_col = columns;  // reassign this' m_col
  }
}

/**********************************************************************
 *void Array<T>::Select(int row, int column)
 *
 *Purpose:	Selects an Array2D element based on the row/column value passed
 *			into the method.
 *Entry:		The Array2D has been created and initialized. The function
 *			is only trying to access an Array2D element.
 *Exit:		The method returns the value at that row/column.
 ***********************************************************************/
template <typename T>
T& Array2D<T>::Select(int row, int column) {
  if (row < 0 || row >= m_row)
		throw Exception("EXCEPTION: Cannot access a row that is out of bounds.");
	else if (column < 0 || column >= m_col)
		throw Exception("EXCEPTION: Cannot access a column that is out of bounds.");
	else
		return m_array[row][column];
}

/**********************************************************************
 *void Array<T>::Select(int row, int column) const
 *
 *Purpose:	Selects an Array2D element based on the row/column value passed
 *			into the method. This method is for const Arraay2D objects.
 *Entry:		The Array2D has been created and initialized. The function
 *			is only trying to access an Array2D element.
 *Exit:		The method returns the value at that row/column.
 ***********************************************************************/
template <typename T>
T& Array2D<T>::Select(int row, int column) const {
  if (row < 0 || row >= m_row)
		throw Exception("EXCEPTION: Cannot access a row that is out of bounds.");
	else if (column < 0 || column >= m_col)
		throw Exception("EXCEPTION: Cannot access a column that is out of bounds.");
	else
		return m_array[row][column];
}

#endif
