#ifndef STACKNQUEUE_QUEUE_H_
#define STACKNQUEUE_QUEUE_H_

#include "list/DLinkedList.h"
#include "stacknqueue/IDeck.h"
#include <string>
#include <sstream>
#include <iostream>
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

template <class T>
class Queue : public IDeck<T>
{
public:
    class Iterator;

protected:
    DLinkedList<T> list;
    void (*deleteUserData)(DLinkedList<T> *);
    bool (*itemEqual)(T &lhs, T &rhs);

public:
    Queue(void (*deleteUserData)(DLinkedList<T> *) = nullptr ,bool (*itemEqual)(T &, T &) = nullptr)
    {
        this->itemEqual = itemEqual;
        this->deleteUserData = deleteUserData;
    }

    void push(T item)
    {
        list.add(item);
    }

    T pop()
    {
        return list.removeAt(0);
    }

    T &peek()
    {
        return list.get(0);
    }

    bool empty()
    {
        return list.empty();
    }

    int size()
    {
        return list.size();
    }

    void clear()
    {
        return list.clear();
    }

    bool remove(T item)
    {
        return list.removeItem(item);
    }

    bool contains(T item)
    {
        bool found = false;
        typename DLinkedList<T>::Iterator it = list.begin();
        while (it != list.end())
        {
            found = equals(*it, item, this->itemEqual);
            if (found)
                break;
            it++;
        }
        return found;
    }

    string toString(string (*item2str)(T &) = nullptr)
    {
        stringstream os;
        os << "FRONT-TO-REAR: " << list.toString(item2str);
        return os.str();
    }

    void println(string (*item2str)(T &) = nullptr)
    {
        cout << toString(item2str) << endl;
    }

    Iterator front()
    {
        return Iterator(this, true);
    }

    Iterator rear()
    {
        return Iterator(this, false);
    }

private:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == nullptr)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

public:
    //ITERATOR: BEGIN
    class Iterator
    {
    private:
        Queue<T> *queue;
        typename DLinkedList<T>::Iterator listIt;
        public:
         Iterator(Queue<T>* queue = nullptr, bool begin=true){
            this->queue = queue;
            if(begin){
                if(queue != nullptr) this->listIt = queue->list.begin();
                else this->listIt = nullptr;
            }
            else{
                if(queue != nullptr) this->listIt = queue->list.end();
                else this->listIt = nullptr;
            }
        }
        Iterator& operator=(const Iterator& iterator ){
            this->queue = iterator.queue;
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

    //ITERATOR : END
};

#endif /* QUEUE_H */