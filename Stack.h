#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack();

    void push(const T& value);
    void pop();
    T peek() const;
    bool isEmpty() const;
    void clear();
    int getSize() const;
    T getElement(int position) const;
};

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    Node* newNode = new Node{value, top};
    top = newNode;
}

template <typename T>
void Stack<T>::pop() {
    if (top != nullptr) {
        Node* nodeToDelete = top;
        top = top->next;
        delete nodeToDelete;
    } else {
        std::cerr << "Error: The stack is empty, cannot pop." << std::endl;
    }
}

template <typename T>
T Stack<T>::peek() const {
    if (top != nullptr) {
        return top->data;
    } else {
        std::cerr << "Error: The stack is empty, cannot get the top element." << std::endl;
        throw std::runtime_error("The stack is empty"); // Lanza una excepción en lugar de devolver un valor por defecto

    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
int Stack<T>::getSize() const {
    int size = 0;
    Node* currentNode = top;
    while (currentNode != nullptr) {
        size++;
        currentNode = currentNode->next;
    }
    return size;
}

template <typename T>
T Stack<T>::getElement(int position) const {
    if (position < 0) {
        std::cerr << "Error: The position cannot be negative." << std::endl;
        throw std::out_of_range("Invalid position"); // Lanza una excepción en lugar de devolver un valor por defecto

    }

    Node* currentNode = top;
    for (int i = 0; i < position && currentNode != nullptr; i++) {
        currentNode = currentNode->next;
    }

    if (currentNode != nullptr) {
        return currentNode->data;
    } else {
        std::cerr << "Error: The position is out of range." << std::endl;
        throw std::out_of_range("Position out of range"); // Lanza una excepción en lugar de devolver un valor por defecto

    }
}

#endif // STACK_H
