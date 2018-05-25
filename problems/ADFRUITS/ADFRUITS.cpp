#include<iostream>

using namespace std;

string reverse(string a) {
    string result = "";
    for (int i = a.length() - 1; i >= 0; i--) {
        result += a[i];
    }

    return result;
}

string lcs(string &a, string &b) {
    int dyn[128][128]; // dyn[i][j] = lcs of strings (a[0..i-1],b[0...j-1])
    string result = "";
    for (int i = 0; i <= a.length(); i++) {
        dyn[i][0] = 0;
    }

    for (int j = 0; j <= b.length(); j++) {
        dyn[0][j] = 0;
    }

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            dyn[i][j] = 0;

            if (a[i - 1] != b[j - 1]) {
                dyn[i][j] = max(dyn[i - 1][j], dyn[i][j - 1]);
            } else {
                dyn[i][j] = dyn[i - 1][j - 1] + 1;
            }
        }
    }
    int i = a.length();
    int j = b.length();
    while (i != 0 && j != 0) {
        if (a[i - 1] == b[j - 1]) {
            result += a[i - 1];
            i -= 1;
            j -= 1;
        } else {
            if (dyn[i - 1][j] < dyn[i][j - 1]) {
                j -= 1;
            } else {
                i -= 1;
            }
        }
    }

    result = reverse(result);


//    cout << "LCS LEN " << dyn[a.length()][b.length()] << endl;
//    cout << result << endl;
    return result;
}

string replace(string b, string common) {
    string replaced = "";
    int j = 0;

    for (int i = 0; i < b.length(); i++) {
        if (j < common.length() && b[i] == common[j]) {
            replaced += '$';
            j++;
        } else {
            replaced += b[i];
        }
    }
    return replaced;
}

void solve(string a, string b) {
    string common = lcs(a, b);
    string repla = replace(a, common);
    string replb = replace(b, common);

    int i = 0;
    int j = 0;
    int k = 0;
    string str = "";
    while (i < repla.length() && j < replb.length() && k < common.length()) {
        if (repla[i] == '$' && replb[j] == '$') {
            str += common[k];
            k++;
            i++;
            j++;
        } else {
            if (repla[i] != '$') {
                str += repla[i];
                i++;
            }

            if (replb[j] != '$') {
                str += replb[j];
                j++;
            }
        }
    }

    while (i < repla.length()) {
        if (repla[i] == '$') {
            if (k < common.size()) {
                str += common[k];
                k++;
            }
        } else {
            str += repla[i];
        }
        i++;
    }

    while (j < replb.length()) {
        if (replb[j] == '$') {
            if (k < common.size()) {
                str += common[k];
                k++;
            }
        } else {
            str += replb[j];
        }
        j++;
    }

    cout << str << endl;
}

int main() {
    string a, b;

//    solve("banana", "ananas");

    while (cin >> a && cin >> b) {
        solve(a, b);
    }

    return 0;

}