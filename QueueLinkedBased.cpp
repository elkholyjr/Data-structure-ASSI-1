#include <iostream>
using namespace std;
template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedQueue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~LinkedQueue() {
        clear();
    }

    void enqueue(T e) {
        Node<T>* newNode = new Node<T>(e);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        ++size;
    }

    T dequeue() {
        if (isEmpty()) {
            return -1;
        }
        T dequeuedElement = front->data;
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        --size;
        if (isEmpty()) {
            rear = nullptr;
        }
        return dequeuedElement;
    }

    T first() {
        if (isEmpty()) {
            return -1;
        }
        return front->data;
    }

    bool isEmpty() {
        return (size == 0);
    }

    int queueSize() {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void print() {
        Node<T>* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
}
