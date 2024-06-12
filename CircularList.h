#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class CircularList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    CircularList() : head(nullptr), tail(nullptr), size(0) {}

    ~CircularList() {
        if (!head) return;
        Node<T>* current = head;
        do {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        } while (current != head);
    }

    void insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = tail = newNode;
            newNode->next = newNode;
        } else {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        size++;
    }

    void insertAt(T data, int position) {
        if (position < 0 || position > size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* newNode = new Node<T>(data);
        if (position == 0) {
            if (!head) {
                head = tail = newNode;
                newNode->next = newNode;
            } else {
                newNode->next = head;
                tail->next = newNode;
                head = newNode;
            }
        } else {
            Node<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == head) {
                tail = newNode;
            }
        }
        size++;
    }

    void remove(T data) {
        if (!head) return;
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        do {
            if (current->data == data) {
                if (current == head) {
                    head = head->next;
                    tail->next = head;
                    if (current == tail) {
                        tail = nullptr;
                        head = nullptr;
                    }
                } else if (current == tail) {
                    previous->next = head;
                    tail = previous;
                } else {
                    previous->next = current->next;
                }
                delete current;
                size--;
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);
    }

    void removeAt(int position) {
        if (position < 0 || position >= size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        if (position == 0) {
            head = head->next;
            tail->next = head;
            delete current;
            if (--size == 0) {
                head = nullptr;
                tail = nullptr;
            }
        } else {
            for (int i = 0; i < position; i++) {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            if (current == tail) {
                tail = previous;
            }
            delete current;
            size--;
        }
    }

    Node<T>* search(const T& key) const {
        if (!head) return nullptr;
        Node<T>* current = head;
        do {
            if (current->data == key) {
                return current;
            }
            current = current->next;
        } while (current != head);
        return nullptr;
    }

    void display() const {
        if (!head) {
            std::cout << "The list is empty." << std::endl;
            return;
        }
        Node<T>* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    int getSize() const {
        return size;
    }

    T getElement(int position) const {
        if (position < 0 || position >= size) {
            throw std::out_of_range("Invalid position");
        }
        Node<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        return current->data;
    }

    void sort() {
        if (!head) return;
        Node<T>* current = head;
        do {
            Node<T>* next = current->next;
            while (next != head) {
                if (current->data > next->data) {
                    T temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            current = current->next;
        } while (current->next != head);
    }
};

#endif // CIRCULAR_LIST_H
