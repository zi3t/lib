/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IBST.h
 *
 * Created on 20 August 2020, 15:05
 */

#ifndef TREE_IBST_H_
#define TREE_IBST_H_
#include <memory>
#include <string>


#include "list/DLinkedList.h"
/* 
 * K: KeyType: required supporting operator "less-than: <"; can be:
 *   + Primitive types: int, float, double
 *   + Class Type: Point, Student (must override operator:"<")
 * V: Value Type: must be a pointer type
 *    For example: int*, Point*
 */
template<class K, class V>
class IBST{
public:
    virtual void add(K key, V value = {}) = 0;
    
    /**
     * 
     * @param key: key want to remove
     * @param success: if users do not want checking removals success or not, leave it default (null)
     otherwise: pass a pointer to a boolean variable to receive the result.
     WHY success is a pointer to boolean (instead of a reference type) => make this param is optional!
     * 
     * @return value (a pointer type) stored in the tree
     */
    virtual V remove(K key, bool* success = nullptr) = 0;
    virtual V search(K key, bool& found)=0;
    virtual int size()=0;
    virtual int height()=0;
    virtual void clear()=0;
    virtual bool empty()=0;
    virtual DLinkedList<V> ascendingList()=0;
    virtual DLinkedList<V> descendingList()=0;
    virtual std::string toString(std::string (*entry2str)(K&, V&) = nullptr, bool avl=false) = 0;
};


#endif /* IBST_H */
