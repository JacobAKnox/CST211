// Jacob Knox CST211 Lab6 Due: 2/16/2023

#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T>
class Node {
 private:
  T n_data;
  Node<T>* left_ptr;
  Node<T>* right_ptr;

  template <typename U>
  friend class BST;

 public:
  Node();
  Node(const Node& copy);
  Node(Node&& copy) noexcept;
  Node(const T data);
  Node(const T data, Node<T>* next, Node<T>* prev);
  ~Node();

  Node<T>& operator=(const Node& copy);
  Node<T>& operator=(Node&& copy) noexcept;

  T& Value() noexcept;
  T Value() const noexcept;
  void Value(const T data);

  Node<T>* Left() noexcept;
  Node<T>* Left() const noexcept;
  Node<T>* Right() noexcept;
  Node<T>* Right() const noexcept;
  void Left(Node<T>* const next) noexcept;
  void Right(Node<T>* const previous) noexcept;
};

template <typename T>
Node<T>::Node() : n_data(0), left_ptr(nullptr), right_ptr(nullptr) {
}

template <typename T>
Node<T>::Node(const T data)
    : n_data(data) {
}

template <typename T>
Node<T>::~Node() {
  // destructor
  this->n_data = T{};
  this->left_ptr = nullptr;
  this->right_ptr = nullptr;
}

template <typename T>
Node<T>::Node(const Node& copy) {
  // copy constructor, perform a shallpow copy of copy
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
Node<T>::Node(Node&& copy) noexcept {
  // move constructor
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
Node<T>::Node(const T data, Node<T>* next, Node<T>* prev) {
  // constructor with data and next and previous pointers
  this->n_data = data;
  this->left_ptr = next;
  this->right_ptr = prev;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node& copy) {
  // copy assignment operator
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
Node<T>& Node<T>::operator=(Node&& copy) noexcept {
  // move assignment operator
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <class T>
T& Node<T>::Value() noexcept {
  // return the data
  return this->n_data;
}

template <class T>
T Node<T>::Value() const noexcept {
  // return the data
  return this->n_data;
}

template <class T>
void Node<T>::Value(const T data) {
  // set the data
  this->n_data = data;
}

template <typename T>
Node<T>* Node<T>::Left() noexcept {
  // return the next pointer
  return this->left_ptr;
}

template <typename T>
Node<T>* Node<T>::Left() const noexcept {
  // return the next pointer
  return this->left_ptr;
}

template <typename T>
Node<T>* Node<T>::Right() noexcept {
  // return the previous pointer
  return this->right_ptr;
}

template <typename T>
Node<T>* Node<T>::Right() const noexcept {
  // return the previous pointer
  return this->right_ptr;
}

template <typename T>
void Node<T>::Left(Node<T>* const next) noexcept {
  // set the next pointer
  this->left_ptr = next;
}

template <typename T>
void Node<T>::Right(Node<T>* const previous) noexcept {
  // set the previous pointer
  this->right_ptr = previous;
}

#endif  // NODE_TEMPLATE_H
