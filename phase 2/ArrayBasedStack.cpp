#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    int capacity;
    T* arr;
    int size;
    void extend() {
        capacity *= 2;
        T* temp = new T[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
public:
    Stack() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }
    Stack(int sz) {
        size = 0;
        capacity = sz;
        arr = new T[capacity];
    }
    bool isEmpty() {
        return (size == 0);
    }

    T top() {
        if (isEmpty()) {
            throw underflow_error("Stack is Empty!\n");
        }
        return arr[size - 1];
    }
    void push(T value) {
        if (size == capacity) {
            extend();
        }
        arr[size++] = value;
    }
    T pop() {
        if (isEmpty()) {
            throw underflow_error("Stack is Empty!\n");
        }
        return arr[size--];
    }
    
    int stackSize() {
        return size;
    }
    void clear() {
        delete[] arr;
        size = 0;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
    ~Stack() {
        delete[] arr;
    }

};

int main() {
    Stack<string> mystack;
    mystack.push("5");
    mystack.pop();
    cout << mystack.isEmpty();
    mystack.pop();
}