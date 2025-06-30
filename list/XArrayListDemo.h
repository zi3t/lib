/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayListDemo.h
 *
 * Created on 19 August 2020, 21:05
 */

#ifndef LIST_XARRAYLISTDEMO_H_
#define LIST_XARRAYLISTDEMO_H_
#include "list/XArrayList.h"
#include "util/Point.h"
#include <iostream>
#include <iomanip>


void xlistDemo1(){
    XArrayList<int> iList;
    for(int i = 0; i< 10 ; i++)
        iList.add(i, i*i);
    
    //iList.dump();
    for(XArrayList<int>::Iterator it=iList.begin(); it != iList.end(); it++ )
        std::cout << *it << ", found at: " << iList.indexOf(*it) << std::endl;
    std::cout << std::endl;
    int item = 120;
    int foundIdx = iList.indexOf(item);
    std::cout    << "lookup for " << item  << " found at: " << foundIdx << std::endl;
}

void xlistDemo2(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));  
    alist.println();
}

void xlistDemo3(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));  
    
    int idx1 = alist.indexOf(Point(24.6f, 23.1f));
    int idx2 = alist.indexOf(Point(24.61f, 23.1f));
    
    std::cout << "result 1 : " << idx1 << std::endl;
    std::cout << "result 2 : " << idx2 << std::endl;
}

void xlistDemo4(){
    XArrayList<Point*> list1(&XArrayList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));  
    list1.add(new Point(12.5f, 22.3f)); 
    
    for(XArrayList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        std::cout << **it << std::endl;
    
    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    std::cout << *p1 << "=> " << (list1.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list1.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p2) << std::endl;
    
    ///Different results if not pass &Point::equals
    std::cout << std::endl << std::endl;
    XArrayList<Point*> list2(&XArrayList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));  
    list2.add(new Point(12.5f, 22.3f)); 
    
    for(XArrayList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        std::cout << **it << std::endl;
    
    std::cout << *p1 << "=> " << (list2.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list2.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p2) << std::endl;
    
    delete p1; delete p2;
}

#endif /* XARRAYLISTDEMO_H */

