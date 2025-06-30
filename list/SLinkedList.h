/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SLinkedList.h
 *
 * Created on 19 August 2020, 16:56
 */

#ifndef LIST_SLINKEDLIST_H_
#define LIST_SLINKEDLIST_H_

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>

template <class T> class SLinkedList;

template<class T>
class SLinkedList: public IList<T> {
public:
    class Iterator; //forward declaration
    class Node; //forward declaration
    
protected:
    Node *head; //this node does not contain user's data
    Node *tail; //this node does not contain user's data
    int  count;  //keep number of items stored in the list
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(SLinkedList<T>*);
    
public:
    SLinkedList(
            void (*deleteUserData)(SLinkedList<T>*)=nullptr, 
            bool (*itemEqual)(T&, T&)=nullptr);
    SLinkedList(const SLinkedList<T>& list);
    SLinkedList<T>& operator=(const SLinkedList<T>& list);
    ~SLinkedList();
    
    //Inherit from IList: BEGIN
    void    add(T e);
    void    add(int index, T e);
    T       removeAt(int index);
    bool    removeItem(T item, void (*removeItemData)(T)=nullptr);
    bool    empty();
    int      size();
    void    clear();
    T&      get(int index);
    int      indexOf(T item);
    bool    contains(T item);
    std::string  toString(std::string (*item2str)(T&)=nullptr );
    //Inherit from IList: BEGIN
    
    
    void println(std::string (*item2str)(T&)=nullptr ){
        std::cout << toString(item2str) << std::endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(SLinkedList<T>*) = nullptr){
        this->deleteUserData = deleteUserData;
    }

    Iterator begin(){
        return Iterator(this, true);
    }
    Iterator end(){
        return Iterator(this, false);
    }
    
    static void free(SLinkedList<T> *list){
        typename SLinkedList<T>::Iterator it = list->begin();
        while(it != list->end()){
            delete *it;
            it++;
        }
    }


protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T& )){
        if(itemEqual == nullptr) return lhs == rhs;
        else return itemEqual(lhs, rhs);
    }
    
    void copyFrom(const SLinkedList<T>& list);
    void removeInternalData();
       
