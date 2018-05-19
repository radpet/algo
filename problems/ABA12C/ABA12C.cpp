#include <iostream>

using namespace std;

int dyn[128][128];
const int L = 10000;

int solverec(int n, int k, int c[], int s) {
//    if (n < 0) {
//        return L;
//    }
    if (s == 0) {
        return 0;
    }

    int minCost = dyn[k][s];
    if (dyn[k][s] != L) {
        return dyn[k][s];
    }

    for (int i = 1; i <= k; i++) {
        if (c[i] != -1 && s - i >= 0) {
            minCost = min(minCost, solverec(n - 1, k, c, s - i) + c[i]);
        }
    }

    return dyn[k][s] = minCost;

}


int solve(int n, int k, int c[]) {

    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            dyn[i][j] = L;
        }
    }
    int minCost = solverec(n, k, c, k);

    if (minCost == L) {
        return -1;
    } else {
        return minCost;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        int c[128];
        cin >> n >> k;

        for (int i = 1; i <= k; i++) {
            cin >> c[i];
        }

        cout << solve(n, k, c) << endl;
    }
}