#include<iostream>

using namespace std;
int a[5001];

int love(int i) {
    return a[i];
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= 1;
    }

    for (int i = 0; i < n; i++) {
        if (love(love(love(i))) == i) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}