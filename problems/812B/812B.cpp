#include<iostream>

using namespace std;

bool flat[16][128];
int n, m;
int topFloor = -1;

int solve(int curF, int curR) {
    // choosed left stairs
    int steps = 0;
    if (curR == 0) {
        for (int i = 1; i <= m; i++) {
            if (flat[curF][i]) {
                steps = i;
                curR = i;
            }
        }
    }

    if (curR == m + 1) {
        for (int i = m; i >= 1; i--) {
            if (flat[curF][i]) {
                steps = m + 1 - i;
                curR = i;
            }
        }
    }
    if (curF - 1 < topFloor) {
        return steps;
    }

    // chose left or right
    int left = steps + curR + 1 + solve(curF - 1, 0);
    int right = steps + m + 1 - curR + 1 + solve(curF - 1, m + 1);

    return min(left, right);

}

int main() {

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m + 2; j++) {
            char c;
            cin >> c;
            flat[i][j] = c - '0';
            if (flat[i][j]) {
                if (topFloor == -1) {
                    topFloor = i;
                }
            }
        }
    }
    if (topFloor == -1) {
        cout << 0 << endl;
    } else {
        cout << solve(n - 1, 0) << endl;
    }


    return 0;

}