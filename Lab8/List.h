// Jacob Knox CST211 Lab3 Due: 2/2/2023

#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::move;

#include "Exception.h"
#include "LNode.h"

template <typename T>
class List {
 private:
  LNode<T>* l_head;
  LNode<T>* l_tail;
  int l_count;

  void AddNode(LNode<T>* const before, LNode<T>* const after, T data);
  void RemoveNode(LNode<T>* const node);

 public:
  List();
  List(const T data);
  List(const List& copy);
  List(List&& move) noexcept;
  ~List();

  List& operator=(const List& copy);
  List& operator=(List&& move) noexcept;
  explicit operator bool() const;

  void Append(const T data);
  void Prepend(const T data);
  void RemoveLast();
  void RemoveFirst();
  void Extract(const T data);
  void InsertAfter(const T data, const T after);
  void InsertBefore(const T data, const T before);
  void Purge() noexcept;

  T& Last();//
  T Last() const;
  T& First();
  T First() const;

  LNode<T>* getHead();
  LNode<T>* getTail();
  bool isEmpty() const noexcept;
  size_t Size() const noexcept;
  bool operator==(const List<T>& rhs) const noexcept;
};

// should only be called when node is not at the head or tail
// i.e. before != nullptr && after != nullptr
template <typename T>
void List<T>::AddNode(LNode<T>* const before, LNode<T>* const after, T data) {
  // create a new node with data
  LNode<T>* new_node = new LNode<T>(data);

  // set the new node's next pointer to the node after the node to add before
  new_node->next_ptr = after;
  // set the new node's previous pointer to the node before the node to add after
  new_node->prev_ptr = before;

  // set the node before the node to add after's next pointer to the new node
  before->next_ptr = new_node;
  // set the node after the node to add before's previous pointer to the new node
  after->prev_ptr = new_node;

  // increment the count
  l_count++;
}

// should only be called when node is not at the head or tail
// i.e. node->prev_ptr != nullptr && node->next_ptr != nullptr
template <typename T>
void List<T>::RemoveNode(LNode<T>* const node) {
  // set the previous node's next pointer to the next node
  node->prev_ptr->next_ptr = node->next_ptr;
  // set the next node's previous pointer to the previous node
  node->next_ptr->prev_ptr = node->prev_ptr;
  // delete the node
  delete node;
  // decrement the count
  l_count--;
}

template <typename T>
List<T>::List() : l_head(nullptr), l_tail(nullptr), l_count(0) {}

template <typename T>
List<T>::List(const T data) {
  // create a new node with data and set it as the head and tail
  l_head = new LNode<T>(data);
  l_tail = l_head;
  l_count = 1;
}

template <typename T>
List<T>::List(const List& copy) {
  // copy constructor, perform a deep copy of copy
  if (copy.l_head == nullptr) {
    // other list is empty, set this list to empty
    this->l_count = 0;
    this->l_head = nullptr;
    this->l_tail = nullptr;
    return;
  }
  // copy the first node
  this->l_head = new LNode<T>(copy.l_head->n_data);
  LNode<T>* copy_temp = copy.l_head->next_ptr;
  LNode<T>* temp = this->l_head;
  // copy the rest of the nodes
  while (copy_temp != nullptr) {
    temp->next_ptr = new LNode<T>(copy_temp->n_data);
    temp->next_ptr->prev_ptr = temp;
    copy_temp = copy_temp->next_ptr;
    temp = temp->next_ptr;
  }
  // set the tail
  this->l_tail = temp;
  // set the count
  this->l_count = copy.l_count;
}

template <typename T>
List<T>::List(List&& move) noexcept {
  // move constructor, perform a shallow copy of move
  this->l_head = move.l_head;
  this->l_tail = move.l_tail;
  this->l_count = move.l_count;
  // set move to empty
  move.l_head = nullptr;
  move.l_tail = nullptr;
  move.l_count = 0;
}

template <typename T>
List<T>::~List() {
  // delete all nodes in the list
  LNode<T>* temp = l_head;
  while (temp != nullptr) {
    LNode<T>* next = temp->next_ptr;
    delete temp;
    temp = next;
  }
}

template <typename T>
List<T>& List<T>::operator=(const List& copy) {
  // copy assignment, perform a deep copy of copy
  if (copy.l_head == nullptr) {
    // other list is empty, set this list to empty
    this->l_count = 0;
    this->l_head = nullptr;
    this->l_tail = nullptr;
    return *this;
  }
  // copy the first node
  this->l_head = new LNode<T>(copy.l_head->n_data);
  LNode<T>* copy_temp = copy.l_head->next_ptr;
  LNode<T>* temp = this->l_head;
  // copy the rest of the nodes
  while (copy_temp != nullptr) {
    temp->next_ptr = new LNode<T>(copy_temp->n_data);
    temp->next_ptr->prev_ptr = temp;
    copy_temp = copy_temp->next_ptr;
    temp = temp->next_ptr;
  }
  // set the tail
  this->l_tail = temp;
  // set the count
  this->l_count = copy.l_count;
  return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& move) noexcept {
  // just need to copy the pointers and count
  this->l_head = move.l_head;
  this->l_tail = move.l_tail;
  this->l_count = move.l_count;
  // set move's pointers to null and count to 0 so nodes aren't deleted
  move.l_head = nullptr;
  move.l_tail = nullptr;
  move.l_count = 0;
  return *this;
}

template <typename T>
List<T>::operator bool() const {
  // if the list is empty, return false
  return l_head != nullptr;
}

