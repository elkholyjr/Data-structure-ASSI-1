#include <iostream>
using namespace std;

template <typename T>
class doubleLinkedList {
  private:
    struct node {
        node *next;
        node *prev;
        T data;
    };
    int count;
    node *first;
    node *last;

  public:
    doubleLinkedList();

    void insertAtHead(T element);

    void insertAtTail(T element);

    void insertAt(T element, int index);

    void removeAtHead();

    void removeAtTail();

    void removeAt(int index);

    T retrieveAt(int index);

    void replaceAt(T newElement, int index);

    bool isExist(T element);

    bool isItemAtEqual(T element, int index);

    void swap(int firstItemIdx, int secondItemIdx);

    bool isEmpty();

    int linkedListSize();

    void clear();

    void print();
};

template <typename T>
doubleLinkedList<T>::doubleLinkedList() : count(0), first(nullptr), last(nullptr) {}

template <typename T>
bool doubleLinkedList<T>::isEmpty() {
    return count == 0;
}
template <typename T>
int doubleLinkedList<T>::linkedListSize() {
    return count;
}

template <typename T>
void doubleLinkedList<T>::clear() {
    while (first != nullptr) {
        node *temp = first;
        first = first->next;
        delete temp;
    }
    last = nullptr;
    count = 0;
}

template <typename T>
void doubleLinkedList<T>::insertAtHead(T element) {
    node *newNode = new node;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    newNode->data = element;
    if (isEmpty()) {
        first = last = newNode;
    } else {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    count++;
}

template <typename T>
void doubleLinkedList<T>::insertAtTail(T element) {
    node *newNode = new node;
    newNode->next = nullptr;
    newNode->data = element;
    if (isEmpty()) {
        first = last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }
    count++;
}

template <typename T>
void doubleLinkedList<T>::insertAt(T element, int index) {
    if (index < 0 || index > count) {
        cout << "Index out of bounds." << endl;
        return;
    }
    if (index == 0) {
        insertAtHead(element);
    } else if (index == count) {
        insertAtTail(element);
    } else {
        node *current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        node *newNode = new node;
        newNode->next = current;
        newNode->prev = current->prev;
        newNode->data = element;
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }
}

template <typename T>
void doubleLinkedList<T>::removeAtHead() {
    if (!isEmpty()) {
        node *temp = first;
        if (first == last) {
            first = last = nullptr;
        } else {
            first = first->next;
            first->prev = nullptr;
        }
        delete temp;
        count--;
    }
}

template <typename T>
void doubleLinkedList<T>::removeAtTail() {
    if (!isEmpty()) {
        node *temp = last;
        if (first == last) {
            first = last = nullptr;
        } else {
            last = last->prev;
            last->next = nullptr;
        }
        delete temp;
        count--;
    }
}

template <typename T>
void doubleLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        cout << "Index out of bounds." << endl;
        return;
    }

    if (index == 0) {
        removeAtHead();
    } else if (index == count - 1) {
        removeAtTail();
    } else {
        node *current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }
}

template <typename T>
T doubleLinkedList<T>::retrieveAt(int index) {
    if (index < 0 || index >= count) {
        cout << "Index out of bounds." << endl;
        return -1;
    }

    node *current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void doubleLinkedList<T>::replaceAt(T newElement, int index) {
    if (index < 0 || index >= count) {
        cout << "Index out of bounds." << endl;
        return;
    }

    node *current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = newElement;
}

template <typename T>
bool doubleLinkedList<T>::isExist(T element) {
    node *current = first;
    while (current != nullptr) {
        if (current->data == element) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool doubleLinkedList<T>::isItemAtEqual(T element, int index) {
    if (index < 0 || index >= count) {
        cout << "Index out of bounds." << endl;
        return false;
    }

    node *current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data == element;
}

template <typename T>
void doubleLinkedList<T>::swap(int firstItemIdx, int secondItemIdx) {
    if (firstItemIdx < 0 || firstItemIdx >= count || secondItemIdx < 0 || secondItemIdx >= count) {
        cout << "Index out of bounds." << endl;
        return;
    }

    if (firstItemIdx == secondItemIdx) {
        return;
    }

    node *firstNode = first;
    node *secondNode = first;

    for (int i = 0; i < firstItemIdx; i++) {
        firstNode = firstNode->next;
    }
    for (int i = 0; i < secondItemIdx; i++) {
        secondNode = secondNode->next;
    }

    node *firstPrev = firstNode->prev;
    node *firstNext = firstNode->next;
    node *secondPrev = secondNode->prev;
    node *secondNext = secondNode->next;

    if (firstPrev != nullptr)
        firstPrev->next = secondNode;
    if (firstNext != nullptr)
        firstNext->prev = secondNode;
    if (secondPrev != nullptr)
        secondPrev->next = firstNode;
    if (secondNext != nullptr)
        secondNext->prev = firstNode;

    node *temPrev = firstNode->prev;
    node *temNext = firstNode->next;

    firstNode->prev = secondNode->prev;
    firstNode->next = secondNode->next;
    secondNode->prev = temPrev;
    secondNode->next = temNext;

    if (firstPrev == nullptr)
        first = secondNode;
    if (secondPrev == nullptr)
        first = firstNode;

    if (firstNext == nullptr)
        last = secondNode;
    if (secondNext == nullptr)
        last = firstNode;
}

template <typename T>
void doubleLinkedList<T>::print() {
    node *current = first;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    doubleLinkedList<int> myList;

    myList.insertAtTail(10);
    myList.insertAtTail(20);
    myList.insertAtTail(30);
    myList.insertAtTail(40);

    cout << "our current List: ";
    myList.print();

    cout << "Size Of Our Linked List: ";
    cout << myList.linkedListSize() << endl;

    myList.insertAtHead(9);
    cout << "our List After Insertion (9) at head: ";
    myList.print();

    myList.insertAt(15, 1);
    cout << "Our List After Insertion (15) at Index 1: ";
    myList.print();

    myList.insertAtTail(7);
    cout << "Our List After Insertion (7) At Tail: ";
    myList.print();

    myList.replaceAt(10, 2);
    cout << "Our List After Replacement (10) at Index 2: ";
    myList.print();

    cout << "Retrive Data In The List At Index 3: ";
    cout << myList.retrieveAt(3) << endl;

    myList.removeAtHead();
    cout << "Our List After Removing Head: ";
    myList.print();

    myList.removeAtTail();
    cout << "Our List After Removing Tail: ";
    myList.print();

    myList.removeAt(1);
    cout << "Our List After Removing At Index 1: ";
    myList.print();

    if (myList.isExist(25)) {
        cout << "Element (25) exists in the list." << endl;
    } else {
        cout << "Element (25) does not exist in the list." << endl;
    }

    if (myList.isItemAtEqual(15, 0)) {
        cout << "Element (15) equal the item at index 0" << endl;
    } else {
        cout << "Element (15) does not equal the item at index 0" << endl;
    }

    myList.swap(0, 3);
    cout << "Our List After Swapping Indices 0 and 3: ";
    myList.print();

    cout << "Clear our list" << endl;
    myList.clear();
    cout << "List Is Empty? " << (myList.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
