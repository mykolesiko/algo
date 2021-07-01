#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>

using namespace std;

struct edge_t{
    edge_t(): from(0), to(0), c(0), f(0), ind(0) {}
    int from;
    int to;
    int c;
    int f;
    int ind;
    //bool pr_input;

};

class Graf {
  public:
    int n;
    int m;
    int begin;
    int end;
    int maxflow = 0.0;
    const int INF = 1e9;
    vector<vector<edge_t>> edges;
    vector<pair<int, int>> path;
    vector<pair<int, int>> edges_in_input;
    int max_c;



    int get_maxflow() {
        vector<int> used;
        used.resize(n, 0);
        path.resize(n, make_pair(0, 0));
        int result = 0;
        int scale = int(log2(max_c));
        if (scale < 1) scale = 1;
        while (scale >= 1) {

            fill(used.begin(), used.end(), 0);
            fill(path.begin(), path.end(), make_pair(0, 0));

            bool found = pushFlow(0, n - 1, used, scale);
            if (found) {
              int v = end;
              int delta = INF;
              while (v != begin) {
                  pair<int, int> parent = path[v];
                  v = parent.first;
                  edge_t* pedge = &edges[parent.first][parent.second];
                  delta = min(delta, pedge->c - pedge->f);
              }
              v = end;
              while (v != begin) {
                  pair<int, int> parent = path[v];
                  v = parent.first;
                  edge_t* pedge = &edges[parent.first][parent.second];
                  pedge->f += delta;
                  edges[pedge->to][pedge->ind].f -= delta;
              }
              if (delta > 0) {
                result += delta;
              }
            } else {
              if (scale == 1) {
                break;
              } else {
                scale  = int(float(scale)/2);
                if (scale < 1) scale = 1;
              }

           }
        }
        maxflow = result;
        return result;

    }

    void print_result() {
        cout <<  maxflow << "\n";
        for (auto el : edges_in_input) {
            edge_t edge = edges[el.first][el.second];
            cout << edge.f << "\n";
        }
    }


    bool pushFlow(int v, int t, vector<int> &used, int scale) {
        queue<int> q_bfs;
        q_bfs.push(begin);
        used[begin] = 1;
        while (q_bfs.size() != 0) {
            int from = q_bfs.front();
            q_bfs.pop();
            for (int i = 0; i < edges[from].size(); i++) {
                edge_t edge = edges[from][i];
                if ((!used[edge.to]) && (edge.f <= edge.c - scale)) {
                    q_bfs.push(edge.to);
                    used[edge.to] = 1;
                    path[edge.to] = make_pair(from, i);
                    if (edge.to == t) {
                        return (true);
                    }
                }
            }
        }
        return (false);
    }


    void init() {
        cin >> n;
        cin >> m;
        edges.resize(n, vector<edge_t>());
        max_c = -INF;

        for (int i = 0; i < m; i++) {
            struct edge_t edge1, edge2;
            begin = 0;
            end = n - 1;
            int from, to;
            int c;
            cin >> from >> to>> c;
            edge1.from = edge2.to = from - 1;
            edge1.to = edge2.from = to - 1;
            edge2.c = edge1.c = c;
            if (max_c < c) {
                max_c = c;
            }


            edge1.ind = edges[edge1.to].size();
            edge2.ind = edges[edge1.from].size();
            edges[edge1.from].push_back(edge1);
            edges[edge2.from].push_back(edge2);
            edges_in_input.push_back(make_pair(edge1.from, edges[edge1.from].size() - 1));
          }
    }
};

int main()
{
    int n, m;
    Graf graf;
    graf.init();
    int maxflow = graf.get_maxflow();
    graf.print_result();
    return 0;
}






