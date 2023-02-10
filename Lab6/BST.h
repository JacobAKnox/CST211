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
    BST(BST&& copy) noexcept;
    ~BST();

    BST<T>& operator=(const BST& copy);
    BST<T>& operator=(BST&& copy) noexcept;

    void Insert(const T& data, Node<T>*& root = root);
    void Delete(const T& data, Node<T>*& root = root);
    void Purge();
    int Height() const;

    void InOrder(Vistor v, Node<T>*& root = root) const;
    void PreOrder(Vistor v, Node<T>*& root = root) const;
    void PostOrder(Vistor v, Node<T>*& root = root) const;
    void BreadthFirst(Vistor v, Node<T>*& root = root) const;
};

#endif  // BST_TEMPLATE_H
