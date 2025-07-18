/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BubbleSort.h
 *
 * Created on 23 August 2020, 17:16
 */

#ifndef SORTING_BUBBLESORT_H_
#define SORTING_BUBBLESORT_H_

#include "sorting/ISort.h"

template <class T>
class BubbleSort : public ISort<T>
{
public:
    void sort(T array[], int size, int (*comparator)(T &, T &))
    {
        int walker;
        int current = 0;
        bool flag = false;
        while ((current < size) && (flag == false))
        {
            walker = size - 1;
            flag = true;
            while (walker > current)
            {
                if (comparator(array[walker], array[walker - 1]) < 0)
                {
                    flag = false;
                    T temp = array[walker];
                    array[walker] = array[walker - 1];
                    array[walker - 1] = temp;
                }
                walker -= 1;
            }
            current += 1;
        }
    }
};

#endif /* BUBBLESORT_H */
