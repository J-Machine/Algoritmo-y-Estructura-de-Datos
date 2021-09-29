#ifndef __NODE_H__
#define __NODE_H__

class Node
{
    private:
        int data;
        Node *next, *prev;
    public:
        explicit Node(int);
        ~Node();
        // Getters
        int getData() const;
        Node* getNext() const;
        Node* getPrev() const;
        // Setters
        void setData(int _data);
        void setNext(Node* _ptro);
        void setPrev(Node* _ptro);
};

Node::Node(int _data)
{
    data = _data;
    next, prev = nullptr;
}

Node::~Node()
{
    std::cout << "Se elimino el elemento "<<data<<std::endl;
}

// Getters
int Node::getData() const
{
    return data;
}
Node* Node::getNext() const
{
    return next;
}
Node* Node::getPrev() const
{
    return prev;
}
// Setters
void Node::setData(int _data)
{
    this->data = data;
}
void Node::setNext(Node* _newNode)
{
    this->next = _newNode;
}
void Node::setPrev(Node* _newNode)
{
    this->next = _newNode;
}

#endif