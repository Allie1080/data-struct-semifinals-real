#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

#include "combat-data.h"

struct qNode {
    Enemy _data;
    qNode* _next;

    qNode(Enemy data);
};

struct sNode {
    Action _data;
    sNode* _next;

    sNode (Action data);
};

class Stack {
private:
    sNode *_top;
    int _size{0};

public:
    Stack();
    ~Stack();
    void push(Action data);
    int pop();
    Action peek();
    int getSize() const;
    bool isEmpty() const;

};

class Queue {
private:
    qNode *_front;
    qNode *_rear;
    int _size{0};

public:
    Queue();
    ~Queue();
    void enqueue(Enemy data);
    int dequeue(bool isInsideFunction);
    // int rotateQueue();
    Enemy peek(); 
    int getSize() const;
    bool isEmpty() const;
};

#endif // QUEUE_STACK_H