#include <iostream>
#include <stdexcept>

using namespace std;

class CreateQueue {
private:
    int* arr;
    int mxSize;
    int front;
    int rear;
    int currentSize;

public:
    CreateQueue(int size) {
        mxSize = size;
        arr = new int[mxSize];
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    ~CreateQueue() {
        delete[] arr;
    }

    void enqueue(int element) {
        if (currentSize == mxSize) {
            throw overflow_error("Queue is full");
        }
        rear = (rear + 1) % mxSize;
        arr[rear] = element;
        ++currentSize;
    }

    int dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        int dequeuedElement = arr[front];
        front = (front + 1) % mxSize;
        --currentSize;
        return dequeuedElement;
    }

    int first() {
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
            i = (i + 1) % mxSize;
            ++count;
        }
        cout << endl;
    }
};

int main() {
}
