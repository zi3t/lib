/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef GRAPH_DGRAPHMODEL_H_
#define GRAPH_DGRAPHMODEL_H_
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/XHashMap.h"
#include "stacknqueue/PriorityQueue.h"
#include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        typename AbstractGraph<T>::VertexNode* nodeF = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* nodeT = this->getVertexNode(to);
        if(nodeF == nullptr) throw VertexNotFoundException(this->vertex2Str(*nodeF));
        if(nodeT == nullptr) throw VertexNotFoundException(this->vertex2Str(*nodeT));
        nodeF->connect(nodeT, weight);
    }
    void disconnect(T from, T to){
         typename AbstractGraph<T>::VertexNode* nodeF = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* nodeT = this->getVertexNode(to);
        if(nodeF == nullptr) throw VertexNotFoundException(this->vertex2Str(*nodeF));
        if(nodeT == nullptr) throw VertexNotFoundException(this->vertex2Str(*nodeT));

          typename AbstractGraph<T>::Edge* edge = nodeF->getEdge(nodeT);
          if(edge == nullptr) throw EdgeNotFoundException(this->edge2Str(*edge));
          nodeF->removeTo(nodeT);
    }
    void remove(T vertex){
         typename AbstractGraph<T>::VertexNode* nodeA = this->getVertexNode(vertex);
        if(nodeA == nullptr) throw VertexNotFoundException(this->vertex2Str(*nodeA));

        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator nodeIt;
        nodeIt = this->nodeList.begin();
        while(nodeIt != this->nodeList.end()) {
            typename AbstractGraph<T>::VertexNode* nodeB = *nodeIt;
            typename AbstractGraph<T>::Edge* edge = nodeB->getEdge(nodeA);
            if(edge != nullptr) nodeB->removeTo(nodeA);
            edge = nodeA->getEdge(nodeB);
            if(edge != nullptr) nodeA->removeTo(nodeB);
            nodeIt++;
        }
        this->nodeList.removeItem(nodeA);
    }
    static DGraphModel<T>* create(T* vertices, int nvertices, Edge<T>* edges, int nedges, bool(*vertexEQ)(T&, T&), string (*vertex2str)(T&)){
        DGraphModel<T>* model = new DGraphModel<T>(vertexEQ, vertex2str);
        for(int vidx = 0; vidx < nvertices; vidx++){
            model->add(vertices[vidx]);
        }
            
        for(int eidx = 0; eidx < nedges; eidx++){
            model->connect(edges[eidx].from, edges[eidx].to, edges[eidx].weight);
        }
            
        return model;
    }
};

#endif /* DGRAPHMODEL_H */

