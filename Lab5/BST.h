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
  int height;

  Node<T>* Insert(const T& data, Node<T>* node, int height);
  Node<T>* Delete(const T& data, Node<T>* node);
  void Purge(Node<T>* node);

  void InOrder(Vistor v, Node<T>* node) const;
  void PreOrder(Vistor v, Node<T>* node) const;
  void PostOrder(Vistor v, Node<T>* node) const;
  void BreadthFirst(Vistor v, Node<T>* node, int level) const;

  Node<T>* CopyHelper(Node<T>* node) const;
  int CalcHeight(Node<T>* node) const;

  bool Contains(const T& data, Node<T>* node) const;

 public:
  // fractions are test counts
  BST(); // 1/1
  BST(const BST& copy); // 1/2
  BST(BST&& move) noexcept; // 1/2
  ~BST();

  BST<T>& operator=(const BST& copy); // 1/2
  BST<T>& operator=(BST&& move) noexcept; // 1/2

  void Insert(const T& data); // 2/4
  void Delete(const T& data); // 3/5
  void Purge(); // 2/2
  int Height() const; // 2/3

  void InOrder(Vistor v) const; // 1/1
  void PreOrder(Vistor v) const; // 1/1
  void PostOrder(Vistor v) const; // 1/1
  void BreadthFirst(Vistor v) const; // 1/1 

  // not required
  Node<T>* GetRoot() const; // 0/0
  bool Contains(const T& data) const; // 1/2
};

// root just needs to be initialized to nullptr
template <typename T>
BST<T>::BST() : root(nullptr), height(0) {
}

template <typename T>
BST<T>::~BST() {
  // can call Purge() here
  Purge();
}

// can jsut copy the root pointer
template <typename T>
BST<T>::BST(const BST& copy) {
  this->height = copy.height;
  this->root = CopyHelper(copy.root);
}

// can jsut move the root pointer
template <typename T>
BST<T>::BST(BST&& move) noexcept {
  this->height = move.height;
  this->root = CopyHelper(move.root);
}

// can jsut copy the root pointer
template <typename T>
BST<T>& BST<T>::operator=(const BST& copy) {
  this->height = copy.height;
  this->root = CopyHelper(copy.root);
  return *this;
}

// can jsut move the root pointer
template <typename T>
BST<T>& BST<T>::operator=(BST&& move) noexcept {
  this->height = move.height;
  this->root = CopyHelper(move.root);
  return *this;
}

template <typename T>
void BST<T>::Insert(const T& data) {
  // call Insert with the root pointer
  root = Insert(data, root, 1);
}

template <typename T>
Node<T>* BST<T>::Insert(const T& data, Node<T>* node, int height) {
  if (node == nullptr) {
    // if height is greater than the current height, set the height
    if (height > this->height)
      this->height = height;
    // if node is nullptr, create a new node
    return new Node<T>{data};
  }
  if (data < node->Value()) {
    // if data is less than node, insert left
    node->left_ptr = Insert(data, node->Left(), height + 1);
  }
  if (data > node->Value()) {
    // if data is greater than node, insert right
    node->right_ptr = Insert(data, node->Right(), height + 1);
  }
  if (data == node->Value()) {
    // if data is equal to node, throw exception
    throw Exception("Duplicate value");
  }
  return node;
}

template <typename T>
void BST<T>::Delete(const T& data) {
  // // call Delete with the root pointer
  root = Delete(data, root);
  height = CalcHeight(root);
}

template <typename T>
Node<T>* BST<T>::Delete(const T& data, Node<T>* node) {
  if (node == nullptr) {
    // if node is null, throw exception
    // data was not found
    throw Exception("Value not found");
  }
  if (data == node->Value()) {
    // if data is equal to node, delete the node
    Purge(node);
    return nullptr;
  }
  if (data < node->Value()) {
    // if data is less than node, delete left
    node->left_ptr = Delete(data, node->Left());
  }
  if (data > node->Value()) {
    // if data is greater than node, delete right
    node->right_ptr = Delete(data, node->Right());
  }
  return node;
}

