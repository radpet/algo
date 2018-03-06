#include<iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int positive = 0;
    int negative = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a >= 0) {
            positive += a;
        } else {
            negative += a;
        }
    }

    cout << positive - negative << endl;

    return 0;
}