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

    T& operator[](int index) = delete;
    const T& operator[](int index) const;

    T extract();
    const T& front() const;
    const T& back() const;
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
            for(int i = 0, j = head; i < elemQty; ++i)
            {
                fout << this->array[getOurIndex(j++)];
                
                if(i < elemQty - 1)
                    fout << " <- ";
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
            
            if((elemQty++) == 0)
            {
                array[tail] = newElement;
                return;
            }

            tail = getOurIndex(tail + 1);
            array[tail] = newElement;
        }


    template <typename T>
        int Queue <T>::getOurIndex(int index) const
        {
            if(index > elemQty-1)
                return (index % queueLenght);
            else
                return index;
        }

    template <typename T>
        const T& Queue <T>::front() const
        {
            return array[head];
        }

    template <typename T>
        const T& Queue <T>::back() const
        {
            return array[tail];
        }

    template <typename T>
        const T& Queue <T>::operator[](int index) const
        {
            return array[getOurIndex(index)];
        }

#endif