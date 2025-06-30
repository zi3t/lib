/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 *
 * Created on 19 August 2020, 22:01
 */

#ifndef STACKNQUEUE_STACK_H_
#define STACKNQUEUE_STACK_H_

#include "list/DLinkedList.h"
#include "stacknqueue/IDeck.h"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

template<class T>
class Stack: public IDeck<T>{
public:
    class Iterator; //forward declaration
    
protected:
    DLinkedList<T> list; //internal list
    void (*deleteUserData)(DLinkedList<T>*); //function pointer: be called to remove items (if they are pointer type)
    bool (*itemEqual)(T& lhs, T& rhs); //function pointer: test if two items (type: T&) are equal or not
    
public:
    Stack(  void (*deleteUserData)(DLinkedList<T>*) = nullptr,
            bool (*itemEqual)(T&, T&) = nullptr){
        this->itemEqual = itemEqual;
        this->deleteUserData = deleteUserData;
    }
    void push(T item){
        list.add(0,item);
    }
    T pop(){
        if(list.empty()) throw Underflow("Stack");
        return list.removeAt(0);
    }
    T& peek(){
        if(list.empty()) throw Underflow("Stack");
        return list.get(0);
    }
    bool empty(){
        return list.empty();
    }
    int size(){
        return list.size();
    }
    void clear(){
        list.clear();
    }
    bool remove(T item){
        return list.removeItem(item);
    }
    bool contains(T item){
        return list.contains(item);
    }
    string  toString(string (*item2str)(T&) = nullptr ){
        stringstream os;
        os << "FROM TOP: " << list.toString(item2str);
        return os.str();
    }
    void println(string (*item2str)(T&) = nullptr ){
        cout << toString(item2str) << endl;
    }
    ///
    Iterator top(){
        return Iterator(this, true);
    }
    Iterator bottom(){
        return Iterator(this, false);
    }
    
    
private:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T& )){
        if(itemEqual == nullptr) return lhs == rhs;
        else return itemEqual(lhs, rhs);
    }
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
    
public:
    
//Iterator: BEGIN
    class Iterator{
    private:
        Stack<T>* stack;
        typename DLinkedList<T>::Iterator listIt;
    public:
        Iterator(Stack<T>* stack = nullptr, bool begin=true){
            this->stack = stack;
            if(begin){
                if(stack != nullptr) this->listIt = stack->list.begin();
                else this->listIt = nullptr;
            }
            else{
                if(stack != nullptr) this->listIt = stack->list.end();
                else this->listIt = nullptr;
            }
        }
        Iterator& operator=(const Iterator& iterator ){
            this->stack = iterator.stack;
            this->listIt = iterator.listIt;
            return *this;
        }
        
        T& operator*(){
            return *(this->listIt);
        }
        bool operator!=(const Iterator& iterator){
            return this->listIt != iterator.listIt;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            listIt++;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
        void remove(void (*removeItem)(T) = nullptr){
            listIt.remove(removeItem);
        }
    };
    //Iterator: END
};


#endif /* STACK_H */