template <typename T>
void List<T>::Append(const T data) {
  // create a new node with data
  LNode<T>* temp = new LNode<T>(data);
  // if the list is empty, set the head and tail to the new node
  if (l_head == nullptr) {
    l_head = temp;
    l_tail = temp;
  } else {
    // append the new node to the end of the list
    l_tail->next_ptr = temp;
    temp->prev_ptr = l_tail;
    l_tail = temp;
  }
  l_count++;
}

template <typename T>
void List<T>::Prepend(const T data) {
  // create a new node with data
  LNode<T>* temp = new LNode<T>(data);
  // if the list is empty, set the head and tail to the new node
  if (l_head == nullptr) {
    l_head = temp;
    l_tail = temp;
  } else {
    // prepend the new node to the beginning of the list
    l_head->prev_ptr = temp;
    temp->next_ptr = l_head;
    l_head = temp;
  }
  l_count++;
}

template <typename T>
void List<T>::RemoveLast() {
  // pop the last node off the list
  LNode<T>* temp = l_tail;
  l_tail = l_tail->prev_ptr;
  // if the tail is null, the list is empty
  if (l_tail != nullptr) {
    l_tail->next_ptr = nullptr;
  } else {
    l_head = nullptr;
  }
  delete temp;
  l_count--;
}

template <typename T>
void List<T>::RemoveFirst() {
  // pop the first node off the list
  LNode<T>* temp = l_head;
  l_head = l_head->next_ptr;
  // if the head is null, the list is empty
  if (l_head != nullptr) {
    l_head->prev_ptr = nullptr;
  } else {
    l_tail = nullptr;
  }
  delete temp;
  l_count--;
}

template <typename T>
void List<T>::Extract(const T data) {
  // check if the list is empty
  if (l_head == nullptr) {
    throw Exception("List is empty");
  }

  // check if the head is the node to be removed
  if (l_head->n_data == data) {
    RemoveFirst();
    return;
  }

  // check if the tail is the node to be removed
  if (l_tail->n_data == data) {
    RemoveLast();
    return;
  }

  // check if the node to be removed is in the middle of the list
  LNode<T>* temp = l_head;
  while (temp != nullptr) {
    if (temp->n_data == data) {
      RemoveNode(temp);
      return;
    }
    temp = temp->next_ptr;
  }

  // if the node is not in the list, throw an exception
  throw Exception("Node not found");
}

template <typename T>
void List<T>::InsertAfter(const T data, const T after) {
  // insert data after the node with the data after
  // check if the list is empty
  if (l_head == nullptr) {
    throw Exception("List is empty");
  }

  // check if the tail is the node to be inserted after
  if (l_tail->n_data == after) {
    Append(data);
    return;
  }

  // check if the node to be inserted after is in the middle of the list
  // if we go back to the head, no need to check the head specifically
  LNode<T>* temp = l_tail;
  while (temp != nullptr) {
    if (temp->n_data == after) {
      AddNode(temp, temp->next_ptr, data);
      return;
    }
    temp = temp->prev_ptr;
  }

  // no match found, throw an exception
  throw Exception("Node not found");
}

template <typename T>
void List<T>::InsertBefore(const T data, const T before) {
  // insert data before the node with the data before
  // check if the list is empty
  if (l_head == nullptr) {
    throw Exception("List is empty");
  }

  // check if the head is the node to be inserted before
  if (l_head->n_data == before) {
    Prepend(data);
    return;
  }

  // check if the node to be inserted before is in the middle of the list
  LNode<T>* temp = l_head;
  while (temp != nullptr) {
    if (temp->n_data == before) {
      AddNode(temp->prev_ptr, temp, data);
      return;
    }
    temp = temp->next_ptr;
  }

  // no match found, throw an exception
  throw Exception("Node not found");
}

template <typename T>
void List<T>::Purge() noexcept {
  // delete all nodes in the list
  LNode<T>* temp = l_head;
  while (temp != nullptr) {
    LNode<T>* next = temp->next_ptr;
    delete temp;
    temp = next;
  }
  l_head = nullptr;
  l_tail = nullptr;
  l_count = 0;
}

template <typename T>
T& List<T>::Last() {
  // return the data in the tail pointer
  if (l_tail == nullptr) {
    throw Exception("List is empty");
  }
  return l_tail->n_data;
}

template <typename T>
T List<T>::Last() const {
  // return the data in the tail pointer
  if (l_tail == nullptr) {
    throw Exception("List is empty");
  }
  return l_tail->n_data;
}

template <typename T>
T& List<T>::First() {
  // return the data in the head pointer
  if (l_head == nullptr) {
    throw Exception("List is empty");
  }
  return l_head->n_data;
}

template <typename T>
T List<T>::First() const {
  // return the data in the head pointer
  if (l_head == nullptr) {
    throw Exception("List is empty");
  }
  return l_head->n_data;
}

template <typename T>
LNode<T>* List<T>::getHead() {
  // return the head pointer
  return l_head;
}

template <typename T>
LNode<T>* List<T>::getTail() {
  // return the tail pointer
  return l_tail;
}

template <typename T>
bool List<T>::isEmpty() const noexcept {
  // return true if the head pointer is null
  return l_head == nullptr;
}

template <typename T>
size_t List<T>::Size() const noexcept {
  // return the size of the list
  return l_count;
}

template <typename T>
bool List<T>::operator==(const List<T>& rhs) const noexcept {
  // check if the two lists are the same size
  if (this->l_count != rhs.l_count) {
    return false;
  }
  // check if the two lists are the same
  LNode<T>* temp = this->l_head;
  LNode<T>* temp2 = rhs.l_head;
  while (temp != nullptr) {
    if (temp->n_data != temp2->n_data) {
      return false;
    }
    temp = temp->next_ptr;
    temp2 = temp2->next_ptr;
  }
  return true;
}

#endif  // LIST_TEMPLATE_H
