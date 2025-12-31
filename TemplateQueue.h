#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <iostream>
#include "TemplateQueueErrors.h"

template <typename T> class Queue
{
private:
    const int queueLenght;  //Параметр-размерность очереди
    int elemQty;            //Кол-во элементов

    int head;
    int tail;

    T* array = nullptr;    

public:
    //Конструктор по умолчанию
    Queue(int arrayLenght = 0): queueLenght(arrayLenght), elemQty(0), head(0), tail(elemQty)
        { array = new T[arrayLenght]; }

    //Конструктор для копирования из массива
    Queue(int arrayLenght,  //Выделение памяти под кол-во элементов
          int elemQty,      //Кол-во импортируемых элементов
          T source[])     //Источник импорта
        : queueLenght(arrayLenght), elemQty(elemQty), head(0), tail(elemQty - 1)
    {
        array = new T[arrayLenght];

        for(int i = 0; i < arrayLenght; ++i)
            array[i] = source[i];
    }

    //Конструктор копирования
    Queue(Queue& other): queueLenght(other.queueLenght), elemQty(other.elemQty), head(0), tail(elemQty - 1)
    {
        delete array;
        array = new T[queueLenght];

        for(int i = 0, j = other.getHeadIndex(); i < elemQty; ++i)
        {
            array[i] = other.array[j];
            j = getOurIndex(++j);
        }
    }
    
    ~Queue()
        { delete[] array; }


    
    int getHeadIndex() const
    {
        return head;
    }

    void print(std::ostream& fout = std::cout) const;

    friend std::ostream& operator<<(std::ostream& fout, const Queue& object)
    {
        object.print(fout);
        return fout;
    }

    const T& operator[](int index) const;       //Показать по индексу

    T extract();        //Извлечение певрого
    const T& front() const;     //Показать первый
    const T& back() const;      //Показать последний
    void add(T newElement);     //Добавление в конец
    int getOurIndex(int index) const;       //"Цикличный" индекс - при переходе за крайнее значение возвращается в начало пока не дойдет до нужного
};

template <typename T> 
    void Queue <T>::print(std::ostream& fout) const
    {
        if(elemQty == 0)        //Пропускаем пустую очередь
        {
            std::cout << "\n";
            return;
        }

        else
        {
            for(int i = 0, j = head; i < elemQty; ++i)
            {
                fout << this->array[getOurIndex(j++)];      //Печатем поэлементно
                
                if(i < elemQty - 1)
                    fout << " <- ";
            }
        }
    }

template <typename T>
    T Queue <T>::extract()
    {
        if(elemQty == 0)            //Ошибка при попытке извлечь из пустой очереди
            throw EmptyQueueError();
        
        T extracted = array[head];

        head = getOurIndex(head + 1);   //Обновляем индекс первого
        elemQty--;

        return extracted;
    }


    template <typename T>
        void Queue <T>::add(T newElement)
        {
            if(queueLenght == 0)            //Ошибка переполнения очереди
                throw OwerflowQueueError();

            if(elemQty == queueLenght)      //Ошибка переполнения очереди
                throw OwerflowQueueError();
            
            if((elemQty++) == 0)
            {
                array[tail] = newElement;
                return;
            }

            tail = getOurIndex(tail + 1);   //Обновляем индекс последнего
            array[tail] = newElement;
        }


    template <typename T>
        int Queue <T>::getOurIndex(int index) const
        {
            if(index > elemQty-1)           //Если искомый индекс больше длинны очереди, ищем по остатку от деления (остаток - новый индекс) 
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