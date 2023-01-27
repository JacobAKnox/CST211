#ifndef STACKEMPLATE_H
#define STACKTEMPLATE_H

//Jacob Knox CST211 Lab3 Due: 2/2/2023

#include "List.h"
#include "Exception.h"

template<typename T> class Stack {
private:
    List<T> m_stack;
    int num_elements;
    // added because otherwise there is no possibility of overflow, except for when you run out of memory
    size_t max_size;
public:
    Stack();
    // I added a parameterized constructor
    // It allows you to take a size and create a stack with that size
    // data should only be added by push and pop
    // adding data with a constructor could lead to an unexpected data order for the user
    Stack(size_t max_size);
    Stack(const Stack& copy);
    Stack(Stack&& move) noexcept;
    ~Stack();

    Stack<T>& operator=(const Stack& copy);
    Stack<T>& operator=(Stack&& move) noexcept;

    void Push(const T data);
    T Pop();
    T Peek() const;
    bool IsEmpty() const noexcept;
    bool IsFull() const noexcept;
    int getNumElements() const noexcept;
    size_t getMaxSize() const noexcept;
};

//initializing max_size to 0, add no data
template<typename T>
Stack<T>::Stack() : m_stack(), num_elements(0), max_size(-1) {}

//initializing max_size to the parameter, add no data
template<typename T>
Stack<T>::Stack(size_t max_size) : m_stack(), num_elements(0), max_size(max_size) {}

// can rely on the copy constructor of List to copy the data
// max_size and num_elements are primitive types so they are copied
template<typename T>
Stack<T>::Stack(const Stack& copy) : m_stack(copy.m_stack), num_elements(copy.num_elements), max_size(copy.max_size) {}

// can rely on the move constructor of List to move the data
// max_size and num_elements are primitive types so they are moved
template<typename T>
Stack<T>::Stack(Stack&& move) noexcept : m_stack(move.m_stack), num_elements(move.num_elements), max_size(move.max_size) {}

// default destructor calls list destructor
// max_size and num_elements are primitive types so they are destroyed
template<typename T>
Stack<T>::~Stack() = default;

// can rely on the copy assignment operator of List to copy the data
// max_size and num_elements are primitive types so they are copied
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& copy) { 
    this->m_stack = copy.m_stack;
    this->num_elements = copy.num_elements;
    this->max_size = copy.max_size;
    return *this;
}

// can rely on the move assignment operator of List to move the data
// max_size and num_elements are primitive types so they are moved
template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& move) noexcept { 
    this->m_stack = move.m_stack;
    this->num_elements = move.num_elements;
    this->max_size = move.max_size;
    return *this;
}

// push data to the front of the list
template<typename T>
void Stack<T>::Push(const T data) {
    // check if the stack is full
    if (IsFull()) {
        throw Exception("Stack is full");
    }
    m_stack.Prepend(data);
    // update the number of elements
    num_elements = m_stack.Size();
}

// pop data from the front of the list
template<typename T>
T Stack<T>::Pop() {
    // check if the stack is empty
    if (IsEmpty()) {
        throw Exception("Stack is empty");
    }
    // get the data from the front of the list
    T data = m_stack.First();
    // remove the data from the front of the list
    m_stack.RemoveFirst();
    // update the number of elements
    num_elements = m_stack.Size();
    return data;
}

template<typename T>
T Stack<T>::Peek() const {
    //just need to check if the stack is empty
    if (IsEmpty()) {
        throw Exception("Stack is empty");
    }
    return m_stack.First();
}

// check the number of elements
template<typename T>
bool Stack<T>::IsEmpty() const noexcept {return num_elements == 0;}

// compare the number of elements to the max size
template<typename T>
bool Stack<T>::IsFull() const noexcept {return num_elements == max_size;}

// simple getter for max_size
template<typename T>
int Stack<T>::getNumElements() const noexcept {return num_elements;}

// simple getter for max_size
template<typename T>
size_t Stack<T>::getMaxSize() const noexcept {return max_size;}

#endif //STACK_TEMPLATE_H