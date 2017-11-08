#include<iostream>

template<typename T>
class Stack {
public:
    virtual bool empty() const = 0;

    virtual bool push(const T t) = 0;

    virtual bool pop() = 0;

    virtual T peek() = 0;
};

template<typename T>
class ArrayStack : public Stack<T> {

private:
    static const int MAXN = 128;
    T buffer[MAXN];
    int end;

    bool full() const {
        return end == MAXN;
    }

public:

    ArrayStack() : end(-1) {
    }

    bool empty() const {
        return end == -1;
    }

    bool push(const T t) {
        if (full()) {
            return false;
        }
        buffer[++end] = t;
        return true;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        end -= 1;
        return true;
    }

    T peek() {
        if (empty()) {
            return T();
        }
        return buffer[end];
    }
};


template<typename T>
class LinkedStack : public Stack<T> {

};

template<typename T>
void assertEmpty(ArrayStack<T> &arrayStack, bool expected) {
    std::cout << "AssertEmpty: " << (arrayStack.empty() == expected) << std::endl;
}

int main() {

    ArrayStack<int> arrayStack;

    std::cout << (arrayStack.empty() == true) << std::endl;
    std::cout << (arrayStack.pop() == false) << std::endl;
    arrayStack.push(1);
    assertEmpty(arrayStack, false);
    std::cout << (arrayStack.pop() == true) << std::endl;
    arrayStack.push(1);
    std::cout << (arrayStack.peek() == 1) << std::endl;
    arrayStack.pop();
    assertEmpty(arrayStack, true);
    bool error = false;

    for (int i = 0; i < 1000; i++) {
        if (error) {
            std::cout << "Error at step: " << i << std::endl;
        }
        arrayStack.push(1);
        error |= !(arrayStack.peek() == 1);
        arrayStack.pop();
        error |= !(arrayStack.empty());
    }

    std::cout << (error == false) << std::endl;

    assertEmpty(arrayStack, true);

    for (int i = 0; i < 128; i++) {
        arrayStack.push(i);
    }
    error = false;
    for (int i = 127; i >= 0; i--) {
        error |= !(arrayStack.peek() == i);
        arrayStack.pop();
    }
    std::cout << (error == false) << std::endl;
    assertEmpty(arrayStack, true);

    return 0;
}
