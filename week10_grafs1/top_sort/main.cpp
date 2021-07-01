#include <iostream>
#include <vector>

using namespace std;
vector<int> topsort, used;
vector<int> vertex_order;
vector<vector<int>> graf;

void dfs(int i) {
  used[i] = 1;
  for (auto k : graf[i]) {
    if (used[k] == 0) {
      dfs(k);
    }
  }
  topsort.push_back(i);
  vertex_order[i] = topsort.size() - 1;
}

int main()
{
    int n,m;
    cin >> n;
    cin >> m;
    int b, e;
    graf.assign(n, vector<int>());
    for (int i = 0; i < m; i++)
    {
        cin >> b >> e;
        if (b == e) {
            cout << "-1\n";
            return (0);
        }
        graf[b - 1].push_back(e - 1);
        //graf[e - 1].push_back(b - 1);
    }
    used.assign(n, 0);
    vertex_order.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      if (used[i] == 0) {
        dfs(i);
      }
    }
    reverse(topsort.begin(), topsort.end());
    bool could_top_sort = true;
    for (int i = 0; i < n; ++i) {
        for (auto k : graf[i]) {
            if (vertex_order[i] < vertex_order[k]) {
                could_top_sort  = false;
                break;
            }
        }
    }
    if (!could_top_sort) {
        cout << "-1\n";
    } else {
      for (int i = 0; i < topsort.size(); i++) {
          if (i == topsort.size() - 1) {
            cout << topsort[i] + 1 << "\n";
          } else {
            cout << topsort[i] + 1 << " ";
          }
      }
    }
}
