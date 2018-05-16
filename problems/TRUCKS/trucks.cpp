#include<iostream>

using namespace std;
int a[1024];
int dyn[1024][5000]; // dyn[n][k] = max load when choosing from first n items with capacity less than k
int main() {
    int K;
    cin >> K; // max 5000 load

    int N;
    cin >> N; // max 1024 items

    for (int i = 1; i <= N; i++) {
        cin >> a[i]; // max a[i] 5000
    }

    for (int n = 0; n <= N; n++) {
        dyn[n][0] = 0; // capacity 0
    }

    for (int k = 0; k <= K; k++) {
        dyn[0][k] = 0; // no items
    }

    for (int n = 1; n <= N; n++) {
        for (int k = 1; k <= K; k++) {
            if (k >= a[n]) {
                dyn[n][k] = max(dyn[n - 1][k], dyn[n - 1][k - a[n]] +
                                               a[n]); // max(don't take item n, take item n add see what is the best for the remaining capacity)
            } else {
                dyn[n][k] = dyn[n - 1][k]; // cannot take current item
            }
        }
    }

    cout << dyn[N][K] << endl;

    return 0;
}