// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef MINHEAP_H__
#define MINHEAP_H__

#ifdef DEBUG
#include <iostream>
#endif

template <typename T> class MinHeap
{
public:
    MinHeap(int capacity = 2);
    ~MinHeap();

    bool isEmpty();
    void insert(T);
    T delMin();
#ifdef DEBUG
    void debugTrace();
#endif

private:
    void resize(int newCapacity);

    void swim(int k);
    void sink(int k);

    /* T should have operator "<" overloaded. */
    int less(T i, T j);
    void exch(T i, T j);

    T *pq;
    int size;
    int elements_nr;
};


template <typename T>
MinHeap<T>::MinHeap(int capacity)
{
    pq = new T[capacity];
    size = capacity;
    elements_nr = 0;
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    delete []pq;
}

template <typename T>
bool MinHeap<T>::isEmpty()
{
    return elements_nr == 0;
}

template <typename T>
void MinHeap<T>::insert(T item)
{
    if (elements_nr  == size - 1)
        resize(2 * size);

    pq[++elements_nr] = item;
    swim(elements_nr);
}

template <typename T>
T MinHeap<T>::delMin()
{
    T item = pq[1];
    exch(1, elements_nr--);
    sink(1);

    if (elements_nr > 0 && elements_nr == (size - 1)/4)
        resize(size/2);

    return item;
}

#ifdef DEBUG
template <typename T>
void MinHeap<T>::debugTrace()
{
    for (int i = 1; i <= elements_nr; ++i)
        std::cout << pq[i] << " ";

    std::cout << "\n";
}
#endif

template <typename T>
void MinHeap<T>::resize(int newCapacity)
{
    T *newPq = new T[newCapacity];
    T *tmp = pq;

    for (int i = 1; i <= elements_nr; ++i) {
        newPq[i] = pq[i];
    }

    pq = newPq;
    size = newCapacity;

    delete []tmp;
}

template <typename T>
void MinHeap<T>::swim(int k)
{
    while (k > 1 && !less(k/2, k)) {
        exch(k, k/2);
        k = k/2;
    }
}

template <typename T>
void MinHeap<T>::sink(int k)
{
    while (2 * k <= elements_nr) {
        int j = 2 * k;

        if (j < elements_nr && !less(j, j+1))
            j++;
        if (!less(j, k))
            break;

        exch(k, j);
        k = j;
    }
}

template <typename T>
int MinHeap<T>::less(T i, T j)
{
    return pq[i] < pq[j];
}

template <typename T>
void MinHeap<T>::exch(T i, T j)
{
    T tmp = pq[i];
    pq[i] = pq[j];
    pq[j] = tmp;
}

#endif // MINHEAP_H__
