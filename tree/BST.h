/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BST.h
 *
 * Created on 20 August 2020, 15:31
 */

#ifndef TREE_BST_H_
#define TREE_BST_H_
#include "tree/IBST.h"
#include "tree/ITreeWalker.h"
#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"
#include <string>
#include <sstream>
#include <algorithm>
using std::string;

/*IMPOTANT: 
 *  >> Can change nEMPTY to another value
 *  >> CAN NOT change: nLH, nEH, and nRH
 *      :: Because, we define balance-factor = height(right subtree) - height(left subtree)
 */

#define nEMPTY 9
#define nLH -1
#define nEH  0
#define nRH +1
#define sEMPTY "EMPTY"
#define sLH "LH"
#define sEH "EH"
#define sRH "RH"


template<class K, class V>
class BST : public IBST<K,V>, public ITreeWalker<K, V>{
public:
    class Node; //forward declaration  
    class Entry; //forward declaration  
    
protected:
    int count;
    Node* pRoot;
    
public:
    BST();
    ~BST();
    void add(K key, V value = {});
    V remove(K key, bool* success = nullptr);
    V search(K key, bool& found); //return default value if not found
    int size();
    int height();
    void clear();
    DLinkedList<V> ascendingList();
    DLinkedList<V> descendingList();
    DLinkedList<V> dfs();
    DLinkedList<V> bfs();
    DLinkedList<K> bfsKey();
    DLinkedList<V> nlr();
    DLinkedList<V> lrn();
    DLinkedList<V> lnr();
    DLinkedList<V> select(K min, K max);
    bool empty(){
        return this->count == 0;
    }
    std::string toString(std::string (*entry2str)(K&, V&) = nullptr, bool avl=false){
        if(this->pRoot == nullptr) return "(NULL)";
        else return this->pRoot->toString(entry2str, avl);
    }
    void println(std::string (*entry2str)(K&, V&) = nullptr, bool avl=false){
        std::cout << toString(entry2str, avl) << std::endl;
    }
    
    
protected:
    Node* add(Node* pRoot, Entry data);
    Node* remove(Node* pRoot, K key, bool& success, V& retValue);
    V search(Node* pRoot, K key, bool& found);
    int height(Node* pRoot);
    void ascendingList(Node* pRoot, DLinkedList<V>& list);
    void descendingList(Node* pRoot, DLinkedList<V>& list);
    void nlr(Node* pRoot, DLinkedList<V>& list);
    void lrn(Node* pRoot, DLinkedList<V>& list);
    void lnr(Node* pRoot, DLinkedList<V>& list);
    void select(Node* pRoot, K min, K max, DLinkedList<V>& list);
    
    static void remove(Node* pRoot){
        if(pRoot == nullptr) return;
        if(pRoot->pLeft != nullptr) remove(pRoot->pLeft);
        if(pRoot->pRight != nullptr) remove(pRoot->pRight);
        delete pRoot;
    }
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
    
public:
    class Entry{
    public:
        K key; //primitive type
        V value; //pointer always
        friend class BST<K, V>;

    public:
        Entry(K key, V value = nullptr){
            this->key = key;
            this->value = value;
        }
        std::string toString(std::string (*entry2str)(K&,V&) = nullptr){
            if(entry2str != nullptr) return entry2str(key, value);
            else{
                std::stringstream entryos;
                if(value != nullptr)
                    entryos << "<" << key << ", " << *(value) << ">";
                else entryos << key;
                return entryos.str();
            }
        }
        bool operator==(Entry rhs){
            return this->key == rhs.key;
        }
    };

    class Node{
    public:
        static int LH, EH, RH, EMPTY;
        int bfactor; //not used in BST, be used in AVL
        int height_;
        Entry data;
        Node *pLeft, *pRight;
        
        friend class BST<K, V>;
    public:
        Node():data(0, nullptr){
            this->pLeft = nullptr;
            this->pRight = nullptr;
            this->bfactor = EMPTY;
            this->height_ = 1;
        }
        Node(Entry newdata, Node* pLeft = nullptr, Node* pRight = nullptr): data(newdata){
            this->pLeft = pLeft;
            this->pRight = pRight;
            this->bfactor = EH;
            this->height_ = 1;
        }
        ~Node(){
            if(data.value != nullptr) delete data.value;
        }
        void updateHeight(){
            int leftH = 0, rightH = 0;
            if(pLeft != nullptr) leftH = pLeft->height();
            if(pRight != nullptr) rightH = pRight->height();
            height_ = 1 + std::max(leftH, rightH);
            //
            bfactor = rightH - leftH;
        }
        int height(){ return height_; }
        
        bool isLH(){ return bfactor <= LH; }
        void markLH() { bfactor = LH; }
        bool isEH(){ return bfactor == EH; }
        void markEH() { bfactor = EH; }
        bool isRH(){ return bfactor >= RH; }
        void markRH() { bfactor = RH; }
        bool isBalanced(){ return (bfactor >= -1) && (bfactor <= +1); }
        std::string balance(){
            if(isLH()) return "LH ";
            else if(isEH()) return "EH ";
            else return "RH ";
        }

