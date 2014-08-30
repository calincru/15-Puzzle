// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef QUEUE_H__
#define QUEUE_H__

#include <cstdio>
#include <cstdlib>


template <typename T> class Queue
{
public:
    Queue(int capacity = 2);
    ~Queue();

    void enqueue(T item);
    T dequeue();
    bool isEmpty();
    T front();

private:
    void resize(int new_dim);

    T* queueArray;
    int size;
    int elements_nr;
    int first, last;
};


template <typename T>
Queue<T>::Queue(int capacity)
    : queueArray(new T[size]),
      size(capacity),
      elements_nr(0),
      first(0),
      last(0)
{
     // nothing to do
}

template <typename T>
Queue<T>::~Queue()
{
    delete []queueArray;
}

template <typename T>
void Queue<T>::enqueue(T item)
{
    if (elements_nr == size)
         resize(2 * size);

    queueArray[last++] = item;
    elements_nr++;

    if (last == size)
        last = 0;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (isEmpty()) {
        fprintf(stderr, "You cannot dequeue an empty queue!\n");
        exit(EXIT_FAILURE);
    }

    T item = queueArray[first];
    elements_nr--;
    first++;
    if (first == size) first = 0;

    if (elements_nr > 0 && elements_nr == size/4)
        resize(size/2);

    return item;
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return elements_nr == 0;
}

template <typename T>
T Queue<T>::front()
{
    if (isEmpty()) {
        fprintf(stderr, "This Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    return queueArray[first];
}

template <typename T>
void Queue<T>::resize(int new_dim)
{
    T* newQueueArray = new T[new_dim];
    T* tmp = queueArray;

    for (int i = 0; i < elements_nr; i++)
        newQueueArray[i] = queueArray[(first + i) % size];

    size = new_dim;
    queueArray = newQueueArray;
    first = 0;
    last = elements_nr;

    delete [] tmp;
}

#endif // QUEUE_H__
