#include<iostream>
#include<queue>

using namespace std;
const int MAXN = 2024;
bool used[MAXN][MAXN];


struct Coord {
    int x, y;

    Coord(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    queue<Coord> Q;

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x = x - 1;
        y = y - 1;
        used[x][y] = true;
        Q.push(Coord(x, y));
    }

    Coord current(0, 0);
    while (!Q.empty()) {
        current = Q.front();
        Q.pop();

        if (current.x - 1 > 0) {
            int posX = current.x - 1;
            if (!used[posX][current.y]) {
                used[posX][current.y] = true;
                Q.push(Coord(posX, current.y));
            }
        }

        if (current.x + 1 < n) {
            int posX = current.x + 1;
            if (!used[posX][current.y]) {
                used[posX][current.y] = true;
                Q.push(Coord(posX, current.y));
            }
        }

        if (current.y - 1 > 0) {
            int posY = current.y - 1;
            if (!used[current.x][posY]) {
                used[current.x][posY] = true;
                Q.push(Coord(current.x, posY));
            }
        }

        if (current.y + 1 < m) {
            int posY = current.y + 1;
            if (!used[current.x][posY]) {
                used[current.x][posY] = true;
                Q.push(Coord(current.x, posY));
            }
        }

    }

    cout << current.x + 1 << " " << current.y + 1 << endl;

}