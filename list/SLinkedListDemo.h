/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedListDemo.h
 *
 * Created on 19 August 2020, 21:16
 */

#ifndef LIST_SLINKEDLISTDEMO_H_
#define LIST_SLINKEDLISTDEMO_H_

#include "SLinkedList.h"
#include "util/Point.h"
#include <iostream>
#include <iomanip>


void slistDemo1(){
    SLinkedList<int> slist;
    for(int i = 0; i< 20 ; i++)
        slist.add(i*i);
    slist.println();
}
void slistDemo2(){
    SLinkedList<Point*> list1(&SLinkedList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));  
    list1.add(new Point(12.5f, 22.3f)); 
    
    for(SLinkedList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        std::cout << **it << std::endl;
    
    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    std::cout << *p1 << "=> " << (list1.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list1.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p2) << std::endl;
    
    ///Different results if not pass &Point::equals
    std::cout << std::endl << std::endl;
    SLinkedList<Point*> list2(&SLinkedList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));  
    list2.add(new Point(12.5f, 22.3f)); 
    
    for(SLinkedList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        std::cout << **it << std::endl;
    
    std::cout << *p1 << "=> " << (list2.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list2.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p2) << std::endl;
    
    delete p1; delete p2;
}

#endif /* SLINKEDLISTDEMO_H */

