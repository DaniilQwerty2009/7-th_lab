#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <iostream>
#include "TemplateQueueErrors.h"

template <typename T> class Queue
{
private:
    const int queueLenght;
    int elemQty;

    int head;
    int tail;

    T* array = nullptr;    

public:
    Queue(int arrayLenght = 0): queueLenght(arrayLenght), elemQty(0), head(0), tail(elemQty)
        { array = new T[arrayLenght]; }

    Queue(int arrayLenght, int elemQty, T source[]): queueLenght(arrayLenght), elemQty(elemQty), head(0), tail(elemQty - 1)
    {
        array = new T[arrayLenght];

        for(int i = 0; i < arrayLenght; ++i)
            array[i] = source[i];
    }

    Queue(Queue& other): queueLenght(other.queueLenght), elemQty(other.elemQty)
    {
        delete array;

        for(int i = 0; i < elemQty; ++i)
        {
            array[i] = other.array[i];
        }
    }
    
    ~Queue()
        { delete[] array; }


    void print(std::ostream& fout = std::cout) const;

    friend std::ostream& operator<<(std::ostream& fout, const Queue& object)
    {
        object.print(fout);
        return fout;
    }

    T extract();
    void add(T newElement);
    int getOurIndex(int index) const;
};

template <typename T> 
    void Queue <T>::print(std::ostream& fout) const
    {
        if(elemQty == 0)
        {
            std::cout << "\n";
            return;
        }

        else
        {
            for(int i = 0; i < elemQty; ++i)
            {
                fout << this->array[i];
                if(i < elemQty - 1)
                std::cout << " <- ";
            }
        }
    }

template <typename T>
    T Queue <T>::extract()
    {
        if(elemQty == 0)
            throw EmptyQueueError();
        
        T extracted = array[head];

        head = getOurIndex(head + 1);
        elemQty--;

        return extracted;
    }


    template <typename T>
        void Queue <T>::add(T newElement)
        {
            if(queueLenght == 0)
                throw OwerflowQueueError();

            if(elemQty == queueLenght)
                throw OwerflowQueueError();
            
            if(elemQty == 0)
            {
                head = newElement;
                return;
            }

            tail = getOurIndex(tail + 1);
            tail = newElement;
        }


    template <typename T>
        int Queue <T>::getOurIndex(int index) const
        {
            if(index > elemQty)
                return (index % queueLenght) - 1;   //Остаток от деления - позиция элемента (счет с единицы, так что -1)
            else
                return index;
        }

#endif