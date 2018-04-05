#include<iostream>

using namespace std;

int ans[1024];

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    for (int i = 0; i < n; i++) {
        ans[i] = 1;
        int cur = 1;

        for (int j = i; j < n - 1; j++) {
            if (s[j] == 'L') {
                cur += 1;
            }
            if (s[j] == 'R') {
                break;
            }
        }
        ans[i] = max(ans[i], cur);
        cur = 1;
        for (int j = i-1; j >= 0; j--) {
            if (s[j] == 'L') {
                break;
            }

            if (s[j] == 'R') {
                cur += 1;
            }
        }
        ans[i] = max(ans[i], cur);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}