/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XArrayListTest.h
 *
 * Created on 27 August 2020, 05:38
 */

#ifndef TEST_XARRAYLISTTEST_H_
#define TEST_XARRAYLISTTEST_H_

#include "doctest.h"
#include "list/XArrayList.h"
#include "util/Point.h"


//////////////////////////////////////////////////////////////////////
///////////////// XArrayList + Primitive Data Type //////////////////
//////////////////////////////////////////////////////////////////////

TEST_CASE( "XArrayList<int>[1]: adding items" ) {
    XArrayList<int> list;
    REQUIRE( list.size() == 0 );
    int size = 10;
    
 
    SUBCASE("Adding with add(item)"){
        for(int idx=0; idx < size; idx++){
            list.add(idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == idx);
        }
    }
    
    SUBCASE("Adding with add(index:0, item)"){
        for(int idx=0; idx < size; idx++){
            list.add(0, idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == (size - 1 -idx) );
        }
    }
    SUBCASE("Adding with add(index:size(), item)"){
        for(int idx=0; idx < size; idx++){
            list.add(list.size(), idx);
        }
        REQUIRE( list.size() == 10 );
        
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == idx );
        }
    }
    SUBCASE("Adding with add(index:any, item)"){
        int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
        //                0   1   2   3   4   5   6    7
        int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
        int expvalues[]= {8,  15, 2,  4,  7, 10,  40,  6}; 
        for(int idx=0; idx < 8; idx++){
            list.add(index[idx], values[idx]);
        }
        REQUIRE( list.size() == 8 );
        
        for(int idx=0; idx < 8; idx++){
            REQUIRE(list.get(idx) == expvalues[idx]);
        }
    }
}

TEST_CASE( "XArrayList<int>[2]: reading items" ) {
    XArrayList<int> list;
    REQUIRE( list.size() == 0 );
    
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    REQUIRE( list.size() == 10 );

    SUBCASE("Reading: for-loop + integer index"){
        REQUIRE( list.size() == 10 );
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.get(idx) == idx);
        }
    }
    
    SUBCASE("Reading: for-loop + iterator++"){
        REQUIRE( list.size() == 10 );
        
        XArrayList<int>::Iterator it;
        int expvalue = 0;
        for(it = list.begin(); it != list.end(); it++){
            REQUIRE(*it == expvalue);
            expvalue += 1;
        }
    }
    SUBCASE("Reading: for-loop + iterator++"){
        REQUIRE( list.size() == 10 );
        
        XArrayList<int>::Iterator it;
        int expvalue = 0;
        for(it = list.begin(); it != list.end(); ++it){
            REQUIRE(*it == expvalue);
            expvalue += 1;
        }
    }
    
    SUBCASE("Reading: while-loop + iterator"){
        REQUIRE( list.size() == 10 );
        
        XArrayList<int>::Iterator it;
        int expvalue = 0;
        it = list.begin();
        while(it != list.end()){
            REQUIRE(*it == expvalue);
            expvalue += 1;
            
            it++;
        }
    }
}

