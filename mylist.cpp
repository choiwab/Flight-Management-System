#include "mylist.h"
#include "flighthashtable.h"

template <typename T>
MyList<T>::MyList()             //constructor for list
{head = NULL;}

template <typename T>
MyList<T>::~MyList()        //destrcutor: remove each node until list is empty
{
    while (!empty()) 
    {
        removeFront();
    }
}

template <typename T>
bool MyList<T>::empty() const 
{
    return (head == NULL);
}

template <typename T>
void MyList<T>::addFront(T* data) 
{ 
    Node<T>* node = new Node<T>(data);      //create new node object, add as head of list
    node->next = head; 
    head = node; 
}

template <typename T>
void MyList<T>::removeFront() {         //remove head, assign next node as head
    if (!empty()) {
        Node<T>* oldHead = head;
        head = head->next;
        delete oldHead;
    }
}

template <typename T>           //iterate through whole list, count number of nodes
int MyList<T>::size() const {       
    int count = 0;
    Node<T>* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

template <typename T>
T* MyList<T>::operator[](int index)         //operator [] overload to return data of corresponding node
 {
    Node<T>* current = head;
    int i = 0;
    while (current != NULL && i < index) {      //iterate through list until i reaches index
        current = current->next;
        i++;
    }   
    if (current == NULL) {                          //return nothing if current reaches end
        return NULL;
    }
    return current->data;                           //return data
}

template <typename T>
void MyList<T>::remove(Node<T>* nodeToRemove) {             //remove corresponding node
    if (head == NULL) {
        return;                 //if list is empty, return
    }
    if (head == nodeToRemove) {             //node to remove is the head node
        head = nodeToRemove->next;          //assign next node as head
        delete nodeToRemove;                //delete node
        return;
    }
    Node<T>* current = head;
    while (current->next != NULL && current->next != nodeToRemove) {    //iterate through list until node to remove is found
        current = current->next;
    }
    if (current->next != NULL) {                            //if node is before reaching end of list, connect current node to nodetoremoves's next node and delete nodetoremove
        current->next = nodeToRemove->next;
        delete nodeToRemove;
    }
}

template <typename T>
int MyList<T>::countCollision()
{
    string keys[size()];    //declare array to store unique keys
    string key;
    int index = -1;             //index for accessing keys array and returning number of collisions

    Node<T>* current = head;        //access head

    while(current != NULL)      //iterate through list
    {
        bool exists=false;      //boolean flag to see if there is a collision or not
        key = current->data->key;       //set key as current node's key
        for(int i =0; i< size();i++)       //iterate through array of unique keys to see if the key is unique or not
        {
            if(keys[i]==key)            //if the key is not unique, it is not a collision, go on to next node
                {
                    exists = true;
                    break;
                }
        }
        if(exists ==false)              //if the key is unique, increment index and add to array of unique keys
        {
            index ++;
            keys[index] = key;
        }
        current = current ->next;           
    }
    return index+1;         //return number of unique keys in list
}

template class MyList<HashNode>;
