#ifndef TREAP_PAVEL_KOSHKIN_493
#define TREAP_PAVEL_KOSHKIN_493

#include <iostream>

#include <stdio.h>      // printf, scanf, puts, NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include "iPermutationStruct.h"



class node //Элемент дерева
{
private:
    int priority;       // Рандомный приоритет
    int value;          // Само хранящееся значение элемента

    int size;           // Кол-во элементовтов в поддереве с корнем в этом элементе
    long long sum;            // Сумма элементов в поддереве
    int max;            // Максимум в поддереве
    int min;            // Минимум в поддереве

    bool isIncreasing;  // Являются ли элементы в поддереве возрастающими
    bool isDecreasing;  // Являются ли элементы в поддереве убывающими
    bool needToRev;     // Нужно ли произвести реверс поддерева

    node* left;         // Левый сын
    node* right;        // Правый сын

public:
    node (int inVal = 0); // Конструктор по значению и кол-ву элементов в массиве
    node (const node& inNode );

    //Получение указателей на родственников
    node* getLeft() const;
    node* getRight() const;

    //Получение значения полей
    int getPriority() const;
    int getValue() const;
    int getSize() const;
    int getSum() const;
    int getMin() const;
    int getMax() const;
    bool getNeedToRev() const;
    bool getIsIncreas() const;
    bool getIsDecreas() const;

    // Установка значений полям
    void setValue (int inVal);
    void setSize (int inSize);
    void setPriority (int inPriority);
    void setLeft (node* inLeft);
    void setRight (node* inRight);
    void setSum (int inSum);
    void setMax (int inMax);
    void setMin (int inMin);
    void setIsIncreas (bool inIsIncreas);
    void setIsDecreas (bool inIsDecreas);
    void setNeedToRev (bool inNeedToRev);

    void recount();     // Пересчитывает вспомогательные величины, хранящиеся в вершине по детям
    void reverse();     // Меняет местами детей
    void push();        // Проталкивает реверс к потомкам
    void changeRev();   // Изсеняет значение needToRev на противоположное

    friend std::ostream& operator << (std::ostream& out, node& inNode); // Перегрузка оператора для вывода в поток
    node& operator = (node& inNode); // Перегрузка оператора присваивания
};



class treap;

class splitPair
{
public:

    splitPair();

    treap* leftTreap;
    treap* rightTreap;
};



class treap : public virtual iPermutationStruct // Декартово дерево по неявному ключу, будет делать мне афигенный ну почти массив
{
private:
    node* root; // Указатель на корневой элемент

public:
    treap ();                       // Конструктор из ничего
    treap (node* inNode);           // Конструктор из одного лемента
    treap (int value);              // Конструктор для одного значения
    treap (int* inArr, int n);      // Конструктор из массива

    node* getRoot() const;          // Возвращает указатель на корень дерева
    int getSize() const;            // Размер дерева
    int getSum() const;             // Суммма элементов в дереве
    int getMin() const;             // Минимальный элемент в дереве
    int getMax() const;             // Максимальный элемент в дереве
    bool getIsIncreas() const;      // Возрастают ли значения элементов в дереве
    bool getIsDecreas() const;      // Убывают ли значения элементов в дереве

    int getLast() const;            // Получаем самый последний элемент дерева
    node* getLastP() const;         // Получаем указатель на самый последний элемент дерева
    int getFirst() const;            // Получаем самый первый элемент дерева
    node* getFirstP() const;        // Получаем указатель на самый первый элемент дерева

    // Возвращает указатель на первый элемент дерева, больший, чем переданое значение в дереве, котрое отсортировано по возрастанию
    int getFirstBiggerThenIndex (int value);

    // Возможность получить левое и правое поддерево
    treap* left();
    treap* right();

    // Установка размера поддерева, сыновей корневого элемента и самого корневого элемента
    void setSize (int inSize);
    void setRight (node* inRight);
    void setLeft (node* inLeft);
    void setRoot(node* inRoot);

    treap& operator = (treap& inTreap); // Перегрузка оператора присваивания
    friend std::ostream& operator << (std::ostream& out, treap& inTreap); // Перегрузка оператора для вывода в поток
    friend std::ostream& operator << (std::ostream& out, treap* inTreap); // Перегрузка оператора для вывода в поток

    splitPair* split (int x); // Разделяет дерево на 2, отдавая первому первые x элементов, а остальное второму
    splitPair* splitDecrease ();  // Разрезает дерево на наибольший убывающий суффикс и остаток

    virtual void Insert (int value, size_t index);                  // Вставка элемента в определенную позицию
    virtual void Assign (int value, size_t index);                  // Изменение значения элемента, находящегося в позиции index
    virtual long long SubsegmentSum (size_t left, size_t right);    // Возвращает сумму на подотрезке

    virtual void NextPermutation (size_t left, size_t right);       // Возвращает слудующую перестановку на подотрезке

    virtual int getLen();

    void reverse(); //Реверсирует все элементы дерева
    void push(); // Проталкивание реверса потомкам

    void print (int counter = 0);
};

treap* merge (treap* treap1, treap* treap2); // Объявление функции, чтобы использовать её в методах

#endif // TREAP_PAVEL_KOSHKIN
