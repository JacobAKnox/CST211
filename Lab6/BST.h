// Jacob Knox CST211 Lab6 Due: 2/16/2023

#ifndef BSTTEMPLATE_H
#define BSTTEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::move;

#include "Exception.h"
#include "Node.h"

template <typename T>
class BST {
 private:
  Node<T>* root;
  typedef void (*Vistor)(T);

 public:
  BST();
  BST(const BST& copy);
  BST(BST&& move)
  noexcept;
  ~BST();

  BST<T>& operator=(const BST& copy);
  BST<T>& operator=(BST&& move) noexcept;

  void Insert(const T& data);
  void Insert(const T& data, Node<T>* root);
  void Delete(const T& data);
  void Delete(const T& data, Node<T>* root);
  void Purge();
  void Purge(Node<T>* root);
  int Height() const;

  void InOrder(Vistor v) const;
  void InOrder(Vistor v, Node<T>* root) const;
  void PreOrder(Vistor v) const;
  void PreOrder(Vistor v, Node<T>* root) const;
  void PostOrder(Vistor v) const;
  void PostOrder(Vistor v, Node<T>* root) const;
  void BreadthFirst(Vistor v) const;
  void BreadthFirst(Vistor v, Node<T>* root) const;

  // not required
  Node<T>* GetRoot() const;
};

// root just needs to be initialized to nullptr
template <typename T>
BST<T>::BST() : root(nullptr) {
}

template <typename T>
BST<T>::~BST() {
  // can call Purge() here
  Purge();
}

// can jsut copy the root pointer
template <typename T>
BST<T>::BST(const BST& copy) {
  this->root = copy.root;
}

// can jsut move the root pointer
template <typename T>
BST<T>::BST(BST&& move) noexcept {
  this->root = move.root;
}

// can jsut copy the root pointer
template <typename T>
BST<T>& BST<T>::operator=(const BST& copy) {
  this->root = copy.root;
  return *this;
}

// can jsut move the root pointer
template <typename T>
BST<T>& BST<T>::operator=(BST&& move) noexcept {
  this->root = move.root;
  return *this;
}

template <typename T>
void BST<T>::Insert(const T& data) {
  // call Insert with the root pointer
  Insert(data, root);
}

template <typename T>
void BST<T>::Insert(const T& data, Node<T>* root) {
  if (root == nullptr) {
    // if root is null, insert data
    root = new Node<T>(data);
  } else if (data < root->Value()) {
    // if data is less than root, insert to the left
    Insert(data, root->Left());
  } else if (data > root->Value()) {
    // if data is greater than root, insert to the right
    Insert(data, root->Right());
  } else {
    // if data is equal to root, throw an exception
    throw Exception("Duplicate value");
  }
}

template <typename T>
void BST<T>::Delete(const T& data, Node<T>* root) {
}

template <typename T>
void BST<T>::Purge() {
  // call Purge with the root pointer
  Purge(root);
}

template <typename T>
void BST<T>::Purge(Node<T>* root) {
  if (root != nullptr) {
    // if root is not null, purge the left and right
    Purge(root->Left());
    Purge(root->Right());
    delete root;
    root = nullptr;
  }
}

template <typename T>
int BST<T>::Height() const {
  return 0;
}

template <typename T>
Node<T>* BST<T>::GetRoot() const {//
  // return the root pointer
  return root;
}

#endif  // BST_TEMPLATE_H
