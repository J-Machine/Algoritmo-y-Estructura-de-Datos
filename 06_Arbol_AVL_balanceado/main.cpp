#include <bits/stdc++.h>

using namespace std;

template <class T>
class Node
{
public:
    T dato;
    Node *son[2];
    int FE = 0;

    Node(const T &d)
    {
        dato = d;
        son[0] = 0;
        son[1] = 0;
    }
};

template <class T>
class AVL
{
    Node<T> *root;

public:
    AVL() : root(0){};
    void setRoot(T &newRoot)
    {
        root->dato = newRoot;
    }
    void RRL(Node<T> *&p)
    {
        Node<T> *q = p->son[1];
        Node<T> *r = q->son[0];

        q->son[0] = r->son[1];
        p->son[1] = r->son[0];

        r->son[1] = q;
        r->son[0] = p;

        switch (r->FE)
        {
        case 0:
            p->FE = 0, q->FE = 0;
            break;
        case 1:
            p->FE = -1, q->FE = 0, r->FE = 0;
            break;
        case -1:
            q->FE = 1, p->FE = 0;
            r->FE = 0;
            break;
        }
        p = r;
    }

    void RLR(Node<T> *&p)
    {
        Node<T> *q = p->son[0];
        Node<T> *r = q->son[1];

        p->son[0] = r->son[1];
        q->son[1] = r->son[0];

        r->son[1] = p;
        r->son[0] = q;

        switch (r->FE)
        {
        case 0:
            p->FE = 0, q->FE = 0;
            break;
        case 1:
            q->FE = -1, p->FE = 0, r->FE = 0;
            break;
        case -1:
            p->FE = 1, q->FE = 0, r->FE = 0;
            break;
        }
        p = r;
    }

    void RRR(Node<T> *&p)
    {
        Node<T> *q = p->son[1];
        p->son[1] = q->son[0];
        q->son[0] = p;
        p->FE = q->FE = 0;
        p = q;
    }

    void RLL(Node<T> *&p)
    {
        Node<T> *q = p->son[0];
        p->son[0] = q->son[1];
        q->son[1] = p;
        p->FE = q->FE = 0;
        p = q;
    }

    bool insert(const T &d, Node<T> *&aux)
    {
        if (aux == nullptr)
        {
            aux = new Node<T>(d);
            return true;
        }
        if (aux->dato == d)
            return false;
        if (insert(d, aux->son[d > aux->dato]))
        {
            if (d < aux->dato)
                aux->FE--;
            else
                aux->FE++;
            switch (aux->FE)
            {
            case 2:
                if (aux->son[1]->FE == 1)
                    RRR(aux);
                else
                    RRL(aux);
                if (aux->FE == 0)
                    return false;
            case -2:
                if (aux->son[0]->FE == -1)
                    RLL(aux);
                else
                    RLR(aux);
                if (aux->FE == 0)
                    return false;
            }
        }
    }

    bool insert(const T &d)
    {
        return insert(d, root);
    }

