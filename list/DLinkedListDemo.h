/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListDemo.h
 *
 * Created on 19 August 2020, 21:34
 */

#ifndef LIST_DLINKEDLISTDEMO_H_
#define LIST_DLINKEDLISTDEMO_H_

#include "list/DLinkedList.h"
#include "util/Point.h"
#include <iostream>
#include <iomanip>


void dlistDemo1(){
    List<int> dlist;
    for(int i = 0; i< 20 ; i++)
        dlist.add(i, i*i);
    dlist.println();
    
    for(List<int>::Iterator it=dlist.begin(); it != dlist.end(); it++ )
        std::cout << *it << " ";
    std::cout << std::endl;
}
void dlistDemo2(){
    DLinkedList<Point*> list1(&DLinkedList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));  
    list1.add(new Point(12.5f, 22.3f)); 
    
    for(DLinkedList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        std::cout << **it << std::endl;
    
    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    std::cout << *p1 << "=> " << (list1.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list1.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p2) << std::endl;
    
    ///Different results if not pass &Point::equals
    std::cout << std::endl << std::endl;
    DLinkedList<Point*> list2(&DLinkedList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));  
    list2.add(new Point(12.5f, 22.3f)); 
    
    for(DLinkedList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        std::cout << **it << std::endl;
    
    std::cout << *p1 << "=> " << (list2.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p1) << std::endl;
    std::cout << *p2 << "=> " << (list2.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p2) << std::endl;
    
    delete p1; delete p2;
}

void dlistDemo3(){
    DLinkedList<Point> dList;
    dList.add(Point(1.5, 3.5));
    dList.add(Point(2.5, 4.5));
    dList.add(Point(1.6, 3.1));
    
    std::cout << "test for indexOf: " << std::endl;
    Point p(1.6, 3.1);
    std::cout << p << " at: " << dList.indexOf(p);
}
bool pointComparator(Point*& p1, Point*& p2){
    return (p1->getX() == p2->getX()) && (p1->getY() == p2->getY());
}
std::string LpointPtr2Str(Point*& ptr){
    std::stringstream os;
    os << "("   << ptr->getX() << ", " 
                << ptr->getY()
       << ")";
    return os.str();
}
void dlistDemo4(){
    DLinkedList<Point*> dList(&DLinkedList<Point*>::free, &pointComparator);
    dList.add(new Point(1.5, 3.5));
    dList.add(new Point(2.5, 4.5));
    dList.add(new Point(1.6, 3.1));
    dList.println(&LpointPtr2Str);
    
    std::cout << "test for indexOf: " << std::endl;
    Point* p = new Point(1.6, 3.1);
    std::cout << *p << " at: " << dList.indexOf(p) << std::endl;
    delete p;
}
void dlistDemo5(){
    DLinkedList<float> dList;
    dList.add(3.2);
    dList.add(5.5);
    dList.println();
    std::cout << "index of 5.5: " << dList.indexOf(5.5) << std::endl;
    std::cout << "index of 15.5: " << dList.indexOf(15.5) << std::endl;
}

void dlistDemo6(){
    List<int> list;
    for(int i = 0; i< 10 ; i++)
        list.add(i, i*i);
    
    std::cout << std::setw(25) << std::left << "Original list: ";
    list.println();
    
    //
    int& item = list.get(5);
    item = 999;
    std::cout << std::setw(25) << std::left << "After changing an item: ";
    list.println();
}

#endif /* DLINKEDLISTDEMO_H */

