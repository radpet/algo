#include<iostream>

using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    int sign[2];
    sign[0] = -1;
    sign[1] = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (sign[i] * a + sign[j] * b + sign[k] * c == 13) {
                    cout << "Yes" << endl;
                    return 0;
                }
            }
        }
    }

    cout << "No" << endl;
    return 0;

}