#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedQueue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~LinkedQueue() {
        clear();
    }

    void enqueue(int e) {
        Node* newNode = new Node(e);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        ++size;
    }

    int dequeue() {
        if (isEmpty()) {
            return -1;
        }
        int dequeuedElement = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
        --size;
        if (isEmpty()) {
            rear = nullptr;
        }
        return dequeuedElement;
    }

    int first() {
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
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
}

