// Jacob Knox CST211 Lab3 Due: 2/2/2023

#ifndef LNODETEMPLATE_H
#define LNODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T>
class LNode {
 private:
  T n_data;
  LNode<T>* next_ptr;
  LNode<T>* prev_ptr;

  template <typename U>
  friend class List;

 public:
  LNode();
  LNode(const LNode& copy);
  LNode(LNode&& copy) noexcept;
  LNode(const T data);
  LNode(const T data, LNode<T>* next, LNode<T>* prev);
  ~LNode();

  LNode<T>& operator=(const LNode& copy);
  LNode<T>& operator=(LNode&& copy) noexcept;

  T& Value() noexcept;
  T Value() const noexcept;
  void Value(const T data);

  LNode<T>* Next() noexcept;
  LNode<T>* Next() const noexcept;
  LNode<T>* Previous() noexcept;
  LNode<T>* Previous() const noexcept;
  void Next(LNode<T>* const next) noexcept;
  void Previous(LNode<T>* const previous) noexcept;
};

template <typename T>
LNode<T>::LNode() : n_data(0), next_ptr(nullptr), prev_ptr(nullptr) {
}

template <typename T>
LNode<T>::LNode(const T data)
    : n_data(data) {
}

template <typename T>
LNode<T>::~LNode() {
  // destructor
  this->n_data = T{};
  this->next_ptr = nullptr;
  this->prev_ptr = nullptr;
}

template <typename T>
LNode<T>::LNode(const LNode& copy) {
  // copy constructor, perform a shallpow copy of copy
  this->n_data = copy.n_data;
  this->next_ptr = copy.next_ptr;
  this->prev_ptr = copy.prev_ptr;
}

template <typename T>
LNode<T>::LNode(LNode&& copy) noexcept {
  // move constructor
  this->n_data = copy.n_data;
  this->next_ptr = copy.next_ptr;
  this->prev_ptr = copy.prev_ptr;
}

template <typename T>
LNode<T>::LNode(const T data, LNode<T>* next, LNode<T>* prev) {
  // constructor with data and next and previous pointers
  this->n_data = data;
  this->next_ptr = next;
  this->prev_ptr = prev;
}

template <typename T>
LNode<T>& LNode<T>::operator=(const LNode& copy) {
  // copy assignment operator
  this->n_data = copy.n_data;
  this->next_ptr = copy.next_ptr;
  this->prev_ptr = copy.prev_ptr;
}

template <typename T>
LNode<T>& LNode<T>::operator=(LNode&& copy) noexcept {
  // move assignment operator
  this->n_data = copy.n_data;
  this->next_ptr = copy.next_ptr;
  this->prev_ptr = copy.prev_ptr;
}

template <class T>
T& LNode<T>::Value() noexcept {
  // return the data
  return this->n_data;
}

template <class T>
T LNode<T>::Value() const noexcept {
  // return the data
  return this->n_data;
}

template <class T>
void LNode<T>::Value(const T data) {
  // set the data
  this->n_data = data;
}

template <typename T>
LNode<T>* LNode<T>::Next() noexcept {
  // return the next pointer
  return this->next_ptr;
}

template <typename T>
LNode<T>* LNode<T>::Next() const noexcept {
  // return the next pointer
  return this->next_ptr;
}

template <typename T>
LNode<T>* LNode<T>::Previous() noexcept {
  // return the previous pointer
  return this->prev_ptr;
}

template <typename T>
LNode<T>* LNode<T>::Previous() const noexcept {
  // return the previous pointer
  return this->prev_ptr;
}

template <typename T>
void LNode<T>::Next(LNode<T>* const next) noexcept {
  // set the next pointer
  this->next_ptr = next;
}

template <typename T>
void LNode<T>::Previous(LNode<T>* const previous) noexcept {
  // set the previous pointer
  this->prev_ptr = previous;
}

#endif  // LNODE_TEMPLATE_H
