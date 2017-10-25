#include "treap.h"



void node::reverse() // Меняет местами детей
{
    if (isDecreasing)
    {
        isDecreasing = false;
        isIncreasing = true;
    }
    if (isIncreasing)
    {
        isIncreasing = false;
        isDecreasing = true;
    }
    needToRev = !needToRev;
}



void node::push()
{
    if (needToRev)
    {
        node* temp = left;
        left = right;
        right = temp;

        if (left != NULL)
            left->reverse();
        if (right != NULL)
        right->reverse();
        needToRev = false;
    }
    recount();
}



void node::recount() // Пересчитывает вспомогательные величины, хранящиеся в вершине по детям
{
    if (left != NULL)
        left->push();

    if (right != NULL)
        right->push();

    // Кол-во элементов в поддереве
    size = 1;
    if (getLeft() != NULL)
        size += getLeft()->getSize();
    if (getRight() != NULL)
        size += getRight()->getSize();

    // Сумма элементов в поддереве
    sum = value;
    if (getLeft() != NULL)
        sum += getLeft()->getSum();
    if (getRight() != NULL)
        sum += getRight()->getSum();

    // Минимум в поддереве
    min = value;
    int temp = min; // Потом сюда попробуем записать меньший из минимумов на поддеревьях
    if ( (getLeft() != NULL) || (getRight() != NULL) ) // Если хотябы в одном поддереве есть элементы
    {
        if (getLeft() != NULL)
            temp = getLeft()->getMin();
        if (getRight() != NULL)
            if ( getRight()->getMin() < temp )
                temp = getRight()->getMin();
    }
    if (temp < min)
        min = temp;

    // Максимум в поддереве
    max = value;
    temp = max; // Потом сюда попробуем записать больший из максимумов на поддеревьях
    if ( (getLeft() != NULL) || (getRight() != NULL) ) // Если хотябы в одном поддереве есть элементы
    {
        if (getLeft() != NULL)
            temp = getLeft()->getMax();
        if (getRight() != NULL)
            if ( getRight()->getMax() > temp )
                temp = getRight()->getMax();
    }
    if (temp > max)
        max = temp;

    // Тут определяется, убывает дерево или нет по потомкам
    isIncreasing = isDecreasing = false;
    if ( (getLeft() == NULL) && (getRight() == NULL) ) // Вариант, когда детей нет
    {
        isIncreasing = isDecreasing = true;
        return;
    }
    if ( (getLeft() != NULL) && (getRight() != NULL) ) // Вариант, когда оба ребенка есть
    {
        if ( getLeft()->getIsIncreas() && getRight()->getIsIncreas() && (value <= getRight()->getMin()) && (value >= getLeft()->getMax()) )
            isIncreasing = true;
        if ( getLeft()->getIsDecreas() && getRight()->getIsDecreas() && (value <= getLeft()->getMin()) && (value >= getRight()->getMax()) )
            isDecreasing = true;
        return;
    }
    if (getLeft() != NULL) // Вариант, когда нет левого, но есть правый
    {
        if ( getLeft()->getIsIncreas() && (value >= getLeft()->getMax()) )
            isIncreasing = true;
        if ( getLeft()->getIsDecreas() && (value <= getLeft()->getMin()) )
            isDecreasing = true;
    }
    else // Вариант, когда нет правого, но есть левый
    {
        if ( getRight()->getIsIncreas() && (value <= getRight()->getMin()) )
            isIncreasing = true;
        if ( getRight()->getIsDecreas() && (value >= getRight()->getMax()) )
            isDecreasing = true;
    }
}



int node::getMin() const
{
    return min;
}

int node::getMax() const
{
    return max;
}

bool node::getIsIncreas() const
{
    return isIncreasing;
}

bool node::getIsDecreas() const
{
    return isDecreasing;
}

int node::getSum() const
{
    return sum;
}

int node::getSize() const
{
    return size;
}

int node::getValue() const
{
    return value;
}

int node::getPriority() const
{
    return priority;
}

bool node::getNeedToRev() const
{
    return needToRev;
}



