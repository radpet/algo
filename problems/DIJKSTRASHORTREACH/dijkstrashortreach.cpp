#include<iostream>
#include<utility>
#include<vector>
#include<map>
#include<queue>
#include <functional>

using namespace std;


int cmp(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
}

struct triple {
    int first, second, third;

    triple(int _first, int _second, int _third) {
        first = _first;
        second = _second;
        third = _third;
    }

    triple(const triple &other) {
        first = other.first;
        second = other.second;
        third = other.third;
    }

    triple &operator=(const triple &other) {
        first = other.first;
        second = other.second;
        third = other.third;
    }

};

triple make_triple(int _first, int _second, int _third) {
    return triple(_first, _second, _third);
}


vector<int> solve(vector<vector<triple>> *G, int start) {
//    vector<int> minDistances;
//    minDistances.resize(G.size());
//    for (int i = 0; i < minDistances.size(); i++) {
//        minDistances[i] = 100005;
//    }
//
//    priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(pair<int, int>, pair<int, int>)> > Q(cmp);
//
//    Q.push(make_pair(start, 0));
//    const int n = 30000;
//    bool used[n][n][n];
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            for (int p = 0; p < n; p++) {
//                used[i][j][p] = false;
//            }
//        }
//    }
//
//    while (!Q.empty()) {
//        pair<int, int> current = Q.top();
//        Q.pop();
//
//        minDistances[current.first] = min(minDistances[current.first], current.second);
//
//        for (triple neigh: G[current.first]) {
//            if (!used[current.first][neigh.first][neigh.third]) {
//                used[current.first][neigh.first][neigh.third] = true;
//                used[neigh.first][current.first][neigh.third] = true;
//                Q.push(make_pair(neigh.first, current.second + neigh.second));
//            }
//        }
//    }
//
//    return minDistances;
}


int main() {
    int t;

    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<triple>> G(n);
//        G.clear();
//        G.resize(n);
        map<pair<int, int>, int> duplicates;
//
        for (int i = 0; i < m; i++) {
            int x, y, r;
            cin >> x >> y >> r;
            --x;
            --y;
//            if (duplicates.count(make_pair(x, y)) == 0) {
//                duplicates[make_pair(x, y)] = 1;
//            } else {
//                duplicates[make_pair(x, y)]++;
//            }
            G[x].push_back(make_triple(y, r, duplicates[make_pair(x, y)]));
            G[y].push_back(make_triple(x, r, duplicates[make_pair(x, y)]));
        }
        int start;
        cin >> start;
        --start;
        vector<int> minDist = solve(&G, start);
//        for (int i = 0; i < minDist.size(); i++) {
//            if (i != start) {
//                cout << minDist[i] << " ";
//            }
//        }
        cout << endl;
    }

}
