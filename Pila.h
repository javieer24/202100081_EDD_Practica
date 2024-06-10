#ifndef PILA_H
#define PILA_H

#include "Nodo.h"

template <typename T>
class Pila {
private:
    Nodo<T>* cima;

public:
    Pila() : cima(nullptr) {}

    ~Pila() {
        while (cima != nullptr) {
            Nodo<T>* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
    }

    void push(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = cima;
        cima = nuevo;
    }

    void pop() {
        if (cima) {
            Nodo<T>* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
    }

    bool estaVacia() const {
        return cima == nullptr;
    }

};

#endif // PILA_H
