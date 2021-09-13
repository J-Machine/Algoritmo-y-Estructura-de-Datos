/** LAB 01: 
/*    1. Implementar una lista enlazada simple (estructura o clase) considerando las funciones:
/*    ● Insertar
/*    ● Buscar
/*    ● Eliminar
/*    ● Imprimir
**/
#include <iostream>
#include "SimpleList.h"
using namespace std;



int main ()
{
    SimpleList<int> lista;
    lista.insert(15);
    lista.insert(20);
    lista.insert(25);
    lista.insert(8);
    lista.insert(1);
    lista.print();
    lista.remove(8);
    lista.print();
    lista.search(8);
    lista.search(2);

    return 0;
}