#include<iostream>

using namespace std;

template<typename T>
class MaxHeap {
private:
    T *buffer;
    int size;
    int capacity;

    bool isFull() const {
        return size == capacity;
    }

    int parent(int pos) const {
        return (pos - 1) / 2;
    }

    void siftUp(int pos) {
        while (pos > 0 && buffer[pos] > buffer[parent(pos)]) {
            swap(buffer[pos], buffer[parent(pos)]);
            pos = parent(pos);
        }
    }

    int left(int pos) const {
        return 2 * pos + 1;
    }

    int right(int pos) const {
        return 2 * pos + 2;
    }

    int biggerChild(int pos) const {
        if ((left(pos) == size - 1) || buffer[left(pos)] > buffer[right(pos)]) {
            return left(pos);
        }
        return right(pos);
    }

    bool isLeaf(int pos) const {
        return left(pos) >= size;
    }

    void siftDown(int pos) {
        int m;
        while (!isLeaf(pos) && buffer[pos] < buffer[m = biggerChild(pos)]) {
            swap(buffer[pos], buffer[m]);
            pos = m;
        }
    }

    void expand() {
        T *_buffer = new T[capacity];
        for (int i = 0; i < size; i++) {
            _buffer[i] = buffer[i];
        }
        delete[] buffer;

        buffer = new T[2 * capacity];

        for (int i = 0; i < capacity; i++) {
            buffer[i] = _buffer[i];
        }
        capacity = 2 * capacity;

        for (int i = capacity / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }

        delete[] _buffer;
    }

public:
    MaxHeap(int _n = 4) : size(0), capacity(_n) {
        buffer = new T[capacity];
    }

    ~MaxHeap() {
        delete buffer;
    }

    int len() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    // we add it to the end and reorder
    bool add(T const &x) {
        if (isFull()) {
            expand();
        }

        buffer[size++] = x;

        siftUp(size - 1);

        return true;
    }

    T head() const {
        return buffer[0];
    }

    // we move the top element to the end and reorder the queue
    T pop() {
        if (empty()) {
            return T();
        }

        swap(buffer[0], buffer[--size]);
        siftDown(0);
        return buffer[size];
    }

    T const *toArray() const {
        return buffer;
    }
};


int main() {

    MaxHeap<int> heap;

    heap.add(1);
    heap.add(3);
    heap.add(5);
    heap.add(7);

    heap.add(2);
    heap.add(4);
    heap.add(6);
    heap.add(8);

    cout << "Heap len" << heap.len() << endl;

//    const int *a = heap.toArray();
//    for (int i = 0; i < 8; i++) {
//        cout << a[i] << endl;
//    }


    for (int i = 8; i >= 1; i--) {
        cout << heap.pop() << " should be " << i << endl;
    }

}