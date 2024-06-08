#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaCircularDoble() : cabeza(nullptr), cola(nullptr) {}

    ~ListaCircularDoble() {
        if (!cabeza) return;
        Nodo<T>* actual = cabeza;
        do {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        } while (actual != cabeza);
    }

    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            cabeza = cola = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
        } else {
            nuevo->siguiente = cabeza;
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cabeza->anterior = nuevo;
            cola = nuevo;
        }
    }

    Nodo<T>* buscar(const T& dato) {
        if (!cabeza) return nullptr;
        Nodo<T>* actual = cabeza;
        do {
            if (actual->dato == dato) return actual;
            actual = actual->siguiente;
        } while (actual != cabeza);
        return nullptr;
    }

    void eliminar(const T& dato) {
        if (!cabeza) return;
        Nodo<T>* actual = cabeza;
        do {
            if (actual->dato == dato) {
                if (actual == cabeza && actual == cola) {
                    delete actual;
                    cabeza = cola = nullptr;
                } else {
                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;
                    if (actual == cabeza) cabeza = actual->siguiente;
                    if (actual == cola) cola = actual->anterior;
                    delete actual;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    void mostrar() const {
        if (!cabeza) return;
        Nodo<T>* actual = cabeza;
        do {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        } while (actual != cabeza);
        std::cout << std::endl;
    }
};

#endif // LISTACIRCULARDOBLE_H
