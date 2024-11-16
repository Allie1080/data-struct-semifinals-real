#include <iostream>
#include <stdio.h>

#include "queue_stack.h"
#include "combat-data.h"

qNode::qNode (Enemy data) {
    _data = data;
    _next = nullptr;
    
}

Queue::Queue () {
    _front = nullptr;
    _rear = nullptr;

}

void Queue::enqueue (Enemy data) {
    qNode* newNode = new qNode(data);

    if (isEmpty()) {
        _front = _rear = newNode;
    
    } else {
        _rear->_next = newNode;
        _rear = newNode;

    }

    ++_size;

}

int Queue::dequeue (bool isInsideFunction=false) {
    if (isEmpty()) {
        return -1;
    
    }

    // std::cout << "is not empty" << '\n';

    qNode* temp = _front;
    // std::cout << "temp created" << '\n';
    _front = _front->_next;
    // std::cout << "front moved" << '\n';

    if (_front == nullptr) {
        // std::cout << "front is nullptr" << '\n';
        _rear = nullptr;
        // std::cout << "rear turned to nullptr" << '\n';
    
    } else {
        // std::cout << "front not nullptr" << '\n';

    } 

    if (isInsideFunction) {
        delete temp;
        // std::cout << "temp deleted" << '\n';

    }

    --_size;
    std::cout << "size reduced" << '\n';

    return 0;
}

Enemy Queue::peek() {
    if (isEmpty()) {
        return Enemy();

    }

    return _front->_data;

}

int Queue::getSize () const {
    return _size;

}

bool Queue::isEmpty() const {
    return _front == nullptr;

}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Enemy viewEnemy (Queue queue, int placementIndex=0) {
//     Enemy enemy;
  
//     std::cout << '\n' << queue.getSize() << '\n';
//     if (placementIndex != 0) {
//         for (int counter{0}; counter < placementIndex; counter++) {
//             std::cout << "Loop executed" << '\n';
//             queue.dequeue(true);
//             std::cout << "Dequeue executed" << '\n';

//         }

//     } else {
//         std::cout << "Not executed" << '\n';

//     }

//     enemy = queue.peek();

//     return enemy;

// }

// void updateCharacterStatistics (Enemy enemy, bool isFront=false) {
//     if (!isFront) {
//         printf("%s's HP:  %d/%d", enemy.getName().c_str(), enemy.getCurrentHealth(), enemy.getMaxHealth());

//     } else if (enemy.getCurrentHealth() <= enemy.getCriticalHealth()) {
//         printf("%s's HP: ", enemy.getName().c_str());
//         printf("%d/%d", enemy.getCurrentHealth(), enemy.getMaxHealth());

//     } else {
//         printf("%s's HP:  %d/%d", enemy.getName().c_str(), enemy.getCurrentHealth(), enemy.getMaxHealth());

//     }

// }


// int main () {

//     static Queue *enemyQueue = new Queue();
//     enemyQueue->enqueue(Enemy(WATER, Size::MEDIUM, 3, "OCEAN DEMON"));
//     enemyQueue->enqueue(Enemy(WATER, Size::MEDIUM, 3, "FOREST DEMON"));
//     enemyQueue->enqueue(Enemy(WATER, Size::MEDIUM, 3, "MAGMA DEMON"));

//     std::cout << enemyQueue->peek().getName() << '\n';
//     enemyQueue->dequeue();
//     std::cout << enemyQueue->peek().getName() << '\n';
//     updateCharacterStatistics(viewEnemy(*enemyQueue));
//     updateCharacterStatistics(viewEnemy(*enemyQueue, 1));

// }