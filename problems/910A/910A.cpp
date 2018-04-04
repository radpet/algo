#include<iostream>

using namespace std;
bool path[128];

int step(int current, int d, int n) {
    for (int step = d; step >= 1; step--) {
        if (current + step >= n - 1) {
            return n - 1;
        }
        if (path[current + step]) {
            return current + step;
        }
    }
    return -1;
}


int main() {

    int n;
    int d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        path[i] = c - '0';
    }

    int start = 0;
    int steps = 0;
    while (true) {
        if (start == -1) {
            cout << -1 << endl;
            return 0;
        }
        if (start == n - 1) {
            cout << steps << endl;
            return 0;
        }
        start = step(start, d, n);
        steps += 1;
    }
}