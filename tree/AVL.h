/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 *
 * Created on 12 September 2020, 17:11
 */

#ifndef TREE_AVL_H_
#define TREE_AVL_H_
#include "tree/BST.h"
#include "list/DLinkedList.h"
#include "stacknqueue/Queue.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

#define XNode typename BST<K, V>::Node

template <class K, class V>
class AVL : public BST<K, V>
{
public:
    void add(K key, V value = {})
    {
        this->pRoot = add(this->pRoot, new XNode(typename BST<K, V>::Entry(key, value)));
        this->count += 1;
    }
    V remove(K key, bool *success = nullptr)
    {
        V retValue{}; // default value
        bool success_;
        this->pRoot = remove(this->pRoot, key, success_, retValue);
        if (success_)
            this->count -= 1;
        if (success != nullptr)
            *success = success_;

        return retValue;
    }
    int height()
    {
        if (this->pRoot == nullptr)
            return 0;
        return this->pRoot->height();
    }
    void println(std::string (*entry2str)(K &, V &) = nullptr)
    {
        std::cout << "Tree height: " << this->height() << std::endl;
        std::cout << "Tree nodes:" << std::endl;
        std::cout << this->toString(entry2str, true) << std::endl;
    }
    /*
     * bfactor: designed for being used to test AVL tree
     *          so, maybe not useful for real application
     * It returns a list of balance factor (string) of nodes visited with BFS-traversal
     * (see AVLTest for example)
     */
    DLinkedList<std::string> bfactor()
    {
        DLinkedList<std::string> list;
        if (this->pRoot == nullptr)
            return list;

        Queue<XNode *> queue;
        queue.push(this->pRoot);
        while (!queue.empty())
        {
            XNode *pNode = queue.pop();
            if (pNode->bfactor == nEMPTY)
                list.add("EMPTY");
            else if (pNode->bfactor == nLH)
                list.add("LH");
            else if (pNode->bfactor == nEH)
                list.add("EH");
            else
                list.add("RH");

            if (pNode->bfactor == nEMPTY)
            {
                delete pNode; //because alloc in [1] or [2]
                continue;
            }
            if ((pNode->pLeft == nullptr) && (pNode->pRight == nullptr))
                continue;

            if (pNode->pLeft != nullptr)
                queue.push(pNode->pLeft);
            else
                queue.push(new XNode()); //[1]
            if (pNode->pRight != nullptr)
                queue.push(pNode->pRight);
            else
                queue.push(new XNode()); //[2]
        }
        return list;
    }

private:
    /*
     Current tree:
                    45
                   /  \
                 33    72
                      /  \
                     55  84

    Adding 75:
                    45    : RH of RH
                   /  \
                 33    72
                      /  \
                     55  84
                        /
                       75    
     
    rotateLeft(at 45):
                    72
                   /  \
                 45    84
                / \    /
              33  55  75        
    
     */
    XNode *rotateLeft(XNode *root)
    {
        XNode *newRoot = root->pRight;
        root->pRight = newRoot->pLeft;
        newRoot->pLeft = root;
        root->updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    /*
    Current tree:
                45
               /  \
             33    72
            /  \
          24    40
    
    Adding 15:
                45    : LH of LH => Rotate right
               /  \
             33    72
            /  \
          24    40
         /
       15     
    rotateRight(at 45):
             33
            /  \
          24    45
         /     /  \
       15     40   72
        
     */
    XNode *rotateRight(XNode *root)
    {
        XNode *newRoot = root->pLeft;
        root->pLeft = newRoot->pRight;
        newRoot->pRight = root;
        root->updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    XNode *rebalance(XNode *root)
    {
        if (root == nullptr)
            return root;

        root->updateHeight();
        if (root->isBalanced())
            return root;

        //re-balance
        XNode *newRoot = root;
        if (root->isLH())
        {
            XNode *leftTree = root->pLeft;
            if (leftTree->isRH())
            {
                root->pLeft = rotateLeft(root->pLeft);
                newRoot = rotateRight(root);
            }
            else
            {
                newRoot = rotateRight(root);
            }
        }
        else if (root->isRH())
        {
            XNode *rightTree = root->pRight;
            if (rightTree->isLH())
            {
                root->pRight = rotateRight(root->pRight);
                newRoot = rotateLeft(root);
            }
            else
            {
                newRoot = rotateLeft(root);
            }
        }
        return newRoot;
    }

    XNode *add(XNode *root, XNode *newNode)
    {
        if (root == nullptr)
            return newNode;
        if (newNode->data.key < root->data.key)
            root->pLeft = add(root->pLeft, newNode);
        else
            root->pRight = add(root->pRight, newNode);

        return rebalance(root);
    }

    XNode *remove(XNode *root, K key, bool &success, V &retValue)
    {
        if (root == nullptr)
        {
            success = false;
            return nullptr;
        }

        XNode *newRoot = root;
        if (key < root->data.key)
            root->pLeft = remove(root->pLeft, key, success, retValue);
        else if (key > root->data.key)
            root->pRight = remove(root->pRight, key, success, retValue);
        else
        {
            if ((root->pLeft == nullptr) || (root->pRight == nullptr))
            {
                newRoot = ((root->pLeft == nullptr) ? root->pRight : root->pLeft);
                success = true;
                retValue = root->data.value;
                root->data.value = nullptr;
                delete root;
            }
            else
            {
                V backup = root->data.value;
                XNode *largestOnLeft = root->pLeft;
                while (largestOnLeft->pRight != nullptr)
                    largestOnLeft = largestOnLeft->pRight;
                root->data = largestOnLeft->data;
                root->pLeft = remove(root->pLeft, largestOnLeft->data.key, success, retValue);

                success = true;
                retValue = backup;
            }
        }
        return rebalance(newRoot);
    }
};

#endif /* AVL_H */
