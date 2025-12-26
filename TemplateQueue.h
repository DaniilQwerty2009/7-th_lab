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
    int getOurIndex(int index) const inline;
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
        
        T extracted = array[0];

        for(int i = 0; i < elemQty - 1; ++i)
            array[i] = array[i+1];

        elemQty--;

        return extracted;
    }

    template <typename T>
        void Queue <T>::add(T newElement)
        {
            if(elemQty == queueLenght)
                throw OwerflowQueueError();

            array[elemQty++] = newElement;
        }


    template <typename T>
        int Queue <T>::getOurIndex(int index) const inline
        {
            if(index > elemQty)
                return index % elemQty;
        else
            return index;
        }



#endif