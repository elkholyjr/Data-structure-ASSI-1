#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class Queue {
private:
    T* arr;
    int maxSize;
    int front;
    int rear;
    int currentSize;

public:
    Queue(int size) {
        maxSize = size;
        arr = new T[maxSize];
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(T element) {
        if (currentSize == maxSize) {
            throw overflow_error("Queue is full");
        }
        rear = (rear + 1) % maxSize;
        arr[rear] = element;
        ++currentSize;
    }

    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        T dequeuedElement = arr[front];
        front = (front + 1) % maxSize;
        --currentSize;
        return dequeuedElement;
    }

    T first() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        return arr[front];
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    int queueSize() {
        return currentSize;
    }

    void clear() {
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    void print() {
        int i = front;
        int count = 0;
        while (count < currentSize) {
            cout << arr[i] << " ";
            i = (i + 1) % maxSize;
            ++count;
        }
        cout << endl;
    }
};

int main() {
}
