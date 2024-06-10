#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.h"
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDoble() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
    }

    void insertar(T dato, int posicion) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (posicion == 0) {
            if (!cabeza) {
                cabeza = cola = nuevo;
            } else {
                nuevo->siguiente = cabeza;
                cabeza->anterior = nuevo;
                cabeza = nuevo;
            }
        } else {
            Nodo<T>* actual = cabeza;
            int indice = 0;
            while (actual && indice < posicion - 1) {
                actual = actual->siguiente;
                indice++;
            }
            if (!actual) {
                agregar(dato);
            } else {
                nuevo->siguiente = actual->siguiente;
                if (actual->siguiente) {
                    actual->siguiente->anterior = nuevo;
                }
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
                if (!nuevo->siguiente) {
                    cola = nuevo;
                }
            }
        }
    }

    Nodo<T>* buscar(string key) {
        Nodo<T>* actual = cabeza;
        while (actual) {
            if (actual->dato.getNumeroDePasaporte() == key) {  // Asumiendo que el método getNumeroDePasaporte() existe en T
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    Nodo<T>* obtenerCabeza() const {  // Método público para obtener la cabeza
        return cabeza;
    }

    void consultarPasajeros() {
        Nodo<T>* actual = cabeza;

        if (!actual) {
            cout << "No hay pasajeros en la lista." << endl;
            return;
        }

        while (actual) {
            T pasajero = actual->dato;
            cout << "Pasajero ID: " << pasajero.getId() << endl;
            cout << "Nombre: " << pasajero.getNombre() << endl;
            cout << "Apellido: " << pasajero.getApellido() << endl;
            cout << "Edad: " << pasajero.getEdad() << endl;
            cout << "Vuelo: " << pasajero.getVuelo() << endl;

            actual = actual->siguiente;
        }
    }
};

#endif // LISTADOBLE_H