TEST_CASE( "XArrayList<int>[3]: removing items with removeAt") {
    XArrayList<int> list;
    REQUIRE( list.size() == 0 );
    
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    REQUIRE( list.size() == size );
    
    SUBCASE("removeAt: check size-1"){
        int count = size;
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.removeAt(0) == idx);
            count--;
            REQUIRE( list.size() == count );
        }
        
        try{
            list.removeAt(0);
        }
        catch(std::out_of_range e){
            REQUIRE( 1 == 1 ); //pass
            e.what();
        }
    }
    
    SUBCASE("removeAt: check size-2"){
        int count = size;
        for(int idx=0; idx < size; idx++){
            list.removeAt(list.size() - 1);
            count--;
            REQUIRE( list.size() == count );
        }
        try{
            list.removeAt(0);
        }
        catch(std::out_of_range e){
            REQUIRE( 1 == 1 ); //pass
            e.what();
        }
    }
    SUBCASE("removeAt: check size-3, empty, clear"){
        int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
        //                0    1    2    3   4   5    6    7
        int index[]    = {0,   1,   5,   3,  2,  1,   1,   0};
        
        /*                10,  15,  2,   6,  4,  7,   40,  8 //initial list
         *                15,  2,   6,   4,  7,  40,  8      //after removeAt 0
         *                15,  6,   4,   7,  40, 8      //after removeAt 1
         *                15,  6,   4,   7,  40   //after removeAt 5
         *                15,  6,   4,   40   //after removeAt 3
         *                15,  6,   40   //after removeAt 2
         *                15,  40   //after removeAt 1
         *                15,   //after removeAt 1
         *                {}  //after removeAt 0
         */
        int expvalues[][8]= {
            {15,  2,   6,   4,  7,  40,  8},
            {15,  6,   4,   7,  40, 8},
            {15,  6,   4,   7,  40},
            {15,  6,   4,   40 },
            {15,  6,   40},
            {15,  40},
            {15},
            {}
        };
        
        list.clear();
        REQUIRE( list.size() == 0 );
        REQUIRE( list.empty() == true );
        //
        for(int idx=0; idx < 8; idx++)
            list.add(values[idx]);
        REQUIRE( list.size() == 8 );
        
        //removeAt:
        int count = 8;
        for(int idx=0; idx < 8; idx++){
            int idxRemoved = index[idx];
            int rs = list.removeAt(idxRemoved);
            REQUIRE( list.size() == (count - idx -1) );
            //check expected values
            for(int c=0; c < (count - idx -1); c++ ){
                int exp = expvalues[idx][c];
                REQUIRE(exp == list.get(c));
            }
        }
    }
}
TEST_CASE( "XArrayList<int>[4]: removing items with removeItem") {
    XArrayList<int> list;
    REQUIRE( list.size() == 0 );
    
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    REQUIRE( list.size() == size );
    
    SUBCASE("removeItem: check size-1"){
        int count = size;
        bool rem;
        
        for(int idx=0; idx < size; idx++){
            rem = list.removeItem(idx);
            count--;
            REQUIRE( rem == true );
            REQUIRE( list.size() == count );
        }
        rem = list.removeItem(100);
        REQUIRE( rem == false );
    }
    
    SUBCASE("removeItem: then indexOf"){
        int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
        bool rem;
        
        list.clear();
        REQUIRE( list.size() == 0 );
        
        for(int idx=0; idx < 8; idx++) list.add(values[idx]);
        REQUIRE( list.indexOf(10) == 0 );
        REQUIRE( list.indexOf(15) == 1 );
        REQUIRE( list.indexOf(8) == 7 );
        REQUIRE( list.indexOf(7) == 5 );
           
        rem = list.removeItem(10);
        REQUIRE( rem == true );
        REQUIRE( list.contains(10) == false );
        REQUIRE( list.indexOf(10) == -1 );
        
        rem = list.removeItem(8);
        REQUIRE( rem == true );
        REQUIRE( list.contains(8) == false );
        REQUIRE( list.indexOf(8) == -1 );
        
        rem = list.removeItem(7);
        REQUIRE( rem == true );
        REQUIRE( list.contains(7) == false );
        REQUIRE( list.indexOf(7) == -1 );
    }
}

TEST_CASE( "XArrayList<int>[3]: add/removeX/indexOf/contains") {
    XArrayList<int> list;
    REQUIRE( list.size() == 0 );
    
    SUBCASE("add: then indexOf"){
        int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
        for(int idx=0; idx < 8; idx++) list.add(values[idx]);
        int index = 0;
        for(int idx=0; idx < 8; idx++){
            REQUIRE( list.contains(values[idx])  == true);
            REQUIRE( list.indexOf(values[idx])  == index++);
        }
        list.removeItem(8);
        REQUIRE( list.size() == 7 );
        REQUIRE( list.contains(8)  == false);
        REQUIRE( list.indexOf(8)  == -1);
        list.add(100);
        REQUIRE( list.size() == 8);
        REQUIRE( list.contains(100)  == true);
        REQUIRE( list.indexOf(100)  == 7);
    }
}


TEST_CASE( "XArrayList<int>[3]: query info") {
    XArrayList<int> list;
    REQUIRE( list.empty() == true );
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    REQUIRE( list.empty() == false );
    REQUIRE( list.size() == size );
    
    SUBCASE("Using indexOf"){
        REQUIRE( list.indexOf(100) == -1 );
        for(int idx=0; idx < size; idx++){
            REQUIRE( list.indexOf(idx) == idx );
        }
        list.add(100);
        REQUIRE( list.indexOf(100) == size );
        
        list.removeItem(100);
        REQUIRE( list.indexOf(100) == -1 );
    }
    SUBCASE("Using contains"){
        REQUIRE( list.contains(100) == false );
        for(int idx=0; idx < size; idx++){
            REQUIRE( list.contains(idx) == true );
        }
        list.add(100);
        REQUIRE( list.contains(100) == true );
        
        list.removeItem(100);
        REQUIRE( list.contains(100) == false );
    }
    SUBCASE("Using empty"){
        for(int idx=0; idx < size; idx++){
            list.removeAt(0);
        }
        REQUIRE( list.empty() == true );
    }
    SUBCASE("Using clear"){
        list.clear();
        REQUIRE( list.empty() == true );
        
        list.add(100);
        list.add(200);
        REQUIRE( list.empty() == false );
        REQUIRE( list.size() == 2 );
        REQUIRE( list.contains(100) == true );
        REQUIRE( list.contains(200) == true );
        REQUIRE( list.contains(300) == false );
        REQUIRE( list.indexOf(100) == 0 );
        REQUIRE( list.indexOf(200) == 1 );
        REQUIRE( list.indexOf(300) == -1 );
    }
}

