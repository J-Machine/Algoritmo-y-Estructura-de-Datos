#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
        T value;
        Node<T> *next;
    public:
        Node(T);

        T getValue() const;
        void setValue(T);

        void setNext(Node<T> *);
        Node<T> *getNext() const;

};

/** Implementation **/

// Constructor
template<typename T>
Node<T>::Node(T value) {
    this->value = value;
    this->next = nullptr;
}

// Métodos getters y setters
template<typename T>
T Node<T>::getValue() const {
    return value;
}

template<typename T>
void Node<T>::setValue(T value) {
    this->value = value;
}

template<typename T>
void Node<T>::setNext(Node<T> *next) {
    this->next = next;
}

template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

#endif