#ifndef CIRCULAR_DOUBLE_LIST_H
#define CIRCULAR_DOUBLE_LIST_H

#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class CircularDoubleList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    CircularDoubleList() : head(nullptr), tail(nullptr), size(0) {} // Constructor

    ~CircularDoubleList() { // Destructor
        clear();
    }

    void insert(const T& data) {
        Node<T>* newNode = new Node<T>(data); // Crea un nuevo nodo

        if (isEmpty()) { // Si la lista está vacía
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->prev = tail;
            newNode->next = head;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }

        size++;
    }

    void remove(const T& data) { // Elimina un nodo de la lista
        if (isEmpty()) {
            return;
        }

        Node<T>* current = head; // Nodo actual

        do {
            if (current->data == data) {
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    head = current->next;
                    tail->next = head;
                    head->prev = tail;
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = head;
                    head->prev = tail;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                size--;
                return;
            }

            current = current->next;
        } while (current != head);
    }

    bool isEmpty() const {   // Devuelve true si la lista está vacía
        return size == 0;
    }

    void clear() {  // Elimina todos los nodos de la lista
        if (!isEmpty()) {
            Node<T>* current = head;

            do {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            } while (current != head);

            head = nullptr;
            tail = nullptr;
            size = 0;
        }
    }

    void print() const {  // Imprime los elementos de la lista
        if (isEmpty()) {
            std::cout << "The list is empty" << std::endl;
            return;
        }

        Node<T>* current = head;

        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);

        std::cout << std::endl;  // Salto de línea
    }

    int getSize() const {  // Devuelve el tamaño de la lista
        return size;
    }

    T getElement(int index) const {  // Devuelve el elemento en la posición index
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    T* searchByRegistrationNumber(const std::string& registrationNumber) const { // Devuelve un puntero al dato buscado
        if (isEmpty()) {
            return nullptr;
        }

        Node<T>* current = head;

        do {
            if (current->data.getRegistrationNumber() == registrationNumber) {
                return &(current->data);  // Devuelve un puntero al dato buscado
            }

            current = current->next;
        } while (current != head);

        return nullptr; // No se encontró el elemento
    }

    void removeByRegistrationNumber(const std::string& registrationNumber) {
        if (isEmpty()) {
            return;  // La lista está vacía
        }

        Node<T>* current = head;

        do {
            if (current->data.getRegistrationNumber() == registrationNumber) {  // Se encontró el elemento
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (current == head) {
                    head = current->next;
                    tail->next = head;
                    head->prev = tail;
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = head;
                    head->prev = tail;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                size--;
                return;
            }

            current = current->next;
        } while (current != head);
    }

    Node<T>* getHead() const {
        return head;  // Devuelve el puntero al primer nodo de la lista
    }
};

#endif // CIRCULAR_DOUBLE_LIST_H
