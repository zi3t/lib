/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BubbleSortDemo.h
 *
 * Created on 23 August 2020, 17:16
 */

#ifndef SORTING_BUBBLESORTDEMO_H_
#define SORTING_BUBBLESORTDEMO_H_


#include "sorting/BubbleSort.h"
#include <iostream>
#include <iomanip>
using namespace std;

void BuubleSortDemo1(){
    int values[] = {45, 97, 12, 2, 39, 3, 37, 87};
    cout << left << setw(22) << "Before:";
    for(int idx=0; idx < 8; idx++){
        cout << values[idx] << ", ";
    }
    cout << endl;
    
    BubbleSort<int> sortAlg;
    sortAlg.sort(values, 8, &SortSimpleOrder<int>::compare4Ascending);
    
    cout << left << setw(22) << "After, Ascending:";
    for(int idx=0; idx < 8; idx++){
        cout << values[idx] << ", ";
    }
    cout << endl;
    
    sortAlg.sort(values, 8, &SortSimpleOrder<int>::compare4Desending);
    
    cout << left << setw(22) << "After, Descending:";
    for(int idx=0; idx < 8; idx++){
        cout << values[idx] << ", ";
    }
    cout << endl;
}

#endif /* BUBBLESORTDEMO_H */

