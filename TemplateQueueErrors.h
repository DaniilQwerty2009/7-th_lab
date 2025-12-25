#ifndef TEMPLATE_QUEUE_ERROR_H
#define TEMPLATE_QUEUE_ERROR_H 

#include <stdexcept>
#include <iostream>

#include "TemplateQueue.h"

class TemplateQueueErrors : public std::exception
{
protected:
    const char* message;

public:
    TemplateQueueErrors(const char* errorMsg): message(errorMsg)
        {   }
    TemplateQueueErrors(TemplateQueueErrors& other): message(other.message)
        {   }


    virtual const char* what()
    { return message; }
};

class EmptyQueueError : public TemplateQueueErrors
{
public:
    EmptyQueueError(): TemplateQueueErrors("Ошибка: попытка извлечения из пустой очереди")
        {   }
};

class OwerflowQueueError : public TemplateQueueErrors
{
public:
    OwerflowQueueError(): TemplateQueueErrors("Ошибка: попытка добавления элемента в полностью заполненную очередь")
        {   }
};

#endif