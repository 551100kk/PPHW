#include <bits/stdc++.h>
using namespace std;

const char* filename = "in1.txt";
const int maxbuf = 100;


int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

vector<vector<int>> update(vector<vector<int>> &in) {
    int n = in.size();
    int m = in[0].size();
    vector<vector<int>> out(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            for (int d = 0; d < 8; d++) {
                int x = i + dx[d];
                int y = j + dy[d];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                cnt += in[x][y]
            }
        }
    }

}

int main() {
    FILE *file = fopen(filename, "r");
    char buf[maxbuf] = {};
    vector<vector<int>> board;
    while (fscanf(file, "%s", buf) != EOF) {
        vector<int> tmp;
        for (int i = 0; buf[i]; i++) {
            tmp.push_back(buf[i] == '*');
        }
        board.push_back(move(tmp));
    }

    int n = board.size();
    int m = board[0].size();
    printf("(%d, %d)\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", board[i][j] ? '.': ' ');
        }
        puts("");
    }

    fclose(file);
}
