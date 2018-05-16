#include<iostream>

using namespace std;
int dp[10000]; // dp[n] = number of ways for the student to land on step n
int main() {
    int N;
    cin >> N;

    dp[0] = 0;
    dp[1] = 1; //using step1
    dp[2] = 2; // using 2*step1 and using 1*step2

    for (int n = 3; n <= N; n++) {
        dp[n] = dp[n - 1] + dp[n - 2];
    }

    cout << dp[N] << endl;
}