node* node::getLeft() const
{
    return left;
}

node* node::getRight() const
{
    return right;
}



void node::setPriority (int inPriority)
{
    priority = inPriority;
}

void node::setSize (int inSize)
{
    size = inSize;
    recount();
}

void node::setLeft (node* inLeft)
{
    left = inLeft;
    recount();
}

void node::setRight (node* inRight)
{
    right = inRight;
    recount();
}

void node::setValue(int inVal) // Устанавливаем элементу значение
{
    value = inVal;
    recount();
}

void node::setSum (int inSum)
{
    sum = inSum;
    recount();
}

void node::setMax (int inMax)
{
    max = inMax;
}

void node::setMin (int inMin)
{
    min = inMin;
}

void node::setIsIncreas (bool inIsIncreas)
{
    isIncreasing = inIsIncreas;
}

void node::setIsDecreas (bool inIsDecreas)
{
    isDecreasing = inIsDecreas;
}

void node::setNeedToRev (bool inNeedToRev)
{
    needToRev = inNeedToRev;
    recount();
}



node::node(int inVal) // Конструктор по значению и кол-ву элементов в массиве
{
    priority = rand();   // Рандомный приоритет
    value = sum = min = max = inVal;
    size = 1; //Изначально в поддереве только эта вершина

    left = right = NULL; // Родственников пока нет

    isIncreasing = isDecreasing = true; // Один элемент и возрастает и убывает

    needToRev = false;
}

node::node (const node& inNode)
{
    priority = inNode.getPriority();
    value = inNode.getValue();
    size = inNode.getSize();
    sum = inNode.getSum();
    max = inNode.getMax();
    min = inNode.getMin();
    isIncreasing = inNode.getIsIncreas();
    isDecreasing = inNode.getIsDecreas();
    needToRev = inNode.getNeedToRev();

    left = inNode.getLeft();
    right = inNode.getRight();
}



std::ostream& operator << (std::ostream& out, node& inNode) // Перегрузка оператора для вывода в поток
{
    out << "(" << inNode.value << ", " << inNode.getIsDecreas() << ")";
    return out;
}



node& node::operator = (node& inNode)
{
    // Копируем все поля
    priority = inNode.getPriority();
    value = inNode.getValue();
    size = inNode.getSize();
    sum = inNode.getSum();
    max = inNode.getMax();
    min = inNode.getMin();
    isIncreasing = inNode.getIsIncreas();
    isDecreasing = inNode.getIsDecreas();
    needToRev = inNode.getNeedToRev();

    left = inNode.getLeft();
    right = inNode.getRight();

    return *this;
}



void treap::push() // Проталкивание в дереве это просто проталкивание в его корне
{
    root->push();
}

int treap::getFirstBiggerThenIndex (int value)
{
    node *pointer = root, *memory = NULL; // Указатели, чтобы ходить по дереву
    int result = 0; // Результат
    while (true)
    {
        pointer->push();
        if (value < pointer->getValue()) // Если вершина подходит поусловию, надо поискать еще левее
        {
            if (pointer->getLeft() == NULL)
                return result;

            pointer = pointer->getLeft();
        }
        else //Иначе надо поискать правее
        {
            if (pointer->getLeft() != NULL)
                result += pointer->getLeft()->getSize() + 1;
            else
                result += 1;
            if (pointer->getRight() == NULL)
            {
                return result;
            }
            pointer = pointer->getRight();
        }
    }
}



