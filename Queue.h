#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    //Definicio de la estructura de un nodo
    class Node {
    public:
        T value;
        Node* next;

        Node(T val) : value(val), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size = 0;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Destructor
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Method to check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Method to get the size of the queue
    int getSize() const {
        return size;
    }

    // Method to add an element to the queue
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Method to remove and return the first element of the queue
    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("The queue is empty");
        }
        Node* nodeToDelete = front;
        T value = nodeToDelete->value;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete nodeToDelete;
        size--;
        return value;
    }

    // Method to get the first element of the queue without removing it
    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("The queue is empty");
        }
        return front->value;
    }

    // Method to get an element at a specific position in the queue
    T getElement(int pos) const {
        if (pos < 0 || pos >= size) {
            throw std::out_of_range("Invalid position");
        }
        Node* current = front;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->value;
    }
};

#endif // QUEUE_H
