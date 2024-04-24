#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x,y,z=1,t=1,a,b,d;

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};

template<typename T>
class CircularLinkedList {
private:
    Node<T>* head;
    int size;
public:
    CircularLinkedList() : head(nullptr), size(0) {}

    void insertAtHead(T val) {
        Node<T> *node = new Node<T>(val);
        if (!head) {
            node->next = node;
            head = node;
        } else {
            node->next = head->next;
            head->next = node;
        }
        size++;
    }
    void insertAtTail(T val) {
        Node<T>* node = new Node<T>(val);
        if (!head) {
            node->next = node;
            head = node;
        } else {
            node->next = head->next;
            head->next = node;
            head = node;
        }
        size++;
    }
    void insertAt(T val, int idx) {
        if (idx < 0 || idx > size) {
            throw invalid_argument("Error");
        }
        if (idx == 0) {
            insertAtHead(val);
        } else if (idx == size) {
            insertAtTail(val);
        } else {
            Node<T>* node = new Node<T>(val);
            Node<T>* curr = head;
            for (int i = 0; i < idx; i++) {
                curr = curr->next;
            }
            node->next = curr->next;
            curr->next = node;
            size++;
        }
    }
    void removeAtHead() {
        if (!head) {
            return;
        }
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head->next;
            head->next = temp->next;
            delete temp;
        }
        size--;
    }
    void removeAtTail() {
        if (!head) {
            return;
        }
        Node<T>* curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        if (curr == head) {
            delete curr;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            head = curr;
            head->next = temp->next;
            delete temp;
        }
        size--;
    }
    void removeAt(int idx) {
        if (idx < 0 || idx >= size) {
            throw invalid_argument("Error");
        }
        if (idx == 0) {
            removeAtHead();
        } else if (idx == size - 1) {
            removeAtTail();
        } else {
            Node<T>* curr = head;
            for (int i = 0; i < idx; i++) {
                curr = curr->next;
            }
            Node<T>* temp = curr->next;
            curr->next = temp->next;
            delete temp;
            size--;
        }
    }
    T retrieveAt(int idx) {
        if (idx < 0 || idx >= size) {
            throw invalid_argument("Error");
        }
        Node<T>* curr = head;
        for (int i = 0; i < idx; i++) {
            curr = curr->next;
        }
        return curr->data;
    }
    void replaceAt(T newVal, int idx) {
        if (idx < 0 || idx >= size) {
            throw invalid_argument("Error");
        }
        Node<T>* curr = head;
        for (int i = 0; i < idx; i++) {
            curr = curr->next;
        }
        curr->data = newVal;
    }
    bool isExist(T val) {
        Node<T>* curr = head;
        for (int i = 0; i < size; i++) {
            if (curr->data == val) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    bool isItemAtEqual(T val, int idx) {
        if (idx < 0 || idx >= size) {
            throw invalid_argument("Error");
        }
        Node<T>* curr = head;
        for (int i = 0; i < idx; i++) {
            curr = curr->next;
        }
        return curr->data == val;
    }
    void swap(int firstIdx, int secondIdx) {
        if (firstIdx < 0 || firstIdx >= size || secondIdx < 0 || secondIdx >= size) {
            throw invalid_argument("Error");
        }
        if (firstIdx == secondIdx) {
            return;
        }
        if (firstIdx > secondIdx) {
            swap(secondIdx, firstIdx);
            return;
        }
        if (firstIdx == 0 && secondIdx == size - 1) {
            Node<T>* FP = head;
            while (FP->next != head) {
                FP = FP->next;
            }
            Node<T>* SP = head;
            for (int i = 0; i < size - 2; i++) {
                SP = SP->next;
            }
            Node<T>* temp = head;
            head = head->next;
            FP->next = SP->next;
            SP->next = temp;
            temp->next = head;
        } else {
            Node<T>* firstNode = head;
            Node<T>* secondNode = head;
            for (int i = 0; i < firstIdx; i++) {
                firstNode = firstNode->next;
            }
            for (int i = 0; i < secondIdx; i++) {
                secondNode = secondNode->next;
            }
            Node<T>* firstPrev = head;
            for (int i = 0; i < firstIdx - 1; i++) {
                firstPrev = firstPrev->next;
            }
            Node<T>* secondPrev = head;
            for (int i = 0; i < secondIdx - 1; i++) {
                secondPrev = secondPrev->next;
            }
            if (firstIdx == 0) {
                head = secondNode;
            } else {
                firstPrev->next = secondNode;
            }
            if (secondIdx == firstIdx + 1) {
                firstNode->next = secondNode->next;
                secondNode->next = firstNode;
            } else {
                secondPrev->next = firstNode;
                Node<T>* temp = firstNode->next;
                firstNode->next = secondNode->next;
                secondNode->next = temp;
            }
        }
    }
    bool isEmpty() {
        return size == 0;
    }
    int linkedListSize() {
        return size;
    }
    void clear() {
        while (head) {
            removeAtHead();
        }
    }
    void print() {
        if (!head) {
            cout << "is empty" << endl;
            return;
        }
        Node<T>* curr = head->next;
        do {
            cout << curr->data<<' ';
            curr = curr->next;
        } while (curr != head->next);
        cout << "\n";
    }
    ~CircularLinkedList() {
        clear();
    }
};

int main() {
    CircularLinkedList<int> helpMe;
    helpMe.insertAtHead(1);
    helpMe.insertAtTail(2);
    helpMe.insertAtTail(3);
    helpMe.insertAt(4, 1);
    helpMe.print();
    helpMe.removeAt(1);
    helpMe.removeAtTail();
    helpMe.print();
    cout << helpMe.retrieveAt(1) << endl;
    helpMe.replaceAt(5, 1);
    helpMe.print();
    cout << helpMe.isExist(1) << endl;
    cout << helpMe.isItemAtEqual(5, 1) << endl;
    helpMe.swap(0, 1);
    helpMe.print();
    cout << helpMe.isEmpty() << endl;
    cout << helpMe.linkedListSize() << endl;
    helpMe.clear();
    helpMe.print();
    cout << helpMe.isEmpty() << endl;
    return 0;
}
