/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListSE.h
 *
 * Created on 31 August 2020, 21:00
 */

#ifndef SORTING_SLINKEDLISTSE_H_
#define SORTING_SLINKEDLISTSE_H_

#include "list/SLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class SLinkedListSE: public SLinkedList<T>{
public:
    
    SLinkedListSE(
            void (*removeData)(SLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            SLinkedList<T>(removeData, itemEQ){
        
    };
    void sort(int (*comparator)(T&,T&)=0){
        if(this->count > 0){
            typename SLinkedList<T>::Node* first = this->head->next; //first user's data
            this->tail->next->next = nullptr; //to tail => to nullptr
            mergeSort(first, comparator);
            
            //find the last user's data
            typename SLinkedList<T>::Node* last = first;
            while(last->next != nullptr) last = last->next;
            
            //attach to head&tail of the list
            last->next = this->tail;
            this->tail->next = last;
            this->head->next = first;
        }
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&) = nullptr){
        if(comparator != nullptr) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
    void mergeSort(typename SLinkedList<T>::Node*& head, int (*comparator)(T&,T&) = nullptr){
        if((head != nullptr) && (head->next != nullptr)){
            typename SLinkedList<T>::Node* second;
            devide(head, second);
            mergeSort(head, comparator);
            mergeSort(second, comparator);
            merge(head, second, comparator);
        }
    };
    void devide(typename SLinkedList<T>::Node*& first, typename SLinkedList<T>::Node*& second){
         typename SLinkedList<T>::Node *midpoint = first;
        typename SLinkedList<T>::Node *last = first->next;
        while (last != nullptr)
        {
            last = last->next;
            if (last != nullptr)
            {
                last = last->next;
                midpoint = midpoint->next;
            }
        }
        second = midpoint->next;
        midpoint->next = 0;
    }
    void merge(typename SLinkedList<T>::Node*& first, typename SLinkedList<T>::Node*& second, int (*comparator)(T&,T&)=0){
        typename SLinkedList<T>::Node combined;
        typename SLinkedList<T>::Node *lastSorted = &combined;
        while ((first != nullptr) && (second != nullptr))
        {
            if (compare(first->data, second->data, comparator) <= 0)
            {
                lastSorted->next = first;
                lastSorted = first;
                first = first->next;
            }
            else
            {
                lastSorted->next = second;
                lastSorted = second;
                second = second->next;
            }
        }
        if (first == nullptr)
        {
            lastSorted->next = second;
            second = nullptr;
        }
        else
            lastSorted->next = first;

        first = combined.next;
    }
};

#endif /* SLINKEDLISTSE_H */

