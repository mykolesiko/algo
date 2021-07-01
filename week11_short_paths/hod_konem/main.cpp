#include <iostream>
#include <queue>

using namespace std;
queue<pair<int,int>> q_bfs;
vector<vector<bool>> used;
vector<vector<int>> dist;
vector<vector<pair<int, int>>> path;
int N;



vector<pair<int,int>> hod = {{2, 1}, {1, 2}, {2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {-2, -1}, {-1, -2}};
bool check_place(int x, int y) {
    return ((x <= N) && (y <= N) && (x >= 1) && (y >= 1));
}

void bfs(int x2, int y2) {

    while (q_bfs.size() != 0) {
        pair<int, int> from = q_bfs.front();
        q_bfs.pop();
        for (int i = 0; i < hod.size(); i++) {
            pair<int, int> to = make_pair(from.first + hod[i].first, from.second + hod[i].second);

            if (check_place(to.first, to.second)) {
                 if (!used[to.first][to.second]) {
                     q_bfs.push(to);
                     used[to.first][to.second] = true;
                     dist[to.first][to.second] = dist[from.first][from.second] + 1;
                     path[to.first][to.second] = from;
                     if  ((x2 == to.first) && (y2 == to.second)) {
                         return;
                     }
                 }
            }

        }
    }
}

int main()
{
    int x1, y1, x2, y2;
    cin >> N;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    used.resize(N + 1, vector<bool>(N + 1, false));
    dist.resize(N + 1, vector<int>(N + 1, 0));
    path.resize(N + 1, vector<pair<int, int>>(N + 1, pair<int, int>()));
    q_bfs.push(make_pair(x1, y1));
    used[x1][x2] = true;

    if ((x1 == x2) && (y1 == y2)) {
        cout << 1 << "\n";
        cout << x1 << y1 << "\n";
        return(0);
    }
    bfs(x2, y2);
    cout << dist[x2][y2] + 1 << "\n";
    pair<int, int> cur = make_pair(x2, y2);
    vector<pair<int, int>> result;
    for (int i = 0; i < dist[x2][y2] + 1; i++) {
         //cout << cur.first << " " << cur.second << "\n";
         result.push_back(cur);
         cur = path[cur.first][cur.second];
    }
    for (int i = dist[x2][y2]; i >= 0; i--) {
         cout << result[i].first << " " << result[i].second << "\n";
    }
}
