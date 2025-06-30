/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef GRAPH_TOPOSORTER_H_
#define GRAPH_TOPOSORTER_H_
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "hash/XHashMap.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph , int (*hash_code)(T&, int) = XHashMap<T, int>::simpleHash){
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0){
        bool sorted = false;
        if(mode == DFS) return dfsSort(sorted);
        else return bfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted = true){
        DLinkedList<T> topoOrder;
        XHashMap<T, int> indegreeMap = vertex2inDegree(this->hash_code);
        DLinkedListSE<T> list = listOfZeroInDegrees();
        //if(sorted) list.sort();

        Queue<T> open;
        for(typename DLinkedListSE<T>::Iterator it = list.begin(); it != list.end(); it++)
            open.push(*it);
        while(!open.empty()) {
            T vertex = open.pop();
            topoOrder.add(vertex);

            DLinkedList<T> children = this->graph->getOutwardEdges(vertex);
            //if(sorted) children.sort();
            for(typename DLinkedList<T>::Iterator it=children.begin(); it != children.end(); it++){
                T child = *it;
                if(open.contains(child)) continue;
                if(topoOrder.contains(child)) continue;

                int new_indeg = indegreeMap.get(child) - 1;
                indegreeMap.put(child, new_indeg);
                if(new_indeg == 0) open.push(child);
            }
        } 
        
        return topoOrder;
    }
    
    DLinkedList<T> dfsSort(bool sorted = true){
        DLinkedList<T> topoOrder;
        XHashMap<T, int> outdegreeMap = vertex2outDegree(this->hash_code);
        DLinkedListSE<T> list = listOfZeroInDegrees();
        //if(sorted) list.sort();

        Stack<T> open;
        for(typename DLinkedListSE<T>::Iterator it = list.begin(); it != list.end(); it++)
            open.push(*it);

        while(!open.empty()){
            T vertex = open.peek();
            int outDegree = outdegreeMap.get(vertex);
            if(outDegree == 0){
                open.pop();
            topoOrder.add(0, vertex);
            } else {
                DLinkedList<T> children = this->graph->getOutwardEdges(vertex);
                //if(sorted) children.sort();
                for(typename DLinkedList<T>::Iterator it=children.begin(); it != children.end(); it++){
                    T child = *it;
                    if(open.contains(child)) {
                        open.remove(child);
                        open.push(child);
                    }
                    if(!open.contains(child) && !topoOrder.contains(child))
                        open.push(child);

                    outdegreeMap.put(vertex, outDegree - 1);
                }
            }
        }
        return topoOrder;
    }
protected:
    XHashMap<T, int> vertex2inDegree(int (*hash_code)(T&, int)){
        XHashMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            map.put(vertex, inDegree);
            
            vertexIt++;
        }
        return map;
    }
    XHashMap<T, int> vertex2outDegree(int (*hash_code)(T&, int)){
        XHashMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int outDegree = this->graph->outDegree(vertex);
            map.put(vertex, outDegree);
            
            vertexIt++;
        }
        return map;
    }
    
    DLinkedListSE<T> listOfZeroInDegrees(){
        DLinkedListSE<T> list;
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while(vertexIt != this->graph->end()){
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            if(inDegree == 0) list.add(vertex);
            
            vertexIt++;
        }
        return list;
    }
}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

// /*
//  * To change this license header, choose License Headers in Project Properties.
//  * To change this template file, choose Tools | Templates
//  * and open the template in the editor.
//  */

// /* 
//  * File:   TopoSorter.h
//  *
//  * Created on July 11, 2021, 10:21 PM
//  */

// #ifndef TOPOSORTER_H
// #define TOPOSORTER_H
// #include "graph/DGraphModel.h"
// #include "list/DLinkedList.h"
// #include "sorting/DLinkedListSE.h"
// #include "hash/XHashMap.h"

// template<class T>
// class TopoSorter{
// public:
//     static int DFS;
//     static int BFS; 
    
// protected:
//     DGraphModel<T>* graph;
//     int (*hash_code)(T&, int);
    
