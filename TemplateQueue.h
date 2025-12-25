#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <iostream>
#include "TemplateQueueErrors.h"

template <typename T> class Queue
{
private:
    const int queueLenght;
    int elemCounter;

    T* array = nullptr;    

public:
    Queue(int lenght = 0): queueLenght(lenght), elemCounter(0)
        { array = new T[lenght]; }

    Queue(int lenght, T source[]): queueLenght(lenght), elemCounter(lenght)
    {
        array = new T[lenght];

        for(int i = 0; i < lenght; ++i)
            array[i] = source[i];
    }

    Queue(Queue& other): queueLenght(other.queueLenght), elemCounter(other.elemCounter)
    {
        delete array;

        for(int i = 0; i < elemCounter; ++i)
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
};

template <typename T> 
    void Queue <T>::print(std::ostream& fout) const
    {
        if(elemCounter == 0)
        {
            std::cout << "\n";
            return;
        }

        else
        {
            for(int i = 0; i < elemCounter; ++i)
            {
                fout << this->array[i];
                if(i < elemCounter - 1)
                std::cout << " <- ";
            }
        }
    }

template <typename T>
    T Queue <T>::extract()
    {
        if(elemCounter == 0)
            throw EmptyQueueError();
        
        T extracted = array[0];

        for(int i = 0; i < elemCounter - 1; ++i)
            array[i] = array[i+1];

        elemCounter--;
        return extracted;
    }

    template <typename T>
        void Queue <T>::add(T newElement)
        {
            if(elemCounter == queueLenght)
                throw OwerflowQueueError();

            array[elemCounter++] = newElement;
        }






#endif