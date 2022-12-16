# Priority Queue

This is a C++ program for implementing a priority queue using a binary search tree (BST) data structure. The priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction. The priority queue is implemented as a BST where the root node has the highest priority.
## Features

    Allows for duplicate priorities
    Provides iterators for traversing the priority queue in the order that the elements are stored in the BST
    Provides a clear function for deleting all elements in the priority queue and freeing up memory
    Provides copy constructor and assignment operator for creating a copy of the priority queue

## How to use

To use the priority queue, include the header file priorityqueue.h in your program and create an instance of the priorityqueue class. The priority queue can be initialized with elements by using the enqueue function, which takes in a value and a priority. The dequeue function removes and returns the element with the highest priority (or the element at the root of the BST). The size function returns the number of elements in the priority queue and the empty function returns true if the priority queue is empty and false otherwise. The begin and next functions provide iterators for traversing the priority queue in the order that the
