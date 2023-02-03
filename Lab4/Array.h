#ifndef ARRAYTEMPLATE_H
#define ARRAYTEMPLATE_H

#include <iostream>
#include <string>
#include "Exception.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class Array
{
private:
	T *m_array;
	int m_start_index;
	int m_length;
	int m_newArray;

public:
	Array() : m_array(nullptr), m_start_index(0), m_length(0){}; // default constructor
	Array(int length, int start_index = 0);						 // constructor
	Array(const Array<T> &copy);								 // copy constructor
	Array(Array<T> &&move) noexcept;							 // move constructor

	~Array(); // destructor

	Array<T> &operator=(const Array<T> &copy);	   // overloaded copy assignment operator
	Array<T> &operator=(Array<T> &&move) noexcept; // overloaded move assignment operator
	T &operator[](const int);					   // overloaded subscript operator

	const int getStartIndex();				   // gets start index
	void setStartIndex(const int start_index); // sets start index
	const int getLength();					   // gets length of array
	void setLength(int length);				   // sets length of array

	template <typename U>
	friend class Queue;
};

template <typename T>
Array<T>::Array(int length, int start_index)
{
	// parameterized constructor, assign all the values
	m_array = new T[length];
	m_start_index = start_index;
	m_length = length;
	m_newArray = 0;
}

template <typename T>
Array<T>::Array(const Array<T> &copy)
{
	// copy constructor
	this->m_start_index = copy.m_start_index;
	this->m_length = copy.m_length;
	this->m_array = new T[m_length];
	// copy values to new array
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = copy.m_array[i];
	}
	this->m_newArray = copy.m_newArray;
}

template <typename T>
Array<T>::Array(Array<T> &&move) noexcept
{
	// move constructor
	this->m_start_index = move.m_start_index;
	this->m_length = move.m_length;
	// just need to copy the pointer
	this->m_array = move.m_array;
	this->m_newArray = move.m_newArray;
	move.m_array = nullptr;
}

template <typename T>
Array<T>::~Array()
{
	// destructor, only need to delete the dyanmic array
	delete[] m_array;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &copy)
{
	// overloaded copy assignment operator
	this->m_start_index = copy.m_start_index;
	this->m_length = copy.m_length;
	this->m_array = new T[m_length];
	// copy values to new array
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = copy.m_array[i];
	}
	this->m_newArray = copy.m_newArray;
	return *this;
}

template <typename T>
Array<T> &Array<T>::operator=(Array<T> &&move) noexcept
{
	// overloaded move assignment operator
	this->m_start_index = move.m_start_index;
	this->m_length = move.m_length;
	// just need to copy the pointer
	this->m_array = move.m_array;
	this->m_newArray = move.m_newArray;
	move.m_array = nullptr;
	return *this;
}

template <typename T>
T &Array<T>::operator[](const int index)
{
	// check if the index is out of boundd
	if (index < m_start_index || index >= m_start_index + m_length)
		throw Exception("Index out of bounds");
	else
		// subtract the start index to get the correct index
		return m_array[index - m_start_index];
}

// return the start index
template <typename T>
const int Array<T>::getStartIndex()
{
	return m_start_index;
}

// set the start index
// no special logic needed here, its all in the [] operator
template <typename T>
void Array<T>::setStartIndex(const int start_index)
{
	m_start_index = start_index;
}

// return the length of the array
template <typename T>
const int Array<T>::getLength()
{
	return m_length;
}

// set the length of the array
template <typename T>
void Array<T>::setLength(int length)
{
	// check if the length is negative
	if (length < 0)
		throw Exception("Length cannot be negative");

	// copy the values to an array of the new length
	m_length = length;
	T *temp = new T[length];
	for (int i = 0; i < m_length; i++)
	{
		temp[i] = m_array[i];
	}
	delete[] m_array;
	m_array = temp;
	m_length = length;
}

#endif // ARRAY_TEMPLATE_H
