#include<iostream>
#include<math.h>

using namespace std;

const int MAXN = 100001;
int a[MAXN];

int solve(int n) {
    int ans = int(1e7);
    for (int i = 0; i < n + 1; i++) {
        int cur = 0;
        if (i != 0) {
            cur = max(cur, a[i - 1] - 1);
        }
        if (i != n) {
            cur = max(cur, int(1e6) - a[i]);
        }
        ans = min(ans, cur);
    }
    return ans;
}

int main() {

    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << solve(n) << endl;

    return 0;
}