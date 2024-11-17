#include <iostream>

#include "queue_stack.h"


sNode::sNode (Action data) {
    _data = data;
    _next = nullptr;
    
}

Stack::Stack () {
    _top = nullptr;

} 

void Stack::push (Action data) {
    sNode* newNode = new sNode(data);
    newNode->_next = _top;
    _top = newNode;

    ++_size;

}

int Stack::pop () {
    if (isEmpty()) {
        return -1;
    }

    sNode* temp = _top;
    _top = _top->_next;
    delete temp;

    if (!isEmpty()) {
        --_size;

    }

    return 0;

}

Action Stack::peek () {
    if (isEmpty()) {
        return Action();

    }
    
    return _top->_data;
}

bool Stack::isEmpty () const {
    return _top == nullptr;
}

int Stack::getSize () const {
    return _size;

}

Stack::~Stack () {
    while (!isEmpty()) {
        pop();
    }
}
