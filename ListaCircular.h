#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "Nodo.h"

template <typename T>
class ListaCircular {
public:
    Nodo<T>* cabeza;

    ListaCircular() : cabeza(nullptr) {}

    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            cabeza = nuevo;
            nuevo->siguiente = cabeza;
        } else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente != cabeza) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
            nuevo->siguiente = cabeza;
        }
    }
};

#endif // LISTACIRCULAR_H
