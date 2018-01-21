#include<iostream>

using namespace std;


struct Node {
    int x;
    Node *left, *right;
};


bool complement(const Node *t1, const Node *t2) {
    if (t2 == nullptr) {
        return true;
    }
    if (t1 == nullptr && t2 != nullptr) {
        return false;
    }

    return (t1->x == t2->x) && complement(t1->left, t2->left) && complement(t1->right, t2->right);
}


int main() {
    Node *t1;
    t1->x = 1;
    t1->left = new Node();
    t1->left->x = 2;
    t1->left->left = nullptr;
    t1->left->right = nullptr;

    t1->right = new Node();
    t1->right->x = 3;
    t1->right->left = nullptr;
    t1->right->right = nullptr;


    Node *t2 = new Node();
    t2->x = 11;
    t2->left = new Node();
    t2->left->x = 2;
    t2->left->left = nullptr;
    t2->left->right = nullptr;

    t2->right = new Node();
    t2->right->x = 3;
    t2->right->left = nullptr;
    t2->right->right = nullptr;


    cout << complement(t1, t2) << endl;
}