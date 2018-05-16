#include<iostream>

using namespace std;


int dp[5001]; //dp[k] - least count of squares that sum to k
int ans[5001]; // ans[k] - last square in the sum
int main() {

    int n; // n<=5000

    cin >> n;

    dp[0] = 0;
    ans[0] = 0;
    dp[1] = 1;
    ans[1] = 1;

    for (int k = 1; k <= n; k++) {
        dp[k] = k + 1;
        ans[k] = 1;
        for (int j = 1; j * j <= k; j++) {
            if (dp[k] > dp[k - (j * j)]) {
                dp[k] = dp[k - (j * j)];
                ans[k] = j * j;
            }
        }
        dp[k] = dp[k] + 1;
    }

    cout << dp[n] << endl;
    int i = n;
    while (ans[i] != 0) {
        cout << ans[i] << " ";
        i = i - ans[i];
    }

    return 0;
}