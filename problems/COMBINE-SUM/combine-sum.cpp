#include<iostream>

using namespace std;

struct Elem {
    int x;
    Elem *next;
};

void combineSum(Elem *lists[], int n, Elem *&L) {
    bool running = true;

    Elem *working[n];
    for (int i = 0; i < n; i++) {
        working[i] = lists[i];
    }
    L = nullptr;
    Elem *tmp = nullptr;

    while (true) {
        int value = 0;
        running = false;
        for (int i = 0; i < n; i++) {
            if (working[i] == nullptr) {
                value += 0;
            } else {
                running = true;
                value += working[i]->x;
                working[i] = working[i]->next;
            }
        }

        if (!running) {
            break;
        }

        if (tmp == nullptr) {
            tmp = new Elem();
            tmp->x = value;
            tmp->next = nullptr;
            L = tmp;
        } else {
            tmp->next = new Elem();
            tmp->next->x = value;
            tmp->next->next = nullptr;
            tmp = tmp->next;
        }
    }


}


int main() {

    Elem *a = new Elem();
    a->x = 1;
    a->next = new Elem();
    a->next->x = 2;
    a->next->next = nullptr;

    Elem *b = new Elem();
    b->x = 1;
    b->next = new Elem();
    b->next->x = 2;
    b->next->next = new Elem();
    b->next->next->x = 3;
    b->next->next->next = nullptr;


    Elem *l[] = {a, b};

    Elem *result = nullptr;

    combineSum(l, 2, result);

    Elem *tmp = result;

    while (tmp != nullptr) {
        cout << tmp->x << " ";
        tmp = tmp->next;
    }

    cout << endl;
}
