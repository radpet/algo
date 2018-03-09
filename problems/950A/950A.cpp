#include<iostream>
#include<cmath>

using namespace std;

int main() {

    int l, r, a;
    cin >> l >> r >> a;
    int total = min(l, r) + min(abs(l - r), a);
    if (a - abs(l - r) > 0) {
        total += (a - abs(l - r)) / 2;
    }
    cout << 2 * total << endl;
    return 0;
}