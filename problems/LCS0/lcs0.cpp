#include<iostream>

using namespace std;

int dyn[5000][5000]; // dyn[i][j] - > lcs of a[0..i-1] and b[0...j-1]

int main() {


    string a;
    string b;
    cin >> a >> b;


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

    cout << dyn[a.length()][b.length()] << endl;

    return 0;

}