        std::string toString(std::string (*entry2str)(K&,V&) = nullptr, bool avl=false){
            std::stringstream nodestr;
            if(avl){
                if((pLeft == nullptr) && (pRight == nullptr))
                    nodestr << "[" << data.toString(entry2str) << ":" << balance() << "]";
                if((pLeft == nullptr) && (pRight != nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str) << ":" << balance() << "[.]" 
                            << pRight->toString(entry2str, avl)
                            << ")";
                if((pLeft != nullptr) && (pRight == nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str) << ":" << balance()
                            << pLeft->toString(entry2str, avl)
                            << "[.]"
                            << ")";
                if((pLeft != nullptr) && (pRight != nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str)  << ":" << balance()
                            << pLeft->toString(entry2str, avl)
                            << pRight->toString(entry2str, avl)
                            << ") ";
            }
            else{
                if((pLeft == nullptr) && (pRight == nullptr))
                    nodestr << "[" << data.toString(entry2str) << "]";
                if((pLeft == nullptr) && (pRight != nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str) << "[.]" 
                            << pRight->toString(entry2str)
                            << ")";
                if((pLeft != nullptr) && (pRight == nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str) 
                            << pLeft->toString(entry2str)
                            << "[.]"
                            << ")";
                if((pLeft != nullptr) && (pRight != nullptr))
                    nodestr << " (" 
                            << data.toString(entry2str) 
                            << pLeft->toString(entry2str)
                            << pRight->toString(entry2str)
                            << ") ";
            }
            return nodestr.str();
        }
    };
};

template<class K, class V>
int BST<K,V>::Node::LH = nLH;
template<class K, class V>
int BST<K,V>::Node::EH = nEH;
template<class K, class V>
int BST<K,V>::Node::RH = nRH;
template<class K, class V>
int BST<K,V>::Node::EMPTY = nEMPTY;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template<class K, class V>
BST<K, V>::BST() {
    count = 0;
    pRoot = nullptr;
}


template<class K, class V>
BST<K, V>::~BST() {
    remove(this->pRoot);
}


template<class K, class V>
void BST<K, V>::add(K key, V value) {
    this->pRoot = add(this->pRoot, Entry(key, value));
    this->count += 1;
}

template<class K, class V>
typename BST<K, V>::Node* BST<K, V>::
add(Node* pRoot, Entry data){
    if(pRoot == nullptr) return new BST<K, V>::Node(data, nullptr, nullptr);
    if(data.key < pRoot->data.key)
        pRoot->pLeft = this->add(pRoot->pLeft, data);
    else
        pRoot->pRight = this->add(pRoot->pRight, data);
    return pRoot;
}

template<class K, class V>
int BST<K, V>::size(){
    return count;
}


template<class K, class V>
V BST<K, V>::remove(K key, bool* success){
    V retValue{};
    bool success_;
    this->pRoot = remove(this->pRoot, key, success_, retValue);
    if(success_) this->count -= 1;
    if(success != nullptr) *success = success_;
    
    return retValue;
}


template<class K, class V>
typename BST<K, V>::Node*  BST<K, V>::
remove(Node* pRoot, K key, bool& success, V& retValue){
    if(pRoot == nullptr){
        success = false;
        return nullptr;
    }
    
    if(key < pRoot->data.key){
        pRoot->pLeft = remove(pRoot->pLeft, key, success, retValue);
        return pRoot;
    }
    else if(key > pRoot->data.key){
        pRoot->pRight = remove(pRoot->pRight, key, success, retValue);
        return pRoot;
    }
    else{
        //found at pRoot, delete pRoot
        if((pRoot->pLeft == nullptr) || (pRoot->pRight == nullptr)){
            Node* newRoot = ((pRoot->pLeft == nullptr)? pRoot->pRight: pRoot->pLeft);
            retValue = pRoot->data.value;
            success = true;

            pRoot->data.value = nullptr; // reset value pointer before deletion
            delete pRoot;
            
            return newRoot; 
        }
        else{
            //left & right: not null
            V backup = pRoot->data.value; //backup returned value (pRoot->data.value)
            
            Node* pLargestOnLeft = pRoot->pLeft;
            while(pLargestOnLeft->pRight != nullptr) pLargestOnLeft = pLargestOnLeft->pRight;
            pRoot->data = pLargestOnLeft->data; //replaced with the largest on left sub-tree
            pRoot->pLeft = remove(pRoot->pLeft, pLargestOnLeft->data.key, success, retValue);
            
            retValue = backup; //restore the backup to retValue
            return pRoot;
        }
    }
}

template<class K, class V>
V BST<K, V>::search(K key, bool& found){
    found = false;
    return search(this->pRoot, key, found);
}

template<class K, class V>
V BST<K, V>::search(Node* pRoot, K key, bool& found){
    if(pRoot == nullptr) return nullptr;
    if(key == pRoot->data.key) {
        //found
        found = true;
        return pRoot->data.value;
    }
    else if(key < pRoot->data.key){
        if(pRoot->pLeft == nullptr) return nullptr;
        else return search(pRoot->pLeft, key, found);
    }
    else{
        if(pRoot->pRight == nullptr) return nullptr;
        else return search(pRoot->pRight, key, found);
    }
}

template<class K, class V>
int BST<K, V>::height(){
    return height(pRoot);
}

template<class K, class V>
int BST<K, V>::height(Node* pRoot){
    if(pRoot == nullptr) return 0;
    else{
        int leftH = height(pRoot->pLeft);
        int rightH = height(pRoot->pRight);
        return 1 + (leftH > rightH ? leftH : rightH);
    }
}
template<class K, class V>
void BST<K, V>::clear(){
    remove(this->pRoot);
    this->pRoot = nullptr;
    this->count = 0;
}

template<class K, class V>
DLinkedList<V> BST<K, V>::ascendingList(){
    DLinkedList<V> list;
    ascendingList(pRoot, list);
    return list;
}

template<class K, class V>
void BST<K, V>::ascendingList(Node* pRoot, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    ascendingList(pRoot->pLeft, list);
    list.add(pRoot->data.value);
    ascendingList(pRoot->pRight, list);
}

template<class K, class V>
DLinkedList<V> BST<K, V>::descendingList(){
    DLinkedList<V> list;
    descendingList(pRoot, list);
    return list;
}

template<class K, class V>
void BST<K, V>::descendingList(Node* pRoot, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    descendingList(pRoot->pRight, list);
    list.add(pRoot->data.value);
    descendingList(pRoot->pLeft, list);
}

template<class K, class V>
DLinkedList<V> BST<K, V>::dfs(){
    DLinkedList<V> list;
    if(pRoot == nullptr) return list;
    
    Stack<Node*> stack;
    stack.push(pRoot);
    while(!stack.empty()){
        Node* pNode = stack.pop();
        list.add(pNode->data.value);
        if(pNode->pRight != nullptr) stack.push(pNode->pRight);
        if(pNode->pLeft != nullptr) stack.push(pNode->pLeft);
    }
    return list;
}

template<class K, class V>
DLinkedList<V> BST<K, V>::bfs(){
    DLinkedList<V> list;
    if(pRoot == nullptr) return list;
    
    Queue<Node*> queue;
    queue.push(pRoot);
    while(!queue.empty()){
        Node* pNode = queue.pop();
        list.add(pNode->data.value);
        if(pNode->pLeft != nullptr) queue.push(pNode->pLeft);
        if(pNode->pRight != nullptr) queue.push(pNode->pRight);
    }
    return list;
}
template<class K, class V>
DLinkedList<K> BST<K, V>::bfsKey(){
    DLinkedList<K> list;
    if(pRoot == nullptr) return list;
    
    Queue<Node*> queue;
    queue.push(pRoot);
    while(!queue.empty()){
        Node* pNode = queue.pop();
        list.add(pNode->data.key);
        if(pNode->pLeft != nullptr) queue.push(pNode->pLeft);
        if(pNode->pRight != nullptr) queue.push(pNode->pRight);
    }
    return list;
}

template<class K, class V>
DLinkedList<V> BST<K, V>::nlr(){
    DLinkedList<V> list;
    nlr(pRoot, list);
    return list;
}
template<class K, class V>
void BST<K, V>::nlr(Node* pRoot, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    list.add(pRoot->data.value);
    nlr(pRoot->pLeft, list);
    nlr(pRoot->pRight, list);
}

template<class K, class V>
DLinkedList<V> BST<K, V>::lrn(){
    DLinkedList<V> list;
    lrn(pRoot, list);
    return list;
}
template<class K, class V>
void BST<K, V>::lrn(Node* pRoot, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    lrn(pRoot->pLeft, list);
    lrn(pRoot->pRight, list);
    list.add(pRoot->data.value);
}

template<class K, class V>
DLinkedList<V> BST<K, V>::lnr(){
    DLinkedList<V> list;
    lnr(pRoot, list);
    return list;
}
template<class K, class V>
void BST<K, V>::lnr(Node* pRoot, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    lnr(pRoot->pLeft, list);
    list.add(pRoot->data.value);
    lnr(pRoot->pRight, list);
}

template<class K, class V>
void BST<K, V>::select(Node* pRoot, K min, K max, DLinkedList<V>& list){
    if(pRoot == nullptr) return;
    
    if(pRoot->data.key < min) select(pRoot->pRight, min, max, list);
    else if(pRoot->data.key == min){
        //key: == min
        list.add(pRoot->data.value);
        select(pRoot->pRight, min, max, list);
    }
    else if(pRoot->data.key <= max){
        // key: (min, max]
        select(pRoot->pLeft, min, max, list);
        list.add(pRoot->data.value);
        select(pRoot->pRight, min, max, list);
    }
    else{
        //key: (max, inf)
        select(pRoot->pLeft, min, max, list);
    }
}

template<class K, class V>
DLinkedList<V> BST<K, V>::select(K min, K max){
    DLinkedList<V> list;
    select(this->pRoot, min, max, list);
    return list;
}


#endif /* BST_H */

