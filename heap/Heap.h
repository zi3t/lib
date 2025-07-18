/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Heap.h
 *
 * Created on 22 August 2020, 18:18
 */

#ifndef HEAP_HEAP_H_
#define HEAP_HEAP_H_
#include "heap/IHeap.h"
#include <iostream>
#include <cstring>
#include <sstream>

/*
 * function pointer: int (*comparator)(T& lhs, T& rhs)
 *      compares objects of type T given in lhs and rhs.
 *      return: sign of (lhs - rhs)
 *              -1: of lhs < rhs
 *              0 : lhs == rhs
 *              +1: ls > rhs
 * 
 * function pointer: void (*deleteUserData)(Heap<T>* pHeap)
 *      remove user's data in case that T is a pointer type
 *      Users should pass &Heap<T>::free for "deleteUserData"
 * 
 */
template <class T>
class Heap : public IHeap<T>
{
public:
    class Iterator; //forward declaration

protected:
    T *elements;                            //a dynamic array to contain user's data
    int capacity;                           //size of the dynamic array
    int count;                              //current count of elements stored in this heap
    int (*comparator)(T &lhs, T &rhs);      //see above
    void (*deleteUserData)(Heap<T> *pHeap); //see above

public:
    Heap(int (*comparator)(T &, T &) = nullptr,
         void (*deleteUserData)(Heap<T> *) = nullptr);

    Heap(const Heap<T> &heap);               //copy constructor
    Heap<T> &operator=(const Heap<T> &heap); //assignment operator

    ~Heap();

    //Inherit from IHeap: BEGIN
    void push(T item);
    T pop();
    const T peek();
    void remove(T item, void (*removeItemData)(T) = nullptr);
    bool contains(T item);
    int size();
    void heapify(T array[], int size);
    void clear();
    bool empty();
    std::string toString(std::string (*item2str)(T &) = nullptr);
    //Inherit from IHeap: END

    void println(std::string (*item2str)(T &) = nullptr)
    {
        std::cout << toString(item2str) << std::endl;
    }

    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

public:
    /* if T is pointer type:
     *     pass the address of method "free" to Heap<T>'s constructor:
     *     to:  remove the user's data (if needed)
     * Example:
     *  Heap<Point*> heap(&Heap<Point*>::free);
     *  => Destructor will call free via function pointer "deleteUserData"
     */
    static void free(Heap<T> *pHeap)
    {
        for (int idx = 0; idx < pHeap->count; idx++)
            delete pHeap->elements[idx];
    }

private:
    bool aLTb(T &a, T &b)
    {
        return compare(a, b) < 0;
    }
    int compare(T &a, T &b)
    {
        if (comparator != nullptr)
            return comparator(a, b);
        else
        {
            if (a < b)
                return -1;
            else if (a > b)
                return 1;
            else
                return 0;
        }
    }

    void ensureCapacity(int minCapacity);
    void swap(int a, int b);
    void reheapUp(int position);
    void reheapDown(int position);
    int getItem(T item);

    void removeInternalData();
    void copyFrom(const Heap<T> &heap);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////

public:
    //Iterator: BEGIN
    class Iterator
    {
    private:
        Heap<T> *heap;
        int cursor;

    public:
        Iterator(Heap<T> *heap = nullptr, bool begin = false)
        {
            this->heap = heap;
            if (begin && (heap != nullptr))
                cursor = 0;
            if (!begin && (heap != nullptr))
                cursor = heap->size();
        }
        Iterator &operator=(const Iterator &iterator)
        {
            this->heap = iterator.heap;
            this->cursor = iterator.cursor;
            return *this;
        }

