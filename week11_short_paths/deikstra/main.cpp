#include <iostream>
#include <vector>
//#include <queue>
#include<set>
#include <algorithm>

using namespace std;
vector<vector<pair<int, int>>> graf;
//priority_queue<pair<int,int>> Q;
set<pair<long long,int>> Q;
vector<int> used;
vector<long long> dist;

const long long INF = 1e11;

void deikstra (int n)
{
    while (!Q.empty()) {
        auto it = Q.begin();
        pair<int,int> from = *it;
        Q.erase(it);
        for (auto to : graf[from.second] )
        {

            long long  w = to.second;
            if ((from.first + w) < dist[to.first])
            {
                Q.erase(make_pair(dist[to.first], to.first));
                dist[to.first] = from.first + w;
                Q.insert(make_pair(dist[to.first], to.first));
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    graf.resize(n, vector<pair<int,int>>());
    used.resize(n, 0);
    for (int i = 0 ; i < m; i++) {
        int i1, j1, w;
        cin >> i1 >> j1 >> w;
        graf[i1 - 1].push_back(make_pair(j1 - 1, w));
        graf[j1 - 1].push_back(make_pair(i1 - 1, w));
    }
    for (int i = 0; i < n; i++)
        dist.push_back(INF);

    dist[0]=0;
    Q.insert(make_pair(0, 0));
    deikstra(n);
    for (int i = 0 ; i < n; i++) {
        cout << dist[i] << " ";
    }
    return 0;
}
