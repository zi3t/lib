/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ISort.h
 *
 * Created on 23 August 2020, 16:20
 */

#ifndef SORTING_ISORT_H_
#define SORTING_ISORT_H_

template<class T>
class ISort{
public:
    virtual void sort(T array[], int size, int (*comparator)(T&,T&) =0) = 0;
    virtual ~ISort(){};
};

template<class T>
class SortSimpleOrder{
public:
    static int compare4Ascending(T& lhs, T& rhs){
        if(lhs < rhs) return -1;
        else if(lhs > rhs) return +1;
        else return 0;
    }
    static int compare4Desending(T& lhs, T& rhs){
        if(lhs < rhs) return +1;
        else if(lhs > rhs) return -1;
        else return 0;
    }
};
#endif /* ISORT_H */