TEST_CASE( "XArrayList<int>[3]: using iterator") {
    XArrayList<int> list;
    REQUIRE( list.empty() == true );
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    REQUIRE( list.empty() == false );
    REQUIRE( list.size() == size );
    
    //////////////////////////////////////////////////////////////////////
    SUBCASE("Iteration with for-loop"){
        XArrayList<int>::Iterator it;
        int v = 0;
        for(it = list.begin(); it != list.end(); it++){
            int value = *it;
            REQUIRE( value == v );
            v += 1;
        }
    }
    SUBCASE("Iteration with for-loop: for removing data"){
        XArrayList<int>::Iterator it;
        int v = 0;
        for(it = list.begin(); it != list.end(); it++){
            int value = *it;
            if(value % 2 == 1) it.remove(); //remove odd number
        }
        REQUIRE( list.size() == 5); //0,2,4,6,8
        
        int expvalues[] = {0,2,4,6,8};
        for(int idx=0; idx < 5; idx++){
            REQUIRE( list.get(idx) == expvalues[idx]); 
        }
    }
    SUBCASE("Iteration with while"){
        XArrayList<int>::Iterator it = list.begin();
        int v = 0;
        while(it != list.end()){
            int value = *it;
            REQUIRE( value == v );
            v += 1;
            
            //always have:
            it++;
        }
    }
    
}
//////////////////////////////////////////////////////////////////////
///////////////// XArrayList + Class Data Type //////////////////////
//////////////////////////////////////////////////////////////////////

TEST_CASE( "XArrayList<Point>[1]: adding" ) {
    XArrayList<Point> list(0, &Point::pointEQ);
    Point array[] = {
        Point(0,0), Point(1,1), Point(2,2), Point(3,3)
    };
    int size = 4;
    for(int idx=0; idx < size; idx++){
        list.add( array[idx]);
    }
    REQUIRE( list.size() == size );
    //////////////////////////////////////////
    
    SUBCASE("Using get()"){
        for(int idx=0; idx < size; idx++){
            Point p = list.get(idx);
            REQUIRE(p.getX() == idx);
            REQUIRE(p.getY() == idx);
        }
    }
    SUBCASE("Using indexOf()"){
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.indexOf(array[idx]) == idx);
        }
    }
    SUBCASE("Using removeItem()"){
        REQUIRE(list.empty() == false);
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.removeItem(array[idx]) == true);
        }
        REQUIRE(list.empty() == true);
    }
    
    SUBCASE("Using contains()"){
        REQUIRE(list.empty() == false);
        for(int idx=0; idx < size; idx++){
            REQUIRE(list.contains(array[idx]) == true);
        }
        REQUIRE(list.contains(Point(1, 5)) == false);
    }
    
}

TEST_CASE( "XArrayList<Point>:[2]") {
    XArrayList<Point> list;
    int size = 10;
    Point* head = Point::genPoints(size, -10, 10);
    for(int idx=0; idx < size; idx++){
        list.add( head[idx]);
    }
    
    REQUIRE( list.size() == size );
    for(int idx=0; idx < size; idx++){
        Point p = list.get(idx);
        REQUIRE(p.getX() == head[idx].getX());
        REQUIRE(p.getY() == head[idx].getY());
    }
    
    //Point::println(head, size);
    delete []head;
}


//////////////////////////////////////////////////////////////////////
///////////////// XArrayList + Class Data Type //////////////////////
//////////////////////////////////////////////////////////////////////

/*
 * To contain object pointer in list, programmer need pass to:
 * 1/ Function for removing user data, e.g., &XArrayList<Point*>::free
 * 2/ Function for comparing two user data, e.g., &Point::pointPtrEQ
 * See how to create a list:
 *  XArrayList<Point*> list(&XArrayList<Point*>::free, &Point::pointPtrEQ);
 */

void removeItemDataX(Point* p){
    delete p;
}

TEST_CASE( "XArrayList<Point*>:[2]" ) {
    XArrayList<Point*> list(&XArrayList<Point*>::free, &Point::pointEQ);
    REQUIRE( list.size() == 0 );
    list.add(new Point(1,1));
    list.add(new Point(2,2));
    list.add(new Point(3,3));
    REQUIRE( list.size() == 3 );
    
    SUBCASE("Using indexOf"){
        Point *p = new Point(10,10);
        REQUIRE( list.indexOf(p) == -1 ); delete p;
        
        p = new Point(1,1);
        REQUIRE( list.indexOf(p) == 0 ); delete p;
        
        p = new Point(2,2);
        REQUIRE( list.indexOf(p) == 1 ); delete p;
        
        p = new Point(3,3);
        REQUIRE( list.indexOf(p) == 2 ); delete p;
    }
    SUBCASE("Using removeItem"){
        Point *p = new Point(10,10);
        REQUIRE( list.indexOf(p) == -1 ); delete p;
        
        p = new Point(1,1);
        REQUIRE( list.removeItem(p, &removeItemDataX) == true ); delete p;
        REQUIRE( list.size() == 2 );
        
        
        p = new Point(2,2);
        REQUIRE( list.removeItem(p, &removeItemDataX) == true ); delete p;
        REQUIRE( list.size() == 1 );
        
        //Left one item will be delete by: XArrayList<Point*>::free
    }
}

#endif /* XARRAYLISTTEST_H */

