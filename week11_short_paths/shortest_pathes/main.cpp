#include <iostream>
#include <vector>
//#include <queue>
#include<set>
#include <algorithm>


struct edge{
    int begin;
    int end;
    long long w;
};

using namespace std;
vector<struct edge> edges;
vector<long long> dist;
vector<vector<int>> graf;
vector<int> used;

bool dfs(int v) {
    used[v] = true;
    for (auto el : graf[v])
    {
        if  (!used[el])
        {
           dfs(el);
        }
    }
    return(true);
}

const long long INF = 8e18;
using namespace std;

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    graf.resize(n + 1, vector<int>());
    for (int i = 0 ; i < m; i++) {
        edge e;
        cin >> e.begin >> e.end >> e.w;
        edges.push_back(e);
        graf[e.begin].push_back(e.end);

    }
    dist.resize(n + 1, INF);
    used.resize(n + 1, 0);

    dist[s]  = 0;

    for (int i = 0; i <= n ; i++) {

        for (auto el : edges) {
              if (dist[el.begin] < INF) {
                  if ((dist[el.begin] + el.w) < dist[el.end]) {
                      dist[el.end] = max(-INF, dist[el.begin] + el.w);
                      if (i == n)
                      {
                         dfs(el.end);
                      }
                  }
              }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (dist[i] == INF) {
           cout << "*" << "\n";
        } else {

            if (!used[i]) {
               cout << dist[i] << "\n";
            } else {
                cout << "-\n";

            }
        }

    }

    return(0);
}





