/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShellSortDemo.h
 *
 * Created on 23 August 2020, 16:45
 */

#ifndef SORTING_SHELLSORTDEMO_H_
#define SORTING_SHELLSORTDEMO_H_


#include "sorting/ShellSort.h"
#include <iostream>
#include <iomanip>



void ShellSortDemo1(){
    int values[] = {45, 97, 12, 2, 39, 3, 37, 87};
    std::cout << std::left << std::setw(22) << "Before:";
    for(int idx=0; idx < 8; idx++){
        std::cout << values[idx] << ", ";
    }
    std::cout << std::endl;
    
    int num_segments[] = {1, 3, 7};
    ShellSort<int> sortAlg(num_segments, 3);
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

#endif /* SHELLSORTDEMO_H */