template <typename T>
void BST<T>::Purge() {
  // call Purge with the root pointer
  Purge(root);
  root = nullptr;
  height = 0;
}

template <typename T>
void BST<T>::Purge(Node<T>* node) {
  if (node != nullptr) {
    // if node is not null, purge the left and right
    Purge(node->left_ptr);
    Purge(node->right_ptr);
    delete node;
  }
}

template <typename T>
void BST<T>::InOrder(Vistor v) const {
  // call InOrder with the root pointer
  InOrder(v, root);
}

template <typename T>
void BST<T>::InOrder(Vistor v, Node<T>* node) const {
  if (node != nullptr) {
    // if node is not null, visit the left, node, and right
    InOrder(v, node->Left());
    v(node->Value());
    InOrder(v, node->Right());
  }
}

template <typename T>
void BST<T>::PreOrder(Vistor v) const {
  // call PreOrder with the root pointer
  PreOrder(v, root);
}

template <typename T>
void BST<T>::PreOrder(Vistor v, Node<T>* node) const {
  if (node != nullptr) {
    // if node is not null, visit the node, left, and right
    v(node->Value());
    PreOrder(v, node->Left());
    PreOrder(v, node->Right());
  }
}

template <typename T>
void BST<T>::PostOrder(Vistor v) const {
  // call PostOrder with the root pointer
  PostOrder(v, root);
}

template <typename T>
void BST<T>::PostOrder(Vistor v, Node<T>* node) const {
  if (node != nullptr) {
    // if node is not null, visit the left, right, and node
    PostOrder(v, node->Left());
    PostOrder(v, node->Right());
    v(node->Value());
  }
}

template <typename T>
void BST<T>::BreadthFirst(Vistor v) const {
  for (int i = 1; i <= height; i++) {
    // for each level, call BreadthFirst with the root pointer
    BreadthFirst(v, root, i);
  }
}

template <typename T>
void BST<T>::BreadthFirst(Vistor v, Node<T>* node, int level) const {
  if (node == nullptr) {
    // if node is null, return
    return;
  }
  if (level == 1) {
    // if level is 1, visit the node
    v(node->Value());
  } else if (level > 1) {
    // if level is greater than 1, visit the left and right
    BreadthFirst(v, node->Left(), level - 1);
    BreadthFirst(v, node->Right(), level - 1);
  }
}

template <typename T>
int BST<T>::Height() const {
  return height;
}

template <typename T>
int BST<T>::CalcHeight(Node<T>* node) const {
  if (node == nullptr) {
    // if node is null, return 0
    return 0;
  }
  // return the max of the left and right heights + 1
  return std::max(CalcHeight(node->Left()), CalcHeight(node->Right())) + 1;
}

template <typename T>
Node<T>* BST<T>::GetRoot() const {  //
  // return the root pointer
  return root;
}

template <typename T>
Node<T>* BST<T>::CopyHelper(Node<T>* node) const {
  if (node == nullptr) {
    // if node is null, return null
    return nullptr;
  }
  // create a new node with the node value
  Node<T>* new_node = new Node<T>(node->Value());
  // set the left and right to the copy of the left and right
  new_node->left_ptr = CopyHelper(node->Left());
  new_node->right_ptr = CopyHelper(node->Right());
  return new_node;
}

template <typename T>
bool BST<T>::Contains(const T& data) const {
  // call Contains with the root pointer
  return Contains(data, root);
}

template <typename T>
bool BST<T>::Contains(const T& data, Node<T>* node) const {
  if (node == nullptr) {
    // if node is null, return false
    return false;
  }
  if (data == node->Value()) {
    // if data is equal to node, return true
    return true;
  }
  if (data < node->Value()) {
    // if data is less than node, check left
    return Contains(data, node->Left());
  }
  if (data > node->Value()) {
    // if data is greater than node, check right
    return Contains(data, node->Right());
  }
  return false;
}

#endif  // BST_TEMPLATE_H
