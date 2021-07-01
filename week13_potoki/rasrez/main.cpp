#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct edge_t{
    edge_t(): from(0), to(0), c(0), f(0), ind(0) {}
    int from;
    int to;
    long long c;
    long long f;
    int ind;

};

class Graf {
  public:
    int n;
    int m;
    int begin;
    int end;
    const long long INF = 10e9;

    vector<vector<edge_t>> edges;
    vector<int> parts;
    vector<pair<int, int>> edges_list;


    void dfs(int v) {
        parts[v] = 1;

        for (auto& el : edges[v]) {
            if ((!parts[el.to]) && (el.f < el.c)) {
                dfs(el.to);

            }
        }
        return;
    }


    long long get_maxflow() {
        vector<int> used;
        used.resize(n);

        int result = 0;
        while (true) {
            fill(used.begin(), used.end(), 0);
            long long delta = pushFlow(begin, end, INF,  used);
            if (delta > 0) {
              result += delta;

            } else {
              break;
            }
        }

        parts.resize(n, 0);
        fill(parts.begin(), parts.end(), 0);
        dfs(begin);
        return result;

    }
    void print_cut() {
        int nedges = 0;
        long long sum = 0;
        string edges_nums ="";
        for (int i = 0; i < edges_list.size(); i++) {
            auto el = edges_list[i];
            auto edge = edges[el.first][el.second];
            //if ((parts[edge.from] == 1) && (parts[edge.to] == 0)) {
            if (parts[edge.from]  != parts[edge.to]) {
                nedges++;
                sum += edge.c;
                char str[20];
                itoa(i + 1, str, 10);
                edges_nums += str;
                edges_nums += " ";
            }
        }
        cout << nedges << " " << sum << "\n";
        cout << edges_nums.c_str();

    }

    long long pushFlow(int v, int t, long long curFlow, vector<int> &used) {
        used[v] = 1;
        if (v == t) {
            return curFlow;
            //path.push_back(v);
        }

        for (auto& el: edges[v]) {
            if ((!used[el.to]) && (el.f < el.c)) {
               long long nextFlow = min(curFlow, el.c - el.f);
               long long delta = pushFlow(el.to, t, nextFlow, used);
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
        cin >> n >> m;
        begin = 0;
        end = n - 1;
        edges.resize(n, vector<edge_t>());
        for (int i = 0; i < m; i++) {
            struct edge_t edge1, edge2;
            int from, to;
            long long c;
            cin >> from >> to >> c;
            edge1.from = edge2.to = from - 1;
            edge1.to = edge2.from = to - 1;
            edge1.c = c;
            edge2.c = c;

            edge1.ind = edges[edge1.to].size();
            edge2.ind = edges[edge1.from].size();
            edges[edge1.from].push_back(edge1);
            edges[edge2.from].push_back(edge2);
            edges_list.push_back(make_pair(edge1.from, edge2.ind));
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
    long long maxflow = graf.get_maxflow();
    graf.print_cut();
    return 0;
}





