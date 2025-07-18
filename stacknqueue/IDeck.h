/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IDeck.h
 *
 * Created on 27 August 2020, 10:32
 */

#ifndef STACKNQUEUE_IDECK_H_
#define STACKNQUEUE_IDECK_H_

#include <string>
#include <sstream>
using std::string;
using std::stringstream;

class Underflow: public std::exception{
private:
    string desc;
public:
    Underflow(string desc){
        this->desc = desc;
    }
    const char * what () const throw (){
        stringstream os;
        os << "Underflow: " << this->desc;
        return os.str().c_str();
    }
};


template<class T>
class IDeck{
public:
    virtual void push(T item)=0;
    virtual T pop()=0;
    virtual T& peek()=0;
    virtual bool empty()=0;
    virtual int size()=0;
    virtual void clear()=0;
    virtual bool remove(T item)=0;
    virtual bool contains(T item)=0;
    virtual string toString(string (*item2str)(T&) = nullptr )=0;
};

#endif /* IDECK_H */

