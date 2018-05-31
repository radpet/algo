#include<iostream>
#include<vector>

using namespace std;

int majorityElement(vector<int> &nums) {

    int count = 0;
    int current_el;

    for (int i : nums) {
        if (count == 0) {
            current_el = i;
        }

        if (current_el == i) {
            count += 1;
        } else {
            count -= 1;
        }
    }

    return current_el;
}

int main() {
    vector<int> a = {2, 2, 1, 1, 1, 2, 2};
    cout << majorityElement(a) << endl;
}