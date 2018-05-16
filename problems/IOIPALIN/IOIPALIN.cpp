#include<iostream>

using namespace std;
const int MAXN = 5100;
int dyn[MAXN][MAXN];

int lcs(const string &a, const string &b) {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dyn[i][j] = 0;
        }
    }
    //dyn[i][j] = longest commons subsequence for strings a[0..i-1] b[0...j-1]
    for (int i = 0; i <= a.length(); i++) {
        dyn[i][0] = 0;
    }

    for (int j = 0; j <= b.length(); j++) {
        dyn[0][j] = 0;
    }

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            if (a[i - 1] == b[j - 1]) {
                dyn[i][j] = dyn[i - 1][j - 1] + 1;
            } else {
                dyn[i][j] = max(dyn[i - 1][j], dyn[i][j - 1]);
            }
        }
    }

    return dyn[a.length()][b.length()];
}


int main() {
    int n;
    cin >> n;
    string s;

    cin >> s;
    string s_rev = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        s_rev += s[i];
    }


    int l = lcs(s, s_rev);
    cout << s.length() - l << endl;
    return 0;
}