//////////////////////////////////////////////////////////////////////
////////////////////////  INNER CLASSES DEFNITION ////////////////////
//////////////////////////////////////////////////////////////////////   
public:
    class Node{
    public:
        T data;
        Node *next;
    public:
        Node(Node *next=nullptr){
            this->next = next;
        }
        Node(T data, Node *next=nullptr){
            this->data = data;
            this->next = next;
        }
    };
    
    //////////////////////////////////////////////////////////////////////
    //Iterator
    class Iterator{
    private:
        SLinkedList<T>* pList;
        Node* pNode;
        
    public:
        Iterator(SLinkedList<T>* pList=nullptr, bool begin=true){
            if(begin){
                if(pList !=nullptr) this->pNode = pList->head->next;
                else pNode = nullptr;
            }
            else{
                if(pList !=nullptr) this->pNode = pList->tail;
                else pNode = nullptr;
            }
            this->pList = pList;
        }
        
        Iterator& operator=(const Iterator& iterator){
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        /*
         * remove: slow, O(n), why?
         * while-loop can have n iterations
         * => Use DLinkedList when need a linked-list
         */
        void remove(void (*removeItemData)(T)=nullptr){
            Node* pCur = this->pList->head->next;
            Node* pPrev = this->pList->head;
            bool found = false;
            while(pCur != this->pList->tail){
                found = SLinkedList<T>::equals(pNode->data, pCur->data, pList->itemEqual);
                if(found){
                    //detach
                    pPrev->next = pCur->next;
                    if(pList->tail->next == pCur) pList->tail->next = pPrev; //update tail if needed
                    pList->count -= 1; //dec count in list
                    pCur->next = nullptr;

                    //remove users data + node :
                    if(removeItemData != nullptr) removeItemData(pCur->data);
                    delete pCur; 
                    
                    //prepare for next iteration, usually: it++
                    
                    this->pNode = pPrev;
                    
                    return;
                }
                
                //go next:
                pCur = pCur->next;
                pPrev = pPrev->next;
            }//while
        }
        
        T& operator*(){
            return pNode->data;
        }
        bool operator!=(const Iterator& iterator){
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            pNode = pNode->next;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
    
    };
};


//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
SLinkedList<T>::SLinkedList(
        void (*deleteUserData)(SLinkedList<T>*), 
        bool (*itemEqual)(T&, T&) ) {
    head = new Node();
    tail = new Node();
    head->next = tail; tail->next = head;
    count = 0;
    this->itemEqual = itemEqual;
    this->deleteUserData = deleteUserData;
}

template<class T>
void SLinkedList<T>::copyFrom(const SLinkedList<T>& list){
    //Initialize this list to the empty condition
    this->count = 0;
    this->head->next = this->tail; this->tail->next = this->head;

    //Copy pointers from "list"
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;

    //Copy data from "list"
    Node* ptr= list.head->next;
    while(ptr != list.tail){
        this->add(ptr->data);
        ptr = ptr->next;
    }
}

template<class T>
void SLinkedList<T>::removeInternalData(){
    //Remove user's data of this list
    if(deleteUserData != nullptr) deleteUserData(this);
    
    //Remove this list's data (i.e. Node)
    if((head != nullptr) & (tail != nullptr)){
        Node* ptr = head->next;
        while(ptr != tail){
            Node* next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }
}
    
template<class T>
SLinkedList<T>::SLinkedList(const SLinkedList<T>& list){
    //Initialize to the empty condition
    this->head = new Node();
    this->tail = new Node();
    copyFrom(list);
}

template<class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList<T>& list){
    removeInternalData();
    copyFrom(list);
            
    return *this;
}

template<class T>
SLinkedList<T>::~SLinkedList() {
    removeInternalData(); 
    
    if(head != nullptr) delete head;
    if(tail != nullptr) delete tail;
}

template<class T>
void SLinkedList<T>::add(T e) {
    Node* node = new Node(e, tail);
    tail->next->next = node;
    tail->next = node;
    count += 1;
}
template<class T>
void SLinkedList<T>::add(int index, T e) {
    if((index < 0) || (index > count))
        throw std::out_of_range("The index is out of range!");
    //index in [0, count]
    Node* newNode = new Node(e, nullptr);
    Node* prevNode = head;
    int cursor = -1;
    while(cursor < index -1){
        prevNode = prevNode->next;
        cursor +=1; 
    }
    Node* curNode = prevNode->next;
    prevNode->next = newNode;
    newNode->next = curNode;
    
    //Change tail->next if needed
    if(index == count)
        tail->next = newNode;
    count += 1;
}
template<class T>
T SLinkedList<T>::removeAt(int index){
    if((index < 0) || (index > count - 1))
        throw std::out_of_range("The index is out of range!");

    Node* prevNode = head;
    int cursor = -1;

    while(cursor < index -1){
        prevNode = prevNode->next;
        cursor += 1;
    }
    Node* curNode = prevNode->next;
    prevNode->next = curNode->next;
    curNode->next = nullptr;//delete the link between node curr and next  node
    if(index == count){
        tail->next = prevNode;
    }
    this->count -=1;
    return curNode->data;
}

template<class T>
bool SLinkedList<T>::removeItem(T item, void (*removeItemData)(T)){
    bool found = false;
    Node* pNode = head->next;
    Node* pPrev = head;
    while(pNode != tail){
        found = SLinkedList<T>::equals(pNode->data, item,this->itemEqual);
        if(found){
            pPrev->next = pNode->next;
            if(pNode->next == tail)
                tail->next = pPrev;
            pNode->next = nullptr;

            //remove data
            if(removeItemData != nullptr) removeItemData(pNode->data);
            delete pNode;
            this->count -=1;
            return true;
        }
        pNode = pNode->next;
        pPrev = pPrev->next;
    }
    return false;
}

template<class T>
bool SLinkedList<T>::empty(){
    if(!this->count) return true;
    return false;
}

template<class T>
int  SLinkedList<T>::size(){
    return this->count;
}

template<class T>
void SLinkedList<T>::clear(){
    removeInternalData();
    head->next = tail;
    tail->next = head;
    this->count = 0;
}

template<class T>
T& SLinkedList<T>::get(int index){
    if((index < 0) || (index > count - 1))
        throw std::out_of_range("The index is out of range!");
    Node* prevNode = head;
    int cursor = -1;
    while(cursor <index -1){
        prevNode = prevNode->next;
        cursor +=1;
    }
    return prevNode->next->data;
}

template<class T>
int  SLinkedList<T>::indexOf(T item){
    bool found = false;
    Node* pNode = head->next;
    int foundAt = 0;
    while(pNode != tail){
        found = SLinkedList<T>::equals(pNode->data, item, this->itemEqual);
        if(found)
            break;
        pNode = pNode->next;
        foundAt += 1;
    }
    if(found)
        return foundAt;
    else 
        return -1;
}
template<class T>
bool SLinkedList<T>::contains(T item){
    return indexOf(item) != -1;
}

template<class T>
std::string SLinkedList<T>::toString(std::string (*item2str)(T&) ){
     if(this->count <= 0) return "[]";
    
    std::stringstream itemos;
    Node* ptr = head->next;
    while(ptr != tail){
        if(item2str != nullptr) itemos << item2str(ptr->data) << ", ";
        else itemos << ptr->data << ", ";

        ptr = ptr->next;
    }
    //remove the last ", "
    std::string itemstr = itemos.str();
    itemstr = itemstr.substr(0, itemstr.rfind(','));
    return "[" + itemstr + "]";
}

#endif /* SLINKEDLIST_H */

