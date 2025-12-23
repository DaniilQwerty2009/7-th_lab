#include <iostream>

#include "TemplateQueue.h"

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

