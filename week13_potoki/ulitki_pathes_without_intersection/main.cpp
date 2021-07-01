#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int npaths = 2;

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
    int begin;
    int end;
    const int INF = 1e9;

    vector<vector<edge_t>> edges;
    vector<vector<int>> paths;


    bool dfs(int cur, int v, int t, vector<int>& used) {
        used[v] = 1;
        if (v == t) {
            paths[cur].push_back(t);
            return (true);
        }
        bool found = false;
        for (auto& el : edges[v]) {
            if ((el.f == 1) && !used[el.to]) {
                bool res = dfs(cur, el.to, t, used);
                if (!res) return(res);
                el.f = 0;
                //paths[cur].push_back(el.to);
                found = true;
                break;
            }
        }
        if (found) {
           paths[cur].push_back(v);
           return(true);
        }
        return false;
    }


    void find_paths() {
        //vector<int> used;
        //used.resize(n, 0);
        int cur = 0;
        while (cur < npaths) {
          vector<int> used;
          used.resize(n, 0);
          if (dfs(cur, begin, end, used)) {
            reverse(paths[cur].begin(), paths[cur].end());
            cur++;
          }
        }


    }
    int get_maxflow() {
        vector<int> used;
        used.resize(n);

        int result = 0;
        while (true) {
            fill(used.begin(), used.end(), 0);
            int delta = pushFlow(begin, end, INF,  used);
            if (delta > 0) {
              result += delta;
              if (result >= npaths) {
                  find_paths();
                  break;
              }
            } else {
              break;
            }
        }
        return result;

    }
    void print_paths() {
        for (int i = 0; i < npaths; i++) {
            for (auto el: paths[i]) {
                cout << el + 1<< " ";
            }
            cout << "\n";

        }
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
        cin >> n >> m >> begin >> end;
        begin--;
        end--;
        edges.resize(n, vector<edge_t>());
        paths.resize(npaths, vector<int>());
        for (int i = 0; i < m; i++) {
            struct edge_t edge1, edge2;
            int from, to, c;
            cin >> from >> to;//>> c;
            edge1.from = edge2.to = from - 1;
            edge1.to = edge2.from = to - 1;
            edge1.c = 1;
            edge2.c = 0;

            edge1.ind = edges[edge1.to].size();
            edge2.ind = edges[edge1.from].size();
            edges[edge1.from].push_back(edge1);
            edges[edge2.from].push_back(edge2);
          }
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    Graf graf;
    graf.init();
    int maxflow = graf.get_maxflow();
    if (maxflow >= npaths) {
      cout << "YES" << "\n";
      graf.print_paths();
    } else {
      cout << "NO" << "\n";
    }
    return 0;
}





