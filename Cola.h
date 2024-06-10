#ifndef COLA_H
#define COLA_H

#include "Nodo.h"

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}

    ~Cola() {
        while (frente != nullptr) {
            Nodo<T>* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    void encolar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (final) {
            final->siguiente = nuevo;
        } else {
            frente = nuevo;
        }
        final = nuevo;
    }

    void desencolar() {
        if (frente) {
            Nodo<T>* temp = frente;
            frente = frente->siguiente;
            if (!frente) {
                final = nullptr;
            }
            delete temp;
        }
    }

    bool estaVacia() const {
        return frente == nullptr;
    }

    T obtenerFrente() const {  // Agregado para obtener el frente
        if (frente) {
            return frente->dato;
        } else {
            throw std::runtime_error("La cola está vacía");
        }
    }
};

#endif // COLA_H
