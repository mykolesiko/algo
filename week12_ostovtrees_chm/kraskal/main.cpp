#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
vector<struct info_t> cnm;

struct info_t {
    int rang;
    int pred;
};

int get(int i) {
    if (cnm[i].pred != i) {
        cnm[i].pred = get(cnm[i].pred);
    }
    return (cnm[i].pred);
}


void join (int i, int j) {
    i = get(i);
    j = get(j);
    if (i == j) {
       return;
    }
    info_t* x = &cnm[i];
    info_t* y = &cnm[j];
    if  (x->rang > y->rang) {
        swap(x, y);
        swap(i, j);
    }  //x - маленькое дерево y - большое
    if (x->rang == y->rang) {
        y->rang++;
    }
    x->pred = j;
}

/*(struct edge_t{
    int b;
    int e;
};*/


int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; i++) {
        //struct edge_t edge;
        int b, e, w;
        cin >> b >> e >> w;
        //edge.b = b - 1;
        //edge.e = e - 1;
        edges.push_back(make_pair(w, make_pair(b - 1, e - 1)));
    }
    sort(edges.begin(), edges.end());

    long long  result = 0;
    struct info_t info;
    cnm.resize(n, info);
    for (int i = 0; i < n; i++) {
        cnm[i].pred = i;
        cnm[i].rang = 1;
    }
    for (auto el : edges) {
        //cout << el.first << endl;
        if (get(el.second.first) != get(el.second.second)) {
            result += el.first;
            join(el.second.first, el.second.second);
        }
    }
    cout << result << "\n";
    return 0;
}
