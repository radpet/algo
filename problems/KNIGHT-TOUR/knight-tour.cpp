#include<iostream>
#include<vector>

using namespace std;

struct Pos {
    int x;
    int y;

    Pos(int _x, int _y) {
        x = _x;
        y = _y;
    }

    bool operator==(const Pos &other) {
        return x == other.x && y == other.y;
    }

    Pos operator+(const Pos &other) const {
        return Pos(x + other.x, y + other.y);
    }
};

class KnightTourSolver {
private:
    static const int N = 8;
    bool used[N][N];

    bool inside(Pos pos) {
        return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
    }


public:
    KnightTourSolver() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                used[i][j] = false;
            }
        }
    }


    bool dfs(Pos start, Pos end) {
        if (!inside(start) ||
            !inside(end) ||
            used[start.x][start.y]) {
            return false;
        }

        if (start == end) {
            return true;
        }

        used[start.x][start.y] = true;

        for (Pos move : {Pos(2, 1),
                         Pos(1, 2),
                         Pos(-1, 2),
                         Pos(-2, 1),
                         Pos(-2, -1),
                         Pos(-1, -2),
                         Pos(1, -2),
                         Pos(2, -1)
        }

                ) {
            Pos newPos = start + move;
            if (dfs(newPos, end)) {
                return true;
            }
        }

        used[start.x][start.y] = false;
        return false;


    }

};

int main() {

    KnightTourSolver solver;

    cout << solver.dfs({7, 0}, {0, 7});

}