#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    list<T> datalist;
public:
    Stack() {
        list<T> mylist;
    }
    Stack(int size) {
        list<T> mylist(size);
    }
    void push(T val) {
        datalist.push_front(val);
    }
    T top() {
        if (datalist.empty()) {
            throw underflow_error("Stack is Empty!");
        }
        return datalist.front();
    }
    T pop() {
        if (datalist.empty()) {
            throw underflow_error("Stack has no elements!");
        }
        T poppedValue = datalist.front();
        datalist.pop_front();
        return poppedValue;
    }
    bool isEmpty() {
        return (datalist.empty());
    }
    int stackSize() {
        return datalist.size();
    }
    void print() {
        for (auto it = datalist.rbegin(); it != datalist.rend(); it++) {
            cout << *(it) << " ";
        }
    }
    void clear() {
        datalist.clear();
    }
};

int main()
{
}
