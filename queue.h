//
//  queue.hpp
//  queueAndQueue
//
//  Created by Tahmid Imran on 11/16/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cassert>
#include <vector>
// forward declaration of the template class queue
template<class Type>
class queue;

// queueEntry class
template <class Type>
class queueEntry
{
    friend class queue<Type>;
    private:
    // contains the actual data
    Type dataValue;
    // pointer to the next node
    queueEntry<Type>* pNext;
    
    protected:
    //constructor
    queueEntry(const Type &newData, queueEntry<Type> *newNext = nullptr)
    {
        dataValue = newData;
    }
    //destructor
    virtual ~queueEntry()
    {
    }
    //sets next node to a new node
    virtual void next(queueEntry<Type> *pNext)
    {
        this->pNext = pNext;
    }
    // return the data stored in the node
    virtual Type& data()
    {
        return dataValue;
    }
    // return the data stored in the node
    virtual const Type& data() const
    {
        return dataValue;
    }
    //returns the next node
    virtual queueEntry<Type>* next()
    {
        return pNext;
    }
    // get the next node
};
// queue class
template <class Type>
class queue
{
private:
    //theFront node of tree
    queueEntry<Type> *theFront;
    queueEntry<Type> *theBack;
    //keeps count of how many nodes in tree
    std::size_t count;
public:
    //default constructor
    queue();
    // copy constructor
    queue(const queue &other);
    //copy assignment operator
    queue& operator=(const queue &rhs);
    //copy method for copy constructor and assignment operator
    void copy(queueEntry<Type> *node);
    // destructor
    virtual ~queue()
    {
        clear();
    }
    
public:
    //return the data of the top node
    const Type& front() const;
    //return the data of the top node
    Type& front();
    const Type& back() const;
    Type& back();
    //pushes a new node to the top
    void push(const Type &value);
    //removes the top node
    void pop();
    //removes all nodes
    void clear();
    //checks if queue is empty
    bool empty() const
    {
        return theFront == nullptr;
    }
    //number of nodes in queue
    std::size_t size() const
    {
        return count;
    }
    //debug method
    void debug() const
    {
        debug(std::cout);
    }
    //debug method
    void debug(std::ostream &out) const;
    void traverse(void(*applicationFunction)(const Type &nextItem));
};

//constructor
template <class Type>
queue<Type>::queue()
    : theFront(nullptr), theBack(nullptr), count(0)
{
}

//debug method
template<class Type>
void queue<Type>::debug(std::ostream &out) const
{
    const unsigned int ADDRWIDTH = 10;
    out << "START DEBUG" << std::endl;
    out << "theFront  =" << std::setw(ADDRWIDTH) << theFront;
    out << "theBack   =" << std::setw(ADDRWIDTH) << theBack;
    out << ", # nodes=" << size() << std::endl;
    unsigned int count = 1;
    
    if(theFront == nullptr)
    {
        out << "Tree is empty.";
        return;
    }
    for (auto current=theFront; current!= nullptr; current=current->next())
    {
        out << "node " << std::setw(2) << count;
        out << "=" << std::setw(ADDRWIDTH) << current;
        out << ", next=" << std::setw(ADDRWIDTH)
            << current->next();
        out << ", value=" << current->data() << std::endl;
        count++;
    }
    out << "END DEBUG" << std::endl;
}

//copy constructor
template <class Type>
queue<Type>::queue(const queue& other)
{
    theFront = nullptr;
    //copys each item of other into tree
    copy(other.theFront);
}

//copy assignment operator
template <class Type>
queue<Type>& queue<Type>::operator=(const queue &other)
{
    if(this != &other)
    {
        //theFront removes all nodes and copy all nodes to the queue
        clear();
        copy(other.theFront);
    }
    return *this;
}

//copy method
template <class Type>
void queue<Type>::copy(queueEntry<Type> *node)
{
    if(node != nullptr)
    {
        //preorder traversal where all nodes are copied
        push(node->data());
        copy(node->next());
    }
}

//returns the data of the top
template <class Type>
const Type& queue<Type>::front() const
{
    //makes sure top node isn't null
    assert(theFront != nullptr);
    return theFront->data();
}

//returns the data of the top
template <class Type>
Type& queue<Type>::front()
{
    //makes sure top node isn't null
    assert(theFront != nullptr);
    return theFront->data();
}

template <class Type>
const Type& queue<Type>::back() const
{
    //makes sure top node isn't null
    assert(theBack != nullptr);
    return theBack->data();
}

//returns the data of the top
template <class Type>
Type& queue<Type>::back()
{
    //makes sure back node isn't null
    assert(theBack != nullptr);
    return theBack->data();
}

//pushes new node to top
template <class Type>
void queue<Type>::push(const Type &value)
{
    //creates node with data
    queueEntry<Type> *temp = new queueEntry<Type>(value);
    //if queue is empty, makes new node theFront
    if(empty())
    {
        theFront = theBack = temp;
    }
    //sets new nodes next to current top and sets top to new node
    else
    {
        theBack->next(temp);
        theBack = temp;
    }
    count++;
}

//removes top node
template <class Type>
void queue<Type>::pop()
{
    //checks if empty
    if(empty())
        return;
    //checks if only one node
    else if(size() == 1)
    {
        //sets front and back to nullptr
        theFront = theBack = nullptr;
    }
    else
    {
        //creates temp node that is theFront
        queueEntry<Type> *temp = theFront;
        //sets theFront to its next node
        theFront = theFront->next();
        //makes the next of temp to nullptr, so top to be removed isn't pointing to anything
        temp->next(nullptr);
        //deleted top from memory
        delete temp;
    }
    count--;
}

//removes all nodes
template <class Type>
void queue<Type>::clear()
{
    //pops every node while queue isn't empty
    while(!empty())
        pop();
}

//traverses the whole queue
template <class Type>
void queue<Type>::traverse(void (*applicationFunction) (const Type &nextItem))
{
    //if its empty, then it won't traverse
    if(empty())
        return;
    //goes through whole queue and calls static/stand alone method
    for(queueEntry<Type> *i = theFront; i != theBack; i = i->next())
    {
        applicationFunction(i->data());
    }
    //calls static/stand alone function on back node
    applicationFunction(back());
}
#endif /* queue_h */
