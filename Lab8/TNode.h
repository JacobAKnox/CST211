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
class TNode {
 private:
  T n_data;
  TNode<T>* left_ptr;
  TNode<T>* right_ptr;

  template <typename U>
  friend class BST;

 public:
  TNode();
  TNode(const TNode& copy);
  TNode(TNode&& copy) noexcept;
  TNode(const T data);
  TNode(const T data, TNode<T>* next, TNode<T>* prev);
  ~TNode();

  TNode<T>& operator=(const TNode& copy);
  TNode<T>& operator=(TNode&& copy) noexcept;

  T& Value() noexcept;
  T Value() const noexcept;
  void Value(const T data);

  TNode<T>* Left() noexcept;
  TNode<T>* Left() const noexcept;
  TNode<T>* Right() noexcept;
  TNode<T>* Right() const noexcept;
  void Left(TNode<T>* const next) noexcept;
  void Right(TNode<T>* const previous) noexcept;
};

template <typename T>
TNode<T>::TNode() : n_data(0), left_ptr(nullptr), right_ptr(nullptr) {
}

template <typename T>
TNode<T>::TNode(const T data)
    : n_data(data) {
}

template <typename T>
TNode<T>::~TNode() {
  // destructor
  this->left_ptr = nullptr;
  this->right_ptr = nullptr;
}

template <typename T>
TNode<T>::TNode(const TNode& copy) {
  // copy constructor, perform a shallpow copy of copy
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
TNode<T>::TNode(TNode&& copy) noexcept {
  // move constructor
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
TNode<T>::TNode(const T data, TNode<T>* next, TNode<T>* prev) {
  // constructor with data and next and previous pointers
  this->n_data = data;
  this->left_ptr = next;
  this->right_ptr = prev;
}

template <typename T>
TNode<T>& TNode<T>::operator=(const TNode& copy) {
  // copy assignment operator
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <typename T>
TNode<T>& TNode<T>::operator=(TNode&& copy) noexcept {
  // move assignment operator
  this->n_data = copy.n_data;
  this->left_ptr = copy.left_ptr;
  this->right_ptr = copy.right_ptr;
}

template <class T>
T& TNode<T>::Value() noexcept {
  // return the data
  return this->n_data;
}

template <class T>
T TNode<T>::Value() const noexcept {
  // return the data
  return this->n_data;
}

template <class T>
void TNode<T>::Value(const T data) {
  // set the data
  this->n_data = data;
}

template <typename T>
TNode<T>* TNode<T>::Left() noexcept {
  // return the next pointer
  return this->left_ptr;
}

template <typename T>
TNode<T>* TNode<T>::Left() const noexcept {
  // return the next pointer
  return this->left_ptr;
}

template <typename T>
TNode<T>* TNode<T>::Right() noexcept {
  // return the previous pointer
  return this->right_ptr;
}

template <typename T>
TNode<T>* TNode<T>::Right() const noexcept {
  // return the previous pointer
  return this->right_ptr;
}

template <typename T>
void TNode<T>::Left(TNode<T>* const next) noexcept {
  // set the next pointer
  this->left_ptr = next;
}

template <typename T>
void TNode<T>::Right(TNode<T>* const previous) noexcept {
  // set the previous pointer
  this->right_ptr = previous;
}

#endif  // NODE_TEMPLATE_H
