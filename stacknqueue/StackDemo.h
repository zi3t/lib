/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StackDemo.h
 *
 * Created on 20 August 2020, 07:49
 */

#ifndef STACKNQUEUE_STACKDEMO_H_
#define STACKNQUEUE_STACKDEMO_H_
#include "util/Point.h"
#include "stacknqueue/Stack.h"
#include <iostream>
#include <iomanip>


void stackDemo1(){
    Stack<int> stack;
    for(int i=0; i < 5; i++){
        stack.push(i);
    }
    stack.println();
    
    for(int i=-3; i < 10; i++){
        std::cout <<"value " << i <<  " : " << (stack.contains(i) ? "in stack" : "not in stack") << std::endl;
    }
}
void stackDemo2(){
    Stack<Point> stack;
    stack.push(Point(23.2f, 25.4f));
    stack.push(Point(24.6f, 23.1f));  
    
    stack.println();
    
    std::cout << stack.contains(Point(23.2f, 25.4f)) << std::endl;
    std::cout << stack.contains(Point(24.6f, 23.1f)) << std::endl;
    std::cout << stack.contains(Point(123.2f, 25.4f)) << std::endl;
    std::cout << stack.contains(Point(124.6f, 23.1f)) << std::endl;
}

std::std::string sPointPtr2Str(Point*& point){
    std::stringstream os;
    os << "("   << point->getX() << ", "
                << point->getY()
       << ")";
    return os.str();
}
void stackDemo3(){
    Stack<Point*> stack(&DLinkedList<Point*>::free, &Point::pointEQ);
    stack.push(new Point(23.2f, 25.4f));
    stack.push(new Point(24.6f, 23.1f));  
    
    Point* p1 = new Point(23.2f, 25.4f);
    Point* p2 = new Point(24.6f, 23.1f);
    Point* p3 = new Point(123.2f, 25.4f);
    Point* p4 = new Point(124.6f, 23.1f);
    stack.println(&sPointPtr2Str);
    
    std::cout << stack.contains(new Point(23.2f, 25.4f)) << std::endl;
    std::cout << stack.contains(new Point(24.6f, 23.1f)) << std::endl;
    std::cout << stack.contains(new Point(123.2f, 25.4f)) << std::endl;
    std::cout << stack.contains(new Point(124.6f, 23.1f)) << std::endl;
    
    delete p1; delete p2; delete p3; delete p4;
}

#endif /* STACKDEMO_H */

