#include <iostream>
using namespace std;

template <class T>
class Stack {
  private:
    struct Node {
        T value;
        Node *next = nullptr;
        Node(T value, Node *next) : value(value), next(next) {}
    };

    int size = 0;
    Node *head = nullptr;

  public:
    Stack() {
        head = nullptr;
        size = 0;
    }

    T top() {
        if (!size)
            throw invalid_argument("Empty Stack");
        return head->value;
    }

    void push(T value) {
        head = new Node(value, head);
        size++;
    }

    void pop() {
        if (!size) {
            throw invalid_argument("Empty Stack");
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void print() {
        Node *curr = head;
        while (curr) {
            cout << curr->value << ' ';
            curr = curr->next;
        }
        cout << '\n';
    }

    int stackSize() {
        return size;
    }

    bool empty() {
        return size == 0;
    }
};

int main() {
    Stack<int> ss;

    ss.push(1);
    ss.push(2);
    ss.push(3);
    ss.push(4);
    ss.push(5);

    cout << ss.stackSize() << '\n';
    ss.print();

    ss.pop();

    ss.pop();

    cout << ss.stackSize() << '\n';
    ss.print();
}