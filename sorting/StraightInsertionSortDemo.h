/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StraightInsertionSortDemo.h
 *
 * Created on 23 August 2020, 16:26
 */

#ifndef SORTING_STRAIGHTINSERTIONSORTDEMO_H_
#define SORTING_STRAIGHTINSERTIONSORTDEMO_H_

#include "sorting/StraightInsertionSort.h"
#include <iostream>
#include <iomanip>


void straightSDemo1(){
    int values[] = {45, 97, 12, 2, 39, 3, 37, 87};
    std::cout << std::left << std::setw(22) << "Before:";
    for(int idx=0; idx < 8; idx++){
        std::cout << values[idx] << ", ";
    }
    std::cout << std::endl;
    
    StraightInsertionSort<int> sortAlg;
    sortAlg.sort(values, 8, &SortSimpleOrder<int>::compare4Ascending);
    
    std::cout << std::left << std::setw(22) << "After, Ascending:";
    for(int idx=0; idx < 8; idx++){
        std::cout << values[idx] << ", ";
    }
    std::cout << std::endl;
    
    sortAlg.sort(values, 8, &SortSimpleOrder<int>::compare4Desending);
    
    std::cout << std::left << std::setw(22) << "After, Descending:";
    for(int idx=0; idx < 8; idx++){
        std::cout << values[idx] << ", ";
    }
    std::cout << std::endl;
}


#endif /* STRAIGHTINSERTIONSORTDEMO_H */