    Node<T> *findMax(Node<T> *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->son[1] == nullptr)
            return t;
        return findMax(t->son[1]);
    }

    bool remove(T x, Node<T> *&t)
    {
        if (t == nullptr)
            return false;
        if (x < t->dato || x > t->dato)
        {
            if (remove(x, t->son[x > t->dato]))
            {
                if (x < t->dato)
                    t->FE++;
                else
                    t->FE--;
                switch (t->FE)
                {
                case 2:
                    if (t->son[0]->FE == 0)
                    {
                        RRR(t);
                        t->son[0]->FE = 1;
                        t->FE = -1;
                    }
                    else if (t->son[1]->FE == 1)
                        RRR(t);
                    else
                        RRL(t);
                    break;
                case -2:
                    if (t->son[0]->FE == 0)
                    {
                        RLL(t);
                        t->son[1]->FE = -1;
                        t->FE = 1;
                    }
                    else if (t->son[0]->FE == -1)
                        RLL(t);
                    else
                        RLR(t);
                    break;
                }
                if (t->FE == 0)
                    return true;
                else
                    return false;
            }
        }
        else if (t->son[0] != nullptr && t->son[1] != nullptr)
        {
            t->dato = findMax(t->son[0])->dato;
            if (remove(t->dato, t->son[0]))
            {
                t->FE++;
                switch (t->FE)
                {
                case 2:
                    if (t->son[0]->FE == 0)
                    {
                        RRR(t);
                        t->son[0]->FE = 1;
                        t->FE = -1;
                    }
                    else if (t->son[1]->FE == 1)
                        RRR(t);
                    else
                        RRL(t);
                    break;
                case -2:
                    if (t->son[0]->FE == 0)
                    {
                        RLL(t);
                        t->son[1]->FE = -1;
                        t->FE = 1;
                    }
                    else if (t->son[0]->FE == -1)
                        RLL(t);
                    else
                        RLR(t);
                    break;
                }
                if (t->FE == 0)
                    return true;
                else
                    return false;
            }
        }
        else
        {
            Node<T> *aux = t;
            t = (t->son[0] != nullptr) ? t->son[0] : t->son[1];
            delete aux;
            return true;
        }
    }

    bool remove(const T &d)
    {
        return remove(d, root);
    }

    // Pre Order
    std::string preorder()
    {
        std::string cad;
        preorder(root, cad);
        return cad;
    }

    void preorder(Node<T> *aux, std::string &cadena)
    {
        if (!aux)
            return;
        cadena += to_string(aux->dato) + "->";
        postorder(aux->son[0], cadena);
        postorder(aux->son[1], cadena);
    }

    // In Order
    std::string inorder()
    {
        std::string cad;
        inorder(root, cad);
        return cad;
    }
    void inorder(Node<T> *aux, std::string &cadena)
    {
        if (!aux)
            return;
        inorder(aux->son[0], cadena);
        cadena += to_string(aux->dato) + "->";
        inorder(aux->son[1], cadena);
    }

    // Post Order
    std::string postorder()
    {
        std::string cad;
        postorder(root, cad);
        return cad;
    }
    void postorder(Node<T> *aux, std::string &cadena)
    {
        if (!aux)
            return;
        postorder(aux->son[0], cadena);
        postorder(aux->son[1], cadena);
        cadena += to_string(aux->dato) + "->";
    }

    bool find(const T &d, Node<T> *p)
    {
        if (p == nullptr)
            return false;
        if (p->dato == d)
            return true;
        else if (p->dato > d)
            return find(d, p->son[0]);
        else if (p->dato < d)
            return find(d, p->son[1]);
        else
            return false;
    }

    bool find(const T &d)
    {
        return find(d, root);
    }

    // Vaciar arbol
    void clearNodes(Node<T> *_node)
    {
        if (!_node)
            return;
        clearNodes(_node->son[0]);
        clearNodes(_node->son[1]);
        cout << "\n Eliminando nodo: " << _node->dato;
        if (_node == root)
            root = 0;
        else
            delete _node;
    }

    void clear()
    {
        clearNodes(root);
    }

    //////////////////////GRAFICAR//////////////////////////////////
    void escribirdot(ofstream &archivo, Node<T> *ARBOL, int i)
    {
        if (ARBOL)
        {
            if (ARBOL->dato)
            { // solo si ARBOL LETRA NO ESTA VACIO
                archivo << "\"" << ARBOL << "\" [label=\"<f0> " << ARBOL->dato << "|<f1>" << ARBOL->FE << "\"];\n";
            }
            else
            { // si lo esta solo manda cantidad
                archivo << "\"" << ARBOL << "\" [label=\"<f0> |<f1> " << ARBOL->FE << "\"];\n";
            }
            if (ARBOL->son[0])
            {
                archivo << "\"" << ARBOL << "\" -> \"" << ARBOL->son[0] << "\"\n";
            }
            if (ARBOL->son[1])
            {
                archivo << "\"" << ARBOL << "\" -> \"" << ARBOL->son[1] << "\"\n";
            }
            escribirdot(archivo, ARBOL->son[0], i); // recorrer por la derecha
            escribirdot(archivo, ARBOL->son[1], i); // recorrer por la izquierda
        }
    }

    void graficar()
    {
        ofstream arch;
        arch.open("D:\\Graphviz\\bin\\arbolavl.dot");
        if (arch.is_open())
        {
            arch << "digraph C { \n";
            arch << "node [shape=record];\n";
            escribirdot(arch, root, 0);
            arch << "}\n";
            arch.close();
            system("dot -Tpng D:\\Graphviz\\bin\\arbolavl.dot -o D:\\Graphviz\\bin\\arbolavl.png ");
        }
        else
        {
            cout << "error al crear archivo";
        }
    }
};

int main()
{
    AVL<int> A;
    // INSERTAR
    int x;
    int a, b;
    do
    {
        cout << "\nMENU\n";
        cout << "1) Insertar\n";
        cout << "2) Eliminar\n";
        cout << "3) Buscar\n";
        cout << "4) Elementos en Pre orden\n";
        cout << "5) Elementos en In orden\n";
        cout << "6) Elementos en Post orden\n";
        cout << "7) Clear\n";
        cout << "8) Graficar\n";
        cout << "9) SALIR\n";
        cout << "\nIngrese la opcion: ";
        cin >> a;
        switch (a)
        {
        case 1:
            for (int i = 1; i < 51; i++)
            {
                A.insert(i);
            }
            break;
        case 2:
            cout << endl;
            cout << " Ingrese valor para eliminar ... ";
            cin >> x;
            cout << (A.remove(x) ? " Eliminado" : " No eliminado") << endl;
            cout << endl;
            break;
        case 3:
            cout << endl;
            cout << " Ingrese valor para buscar : ";
            cin >> x;
            cout << (A.find(x) ? " Encontrado" : " No encontrado") << endl;
            cout << endl;
            break;
        case 4:
            cout << endl;
            cout << " Arbol en PreOrden: ";
            cout << A.preorder() << endl;
            break;
        case 5:
            cout << endl;
            cout << " Arbol en InOrden: ";
            cout << A.inorder() << endl;
            break;
        case 6:
            cout << " Arbol en PostOrden: ";
            cout << A.postorder() << endl;
            break;
        case 7:
            cout << " Vaciando arbol: ";
            A.clear();
            cout << endl;
            break;

        case 8:
            cout << " Generando gráfico del arbol";
            A.graficar();
            system("D:\\Graphviz\\bin\\arbolavl.png");
            break;

        case 9:
            cout << endl;
            cout << "Seguro que quiere salir?(SI=1)(NO=0) :";
            cin >> b;
            cout << endl;
            if (b == 1)
                a = 0;
            else if (b == 0)
                break;
        }
    } while (a != 0);
    return 0;
}
