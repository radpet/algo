#include<iostream>

using namespace std;

bool isV(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main() {
    int n;
    cin >> n;
    char lastCh;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (i != 0) {
            if (isV(lastCh) && isV(ch)) {
            } else {
                cout << ch;
            }
        } else {
            cout << ch;
        }
        lastCh = ch;
    }
    cout << endl;
    return 0;
}