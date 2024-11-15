#include <iostream>
#include <string>

struct Node {
    int data;
    Node* next;
    
    Node(int data) : data(data), next(nullptr) {}
};

class Stack {
public:
    Node* top;

    Stack() : top(nullptr) {}

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty!\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (isEmpty()) {
            std::cout << "Stack is empty!\n";
            return -1;
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Queue {
public:
    Node* front;
    Node* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    int peek() {
        if (isEmpty()) {
            std::cout << "Queue is empty!\n";
            return -1;
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

void displayStack(Stack& stack) {
    Stack tempStack;
    while (!stack.isEmpty()) {
        int data = stack.peek();
        std::cout << data << " ";
        tempStack.push(data);
        stack.pop();
    }
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.peek());
        tempStack.pop();
    }
    std::cout << '\n';
}

void displayQueue(Queue& queue) {
    Queue tempQueue;
    while (!queue.isEmpty()) {
        int data = queue.peek();
        std::cout << data << " ";
        tempQueue.enqueue(data);
        queue.dequeue();
    }
    while (!tempQueue.isEmpty()) {
        queue.enqueue(tempQueue.peek());
        tempQueue.dequeue();
    }
    std::cout << '\n';
}

int main() {
    Stack stack;
    Queue queue;
    int choice, value;

    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Push to Stack\n";
        std::cout << "2. Pop from Stack\n";
        std::cout << "3. Display Stack\n";
        std::cout << "4. Enqueue to Queue\n";
        std::cout << "5. Dequeue from Queue\n";
        std::cout << "6. Display Queue\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to push to stack: ";
                std::cin >> value;
                stack.push(value);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                std::cout << "Stack contents: ";
                displayStack(stack);
                break;
            case 4:
                std::cout << "Enter value to enqueue to queue: ";
                std::cin >> value;
                queue.enqueue(value);
                break;
            case 5:
                queue.dequeue();
                break;
            case 6:
                std::cout << "Queue contents: ";
                displayQueue(queue);
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
