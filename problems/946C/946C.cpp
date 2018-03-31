#include<iostream>
#include<string>

using namespace std;
const string target = "abcdefghijklmnopqrstuvwxyz";

int main() {
    string in;
    cin >> in;
    string output = "";
    bool complete = false;
    if (in.size() >= target.size()) {
        int target_index = 0;
        for (int i = 0; i < in.size(); i++) {

            if (in[i] <= target[target_index] && complete != true) {
                output += target[target_index];
                target_index++;
            } else {
                output += in[i];
            }
            if (target_index == target.size()) {
                complete = true;
            }
        }
        if (complete) {
            cout << output << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}