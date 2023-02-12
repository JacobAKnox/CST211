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

  Node<T>* Insert(const T& data, Node<T>* root, int height);
  Node<T>* Delete(const T& data, Node<T>* root);
  void Purge(Node<T>* root);

  void InOrder(Vistor v, Node<T>* root) const;
  void PreOrder(Vistor v, Node<T>* root) const;
  void PostOrder(Vistor v, Node<T>* root) const;
  void BreadthFirst(Vistor v, Node<T>* root) const;

  Node<T>* CopyHelper(Node<T>* root) const;
  int CalcHeight(Node<T>* root) const;

  bool Contains(const T& data, Node<T>* root) const;

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
  void Purge(); // 0/2
  int Height() const; // 0/3

  void InOrder(Vistor v) const; // 0/1
  void PreOrder(Vistor v) const; // 0/1
  void PostOrder(Vistor v) const; // 0/1
  void BreadthFirst(Vistor v) const; // 0/1 

  // not required
  Node<T>* GetRoot() const;
  bool Contains(const T& data) const;
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
Node<T>* BST<T>::Insert(const T& data, Node<T>* root, int height) {
  if (root == nullptr) {
    // if height is greater than the current height, set the height
    if (height > this->height)
      this->height = height;
    // if root is nullptr, create a new node
    return new Node<T>{data};
  }
  if (data < root->Value()) {
    // if data is less than root, insert left
    root->left_ptr = Insert(data, root->Left(), height + 1);
  }
  if (data > root->Value()) {
    // if data is greater than root, insert right
    root->right_ptr = Insert(data, root->Right(), height + 1);
  }
  if (data == root->Value()) {
    // if data is equal to root, throw exception
    throw Exception("Duplicate value");
  }
  return root;
}

template <typename T>
void BST<T>::Delete(const T& data) {
  // call Delete with the root pointer
  root = Delete(data, root);
  height = CalcHeight(root);
}

template <typename T>
Node<T>* BST<T>::Delete(const T& data, Node<T>* root) {
  if (root == nullptr) {
    // if root is null, throw exception
    // data was not found
    throw Exception("Value not found");
  }
  if (data == root->Value()) {
    // if data is equal to root, delete the node
    Purge(root);
    delete root;
    return nullptr;
  }
  if (data < root->Value()) {
    // if data is less than root, delete left
    root->left_ptr = Delete(data, root->Left());
  }
  if (data > root->Value()) {
    // if data is greater than root, delete right
    root->right_ptr = Delete(data, root->Right());
  }
  return root;
}

template <typename T>
void BST<T>::Purge() {
  // call Purge with the root pointer
  Purge(root);
  height = 0;
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
void BST<T>::InOrder(Vistor v) const {
  // call InOrder with the root pointer
  InOrder(v, root);
}

template <typename T>
void BST<T>::InOrder(Vistor v, Node<T>* root) const {
  if (root != nullptr) {
    // if root is not null, visit the left, root, and right
    InOrder(v, root->Left());
    v(root->Value());
    InOrder(v, root->Right());
  }
}

template <typename T>
int BST<T>::Height() const {
  return height;
}

template <typename T>
int BST<T>::CalcHeight(Node<T>* root) const {
  if (root == nullptr) {
    // if root is null, return 0
    return 0;
  }
  // return the max of the left and right heights + 1
  return std::max(CalcHeight(root->Left()), CalcHeight(root->Right())) + 1;
}

template <typename T>
Node<T>* BST<T>::GetRoot() const {  //
  // return the root pointer
  return root;
}

template <typename T>
Node<T>* BST<T>::CopyHelper(Node<T>* root) const {
  if (root == nullptr) {
    // if root is null, return null
    return nullptr;
  }
  // create a new node with the root value
  Node<T>* new_node = new Node<T>(root->Value());
  // set the left and right to the copy of the left and right
  new_node->left_ptr = CopyHelper(root->Left());
  new_node->right_ptr = CopyHelper(root->Right());
  return new_node;
}

template <typename T>
bool BST<T>::Contains(const T& data) const {
  // call Contains with the root pointer
  return Contains(data, root);
}

template <typename T>
bool BST<T>::Contains(const T& data, Node<T>* root) const {
  if (root == nullptr) {
    // if root is null, return false
    return false;
  }
  if (data == root->Value()) {
    // if data is equal to root, return true
    return true;
  }
  if (data < root->Value()) {
    // if data is less than root, check left
    return Contains(data, root->Left());
  }
  if (data > root->Value()) {
    // if data is greater than root, check right
    return Contains(data, root->Right());
  }
  return false;
}

#endif  // BST_TEMPLATE_H
