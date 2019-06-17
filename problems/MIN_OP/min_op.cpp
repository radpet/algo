#include<iostream>

using namespace std;

long minRules(int k, long MEMO[]) {
    if (MEMO[k] != -1) {
        return MEMO[k];
    }
    if (k == 0) {
        return MEMO[k] = 0;
    }
    if (k == 1 || k == 2 || k == 3) {
        return MEMO[k] = 1;
    }


    long minusOne = minRules(k - 1, MEMO);
    long even = minusOne;
    long three = minusOne;

    if (k % 2 == 0) {
        even = minRules(k / 2, MEMO);
    }

    if (k % 3 == 0) {
        three = minRules(k / 3, MEMO);
    }
    return MEMO[k] = min(min(minusOne, even), three) + 1;
}

long solve(int N) {
    long *MEMO = new long[max(4, N) + 1];
    for (int i = 0; i <= N; i++) {
        MEMO[i] = -1;
    }
    long result = minRules(N, MEMO);
    delete[] MEMO;
    return result;
}

long solveIterative(int N) {
    long *dp = new long[max(4, N) + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;
    for (int i = 4; i < N; i++) {
        dp[i] = i;
    }

    for (int i = 4; i <= N; i++) {
        int minusOne = dp[i - 1];
        int even = minusOne;
        int three = minusOne;
        if (i % 2 == 0) {
            even = dp[i / 2];
        }

        if (i % 3 == 0) {
            three = dp[i / 3];
        }


        dp[i] = min(min(minusOne, even), three) + 1;
    }

    long result = dp[N];
    delete[] dp;
    return result;
}

int main() {

    int testCases[] = {1, 5, 6, 7, 22, 33, 45, 99, 542, 123, 121, 0,
                       110, 115, 226, 2690, 4470, 6809, 7777,
                       50000, 99999};
    for (int testCase : testCases) {
        long recursive = solve(testCase);
        long iterative = solveIterative(testCase);
        if (recursive != iterative) {
            cout << "!!!ERROR!!! " << "N=" << testCase << " recursive=" << recursive << " vs iterative=" << iterative
                 << endl;
            return 1;
        } else {
            cout << "N=" << testCase << " recursive=" << recursive << " vs iterative=" << iterative
                 << endl;
        }
    }

    cout << "PASS" << endl;
    return 0;
}