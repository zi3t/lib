/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IGraph.h
 *
 * Created on 23 August 2020, 17:28
 */

#ifndef GRAPH_IGRAPH_H_
#define GRAPH_IGRAPH_H_
#include "list/DLinkedList.h"
#include <iostream>
#include <string>
#include <sstream>


class VertexNotFoundException: public std::exception{
private:
    std::string vertex;
public:
    VertexNotFoundException(std::string vertex){
        this->vertex = vertex;
    }
    const char * what () const throw (){
        std::stringstream os;
        os << "Vertex (" << this->vertex << "): is not found";
        return os.str().c_str();
    }
};

class EdgeNotFoundException: public std::exception{
private:
    std::string edge;
public:
    EdgeNotFoundException(std::string edge){
        this->edge = edge;
    }
    const char * what () const throw (){
        std::stringstream os;
        os << "Edge (" << edge << "): is not found";
        return os.str().c_str();
    }
};

/*
 * IGraph: define APIs for a graph data structure
 *  >> T: type of vertices
 */
template<class T>
class IGraph{
public:
    virtual ~IGraph(){};
    virtual void add(T vertex)=0;
    virtual void remove(T vertex)=0;
    virtual bool contains(T vertex)=0;
    
    virtual void connect(T from, T to, float weight=0)=0;
    virtual void disconnect(T from, T to)=0;
    virtual float weight(T from, T to)=0;
    
    virtual DLinkedList<T> getOutwardEdges(T from)=0;
    virtual DLinkedList<T> getInwardEdges(T to)=0;
    
    virtual int size()=0;
    virtual bool empty()=0;
    virtual void clear()=0;
    
    virtual int inDegree(T vertex)=0;
    virtual int outDegree(T vertex)=0;
    
    virtual DLinkedList<T> vertices()=0;
    virtual bool connected(T from, T to)=0;
    
    virtual std::string toString()=0;
};

/*
 * Path: model a path on graphs
 *  >> a path = sequence of vertices,
 *      -> stored in: "path" (DLinkedList<T>)
 *      -> its cost: stored in "cost" (float)
 *   
 */
template<class T>
class Path{
private:
    DLinkedList<T> path;
    float cost;
public:
    Path(){
        cost = 0;
    }
    DLinkedList<T>& getPath(){ 
        return this->path; 
    }
    float getCost(){ 
        return cost; 
    }
    void setCost(float cost){ 
        this->cost = cost; 
    }

    ///////////////////////////////////////////
    void add(T item){
        this->path.add(item);
    }
    std::string toString(std::string (*item2str)(T&)=0){
        std::stringstream os;
        os << this->path.toString(item2str)
                << ", cost: " << this->cost;
        return os.str();
    }
};

/*
 * IFinder: the path finder, contains searching algorithms on graph
 * 
 */
template<class T>
class IFinder{
    virtual DLinkedList<Path<T>> dijkstra(IGraph<T>* pGraph, T start)=0;
};


template<class T>
class Edge{
     public:
        T from;
        T to;
        float weight;
        
        Edge(){}
        Edge(T from, T to, float weight=0){
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
};

#endif /* IGRAPH_H */

