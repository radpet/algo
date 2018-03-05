#include<iostream>

using namespace std;

int main() {

    long long n, k;

    cin >> n >> k;
    long long ans;
    long long ansType;
    long long rem;
    bool init = false;
    for (int i = 0; i < k; i++) {
        long long cap;
        cin >> cap;
        if (cap > n) {
            continue;
        }
        if (init) {
            if (rem > (n % cap)) {
                ansType = i;
                ans = n / cap;
                rem = n % cap;
            }
        } else {
            init = true;
            ansType = i;
            ans = n / cap;
            rem = n % cap;
        }

    }
    if (!init) {
        ansType = 0;
        ans = 0;
    }
    cout << ansType + 1 << " " << ans << endl;
    return 0;
}