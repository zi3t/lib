/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayListSE.h
 *
 * Created on 31 August 2020, 16:01
 */

#ifndef SORTING_XARRAYLISTSE_H_
#define SORTING_XARRAYLISTSE_H_

#include "list/XArrayList.h"
#include "sorting/QuickSort.h"

template<class T>
class XArrayListSE: public XArrayList<T>{
public:
    XArrayListSE(
            void (*removeData)(XArrayList<T>*) = nullptr,
            bool (*itemEQ)(T&, T&) = nullptr,
            ISort<T>* sortAlg = nullptr):
                XArrayList<T>(removeData, itemEQ){
                    
        useDefault = false;            
        if(sortAlg != nullptr) this->sortAlg = sortAlg;
        else{
            this->sortAlg = new QuickSort<T>(); //use QuickSort by default
            useDefault = true;
        }
    };
    ~XArrayListSE(){
        if(useDefault) delete this->sortAlg; //DO NOT delete the external sort-algorithm
    }
    
    void sort(int (*comparator)(T&,T&) = nullptr){
        sortAlg->sort(this->data, this->count, comparator);
    }
    
protected: 
    ISort<T>* sortAlg;
    bool useDefault;
};

#endif /* XARRAYLISTSE_H */

