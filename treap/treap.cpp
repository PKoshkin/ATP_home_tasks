#include "treap.h"



void node::reverse() // ������ ������� �����
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



void node::recount() // ������������� ��������������� ��������, ���������� � ������� �� �����
{
    if (left != NULL)
        left->push();

    if (right != NULL)
        right->push();

    // ���-�� ��������� � ���������
    size = 1;
    if (getLeft() != NULL)
        size += getLeft()->getSize();
    if (getRight() != NULL)
        size += getRight()->getSize();

    // ����� ��������� � ���������
    sum = value;
    if (getLeft() != NULL)
        sum += getLeft()->getSum();
    if (getRight() != NULL)
        sum += getRight()->getSum();

    // ������� � ���������
    min = value;
    int temp = min; // ����� ���� ��������� �������� ������� �� ��������� �� �����������
    if ( (getLeft() != NULL) || (getRight() != NULL) ) // ���� ������ � ����� ��������� ���� ��������
    {
        if (getLeft() != NULL)
            temp = getLeft()->getMin();
        if (getRight() != NULL)
            if ( getRight()->getMin() < temp )
                temp = getRight()->getMin();
    }
    if (temp < min)
        min = temp;

    // �������� � ���������
    max = value;
    temp = max; // ����� ���� ��������� �������� ������� �� ���������� �� �����������
    if ( (getLeft() != NULL) || (getRight() != NULL) ) // ���� ������ � ����� ��������� ���� ��������
    {
        if (getLeft() != NULL)
            temp = getLeft()->getMax();
        if (getRight() != NULL)
            if ( getRight()->getMax() > temp )
                temp = getRight()->getMax();
    }
    if (temp > max)
        max = temp;

    // ��� ������������, ������� ������ ��� ��� �� ��������
    isIncreasing = isDecreasing = false;
    if ( (getLeft() == NULL) && (getRight() == NULL) ) // �������, ����� ����� ���
    {
        isIncreasing = isDecreasing = true;
        return;
    }
    if ( (getLeft() != NULL) && (getRight() != NULL) ) // �������, ����� ��� ������� ����
    {
        if ( getLeft()->getIsIncreas() && getRight()->getIsIncreas() && (value <= getRight()->getMin()) && (value >= getLeft()->getMax()) )
            isIncreasing = true;
        if ( getLeft()->getIsDecreas() && getRight()->getIsDecreas() && (value <= getLeft()->getMin()) && (value >= getRight()->getMax()) )
            isDecreasing = true;
        return;
    }
    if (getLeft() != NULL) // �������, ����� ��� ������, �� ���� ������
    {
        if ( getLeft()->getIsIncreas() && (value >= getLeft()->getMax()) )
            isIncreasing = true;
        if ( getLeft()->getIsDecreas() && (value <= getLeft()->getMin()) )
            isDecreasing = true;
    }
    else // �������, ����� ��� �������, �� ���� �����
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

void node::setValue(int inVal) // ������������� �������� ��������
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



node::node(int inVal) // ����������� �� �������� � ���-�� ��������� � �������
{
    priority = rand();   // ��������� ���������
    value = sum = min = max = inVal;
    size = 1; //���������� � ��������� ������ ��� �������

    left = right = NULL; // ������������� ���� ���

    isIncreasing = isDecreasing = true; // ���� ������� � ���������� � �������

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



std::ostream& operator << (std::ostream& out, node& inNode) // ���������� ��������� ��� ������ � �����
{
    out << "(" << inNode.value << ", " << inNode.getIsDecreas() << ")";
    return out;
}



node& node::operator = (node& inNode)
{
    // �������� ��� ����
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



void treap::push() // ������������� � ������ ��� ������ ������������� � ��� �����
{
    root->push();
}

int treap::getFirstBiggerThenIndex (int value)
{
    node *pointer = root, *memory = NULL; // ���������, ����� ������ �� ������
    int result = 0; // ���������
    while (true)
    {
        pointer->push();
        if (value < pointer->getValue()) // ���� ������� �������� ���������, ���� �������� ��� �����
        {
            if (pointer->getLeft() == NULL)
                return result;

            pointer = pointer->getLeft();
        }
        else //����� ���� �������� ������
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



void treap::NextPermutation (size_t l, size_t r) // �������� ������ ��������� ������������� �� �������
{
    // ������� ������ �������
    splitPair* split1 = split (l);
    splitPair* split2 = split1->rightTreap->split (r - l + 1);

    if (split2->leftTreap->getRoot()->getSize() == 1)
    {
        setRoot(merge(split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot());
        return;
    }
    if (split2->leftTreap->getRoot()->getIsDecreas()) // � ��������� ������������ ��� ���������
    {
        split2->leftTreap->getRoot()->reverse();
        setRoot(merge(split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot());
        return;
    }

    // ������� ��� ����� ������� ��������� �������
    splitPair* suffixSplit = split2->leftTreap->splitDecrease();

    suffixSplit->rightTreap->getRoot()->reverse(); // ���������� �������

    // ������� ������ ������� � ��������, ������� ���������� � �������
    int biggerIndex = suffixSplit->rightTreap->getFirstBiggerThenIndex(suffixSplit->leftTreap->getLast());
    int lastIndex = suffixSplit->leftTreap->getSize() - 1;

    splitPair* splitSuf = suffixSplit->rightTreap->split (biggerIndex);
    splitPair* splitSufRes = splitSuf->rightTreap->split(1);
    splitPair* splitPref = suffixSplit->leftTreap->split (lastIndex);

    int temp = splitSufRes->leftTreap->getRoot()->getValue();
    splitSufRes->leftTreap->getRoot()->setValue(splitPref->rightTreap->getRoot()->getValue());
    splitPref->rightTreap->getRoot()->setValue(temp);

    //��������� ������� �����
    treap* pTreap = merge( merge(splitPref->leftTreap, splitPref->rightTreap), merge(splitSuf->leftTreap, merge(splitSufRes->leftTreap, splitSufRes->rightTreap) ) );
    setRoot( merge( split1->leftTreap, merge( pTreap, split2->rightTreap ) )->getRoot() );
}



void treap::reverse()
{
    root->recount();
    root->reverse(); // �������� ��� �������
}



long long treap::SubsegmentSum (size_t l, size_t r) // ����� �� ����������
{
    // ������� �������� ������ �����
    splitPair* split1 = split (l);
    splitPair* split2 = split1->rightTreap->split (r - l + 1);

    long long result = split2->leftTreap->getSum(); // ������ ����� ����� �� ����� �����

    // � ������� ��������� ������
    setRoot( merge (split1->leftTreap, merge (split2->leftTreap, split2->rightTreap))->getRoot() );

    return result; // ���������� ���������
}



int treap::getFirst() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // ��������� ��� ����� �����, ��� ����� ������
        pointer = pointer->getLeft();
    return pointer->getValue(); // ��� � ����� ��������� �������
}

node* treap::getFirstP() const
{
    node* pointer = root;
    while (pointer->getLeft() != NULL) // ��������� ��� ����� �����, ��� ����� ������
        pointer = pointer->getLeft();
    return pointer; // ��� � ����� ������ �������
}

int treap::getLast() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // ��������� ��� ����� ������, ��� ����� ������
        pointer = pointer->getRight();
    return pointer->getValue(); // ��� � ����� ������ �������
}

node* treap::getLastP() const
{
    node* pointer = root;
    while (pointer->getRight() != NULL) // ��������� ��� ����� ������, ��� ����� ������
        pointer = pointer->getRight();
    return pointer; // ��� � ����� ��������� �������
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
    if (root == NULL) // ���� ������ ������ ��� ����� ������������ ��� ������� ������� ������
        return; // ������ ������
    if (root->getSize() <= index)
        return;

    //���� �� ��� ������...
    splitPair* split1 = split(index); // ��������� ������ � ��� �����, ���� ���� �������� �������
    splitPair* split2 = split1->rightTreap->split(1);

    split2->leftTreap->getRoot()->setValue(value); // � �������� �������� � ������ �������

    //������ ���������� ������� 3-� ��������
    setRoot( merge (split1->leftTreap, merge(split2->leftTreap, split2->rightTreap))->getRoot() );
}



void treap::Insert(int value, size_t index)
{
    if (root == NULL) // ���� ������ ������, �� ������� ��� �� ����� �������
    {
        root = new node(value);
        return;
    }
    if (index >= root->getSize()) // ������, ����� ������������ ��� ������� ������� ������
    {
        // �� �����, �������� �����
        setRoot( merge (this, new treap(value))->getRoot() );
        return;
    }

    //���� �� ��� ������...
    splitPair* splitRes = split(index); // ��������� ������ � ��� �����, ���� ���� �������� �������
    treap* tempTreap = new treap(value); // � ������� ��������� ������ �� ����������� �������

    //������ ���������� ������� 3-� ��������
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



void treap::print (int counter) // ����� ������ �������, ����� ����� ���� ������ ��� ���������. ����� ��� ������� � ��������
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
    splitPair* result = new splitPair; // ������������ ��������

    if (root == NULL) // ������ ������ �� �� ��� ���������
    {
        result->leftTreap = new treap;
        result->rightTreap = new treap;

        return result;
    }

    if (x == 0) // �������� ��������� ������ ��������� 0 �����
    {
        treap* treapR = new treap;
        treapR->setRoot(root);

        result->rightTreap = treapR; // � ����� ������ ������������ ������ ������� ����� ��� ��������
        result->leftTreap = new treap; // � ����� �����

        return result;
    }

    if (root->getSize() == x) // ��� ���� ������, ����� ��� ������ ���� �������� ���������
    {
        treap* treapL = new treap;

        treapL->setRoot(root);
        result->leftTreap = treapL; // ����� ����� ������ - ��� ��������
        result->rightTreap = new treap; // � ������ ������

        return result;
    }

    int rootIndex = left()->getSize() + 1; // ��������� ������ ����� ��� ���������

    if (rootIndex == x) // ��������� ������, ����� ���� ��������� ����� �� �����
    {
        treap *treapL = new treap;

        treapL->setRoot(root);
        result->rightTreap = right(); //����� ������ ��������� ���������� ������
        root->setRight(NULL);
        result->leftTreap = treapL; // � ���������, ������� ������ ����� �����

        return result;
    }

    // ������ ������������� ������

    push(); // ������� ������������� �������

    treap *treapL = new treap, *treapR = new treap; //���� ������� ���� �������

    if (rootIndex <= x) // �������, � ����� ��� ������ ����� ������ ���� ������ ���������
    {
        splitPair* temp = new splitPair;

        if (right()->getRoot() != NULL) // � ������ ��������� �� ����� x - rootIndex
            temp = right()->split(x - rootIndex);

        // ����� ��������� ������� ����� �����
        treapL->setRoot(root); // �� ����, ��� ���� ����� �����
        if (temp->leftTreap != NULL)
            treapL->setRight ( temp->leftTreap->getRoot() ); // � ����, ��� ���������� ��������
        else
            treapL->setRight (NULL);

        treapR = temp->rightTreap; //������ ����� �������� ��������
    }
    else
    {
        splitPair* temp = new splitPair;

        if (left()->getRoot() != NULL) // � ����� ����� ������ ���� �� ���� �� �����, ��� � ������
            temp = left()->split(x);

        // � �������� �� ������ ������ ����� ������ ������
        treapR->setRoot(root);
        if (temp->rightTreap != NULL )
            treapR->setLeft( temp->rightTreap->getRoot() ); // ���������� � ������ ����� ������� ������ ���������� ����������
        else
            treapR->setLeft(NULL);
        treapL = temp->leftTreap; // ����� ����� �������� ��������
    }

    //������ ���������� ���������
    result->leftTreap = treapL;
    result->rightTreap = treapR;
    return result; // � ���������� ���
}



splitPair* treap::splitDecrease()
{
    splitPair* result = new splitPair;

    if (root == NULL) // ������� ������� ������
    {
        result->leftTreap = new treap;
        result->rightTreap = new treap;
        return result;
    }

    push(); // ������������� �������

    if (getIsDecreas()) // ���� ��� ������ �������
    {
        treap *prefix = new treap, *suffix = new treap;
        suffix->setRoot(root); // ������� ��� ��� ������, � ������� ����

        // ���������� ���������
        result->rightTreap = suffix;
        result->leftTreap = prefix;
        return result;
    }

    //������� ��� ������� ���������� � ������� ������� � ������ ��������� ��� ��������
    bool isRight = (right()->getRoot() != NULL), isLeft = (left()->getRoot() != NULL);

    bool needRight = false; // ������, ��������� ������� ������ � ������ ��������� ��� ���
    if (isRight)
        if (! root->getRight()->getIsDecreas())
            needRight = true;

    if (needRight) // ���� ������ ��������� �� ��������� �������, �� ������ ���� � ���
    {
        treap *prefix = new treap, *suffix = new treap;

        splitPair* tempSplit = right()->splitDecrease(); // ��������� �������� ������� � ������ ���������
        suffix->setRoot(tempSplit->rightTreap->getRoot());

        // � ����� ��������������� �������
        root->setRight (NULL);
        setRight(tempSplit->leftTreap->getRoot());
        prefix->setRoot(root);

        // �������� � ���������� ���������
        result->leftTreap = prefix;
        result->rightTreap = suffix;
        return result; // � ���������� ���������
    }
    else // ����� ���� �������� �����-�� ����� ������ ���������
    {
        // ������� ������, ����� �� ����� ������ ������
        bool needRoot = false;
        if (!isRight)
            needRoot = true;
        else if ( root->getValue() >= right()->getMax() )
            needRoot = true;

        if (needRoot) // ���� ������ �����
        {
            splitPair* tempSplit = new splitPair;
            treap *prefix = new treap, *suffix = new treap;

            if (isLeft) // ���� ���� ����� ���������
                tempSplit = left()->splitDecrease (); // ���������� �������� �� ���� ��� �������

            // �������������� ��������� �������� � ��������
            prefix->setRoot(tempSplit->leftTreap->getRoot());
            root->setLeft(NULL);
            suffix->setRoot(root);

            bool needTempSuf = false; // ������ ������, ����� �� ���, ���������� ��������� ������� ����������� � ���������
            if (tempSplit->rightTreap->getRoot() != NULL)
                if (root->getValue() <= tempSplit->rightTreap->getMin())
                    needTempSuf = true;

            if (needTempSuf) // � ����������� �� ����� ����������� ���������� ��������� ������� � �������� ��� ��������� ��������
                suffix = merge (tempSplit->rightTreap, suffix);
            else
                prefix = merge (prefix, tempSplit->rightTreap);

            // �������� � ���������� ���������
            result->leftTreap = prefix;
            result->rightTreap = suffix;
            return result;
        }
        else // � ���� ������ �� �����
        {
            treap *prefix = new treap, *suffix = new treap;

            suffix->setRoot(root->getRight()); // �� ������� ��� ������ ���������
            root->setRight(NULL);
            prefix->setRoot(root); // � ������� - ��� ��������� (� ��������� ������ ����������)

            // ���������
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



treap* treap::left() // ���������� ����� ���������
{
    treap* res = new treap;
    res->setRoot(root->getLeft());
    return res;
}

treap* treap::right() // ���������� ������ ���������
{
    treap* res = new treap;
    res->setRoot(root->getRight());
    return res;
}



std::ostream& operator << (std::ostream& out, treap& inTreap) // ���������� ��������� ��� ������ � �����
{
    if (inTreap.getRoot() == NULL) //���� ������ �������, �� ������ ������
        return out;

    inTreap.getRoot()->push(); // ������������ ��������, ���� ��� ���������

    // in-order ������� ���������� ������� �������� �� �����
    if (inTreap.left()->getRoot() != NULL)  // ����� ���������
        out << *inTreap.left();
    if (inTreap.getRoot() != NULL)          // ������
        out << inTreap.getRoot()->getValue() << std::endl;
    if (inTreap.right()->getRoot() != NULL) // � ������ ���������
        out << *inTreap.right();
    return out;
}

std::ostream& operator << (std::ostream& out, treap* inTreap) // ���������� ��������� ��� ������ � �����
{
    if (inTreap->getRoot() == NULL) //���� ������ �������, �� ������ ������
        return out;

    inTreap->getRoot()->push(); // ������������ ��������, ���� ��� ���������

    // in-order ������� ���������� ������� �������� �� �����
    if (inTreap->left()->getRoot() != NULL)  // ����� ���������
        out << inTreap->left();
    if (inTreap->getRoot() != NULL)          // ������
        out << inTreap->getRoot()->getValue() << std::endl;
    if (inTreap->right()->getRoot() != NULL) // � ������ ���������
        out << inTreap->right();
    return out;
}



treap& treap::operator = (treap& inTreap)
{
    if (inTreap.getRoot() != NULL) // ����������� ������
        root = inTreap.getRoot();
    else
        root = NULL;

    return *this; // � ���������� ���������
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

node* treap::getRoot() const // ���������� ��������� �� ������ ������
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



treap::treap(int* inArr, int n) // ����������� �� �������
{
    treap* res = new treap; // �������������� ������

    for (int i = 0; i < n; i++) // ������ ���������� � ������ ��� �������� �� �������
    {
        treap* temp = new treap (inArr[i]);
        res->setRoot(merge(res, temp)->getRoot());
    }

    setRoot(res->getRoot()); // ������������� ������ � ������������ ������
}

treap::treap (node* inNode) //����������� �� ������ ��������
{
    node newNode = *inNode;
    root = &newNode;
}

treap::treap () //����������� �� ������ ��������
{
    root = NULL;
}

treap::treap (int value)
{
    root = new node(value);
}



treap* merge (treap* treap1, treap* treap2) //������� ���� �������� � ����
{
    // ���� �����-�� ������ �������, �� ����� ���������
    if (treap1->getRoot() == NULL)
        return treap2;
    if (treap2->getRoot() == NULL)
        return treap1;

    // ������������� �������
    treap1->push();
    treap2->push();

    treap* resTreap = new treap; // ��� ����� �����������, ����� ���� �� ���� ������ �� ������

    if ( treap1->getRoot()->getPriority() > treap2->getRoot()->getPriority() ) // �������, � ������ ��� ����� ������ ������ ��������� �����
    {
        resTreap->setRoot(treap1->getRoot()); // ��, ��� ������ ��������� ������ � ������ (��� ���� ����� ����� � ��� ����������)

        treap* tempRight = new treap; // ������ ����������, ��� � ������ ���������
        tempRight->setRoot(treap1->getRoot()->getRight());
        tempRight = merge(tempRight, treap2); // ��� ������� T2 � ������� ��������� T1

        resTreap->setRight( tempRight->getRoot() ); // ���������� �� �����

    }
    else
    {
        resTreap->setRoot(treap2->getRoot()); // ��, ��� ������ ��������� ������ � ������ (��� ���� ������ ����� � ��� ����������)

        treap* tempLeft = new treap; // ������ ����������, ��� � ����� ���������
        tempLeft->setRoot (treap2->getRoot()->getLeft());
        tempLeft = merge (treap1, tempLeft); // ��� ������� T1 � ������ ��������� T2

        resTreap->setLeft( tempLeft->getRoot() ); // ���������� �� �����
    }

    return resTreap; // ���������� ���������
}

splitPair::splitPair()
{
    leftTreap = NULL;
    rightTreap = NULL;
}
