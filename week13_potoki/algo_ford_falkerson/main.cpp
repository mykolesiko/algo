#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge_t{
    edge_t(): from(0), to(0), c(0), f(0), ind(0) {}
    int from;
    int to;
    int c;
    int f;
    int ind;

};

class Graf {
  public:
    int n;
    int m;
    const int INF = 1e9;
    vector<vector<edge_t>> edges;
    int get_maxflow() {
        vector<int> used;
        used.resize(n);

        int result = 0;
        while (true) {
            fill(used.begin(), used.end(), 0);
            int delta = pushFlow(0, n - 1, INF,  used);
            if (delta > 0) {
              result += delta;
            } else {
              break;
            }
        }
        return result;

    }

    int pushFlow(int v, int t, int curFlow, vector<int> &used) {
        used[v] = 1;
        if (v == t) {
            return curFlow;
            //path.push_back(v);
        }

        for (auto& el: edges[v]) {
            if ((!used[el.to]) && (el.f < el.c)) {
               int nextFlow = min(curFlow, el.c - el.f);
               int delta = pushFlow(el.to, t, nextFlow, used);
               if (delta > 0) {
                   el.f += delta;
                   int ind = el.ind;
                   edges[el.to][ind].f -= delta;
                   return(delta);
               }
            }
        }
        return(0);
    }
    void init() {
        cin >> n;
        cin >> m;
        edges.resize(n, vector<edge_t>());
        for (int i = 0; i < m; i++) {
            struct edge_t edge1, edge2;
            int from, to, c;
            cin >> from >> to>> c;
            edge1.from = edge2.to = from - 1;
            edge1.to = edge2.from = to - 1;
            edge2.c = edge1.c = c;

            edge1.ind = edges[edge1.to].size();
            edge2.ind = edges[edge1.from].size();
            edges[edge1.from].push_back(edge1);
            edges[edge2.from].push_back(edge2);
          }
    }
};

int main()
{
    int n, m;
    Graf graf;
    graf.init();
    int maxflow = graf.get_maxflow();
    cout << maxflow << "\n";
    return 0;
}





