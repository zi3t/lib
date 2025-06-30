/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IHeap.h
 *
 * Created on 22 August 2020, 07:54
 */

#ifndef HEAP_IHEAP_H_
#define HEAP_IHEAP_H_
#include <string>


template<class T>
class IHeap {
public:
    virtual ~IHeap(){};
    virtual void push(T item)=0;
    virtual T pop()=0;
    virtual const T peek()=0;
    virtual void remove(T item, void (*removeItemData)(T)=nullptr)=0;
    virtual bool contains(T item)=0;
    virtual int size()=0;
    virtual void heapify(T array[], int size)=0; //build heap from array having size items
    virtual void clear()=0;
    virtual bool empty()=0;
    virtual std::string toString(std::string (*item2str)(T&)=nullptr)=0;
};


#endif /* IHEAP_H */