// public:
//     TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
//         this->graph = graph;
//         this->hash_code = hash_code;
//     }   
//     DLinkedList<T> sort(int mode=0){
//         //bool sorted = false;
//         if(mode == DFS) return dfsSort(sorted);
//         else return bfsSort(sorted);
//     }
//     DLinkedList<T> bfsSort(bool sorted = true){
//         DLinkedList<T> topoOrder;
//         Queue<T> open;
//         XHashMap<T, int> indegreeTable = vertex2inDegree();
//         DLinkedList<T> list = listOfZeroInDegrees();
//         if (sorted) list.sort();
//         for(typename DLinkedList<T>::Iterator it = list.begin(); it != list.end(); it++){
//             open.push(*it);
//             while (!open.empty())
//             {
//                 T vertex = open.pop();
//                 topoOrder.add(vertex);
            
//             DLinkedList<T> children = this->graph->getOutwardEdges(vertex);
//             children.sort();
//             for (typename DLinkedList<T>::Iterator iter = children.begin(); iter != children.end(); iter++){
//                 T child = *it;
//                 if (open.contains(child)) continue;
//                 if (topoOrder.contains(child)) continue;
                
//                 int new_inde = indegreeTable.get(child) - 1;
//                 indegreeTable.put(child, new_inde);
//                 if (new_inde == 0) open.push(child);
//             }
//         }
//     }
    
//         return topoOrder;
// }
    
//     DLinkedList<T> dfsSort(bool sorted = true){
//     DLinkedList<T> topoOrder;
//     Stack<T> open;
//     XHashMap<T, int> OutdegreeTable = vertex2outDegree();
//     DLinkedList<T> list0Degree = this->listOfZeroInDegrees();
//     if (sorted) list0Degree.sort();
//     for(typename DLinkedList<T>::Iterator it = list0Degree.begin(); it != list0Degree.end(); it++){
//         open.push(*it); // put all zero indegree vertex into stack
//     }
//     while (!open.empty()){
//         // if stack not empty then check the top vertex for their children
//         T vertex = open.peek();
//         int outDegree = OutdegreeTable.get(vertex);
//         if (outDegree == 0){
//             open.pop();
//             open.add(0, vertex);
//         }
//         else {
//             DLinkedList<T> children = this->graph->getOutwardEdges(vertex);
//             if (sorted) children.sort();
//             for (typename DLinkedList<T>:: Iterator it = children.begin(); it != children.end(); it++){
//                 T child = *it;
//                 if (open.contains(child)){
//                     open.remove(child);
//                     open.push(child);
//                     // if children is in open, then pop and then add to top
//                 }
//                 if (!topoOrder.contains(child) && !open.contains(child)){
//                     open.push(child);
//                 }
//             }
//             OutdegreeTable.put(vertex, outDegree - 1);
//         }
//     }
//     return topoOrder;
// }

// protected:
//     XHashMap<T, int> vertex2inDegree(){
//         XHashMap<T, int> map(&XHashMap<T, int>::simpleHash);
//         typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
//         while(vertexIt != this->graph->end()){
//             T vertex = *vertexIt;
//             int inDegree = this->graph->inDegree(vertex);
//             map.put(vertex, inDegree);
            
//             vertexIt++;
//         }
//         return map;
//     }
//     XHashMap<T, int> vertex2outDegree(){
//         XHashMap<T, int> map(&XHashMap<T, int>::simpleHash);
//         typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
//         while(vertexIt != this->graph->end()){
//             T vertex = *vertexIt;
//             int outDegree = this->graph->outDegree(vertex);
//             map.put(vertex, outDegree);
            
//             vertexIt++;
//         }
//         return map;
//     }
    
//     DLinkedList<T> listOfZeroInDegrees(){
//         DLinkedList<T> list;
//         typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
//         while(vertexIt != this->graph->end()){
//             T vertex = *vertexIt;
//             int inDegree = this->graph->inDegree(vertex);
//             if(inDegree == 0) list.add(vertex);
            
//             vertexIt++;
//         }
//         return list;
//     }
// }; //TopoSorter
// template<class T>
// int TopoSorter<T>::DFS = 0;
// template<class T>
// int TopoSorter<T>::BFS = 1;

// /////////////////////////////End of TopoSorter//////////////////////////////////


// #endif /* TOPOSORTER_H */