void treap::NextPermutation (size_t l, size_t r) // Заменяет дерево следующей перестановкой на отрезке
{
    // Вырежем нужный отрезок
    splitPair* split1 = split (l);
    splitPair* split2 = split1->rightTreap->split (r - l + 1);

    if (split2->leftTreap->getRoot()->getSize() == 1)
    {
        setRoot(merge(split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot());
        return;
    }
    if (split2->leftTreap->getRoot()->getIsDecreas()) // У убывающей перестановки нет следующей
    {
        split2->leftTreap->getRoot()->reverse();
        setRoot(merge(split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot());
        return;
    }

    // Отрежем его самый длинный убывающий суффикс
    splitPair* suffixSplit = split2->leftTreap->splitDecrease();

    suffixSplit->rightTreap->getRoot()->reverse(); // Перевернем суффикс

    // Вырежем первый элемент в суффиксе, больший последнего в остатке
    int biggerIndex = suffixSplit->rightTreap->getFirstBiggerThenIndex(suffixSplit->leftTreap->getLast());
    int lastIndex = suffixSplit->leftTreap->getSize() - 1;

    splitPair* splitSuf = suffixSplit->rightTreap->split (biggerIndex);
    splitPair* splitSufRes = splitSuf->rightTreap->split(1);
    splitPair* splitPref = suffixSplit->leftTreap->split (lastIndex);

    int temp = splitSufRes->leftTreap->getRoot()->getValue();
    splitSufRes->leftTreap->getRoot()->setValue(splitPref->rightTreap->getRoot()->getValue());
    splitPref->rightTreap->getRoot()->setValue(temp);

    //Склеиваем обратно куски
    treap* pTreap = merge( merge(splitPref->leftTreap, splitPref->rightTreap), merge(splitSuf->leftTreap, merge(splitSufRes->leftTreap, splitSufRes->rightTreap) ) );
    setRoot( merge( split1->leftTreap, merge( pTreap, split2->rightTreap ) )->getRoot() );
}



void treap::reverse()
{
    root->recount();
    root->reverse(); // Реверсим эту вершину
}



long long treap::SubsegmentSum (size_t l, size_t r) // Сумма на подотрезке
{
    // Сначала вырезаем нужный кусок
    splitPair* split1 = split (l);
    splitPair* split2 = split1->rightTreap->split (r - l + 1);

    long long result = split2->leftTreap->getSum(); // Теперь берес сумму на жэтом куске

    // И обратно склеиваем дерево
    setRoot( merge (split1->leftTreap, merge (split2->leftTreap, split2->rightTreap))->getRoot() );

    return result; // Возвращаем результат
}



int treap::getFirst() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // Просходим все время влево, как можно дальше
        pointer = pointer->getLeft();
    return pointer->getValue(); // Это и будет последний элемент
}

node* treap::getFirstP() const
{
    node* pointer = root;
    while (pointer->getLeft() != NULL) // Просходим все время влево, как можно дальше
        pointer = pointer->getLeft();
    return pointer; // Это и будет первый элемент
}

int treap::getLast() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // Просходим все время вправо, как можно дальше
        pointer = pointer->getRight();
    return pointer->getValue(); // Это и будет первый элемент
}

node* treap::getLastP() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // Просходим все время вправо, как можно дальше
        pointer = pointer->getRight();
    return pointer; // Это и будет последний элемент
}



int treap::getLen()
{
    if (root != NULL)
        return root->getSize();
    else
        return 0;
}


