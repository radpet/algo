#include<iostream>
#include<vector>

using namespace std;

vector<int> pos[26];

int main() {

    string s;

    cin >> s;

    for (int i = 0; i < 26; i++) {
        pos[i].push_back(0);
    }

    for (int i = 0; i < s.size(); i++) {
        pos[s[i] - 'a'].push_back(i + 1);
    }

    int ans = 1e10;
    for (int i = 0; i < 26; i++) {
        int curForI = 0;
        pos[i].push_back(s.size() + 1);

        for (int j = 1; j < pos[i].size(); j++) {
            curForI = max(curForI, pos[i][j] - pos[i][j - 1]);
        }
        ans = min(ans, curForI);
    }

    cout << ans << endl;
    return 0;
}