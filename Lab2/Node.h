//Jacob Knox CST211 Lab2 Due: 1/26/2023

#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<typename T>class Node {
private:
    T n_data;
    Node<T>* next_ptr;
    Node<T>* prev_ptr;

    template<typename U>friend class List;
public:
    Node();
    Node(const Node& copy);
    Node(Node&& copy) noexcept;
    Node(const T data);
    Node(const T data, Node<T>* next, Node<T>* prev);
    ~Node() = default;

    Node<T>& operator=(const Node& copy);
    Node<T>& operator=(Node&& copy) noexcept;

    T& Value() noexcept;
    T Value() const noexcept;
    void Value(const T data);

    Node<T>* Next() noexcept;
    Node<T>* Next() const noexcept;
    Node<T>* Previous() noexcept;
    Node<T>* Previous() const noexcept;
    void Next(Node<T>* const next) noexcept;
    void Previous(Node<T>* const previous) noexcept;
};

template<typename T>
Node<T>::Node() : n_data(0), next_ptr(nullptr), prev_ptr(nullptr) {
}

template <typename T>
Node<T>::Node(const T data)
    : n_data(data)
{
}

template <typename T>
Node<T>::Node(const Node& copy)
{
    // copy constructor, perform a shallpow copy of copy
    this->n_data = copy.n_data;
    this->next_ptr = copy.next_ptr;
    this->prev_ptr = copy.prev_ptr;
}

template <typename T>
Node<T>::Node(Node&& copy) noexcept
{
    // move constructor
    this->n_data = copy.n_data;
    this->next_ptr = copy.next_ptr;
    this->prev_ptr = copy.prev_ptr;
}

template <typename T>
Node<T>::Node(const T data, Node<T>* next, Node<T>* prev)
{
    // constructor with data and next and previous pointers
    this->n_data = data;
    this->next_ptr = next;
    this->prev_ptr = prev;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node& copy)
{
    // copy assignment operator
    this->n_data = copy.n_data;
    this->next_ptr = copy.next_ptr;
    this->prev_ptr = copy.prev_ptr;
}

template <typename T>
Node<T>& Node<T>::operator=(Node&& copy) noexcept
{
    // move assignment operator
    this->n_data = copy.n_data;
    this->next_ptr = copy.next_ptr;
    this->prev_ptr = copy.prev_ptr;
}

template <class T>
T& Node<T>::Value() noexcept
{
    // return the data
    return this->n_data;
}

template <class T>
T Node<T>::Value() const noexcept
{
    // return the data
    return this->n_data;
}

template <class T>
void Node<T>::Value(const T data)
{
    // set the data
    this->n_data = data;
}

template <typename T>
Node<T>* Node<T>::Next() noexcept
{
    // return the next pointer
    return this->next_ptr;
}

template <typename T>
Node<T>* Node<T>::Next() const noexcept
{
    // return the next pointer
    return this->next_ptr;
}

template <typename T>
Node<T>* Node<T>::Previous() noexcept
{
    // return the previous pointer
    return this->prev_ptr;
}

template <typename T>
Node<T>* Node<T>::Previous() const noexcept
{
    // return the previous pointer
    return this->prev_ptr;
}

template <typename T>
void Node<T>::Next(Node<T>* const next) noexcept
{
    // set the next pointer
    this->next_ptr = next;
}

template <typename T>
void Node<T>::Previous(Node<T>* const previous) noexcept
{
    // set the previous pointer
    this->prev_ptr = previous;
}

#endif //NODE_TEMPLATE_H
