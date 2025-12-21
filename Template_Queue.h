#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H


template <typename T> class Queue
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node* next;
    };

    Node* head;
    Node* tail;

public:
    

};











#endif