void treap::Assign (int value, size_t index)
{
    if (root == NULL) // Если дерево пустое или когда пользователь дал слишком большой индекс
        return; // Делаем ничего
    if (root->getSize() <= index)
        return;

    //Если же все хорошо...
    splitPair* split1 = split(index); // Разбиваем дерево в том месте, куда надо вставить элемент
    splitPair* split2 = split1->rightTreap->split(1);

    split2->leftTreap->getRoot()->setValue(value); // И изменяем значение в нужной вершине

    //Теперь производим слияние 3-х деревьев
    setRoot( merge (split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot() );
}



void treap::Insert(int value, size_t index)
{
    if (root == NULL) // Если дерево пустое, то сделаем его из одной вершины
    {
        root = new node(value);
        return;
    }
    if (index >= root->getSize()) // Случай, когда пользователь дал слишком большой индекс
    {
        // Ну ладно, прицепим спава
        setRoot( merge (this, new treap(value))->getRoot() );
        return;
    }

    //Если же все хорошо...
    splitPair* splitRes = split(index); // Разбиваем дерево в том месте, куда надо вставить элемент
    treap* tempTreap = new treap(value); // И сделаем временное дерево из вставляемой вершины

    //Теперь производим слияние 3-х деревьев
    setRoot( merge (merge (splitRes->leftTreap, tempTreap), splitRes->rightTreap)->getRoot() );
}



void treap::setRight (node* inRight)
{
    root->setRight(inRight);
}

void treap::setLeft (node* inLeft)
{
    root->setLeft(inLeft);
}



void treap::print (int counter) // Метод рисует деревце, чтобы можно было понять его структуру. Нужен для отладки в основном
{
    if (root != NULL)
    {
        ++counter;
        std::cout << *root << std::endl;
        if (left()->getRoot() != NULL)
        {
            for (int i = 0; i < counter; i++)
                std::cout << "   ";
            std::cout << "L: ";
            left()->print(counter);
        }
        if (right()->getRoot() != NULL)
        {
            for (int i = 0; i < counter; i++)
                std::cout << "   ";
            std::cout << "R: ";
            right()->print(counter);
        }
    }
}



splitPair* treap::split (int x)
{
    splitPair* result = new splitPair; // Возвращаемая величина

    if (root == NULL) // Пустое дерево не на что разбивать
    {
        result->leftTreap = new treap;
        result->rightTreap = new treap;

        return result;
    }

    if (x == 0) // Отдельно разбираем случай отрезания 0 слева
    {
        treap* treapR = new treap;
        treapR->setRoot(root);

        result->rightTreap = treapR; // В таком случае возвращается правым деревом будет все исходное
        result->leftTreap = new treap; // А левое пусто

        return result;
    }

    if (root->getSize() == x) // Еще один случай, когда все дерево надо отрезать полностью
    {
        treap* treapL = new treap;

        treapL->setRoot(root);
        result->leftTreap = treapL; // Тогда левое дерево - все исходное
        result->rightTreap = new treap; // А правое пустое

        return result;
    }

    int rootIndex = left()->getSize() + 1; // Посчитаем индекс корня для удобвства

    if (rootIndex == x) // Последний случай, когда надо разрезать ровно по корню
    {
        treap *treapL = new treap;

        treapL->setRoot(root);
        result->rightTreap = right(); //Тогда правое поддерево записываем вправо
        root->setRight(NULL);
        result->leftTreap = treapL; // А остальное, отрезав правую часть влево

        return result;
    }

    // Теперь невырожденные случаи

    push(); // Сначала протилкивание реверса

    treap *treapL = new treap, *treapR = new treap; //Сюда запишем наши деревья

    if (rootIndex <= x) // Смотрим, в левой или правой части дерева надо дальше разрезать
    {
        splitPair* temp = new splitPair;

        if (right()->getRoot() != NULL) // В правой разрезаем по ключу x - rootIndex
            temp = right()->split(x - rootIndex);

        // Потом правильно соберем левую часть
        treapL->setRoot(root); // Из того, что было слева корня
        if (temp->leftTreap != NULL)
            treapL->setRight ( temp->leftTreap->getRoot() ); // И того, что рекурсивно отрезали
        else
            treapL->setRight (NULL);

        treapR = temp->rightTreap; //Правая часть остается обрубком
    }
    else
    {
        splitPair* temp = new splitPair;

        if (left()->getRoot() != NULL) // В левой части резать надо по тому же ключу, что и раньше
            temp = left()->split(x);

        // А собирать по частям теперь будем правое дерево
        treapR->setRoot(root);
        if (temp->rightTreap != NULL )
            treapR->setLeft( temp->rightTreap->getRoot() ); // Приклеивая к правой части старого дерева отрезанное рекурсивно
        else
            treapR->setLeft(NULL);
        treapL = temp->leftTreap; // Левая часть остается обрубком
    }

    //Теперь записываем результат
    result->leftTreap = treapL;
    result->rightTreap = treapR;
    return result; // И возвращаем его
}



splitPair* treap::splitDecrease()
{
    splitPair* result = new splitPair;

    if (root == NULL) // Вариант пустого дерева
    {
        result->leftTreap = new treap;
        result->rightTreap = new treap;
        return result;
    }

    push(); // Проталкивание реверса

    if (getIsDecreas()) // Если все дерево убывает
    {
        treap *prefix = new treap, *suffix = new treap;
        suffix->setRoot(root); // Суффикс это все дерево, а префикс пуст

        // Возвращаем результат
        result->rightTreap = suffix;
        result->leftTreap = prefix;
        return result;
    }

    //Сделаем две будевые переменные о наличии правого и левого поддерева для удобства
    bool isRight = (right()->getRoot() != NULL), isLeft = (left()->getRoot() != NULL);

    bool needRight = false; // Рещаем, находится суффикс только в правом поддереве или нет
    if (isRight)
        if (! root->getRight()->getIsDecreas())
            needRight = true;

    if (needRight) // Если правое поддерево не полностью убывает, то искать надо в нем
    {
        treap *prefix = new treap, *suffix = new treap;

        splitPair* tempSplit = right()->splitDecrease(); // Рекрсивно отрезаем суффикс в правом поддереве
        suffix->setRoot(tempSplit->rightTreap->getRoot());

        // А потом восстанавливаем префикс
        root->setRight (NULL);
        setRight(tempSplit->leftTreap->getRoot());
        prefix->setRoot(root);

        // Собираем и возвращаем рузультат
        result->leftTreap = prefix;
        result->rightTreap = suffix;
        return result; // И возвращаем результат
    }
    else // Иначе надо отрезать какую-то часть левого поддерева
    {
        // Сначала решаем, нужно ли брать корень дерева
        bool needRoot = false;
        if (!isRight)
            needRoot = true;
        else if ( root->getValue() >= right()->getMax() )
            needRoot = true;

        if (needRoot) // Если корень нужен
        {
            splitPair* tempSplit = new splitPair;
            treap *prefix = new treap, *suffix = new treap;

            if (isLeft) // Если есть левое поддерево
                tempSplit = left()->splitDecrease (); // Рекурсивно отрезаем от него его суффикс

            // Первоначальные заготовки префикса и суффикса
            prefix->setRoot(tempSplit->leftTreap->getRoot());
            root->setLeft(NULL);
            suffix->setRoot(root);

            bool needTempSuf = false; // Теперь решаем, нужно ли тот, рекурсивно отрезаный суффикс прикреплять к основному
            if (tempSplit->rightTreap->getRoot() != NULL)
                if (root->getValue() <= tempSplit->rightTreap->getMin())
                    needTempSuf = true;

            if (needTempSuf) // В зависивости от этого прикрепляем рекурсивно отрезаный суффикс к префиксу или основному суффиксу
                suffix = merge (tempSplit->rightTreap, suffix);
            else
                prefix = merge (prefix, tempSplit->rightTreap);

            // Собираем и возвращаем результат
            result->leftTreap = prefix;
            result->rightTreap = suffix;
            return result;
        }
        else // А если корень не нужен
        {
            treap *prefix = new treap, *suffix = new treap;

            suffix->setRoot(root->getRight()); // То суффикс это правое поддерево
            root->setRight(NULL);
            prefix->setRoot(root); // А префикс - все остальное (с отрезаным правым поддеревом)

            // Результат
            result->rightTreap = suffix;
            result->leftTreap = prefix;
            return result;
        }
    }
}



void treap::setSize(int inSize)
{
    root->setSize(inSize);
}



treap* treap::left() // Возвращает левое поддерево
{
    treap* res = new treap;
    res->setRoot(root->getLeft());
    return res;
}

treap* treap::right() // Возвращает правое поддерево
{
    treap* res = new treap;
    res->setRoot(root->getRight());
    return res;
}



std::ostream& operator << (std::ostream& out, treap& inTreap) // Перегрузка оператора для вывода в поток
{
    if (inTreap.getRoot() == NULL) //Если дерево нулевое, то делаем ничего
        return out;

    inTreap.getRoot()->push(); // Проталкиваем инверсии, если это требуется

    // in-order обходом рекурсивно выводим элементы на экран
    if (inTreap.left()->getRoot() != NULL)  // Левое поддерево
        out << *inTreap.left();
    if (inTreap.getRoot() != NULL)          // Корень
        out << inTreap.getRoot()->getValue() << std::endl;
    if (inTreap.right()->getRoot() != NULL) // И правое поддерево
        out << *inTreap.right();
    return out;
}

std::ostream& operator << (std::ostream& out, treap* inTreap) // Перегрузка оператора для вывода в поток
{
    if (inTreap->getRoot() == NULL) //Если дерево нулевое, то делаем ничего
        return out;

    inTreap->getRoot()->push(); // Проталкиваем инверсии, если это требуется

    // in-order обходом рекурсивно выводим элементы на экран
    if (inTreap->left()->getRoot() != NULL)  // Левое поддерево
        out << inTreap->left();
    if (inTreap->getRoot() != NULL)          // Корень
        out << inTreap->getRoot()->getValue() << std::endl;
    if (inTreap->right()->getRoot() != NULL) // И правое поддерево
        out << inTreap->right();
    return out;
}



treap& treap::operator = (treap& inTreap)
{
    if (inTreap.getRoot() != NULL) // Присваиваем корень
        root = inTreap.getRoot();
    else
        root = NULL;

    return *this; // И возвращаем результат
}



void treap::setRoot(node* inRoot)
{
    root = inRoot;
}



int treap::getMin() const
{
    return root->getMin();
}

int treap::getMax() const
{
    return root->getMax();
}

bool treap::getIsIncreas() const
{
    return root->getIsIncreas();
}

bool treap::getIsDecreas() const
{
    return root->getIsDecreas();
}

node* treap::getRoot() const // Возвращает указатель на корень дерева
{
    return root;
}

int treap::getSize() const
{
    if (root != NULL)
        return root->getSize();
    return 0;
}

int treap::getSum() const
{
    return root->getSum();
}



treap::treap(int* inArr, int n) // Конструктор из массива
{
    treap* res = new treap; // Результирующее дерево

    for (int i = 0; i < n; i++) // Просто присливаем к дереву все элементы из массива
    {
        treap* temp = new treap (inArr[i]);
        res->setRoot(merge(res, temp)->getRoot());
    }

    setRoot(res->getRoot()); // Устанавливаем корень в получившееся дерево
}

treap::treap (node* inNode) //Конструктор из одного элемента
{
    node newNode = *inNode;
    root = &newNode;
}

treap::treap () //Конструктор из одного элемента
{
    root = NULL;
}

treap::treap (int value)
{
    root = new node(value);
}



treap* merge (treap* treap1, treap* treap2) //Слияние двух деревьев в одно
{
    // Если какое-то дерево нулевое, то ответ тривиален
    if (treap1->getRoot() == NULL)
        return treap2;
    if (treap2->getRoot() == NULL)
        return treap1;

    // Протилкивание реверса
    treap1->push();
    treap2->push();

    treap* resTreap = new treap; // Это будет результатом, когда хотя бы одно дерево не пустое

    if ( treap1->getRoot()->getPriority() > treap2->getRoot()->getPriority() ) // Смотрим, в правом или левом дереве больше приоритет корня
    {
        resTreap->setRoot(treap1->getRoot()); // То, где больше приоритет ставим в корень (при этом левая часть у нас правильная)

        treap* tempRight = new treap; // Теперь разбиремся, что в правом поддереве
        tempRight->setRoot(treap1->getRoot()->getRight());
        tempRight = merge(tempRight, treap2); // Это слияние T2 и правого поддерева T1

        resTreap->setRight( tempRight->getRoot() ); // Записываем на место

    }
    else
    {
        resTreap->setRoot(treap2->getRoot()); // То, где больше приоритет ставим в корень (при этом правая часть у нас правильная)

        treap* tempLeft = new treap; // Теперь разбиремся, что в левом поддереве
        tempLeft->setRoot (treap2->getRoot()->getLeft());
        tempLeft = merge (treap1, tempLeft); // Это слияние T1 и левого поддерева T2

        resTreap->setLeft( tempLeft->getRoot() ); // Записываем на место
    }

    return resTreap; // Возвращаем результат
}

splitPair::splitPair()
{
    leftTreap = NULL;
    rightTreap = NULL;
}
