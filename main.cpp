#include <iostream>
#include <iomanip>
#include <windows.h>

#include "TemplateQueue.h"


using std::cout;
using std::endl;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << std::setfill('=') << std::setw(60) << '=' << endl;
    cout << "ЛАБОРАТОРНАЯ РАБОТА №7" << endl; 
    cout << "ПРИМЕНЕНИЕ ШАБЛОНОВ ФУНКЦИЙ И КЛАССОВ" << endl;
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Создадим два объекта-очереди одного шаблонного класса:" << endl;

    enum arrayLens {intLen = 10, charLen = 5};

    Queue <int> intQueue(intLen);   //int очередь

    try
    {
        for(int i = 0, counter = 0; counter < intLen ; ++i)
        {
            if(i%2 == 0)
            {
                intQueue.add(i);
                counter++;
            }
        }
    }
    catch(TemplateQueueErrors &err)
        { cout << err.what() << endl; }

    char ourCharArray[charLen] = {'A', 'B', 'C', 'D', 'E'};     //char очередь
    Queue <char> charQueue(charLen*2, charLen, ourCharArray);

    
    cout << intQueue << endl;
    cout << charQueue << endl;

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;

    cout << "Извлекем несколько объектов каждой очереди, после добавим несколько произвольных значений." << endl << endl;
    
    int firstInt;
    int secondInt;

    char firstChar;
    char secondChar;

    try     //Извлечение первых элементов
    {
        firstInt = intQueue.extract();
        secondInt = intQueue.extract();

        firstChar = charQueue.extract();
        secondChar = charQueue.extract();
    }
    catch(TemplateQueueErrors& err)
    {
        cout << err.what() << endl;
    }

    cout << "Извлечены элементы: " << endl;
    cout << firstInt << " и " << secondInt << endl;
    cout << firstChar << " и " << secondChar << endl;

    cout << "Очереди приняли вид:" << endl;
    
    cout << intQueue << endl;
    cout << charQueue << endl;

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;

    cout << "Добавим пару произвольных значений в каждую очередь." << endl << endl;

    try     //Добавление элементов в конец очередей
    {
        intQueue.add(99);
        intQueue.add(100);

        charQueue.add('Y');
        charQueue.add('Z');
    }
    catch(TemplateQueueErrors& err)
    {
        cout << err.what() << endl;
    }

    cout << "Очереди приняли вид:" << endl;
    
    cout << intQueue << endl;
    cout << charQueue << endl;

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;

    cout << "Продемонстрируем цикличность очереди путем непрерываного перебора элементов по индексам в цикле for для i от 0 до 25:" << endl;

    for(int i = intQueue.getHeadIndex(); i <= 25; ++i)
        cout << intQueue[i] << ((i == 25)? "\n": ", ");

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Завершение программы..." << endl;
   
    return 0;
}





























// ==================== GIT ШПАРГАЛКА ====================

// 0) Один раз на каждом компе (настройка личности Git):
//    git config --global user.name "Твоё Имя"
//    git config --global user.email "you@mail.com"
//    git config --global core.autocrlf true        # если Windows

// -----------------------------------------------------------------------
// A) Первый запуск на НОВОМ компьютере (когда репо ещё нет локально)

// 1) Клонируем проект:
//    cd C:\Code   (или куда надо)
//    git clone <URL_репозитория>
//    cd <папка_репозитория>

//ИЛИ
// git init
// git remote add origin https://github.com/...


// 2) Проверяем, что всё ок:
//    git status
//    git remote -v

// -----------------------------------------------------------------------
// B) Начинаю работать на ЛЮБОМ компе (каждый раз перед кодингом)

// 1) Перейти в папку проекта
// 2) Забрать свежие изменения:
//    git pull

//    Если ругается на конфликты:
//    - открываешь конфликтующие файлы
//    - правишь вручную (оставляешь правильный вариант)
//    - потом:
//      git add .
//      git commit -m "Resolve merge conflict"
//      git push

// -----------------------------------------------------------------------
// C) В процессе работы (сохраняю прогресс)

// 1) Посмотреть, что изменилось:
//    git status

// 2) Зафиксировать изменения:
//    git add .
//    git commit -m "Коротко что сделал"

// git commit --amend --no-edit
// --amend → «переделай последний коммит»
// --no-edit → «оставь сообщение таким же, не трогай его»

//    Примеры сообщений:
//    - "Lab6: fix input parsing"
//    - "Add Polynomial::operator+"
//    - "Refactor queue memory management"

// 3) Отправить на удалённый репозиторий (чтобы на другом компе было):
//    git push

// -----------------------------------------------------------------------
// D) Перехожу на второй комп

// 1) В папке проекта:
//    git pull

// И всё. Код на месте.

// -----------------------------------------------------------------------
// E) Если забыл закоммитить и надо срочно уйти (временное сохранение)

//    git stash
//    git pull          # если нужно обновиться
//    git stash pop     # вернуть изменения обратно

// (Старайся не жить на stash. Это временный карман.)

// -----------------------------------------------------------------------
// F) Откаты (самое частое)

// 1) Отменить незакоммиченные правки:
//    git restore .

// 2) Убрать файлы из staged (после git add):
//    git restore --staged .

// 3) Убрать последний коммит, НО оставить изменения в файлах:
//    git reset --soft HEAD~1

// 4) Убрать последний коммит И выкинуть изменения:
//    git reset --hard HEAD~1

// 5) Если уже запушил и нужно отменить безопасно:
//    git revert <hash>
//    git push

// -----------------------------------------------------------------------
// G) Быстрые проверки

// - Где я? (корень репо)
//   git rev-parse --show-toplevel

// - Что я изменил?
//   git status

// - Какие коммиты последние?
//   git log --oneline --max-count=10

// -----------------------------------------------------------------------
// H) Золотое правило

// Перед началом работы: git pull
// После завершения работы: git add . && git commit && git push

// =======================================================================
