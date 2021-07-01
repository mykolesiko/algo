#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int WEIGHT_MAX = 1e5;
const long long WEIGHT_MAXMAX = 1e9;
vector<vector<long long>> dist;
vector<vector<int>> next_el;
vector<vector<bool>> not_connected;
vector<vector<bool>> first;
const int WEIGTH_MIN = -10000;
const int NMAX = 100;
const long long  INF = NMAX * NMAX * WEIGTH_MIN;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        dist.push_back(vector<long long>());
        next_el.push_back(vector<int>());
        not_connected.push_back(vector<bool>());
        first.push_back(vector<bool>());
        for (int j = 0; j < N; j++)  {
            long long temp;
            cin >> temp;
            if (temp == WEIGHT_MAX) {
                temp = WEIGHT_MAXMAX;
                not_connected[i].push_back(true);
            } else {
                not_connected[i].push_back(false);
            }
            first[i].push_back(true);
            dist[i].push_back(temp);
            next_el[i].push_back(j);
        }
    }

    for (int k = 0; k < N; k++) {
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                if ((not_connected[u][k]) || (not_connected[k][v])) continue;
                not_connected[u][v] = false;
                if (first[u][v] && not_connected[u][v]) {
                    first[u][v] = false;
                    dist[u][v] = max(INF, dist[u][k] + dist[k][v]);
                    next_el[u][v] = next_el[u][k];

                    continue;
                }
                if (dist[u][v] > (dist[u][k] + dist[k][v])) {
                    dist[u][v] = max(INF, dist[u][k] + dist[k][v]);
                    next_el[u][v] = next_el[u][k];
                }
            }
        }
    }

    //string cycle = "";
    map<int, int> cycle_map;
    vector<int> cycle;
    for (int k = 0; k < N; k++) {
        if (dist[k][k] < 0) {
            int index = 0;
            cout <<  "YES" << "\n";
            cycle.push_back(k);
            cycle_map[k] = 0;
            int cur = next_el[k][k];
            while (true) {
                if (cycle_map.find(cur) != cycle_map.end()) {
                    cycle.push_back(cur);
                    index = cycle_map[cur];
                    break;
                }
                cycle.push_back(cur);
                cycle_map[cur] = cycle.size() - 1;
                cur = next_el[cur][k];
            }

            cout << cycle.size() - index - 1 << "\n";
            for (int i = index + 1; i < cycle.size(); i++) {
                cout << cycle[i] + 1 << " ";
            }

            return(0);
        }

    }
    cout <<  "NO" << "\n";

    return 0;
}
