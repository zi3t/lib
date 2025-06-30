/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueueDemo.h
 *
 * Created on 10 September 2020, 16:51
 */

#ifndef STACKNQUEUE_QUEUEDEMO_H_
#define STACKNQUEUE_QUEUEDEMO_H_

#include "util/Point.h"
#include "stacknqueue/Queue.h"
#include <iostream>
#include <iomanip>


void queueDemo1(){
    Queue<int> queue;
    for(int i=0; i < 5; i++){
        queue.push(i);
    }
    queue.println();
    
    for(int i=-3; i < 10; i++){
        std::cout <<"value " << i <<  " : " << (queue.contains(i) ? "in queue" : "not in queue") << std::endl;
    }
}

void queueDemo2(){
    Queue<Point> queue;
    queue.push(Point(23.2f, 25.4f));
    queue.push(Point(24.6f, 23.1f));  
    
    queue.println();
    
    std::cout << queue.contains(Point(23.2f, 25.4f)) << std::endl;
    std::cout << queue.contains(Point(24.6f, 23.1f)) << std::endl;
    std::cout << queue.contains(Point(123.2f, 25.4f)) << std::endl;
    std::cout << queue.contains(Point(124.6f, 23.1f)) << std::endl;
}

std::std::string qPointPtr2Str(Point*& point){
    std::stringstream os;
    os << "("   << point->getX() << ", "
                << point->getY()
       << ")";
    return os.str();
}
void queueDemo3(){
    Queue<Point*> queue(&DLinkedList<Point*>::free, &Point::pointEQ);
    
    Point* p1 = new Point(23.2f, 25.4f);
    Point* p2 = new Point(24.6f, 23.1f);
    Point* p3 = new Point(123.2f, 25.4f);
    Point* p4 = new Point(124.6f, 23.1f);
    queue.push(p1);
    queue.push(p2);
    queue.push(p3);
    queue.push(p4);
    
    queue.println(&qPointPtr2Str);
    
    std::cout << queue.contains(new Point(23.2f, 25.4f)) << std::endl;
    std::cout << queue.contains(new Point(24.6f, 23.1f)) << std::endl;
    std::cout << queue.contains(new Point(123.2f, 25.4f)) << std::endl;
    std::cout << queue.contains(new Point(124.6f, 23.1f)) << std::endl;
    
    delete p1; delete p2; delete p3; delete p4;
}

#endif /* QUEUEDEMO_H */

