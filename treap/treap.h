#ifndef TREAP_PAVEL_KOSHKIN_493
#define TREAP_PAVEL_KOSHKIN_493

#include <iostream>

#include <stdio.h>      // printf, scanf, puts, NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include "iPermutationStruct.h"



class node //������� ������
{
private:
    int priority;       // ��������� ���������
    int value;          // ���� ���������� �������� ��������

    int size;           // ���-�� ������������ � ��������� � ������ � ���� ��������
    long long sum;            // ����� ��������� � ���������
    int max;            // �������� � ���������
    int min;            // ������� � ���������

    bool isIncreasing;  // �������� �� �������� � ��������� �������������
    bool isDecreasing;  // �������� �� �������� � ��������� ����������
    bool needToRev;     // ����� �� ���������� ������ ���������

    node* left;         // ����� ���
    node* right;        // ������ ���

public:
    node (int inVal = 0); // ����������� �� �������� � ���-�� ��������� � �������
    node (const node& inNode );

    //��������� ���������� �� �������������
    node* getLeft() const;
    node* getRight() const;

    //��������� �������� �����
    int getPriority() const;
    int getValue() const;
    int getSize() const;
    int getSum() const;
    int getMin() const;
    int getMax() const;
    bool getNeedToRev() const;
    bool getIsIncreas() const;
    bool getIsDecreas() const;

    // ��������� �������� �����
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

    void recount();     // ������������� ��������������� ��������, ���������� � ������� �� �����
    void reverse();     // ������ ������� �����
    void push();        // ������������ ������ � ��������
    void changeRev();   // �������� �������� needToRev �� ���������������

    friend std::ostream& operator << (std::ostream& out, node& inNode); // ���������� ��������� ��� ������ � �����
    node& operator = (node& inNode); // ���������� ��������� ������������
};



class treap;

class splitPair
{
public:

    splitPair();

    treap* leftTreap;
    treap* rightTreap;
};



class treap : public virtual iPermutationStruct // ��������� ������ �� �������� �����, ����� ������ ��� ��������� �� ����� ������
{
private:
    node* root; // ��������� �� �������� �������

public:
    treap ();                       // ����������� �� ������
    treap (node* inNode);           // ����������� �� ������ �������
    treap (int value);              // ����������� ��� ������ ��������
    treap (int* inArr, int n);      // ����������� �� �������

    node* getRoot() const;          // ���������� ��������� �� ������ ������
    int getSize() const;            // ������ ������
    int getSum() const;             // ������ ��������� � ������
    int getMin() const;             // ����������� ������� � ������
    int getMax() const;             // ������������ ������� � ������
    bool getIsIncreas() const;      // ���������� �� �������� ��������� � ������
    bool getIsDecreas() const;      // ������� �� �������� ��������� � ������

    int getLast() const;            // �������� ����� ��������� ������� ������
    node* getLastP() const;         // �������� ��������� �� ����� ��������� ������� ������
    int getFirst() const;            // �������� ����� ������ ������� ������
    node* getFirstP() const;        // �������� ��������� �� ����� ������ ������� ������

    // ���������� ��������� �� ������ ������� ������, �������, ��� ��������� �������� � ������, ������ ������������� �� �����������
    int getFirstBiggerThenIndex (int value);

    // ����������� �������� ����� � ������ ���������
    treap* left();
    treap* right();

    // ��������� ������� ���������, ������� ��������� �������� � ������ ��������� ��������
    void setSize (int inSize);
    void setRight (node* inRight);
    void setLeft (node* inLeft);
    void setRoot(node* inRoot);

    treap& operator = (treap& inTreap); // ���������� ��������� ������������
    friend std::ostream& operator << (std::ostream& out, treap& inTreap); // ���������� ��������� ��� ������ � �����
    friend std::ostream& operator << (std::ostream& out, treap* inTreap); // ���������� ��������� ��� ������ � �����

    splitPair* split (int x); // ��������� ������ �� 2, ������� ������� ������ x ���������, � ��������� �������
    splitPair* splitDecrease ();  // ��������� ������ �� ���������� ��������� ������� � �������

    virtual void Insert (int value, size_t index);                  // ������� �������� � ������������ �������
    virtual void Assign (int value, size_t index);                  // ��������� �������� ��������, ������������ � ������� index
    virtual long long SubsegmentSum (size_t left, size_t right);    // ���������� ����� �� ����������

    virtual void NextPermutation (size_t left, size_t right);       // ���������� ��������� ������������ �� ����������

    virtual int getLen();

    void reverse(); //����������� ��� �������� ������
    void push(); // ������������� ������� ��������

    void print (int counter = 0);
};

treap* merge (treap* treap1, treap* treap2); // ���������� �������, ����� ������������ � � �������

#endif // TREAP_PAVEL_KOSHKIN