        T &operator*()
        {
            return this->heap->elements[cursor];
        }
        bool operator!=(const Iterator &iterator)
        {
            return this->cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
        void remove(void (*removeItemData)(T) = nullptr)
        {
            this->heap->remove(this->heap->elements[cursor], removeItemData);
        }
    };
    //Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
Heap<T>::Heap(
    int (*comparator)(T &, T &),
    void (*deleteUserData)(Heap<T> *))
{
    capacity = 10;
    count = 0;
    elements = new T[capacity];

    this->comparator = comparator;
    this->deleteUserData = deleteUserData;
}
template <class T>
Heap<T>::Heap(const Heap<T> &heap)
{
    copyFrom(heap);
}

template <class T>
Heap<T> &Heap<T>::operator=(const Heap<T> &heap)
{
    removeInternalData();
    copyFrom(heap);
    return *this;
}

template <class T>
Heap<T>::~Heap()
{
    removeInternalData();
}

template <class T>
void Heap<T>::push(T item)
{ //item  = 25
    ensureCapacity(count + 1);
    elements[count] = item;
    count++;
    reheapUp(count - 1);
}
/*
      18
     /  \
    15   13
    /
  25 
 =>
      25
     /  \
    18   13
    /
  15 
=> array: [25, 18, 13, 15, , ]
           0   1    2   3
 
 */
template <class T>
T Heap<T>::pop()
{
    if (count == 0)
    {
        throw std::underflow_error("Calling to pop with empty heap");
    }
    T data = elements[0];
    elements[0] = elements[count - 1];
    count--;
    reheapDown(0);
    return data;
}

/*
      15
     /  \
    18   13
 => ReheapDown
      18
     /  \
    15   13
=> Array: [18, 15, 13, , , ]
 */

template <class T>
const T Heap<T>::peek()
{
    if (count == 0)
        throw std::underflow_error("Calling to peek with the empty heap.");
    return elements[0];
}

template <class T>
void Heap<T>::remove(T item, void (*removeItemData)(T))
{
    int foundIdx = this->getItem(item);
    if (foundIdx == -1)
        return;

    if (removeItemData != nullptr)
        removeItemData(elements[foundIdx]);

    int remain = count - foundIdx - 1;
    if (remain > 0)
        memcpy(&elements[foundIdx], &elements[foundIdx + 1], remain * sizeof(T));

    count -= 1;

    int first_data = foundIdx;
    int last_data = count - 1;
    count = foundIdx;

    for (int idx = first_data; idx <= last_data; idx++)
        push(elements[idx]);
}

template <class T>
bool Heap<T>::contains(T item)
{
    bool found = false;
    for (int idx = 0; idx < count; idx++)
    {
        if (compare(elements[idx], item) == 0)
        {
            found = true;
            break;
        }
    }
    return found;
}

template <class T>
int Heap<T>::size()
{
    return count;
}

template <class T>
void Heap<T>::heapify(T array[], int size)
{
    for (int idx = 0; idx < size; idx++)
        push(array[idx]);
}

template <class T>
void Heap<T>::clear()
{
    removeInternalData();

    capacity = 10;
    count = 0;
    elements = new T[capacity];
}

template <class T>
bool Heap<T>::empty()
{
    return count == 0;
}

template <class T>
std::string Heap<T>::toString(std::string (*item2str)(T &))
{
    std::stringstream os;
    if (item2str != nullptr)
    {
        os << "[";
        for (int idx = 0; idx < count - 1; idx++)
            os << item2str(elements[idx]) << ",";
        if (count > 0)
            os << item2str(elements[count - 1]);
        os << "]";
    }
    else
    {
        os << "[";
        for (int idx = 0; idx < count - 1; idx++)
            os << elements[idx] << ",";
        if (count > 0)
            os << elements[count - 1];
        os << "]";
    }
    return os.str();
}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    if (minCapacity >= capacity)
    {
        //re-allocate
        int old_capacity = capacity;
        capacity = old_capacity + (old_capacity >> 2);
        try
        {
            T *new_data = new T[capacity];
            //OLD: memcpy(new_data, elements, capacity*sizeof(T));
            memcpy(new_data, elements, old_capacity * sizeof(T));
            delete[] elements;
            elements = new_data;
        }
        catch (std::bad_alloc e)
        {
            e.what();
        }
    }
}

template <class T>
void Heap<T>::swap(int a, int b)
{
    T temp = this->elements[a];
    this->elements[a] = this->elements[b];
    this->elements[b] = temp;
}

template <class T>
void Heap<T>::reheapUp(int position)
{
    if (position <= 0)
        return;
    int parent = (position - 1) / 2;
    if (aLTb(this->elements[position], this->elements[parent]))
    {
        this->swap(position, parent);
        reheapUp(parent);
    }
}

template <class T>
void Heap<T>::reheapDown(int position)
{
    int lChild = (position * 2) + 1;
    int rChild = (position * 2) + 2;
    int lastPos = this->count - 1;

    if (lChild <= lastPos)
    {
        int smallchild = lChild;
        if (rChild <= lastPos)
        {
            if (aLTb(this->elements[lChild], this->elements[rChild]))
                smallchild = lChild;
            else
                smallchild = rChild;
        }

        if (aLTb(this->elements[smallchild], this->elements[position]))
        {
            this->swap(smallchild, position);
            reheapDown(smallchild);
        }
    }
}

template <class T>
int Heap<T>::getItem(T item)
{
    int foundIdx = -1;
    for (int idx = 0; idx < this->count; idx++)
    {
        if (compare(elements[idx], item) == 0)
        {
            foundIdx = idx;
            break;
        }
    }
    return foundIdx;
}

template <class T>
void Heap<T>::removeInternalData()
{
    if (this->deleteUserData != nullptr)
        deleteUserData(this); //clear users's data if they want
    delete[] elements;
}

template <class T>
void Heap<T>::copyFrom(const Heap<T> &heap)
{
    capacity = heap.capacity;
    count = heap.count;
    elements = new T[capacity];
    this->comparator = heap.comparator;
    this->deleteUserData = heap.deleteUserData;

    //Copy items from heap:
    for (int idx = 0; idx < heap.size(); idx++)
    {
        this->elements[idx] = heap.elements[idx];
    }
}

#endif /* HEAP_H */
