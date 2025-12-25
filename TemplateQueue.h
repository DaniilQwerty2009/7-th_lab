#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <iostream>

template <typename T> class Queue
{
private:
    int queueLenght;

    T* array = nullptr;    

public:
    Queue(int lenght = 0): queueLenght(lenght)
        {   }
    Queue(int lenght, T source[]): queueLenght(lenght)
    {
        array = new T[lenght];

        for(int i = 0; i < lenght; ++i)

        {
            array[i] = source[i];
        }
    }
    Queue(Queue& other): queueLenght(other.queueLenght)
    {
        delete array;

        for(int i = 0; i < queueLenght; ++i)
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

    
};

template <typename T> 
    void Queue <T>::print(std::ostream& fout) const
    {
        if(queueLenght == 0)
            fout << "Queue is empty" << std::endl;

        else
        {
            for(int i = 0; i < queueLenght; ++i)
                fout << this->array[i] << "->";
            fout << std::endl;
        }
    }









#endif