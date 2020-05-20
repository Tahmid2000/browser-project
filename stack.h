//
//  stack.hpp
//  StackAndQueue
//
//  Created by Tahmid Imran on 11/16/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cassert>
// forward declaration of the template class stack
template<class Type>
class stack;

// stackEntry class
template <class Type>
class stackEntry
{
    friend class stack<Type>;
    private:
    // contains the actual data
    Type dataValue;
    // pointer to the next node
    stackEntry<Type>* pNext;
    
    protected:
    //constructor
    stackEntry(const Type &newData, stackEntry<Type> *newNext = nullptr)
    {
        dataValue = newData;
    }
    //destructor
    virtual ~stackEntry()
    {
    }
    //sets next node to a new node
    virtual void next(stackEntry<Type> *pNext)
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
    virtual stackEntry<Type>* next()
    {
        return pNext;
    }
    // get the next node
};
// stack class
template <class Type>
class stack
{
private:
    //theTop node of tree
    stackEntry<Type> *theTop;
    //keeps count of how many nodes in tree
    std::size_t count;
public:
    //default constructor
    stack();
    // copy constructor
    stack(const stack &other);
    //copy assignment operator
    stack& operator=(const stack &rhs);
    //copy method for copy constructor and assignment operator
    void copy(stackEntry<Type> *node);
    // destructor
    virtual ~stack()
    {
        clear();
    }
    
public:
    //return the data of the top node
    const Type& top() const;
    //return the data of the top node
    Type& top();
    //pushes a new node to the top
    void push(const Type &value);
    //removes the top node
    void pop();
    //removes all nodes
    void clear();
    //checks if stack is empty
    bool empty() const
    {
        return theTop == nullptr;
    }
    //number of nodes in stack
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
};

//constructor
template <class Type>
stack<Type>::stack()
    : theTop(nullptr), count(0)
{
}

//debug method
template<class Type>
void stack<Type>::debug(std::ostream &out) const
{
    const unsigned int ADDRWIDTH = 10;
    out << "START DEBUG" << std::endl;
    out << "first  =" << std::setw(ADDRWIDTH) << theTop;
    out << ", # nodes=" << size() << std::endl;
    unsigned int count = 1;
    
    if(theTop == nullptr)
    {
        out << "Tree is empty.";
        return;
    }
    for (auto current=theTop; current!= nullptr; current=current->next())
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
stack<Type>::stack(const stack& other)
{
    theTop = nullptr;
    //copys each item of other into tree
    copy(other.theTop);
}

//copy assignment operator
template <class Type>
stack<Type>& stack<Type>::operator=(const stack &other)
{
    if(this != &other)
    {
        //first removes all nodes and copy all nodes to the stack
        clear();
        copy(other.theTop);
    }
    return *this;
}

//copy method
template <class Type>
void stack<Type>::copy(stackEntry<Type> *node)
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
const Type& stack<Type>::top() const
{
    //makes sure top node isn't null
    assert(theTop != nullptr);
    return theTop->data();
}

//returns the data of the top
template <class Type>
Type& stack<Type>::top()
{
    //makes sure top node isn't null
    assert(theTop != nullptr);
    return theTop->data();
}

//pushes new node to top
template <class Type>
void stack<Type>::push(const Type &value)
{
    //creates node with data
    stackEntry<Type> *temp = new stackEntry<Type>(value);
    //if stack is empty, makes new node theTop
    if(empty())
    {
        theTop = temp;
    }
    //sets new nodes next to current top and sets top to new node
    else
    {
        temp->next(theTop);
        theTop = temp;
    }
    count++;
}

//removes top node
template <class Type>
void stack<Type>::pop()
{
    //checks if empty
    if(empty())
        return;
    //checks if only one node
    if(size() == 1)
    {
        //sets top to nullptr
        theTop = nullptr;
    }
    else
    {
        //creates temp node that is theTop
        stackEntry<Type> *temp = theTop;
        //sets theTop to its next node
        theTop = theTop->next();
        //makes the next of temp to nullptr, so top to be removed isn't pointing to anything
        temp->next(nullptr);
        //deleted top from memory
        delete temp;
    }
    count--;
}

//removes all nodes
template <class Type>
void stack<Type>::clear()
{
    //pops every node while stack isn't empty
    while(!empty())
        pop();
}
#endif /* stack_h */
