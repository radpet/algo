#include<iostream>

using namespace std;

#include<algorithm>

int a[512];
int n, d;
int memo[128][128];

int solve(int first, int last) {
    if (last == first) {
        return 0;
    }
    if (a[last] - a[first] <= d) {
        return 0;
    }

    if (memo[first][last] != -1) {
        return memo[first][last];
    }

    int left = 1 + solve(first + 1, last);
    int right = 1 + solve(first, last - 1);

    return memo[first][last] = min(left, right);

}

int main() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memo[i][j] = -1;
        }
    }
    cout << solve(0, n - 1) << endl;

    return 0;
}