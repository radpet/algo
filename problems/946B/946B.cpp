#include<iostream>

using namespace std;

int main() {

    long long n, m;

    cin >> n >> m;

    while (n > 0 && m > 0) {
        if (n >= 2 * m) {
            n = n % (2 * m);
        } else {

            if (m >= 2 * n) {
                m = m % (2 * n);
            } else {
                break;
            }
        }
    }

    cout << n << " " << m << endl;
}