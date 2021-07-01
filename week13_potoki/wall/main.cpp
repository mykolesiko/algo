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
    const int INF1 = 1e9;
    vector<vector<edge_t>> edges;
    vector<pair<int, int>> path;
    //vector<pair<int, int>> edges_in_input;
    char* pole;
    vector<int> parts;
    vector<pair<int, int>> edges_list;


    int max_c;
    const char MOUNTAIN = '#';
    const char NO_BUILD = '-';
    const char BUILD = '.';
    const int NOT_EXISTS = -1;

    void dfs(int v) {
        parts[v] = 1;

        for (auto& el : edges[v]) {
            if ((!parts[el.to]) && (el.f < el.c)) {
                dfs(el.to);

            }
        }
        return;
    }

    int flow;


    int get_maxflow() {
        vector<int> used;
        used.resize(n * m * 2, 0);
        path.resize(n * m * 2, make_pair(0, 0));
        int result = 0;
        //int scale = int(log2(max_c));
        //if (scale < 1) scale = 1;
        while (true) {

            fill(used.begin(), used.end(), 0);
            fill(path.begin(), path.end(), make_pair(0, 0));

            bool found = pushFlow(begin, end, used);
            cerr << "found = " << found << '\n';
            if (found) {
              int v = end;
              int delta = INF1;
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
              if (delta == INF) {
                return(-1);
              } else {
                result += delta;
              }
            } else {
              break;

           }
        }
        maxflow = result;

        parts.resize(n * m * 2, 0);
        fill(parts.begin(), parts.end(), 0);
        dfs(begin);
        // cerr << "result = " << result << '\n';
        flow = result;
        if (result >= INF) {
            return -1;
        }
        return result;

    }

    vector<pair<int, int>> E;

    void print_cut() {
        for (int i = 0; i < n * m; ++i) {
            if (parts[2 * i] != parts[2 * i + 1]) {
                pole[i] = '+';
            }
        }
        cout << flow << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << pole[i * m + j];
            }
            cout << '\n';
        }
    }

/*    void print_result() {
        cout <<  maxflow << "\n";
        for (auto el : edges_in_input) {
            edge_t edge = edges[el.first][el.second];
            cout << edge.f << "\n";
        }
    }*/


    bool pushFlow(int v, int t, vector<int> &used) {
        queue<int> q_bfs;
        q_bfs.push(begin);
        used[begin] = 1;
        while (q_bfs.size() != 0) {
            int from = q_bfs.front();
            q_bfs.pop();
            for (int i = 0; i < edges[from].size(); i++) {
                edge_t edge = edges[from][i];
                if ((!used[edge.to]) && (edge.f < edge.c)) {
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
    void get_nearest(int i, int* nearest) {
        nearest[0] = (((i + 1) % n) > i) ? (i + 1) : -1;
        nearest[1] = (((i - 1) % n < i) &&  (i >= 1)) ? i - 1 : -1;
        nearest[2] = ((i + n) < m * n) ? i + n : -1;
        nearest[3] = ((i - n) >= 0 ) ? i - n : -1;

    }

 /*   inline static const vector<pair<int, int>> go = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    int restore(int r, int c) {
        return r * m + c;
    }

    int ok(int r, int c) {
        return (r >= 0 && r < n && c >= 0 && c < m);
    }

    void get_nearest(int i, int *nearest) {
        int r = i / m;
        int c = i % m;
        int pos = 0;
        for (auto [dr, dc] : go) {
            if (ok(r + dr, c + dc)) {
                nearest[pos++] = restore(r + dr, c + dc);
            } else {
                nearest[pos++] = -1;
            }
        }
    }*/

    pair<int, int> add_edge(int from, int to, int c) {
        // cerr << "add_edge " << from << " " << to << " " << c << '\n';
        struct edge_t edge1, edge2;
        edge1.from = edge2.to = from;
        edge1.to = edge2.from = to;
        edge2.c = 0;
        edge1.c = c;

        edge1.ind = edges[edge1.to].size();
        edge2.ind = edges[edge1.from].size();
        edges[edge1.from].push_back(edge1);
        edges[edge2.from].push_back(edge2);
        edges_list.push_back(make_pair(edge1.from, edge2.ind));
        return {edge1.from, edge2.ind};
        // cerr << "done" << endl;
        // edges_in_input.push_back(make_pair(edge1.from, edges[edge1.from].size() - 1));
    }


    void process_pair (int i, int j) {
        if ((i == NOT_EXISTS) || (j ==NOT_EXISTS)) return;
        if ((pole[i] == MOUNTAIN) || (pole[j] == MOUNTAIN)) return;
        add_edge(2 * i + 1, 2 * j, INF);
        return;
    }


    void process_cell (int i) {
        if (pole[i] == MOUNTAIN) {
            E.emplace_back(-1, -1);
            return;
        }
        pair<int, int> toE;
        if (pole[i] != BUILD)  {
            toE = add_edge(2 * i, 2 * i + 1, INF);
        } else {
            toE = add_edge(2 * i, 2 * i + 1, 1);
        }
        cerr << "cell " << i << " " << edges[toE.first][toE.second].c << '\n';
        E.push_back(toE);
        return;
    }


    void init() {
        cin >> n >> m;
        edges.resize(2 * n * m, vector<edge_t>());
        //max_c = -INF;

        int s = 0;
        string str;
        char* str1 = new char[n + m];
        pole = new char[n * m];
        for (int i = 0; i < n; i++) {
            cin >> str1;
            str = str1;
            for (int j = 0; j < m; j++) {
                pole[s] = str[j];

                s++;
            }
        }

        for (int i = 0; i < m * n; i++) {
            if (pole[i] == 'A') {
                begin = 2 * i;
            }
            if (pole[i] == 'B') {
                end = 2 * i + 1;
            }
            int* nearest = new int[4];
            get_nearest(i, nearest);
            for (int j = 0; j < 4; j++) {
                process_pair(i, nearest[j]);
            }
            process_cell(i);

       }
       cerr << "begin = " << begin << '\n';
       cerr << "end = " << end << '\n';
    }
};

int main()
{
    int n, m;
    Graf graf;
    graf.init();
    int maxflow = graf.get_maxflow();
    if (maxflow == -1) {
        cout << "-1\n";
    } else {
       graf.print_cut();
    }
    return 0;
}
