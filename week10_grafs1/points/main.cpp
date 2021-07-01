#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
const int MAX_N = 20100;
int used[MAX_N];

int timer, t[MAX_N], up[MAX_N];
set<int> points;
vector<set<int>> graf;

void dfs (int v, int p = -1) {
    int n_childs = 0;
    used[v] = true;
    t[v] = up[v] = timer++;
    for (auto to : graf[v]) {
        //int to = graf[v][i];
        if (to == p)  continue; //предок
        if (used[to]) //здесь уже были и время там посчитано
            up[v] = min (up[v], t[to]);
        else {
            dfs (to, v);
            up[v] = min (up[v], up[to]);
            if ((up[to] >= t[v]) && (p != -1)) {
                points.insert(v);
            }
            ++n_childs;
        }
    }
    if ((p == -1) && (n_childs > 1)) {
        points.insert(v);
    }
}

int main()
{
    int n,m;
    cin >> n;
    cin >> m;
    int b, e;
    graf.assign(n, set<int>());
    for (int i = 0; i < m; i++)
    {
        cin >> b >> e;
        if (b == e) continue;
        graf[b - 1].insert(e - 1);
        graf[e - 1].insert(b - 1);
    }

    fill(used, used + MAX_N, 0);
    timer = 0;
    for (int i = 0; i < n; i++)
    {
        if (!used[i]) {
            dfs(i);
        }
    }
    cout << points.size() << "\n";
    for (auto p : points) {
        cout << p + 1<< " ";
    }
    return (0);
}
