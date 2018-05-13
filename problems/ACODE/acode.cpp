#include<iostream>

using namespace std;

long long solve(string seq) {

    for (int i = 0; i < seq.length() - 1; i++) {
        if ((seq[i] != '1' && seq[i] != '2') && seq[i + 1] == '0') {
            return 0;
        }
    }

    long long dyn[5006];
    dyn[0] = 1;
    dyn[1] = 1;

    for (int k = 2; k <= seq.length(); k++) {
        dyn[k] = 0;
        int last = seq[k - 2] - '0';
        int cur = seq[k - 1] - '0';
        if (last == 1 || (last == 2 && cur <= 6)) {
            dyn[k] += dyn[k - 2];
        }
        if (cur != 0) {
            dyn[k] += dyn[k - 1];
        }
    }
    return dyn[seq.length()];
}


int main() {

    string line;
    while (getline(cin, line)) {
        if (string("0").compare(line) == 0) {
            break;
        }

        cout << solve(line) << endl;

    }

    return 0;
}