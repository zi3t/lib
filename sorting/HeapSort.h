/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapSort.h
 *
 * Created on 14 September 2020, 18:10
 */

#ifndef SORTING_HEAPSORT_H_
#define SORTING_HEAPSORT_H_
#include "sorting/ISort.h"
#include "heap/Heap.h"

template<class T>
class HeapSort: private Heap<T>, public ISort<T>{
public:
    HeapSort(   int (*comparator)(T& , T&)=0, 
                void (*deleteUserData)(Heap<T>*)=0 ):
                Heap<T>(comparator, deleteUserData){
    }
    void sort(T array[], int size, int (*comparator)(T&,T&)=0){  
        Heap<T> minHeap(comparator);
        minHeap.heapify(array, size);
        for(int i = 0; i< size ; i++) array[i] = minHeap.pop();
    }         
                
};


#endif /* HEAPSORT_H */

