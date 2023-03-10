#ifndef QUEUETEMPLATE_H
#define QUEUETEMPLATE_H

#include "Exception.h"
#include "List.h"

const int DEFAULT_MAX_SIZE = 10;

template <typename T>
class Queue
{
private:
    List<T> m_queue;
    int max_size;

public:
    int start_index = 0;
    Queue();
    Queue(int max_size);
    Queue(const Queue &move);
    Queue(Queue &&copy) noexcept;
    ~Queue();

    Queue &operator=(const Queue &move);
    Queue &operator=(Queue &&copy) noexcept;

    void Enqueue(const T data);
    T Dequeue();
    T Peek();

    int getSize() const;
    bool isEmpty() const;
    bool isFull() const;

    int getMaxSize() const;
};

// simple assignments work for all constructors
// array copy/move constructor is called
template <typename T>
Queue<T>::Queue() :m_queue(), max_size(DEFAULT_MAX_SIZE), start_index(0) {}

template <typename T>
Queue<T>::Queue(int max_size) : m_queue(), max_size(max_size), start_index(0) {}

template <typename T>
Queue<T>::Queue(const Queue &move) : m_queue(move.m_queue), max_size(move.max_size), start_index(move.start_index) {}

template <typename T>
Queue<T>::Queue(Queue &&copy) noexcept : m_queue(copy.m_queue), max_size(copy.max_size), start_index(copy.start_index) {}

// no destructor needed, array destructor is called
template <typename T>
Queue<T>::~Queue() = default;

// simple assignments work for all operators
template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &move)
{
    m_queue = move.m_queue;
    max_size = move.max_size;
    start_index = move.start_index;
    return *this;
}

// simple assignments work for all operators
template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&copy) noexcept
{
    m_queue = copy.m_queue;
    max_size = copy.max_size;
    start_index = copy.start_index;
    return *this;
}

template <typename T>
void Queue<T>::Enqueue(const T data)
{
    // if the queue is full, throw an exception
    if (isFull())
    {
        throw Exception("Queue is full");
    }
    // add the new data to the end
    m_queue.Append(data);
}

template <typename T>
T Queue<T>::Dequeue()
{
    // if the queue is empty, throw an exception
    if (isEmpty())
    {
        throw Exception("Queue is empty");
    }
    T data = m_queue.First();
    //remove does not return the data, so we need to store it
    m_queue.RemoveFirst();
    return data;
}

template <typename T>
T Queue<T>::Peek()
{
    // if the queue is empty, throw an exception
    if (isEmpty())
    {
        throw Exception("Queue is empty");
    }
    // data is at the first node
    return m_queue.First();
}

// simple getters below
template <typename T>
int Queue<T>::getSize() const
{
    return m_queue.Size();
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return m_queue.Size() == 0;
}

template <typename T>
bool Queue<T>::isFull() const
{
    return m_queue.Size() == max_size;
}

template <typename T>
int Queue<T>::getMaxSize() const
{
    return max_size;
}

#endif // QUEUE_TEMPLATE_H