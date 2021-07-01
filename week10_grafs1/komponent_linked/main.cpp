#include <iostream>
#include <vector>

using namespace std;
const int MAX_N = 100000;
int used[MAX_N];

bool dfs(int i, vector<vector<int>>& graf, int linked_part_) {
    used[i] = linked_part_;
    for (int k=0; k < graf[i].size(); k++)
    {
        if  (!used[graf[i][k]])
        {
           dfs(graf[i][k], graf,linked_part_);
        }

    }
    return(true);
}

int main()
{
    int n,m;
    cin >> n;
    cin >> m;
    int b, e;
    vector<vector<int>> graf(n);
    for (int i = 0; i < m; i++)
    {
        cin >> b >> e;
        graf[b - 1].push_back(e - 1);
        graf[e - 1].push_back(b - 1);
    }

    fill(used, used + MAX_N, 0);

    int n_linked_part = 1;
    for (int i = 0; i < n; i++)
    {
        if (!used[i]) {
            dfs(i, graf, n_linked_part);
            n_linked_part++;
        }
    }
    cout << n_linked_part - 1 << "\n";
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            cout << used[i] << " ";
        } else {
            cout << used[i] << "\n";
        }
    }
    return 0;
}
