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

int Stack::pop (bool isInsideFunction) {
    if (isEmpty()) {
        return -1;
    }

    sNode* temp = _top;
    _top = _top->_next;

    if (!isInsideFunction) {
        delete temp;

    }

    if (!isEmpty()) {
        --_size;

    }

    return 0;

}

Action Stack::peek (int place) {
    if (isEmpty()) {
        return Action();

    } else if (place == 0) {
        return _top->_data;

    } else if (place == 1) {
        if (_top->_next == nullptr) {
            return Action();

        } else {
            return _top->_next->_data;

        }

        // i got lazy, sorry

    } else {
        sNode *currentNode = _top;

        for (int counter = place; counter > 0; counter++) {
            if (currentNode->_next == nullptr) {
                return Action();

            } else {
                currentNode = currentNode->_next;

            }


        }

        return currentNode->_data;

    }
    
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
