#include<iostream>

using namespace std;

int main() {

    int n;
    cin >> n;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        bool ans = false;
        if (x % 3 == 0) {
            ans = true;
        }

        if (x % 7 == 0) {
            ans = true;
        }

        if (ans != true) {
            for (int a = 0; a < x; a++) {
                if (a * 3 > x) {
                    break;
                }
                if ((x - a * 3) % 7 == 0) {
                    ans = true;
                    break;
                }
            }
        }


        if (ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}