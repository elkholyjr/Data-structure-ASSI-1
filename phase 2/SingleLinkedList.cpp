#include <bits/stdc++.h>
using namespace std;

template <class T>
class Node
{
public:
    T value;
    Node<T> *next;
    Node(T value, Node *next)
    {
        this->value = value;
        this->next = next;
    }
};

template <class T>
class LinkList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    void firstAdd(T value)
    {
        size++;
        Node<T> *newNode = new Node<T>(value, nullptr);
        head = newNode;
        tail = newNode;
    }

    void lastRemove()
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
    }

public:
    LinkList()
    {
        tail = head = nullptr;
        size = 0;
    }

    void insertAtTail(T value)
    {
        if (size == 0)
        {
            firstAdd(value);
            return;
        }
        Node<T> *curr = new Node<T>(value, nullptr);
        tail->next = curr;
        tail = curr;
        size++;
    }

    void insertAtHead(T value)
    {
        if (size == 0)
        {
            firstAdd(value);
            return;
        }
        head = new Node<T>(value, head);
        size++;
    }

    void removeAtHead()
    {
        if (size == 0)
            return;
        if (size == 1)
        {
            lastRemove();
            return;
        }
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void removeAtTail()
    {
        if (size == 0)
            return;
        if (size == 1)
        {
            lastRemove();
            return;
        }
        Node<T> *A = head;
        Node<T> *B = head;
        while (B->next != nullptr)
        {
            A = B;
            B = B->next;
        }
        delete tail;
        tail = A;
        tail->next = nullptr;
        size--;
    }

    void print()
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            cout << curr->value << ' ';
            curr = curr->next;
        }
        cout << '\n';
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    void insertAt(T value, int index)
    {
        if (index == 0)
        {
            insertAtHead(value);
            return;
        }
        if (index == size)
        {
            insertAtTail(value);
            return;
        }
        Node<T> *curr = head;
        Node<T> *before = head;
        while (index)
        {
            before = curr;
            curr = curr->next;
            index--;
        }
        before->next = new Node<T>(value, curr);
        size++;
    }

    void removeAt(int index)
    {
        if (size == 0)
        {
            return;
        }
        if (size == 1)
        {
            lastRemove();
            return;
        }
        if (index == 0)
        {
            removeAtHead();
            return;
        }
        Node<T> *A = head;
        Node<T> *B = head;
        while (index--)
        {
            A = B;
            B = B->next;
        }
        A->next = B->next;
        delete B;
        size--;
    }

    T retrieveAt(int index)
    {
        Node<T> *curr = head;
        while (index)
        {
            index--;
            curr = curr->next;
        }
        return curr->value;
    }

    void replaceAt(T value, int index)
    {
        Node<T> *curr = head;
        while (index)
        {
            index--;
            curr = curr->next;
        }
        curr->value = value;
    }

    bool isExist(T value)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->value == value)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool isItemAtEqual(T value, int index)
    {
        Node<T> *curr = head;
        while (index--)
        {
            curr = curr->next;
        }
        return (value == curr->value);
    }

    void swap(int firstIndex, int secondIndex)
    {
        if (firstIndex == secondIndex)
        {
            return;
        }
        Node<T> *fnd1 = head, *fnd2 = head, *beforeFnd1 = nullptr, *beforeFnd2 = nullptr;
        while (firstIndex || secondIndex)
        {
            if (firstIndex)
            {
                beforeFnd1 = fnd1;
                fnd1 = fnd1->next;
                firstIndex--;
            }
            if (secondIndex)
            {
                beforeFnd2 = fnd2;
                fnd2 = fnd2->next;
                secondIndex--;
            }
        }

        if (beforeFnd1 != nullptr && beforeFnd2 != nullptr)
        {
            beforeFnd1->next = fnd2;
            beforeFnd2->next = fnd1;
        }
        else if (beforeFnd1 == nullptr)
        {
            head = fnd2;
            beforeFnd2->next = fnd1;
        }
        else
        {
            head = fnd1;
            beforeFnd1->next = fnd2;
        }

        Node<T> *temp = fnd1->next;
        fnd1->next = fnd2->next;
        fnd2->next = temp;
    }

    int linkedListSize()
    {
        return size;
    }

    void clear()
    {
        while (!isEmpty())
        {
            removeAtHead();
        }
    }
};

int main()
{
}
