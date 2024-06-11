#ifndef NODE_H
#define NODE_H

#include <iostream> // For std::ostream

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    ~Node() {
        // Destructor in case additional resources need to be freed in the future
    }
    
    // Method to print the node's data, useful for debugging and testing
    void print(std::ostream& os) const {
        os << data;
    }
};

// Overload of the << operator to facilitate printing of nodes
template <typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
    node.print(os);
    return os;
}

#endif // NODE_H
