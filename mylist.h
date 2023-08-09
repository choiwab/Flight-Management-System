#ifndef MYLIST_H
#define MYLIST_H

#include "flighthashtable.h"


#include <string>


template <typename T>
class Node {
    private:
        T* data; 
        Node<T>* next; 
    public:
        Node(T* data) : data(data), next(NULL) { } 
        friend class FlightHASHTABLE;
        template <typename> friend class MyList;
};

template <typename T>
class MyList {
    private:
        Node<T>* head; // pointer to the head of list
    public:
        MyList(); // empty list constructor
        ~MyList(); // destructor to clean up all nodes
        bool empty() const; // is list empty?
        void addFront(T* data); // add a new Node at the front of the list
        int size() const;
        void removeFront(); 
        int countCollision();
        T* operator[](int index);
        void remove(Node<T>* nodeToRemove);

        friend class FlightHASHTABLE;
};

#endif 
