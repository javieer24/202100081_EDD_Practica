#ifndef NODO_H
#define NODO_H

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(const T& dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
    
    ~Nodo() {
        // Destructor por si senecesitas liberar recursos adicionales en el futuro
    }
};

#endif // NODO_H
