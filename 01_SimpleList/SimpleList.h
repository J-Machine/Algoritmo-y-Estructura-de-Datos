#ifndef __SIMPLELIST_H__
#define __SIMPLELIST_H__
#include <iostream>
#include "Node.h"

template <typename T>
class SimpleList;

template <typename T>
std::ostream& operator<<(std::ostream &out,const SimpleList<T> &p);

template <typename T>
class SimpleList {
        int size;
        Node<T> *head;
    public:
        SimpleList();
        SimpleList(T);
        SimpleList(const SimpleList&);
        ~SimpleList();

        void insert(T);
        void remove(T); // remove by value
        bool search(T); // search by value
        void print(); 

        int getSize() const;
};

/** Implementación **/

//Constructor por defecto
template <typename T>
SimpleList<T>::SimpleList() {
    this->size = 0;
    this->head = nullptr;
}
//Constructor parametrizado
template <typename T>
SimpleList<T>::SimpleList(T value) {
    this->size = 1;
    this->head = new Node<T>(value);
}
//Constructor copia
template <typename T>
SimpleList<T>::SimpleList(const SimpleList<T> &o) {
    this->size = o.size;
    Node<T>* nuevo = o.head;
    while(nuevo->getNext() != nullptr){
        insert(nuevo->getValue());
        nuevo = nuevo->getNext();
    }
}
//Destructor
template <typename T>
SimpleList<T>::~SimpleList() {
    Node<T> *p = head;
    while(p){
        p = head->getNext();
        delete head;
        head = p;
    }
}

// Insertar por valor
// Inserta el valor de forma ordenada en la lista
template <typename T>
void SimpleList<T>::insert(T value) {
    Node<T> *new_node = new Node<T>(value);
    Node<T> *temp = head;
    if (!head) {
        head = new_node;
    }else {
        if (head->getValue() > value) {
            new_node->setNext(head);
            head = new_node;
        } else {
            while ((temp->getNext() != nullptr) && (temp->getNext()->getValue() < value)) {
                temp=(temp->getNext());
            }
            new_node->setNext(temp->getNext());
            temp->setNext(new_node);
        }
    }
    size++;
}

//Eliminar por valor
//Recorre la lista hasta encontrar el valor solicitado para eliminar ese nodo 
template <typename T>
void SimpleList<T>::remove(T value) {
    if (head != nullptr){
        Node<T> *temp = nullptr;
        Node<T> *aux_borrar = head;

        while(aux_borrar != nullptr && aux_borrar->getValue() != value){
            temp = aux_borrar;
            aux_borrar = aux_borrar->getNext();
        }
        if(temp == nullptr){
            head = head->getNext();
            delete aux_borrar;
            std::cout << "No se encontró el valor en la lista" << std::endl;
        }
        else {
            temp->setNext(aux_borrar->getNext());
            delete aux_borrar;
        }
    }
    else
        std::cout << "La lista está vacía" << std::endl;
}

//Buscar por valor
//Si encuentra el valor devuelve true. Si no lo encuentra devuelve falso
template <typename T>
bool SimpleList<T>::search(T value) {
    Node<T> *actual = head;
    Node<T> *anterior = nullptr;
    
    while(actual->getValue() != value && actual->getNext() != nullptr){     // Recorre hasta encontrar el valor o llegar al final de la lista
        anterior = actual;
        actual = actual->getNext();
    }
    if(actual->getValue() != value && actual->getNext() ==nullptr ){
        return false;
    } else {
        return true;
    }
}

//Imprimir lista
//Recorre la lista mostrando su valor
template <typename T>
void SimpleList<T>::print() {
    Node<T> *actual = this->head; 
    if(actual == nullptr){
        std::cout << "La lista está vacía" << std::endl;
    } else {
        while(actual){
            if(actual->getNext()==nullptr){
                std::cout << actual->getValue() << "]";
            }else{
                std::cout << actual->getValue() << "->";
            }
            actual = actual->getNext();
        }
        std::cout << std::endl;
    }
}


template <typename T>
int SimpleList<T>::getSize() const {
    return size;
}


#endif