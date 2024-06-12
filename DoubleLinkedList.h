#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "Node.h"
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertAtBeginning(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAtPosition(T data, int position) {
        if (position < 0 || position > size) {
            throw std::out_of_range("Invalid position");
        }
        if (position == 0) {
            insertAtBeginning(data);
        } else if (position == size) {
            insertAtEnd(data);
        } else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }
    }

    void removeFromBeginning() {
        if (!head) return;
        Node<T>* nodeToDelete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete nodeToDelete;
        size--;
    }

    void removeFromEnd() {
        if (!tail) return;
        Node<T>* nodeToDelete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete nodeToDelete;
        size--;
    }

    void removeByData(const T& data) {
        Node<T>* current = head;
        while (current) {
            if (current->data == data) {
                if (current == head) {
                    removeFromBeginning();
                } else if (current == tail) {
                    removeFromEnd();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                }
                return;
            }
            current = current->next;
        }
    }

    Node<T>* search(const std::string& key) const {
        Node<T>* current = head;
        while (current) {
            if (current->data.getNumeroPasaporte() == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayPasajeros() const {
        Node<T>* current = head;
        if (!current) {
            std::cout << "No passengers in the list." << std::endl;
            return;
        }
        while (current) {
            const T& passenger = current->data;
            std::cout << "Pasajero ID: " << passenger.getId() << std::endl;
            std::cout << "Nombre: " << passenger.getNombre() << std::endl;
            std::cout << "Apellido: " << passenger.getApellido() << std::endl;
            std::cout << "Edad: " << passenger.Edad() << std::endl;
            std::cout << "Vuelo: " << passenger.getVuelo() << std::endl;
            current = current->next;
        }
    }

    Node<T>* getHead() const {
        return head;
    }

    int getSize() const {
        return size;
    }

    T getElement(int pos) const {
        if (pos < 0 || pos >= size) {
            throw std::out_of_range("Posciión Invalida");
        }
        Node<T>* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }

    void sortByFlightNumber() {
        if (!head) return;
        Node<T>* current = head;
        while (current->next) {
            Node<T>* next = current->next;
            while (next) {
                if (current->data.getVuelo() > next->data.getVuelo()) {
                    T temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            current = current->next;
        }
    }

    void sortBySeatNumber() {
        if (!head) return;
        Node<T>* current = head;
        while (current->next) {
            Node<T>* next = current->next;
            while (next) {
                if (current->data.getAsiento() > next->data.getAsiento()) {
                    T temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                }
                next = next->next;
            }
            current = current->next;
        }
    }
};

#endif // DOUBLE_LINKED_LIST_H
