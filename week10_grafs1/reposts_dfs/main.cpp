#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;
const int MAX_N = 200;
const int MAX_NAME_LEN = 30;
map<string, int> used;
map<string, vector<string>> graf;
int depth_max = 0;
const string first = "polycarp";


bool dfs(string name, int depth) {
    used[name] = 1;
    if (depth > depth_max) depth_max = depth;
    depth++;
    for (int k=0; k < graf[name].size(); k++)
    {
        string name_next = graf[name][k];
        if  (!used[name_next])
        {

           dfs(name_next, depth);
        }

    }
    return(true);
}

int main()
{
    int n,m;
    cin >> m;
    char name1[MAX_NAME_LEN], name2[MAX_NAME_LEN];
    for (int i = 0; i < m; i++)
    {
        char temp[MAX_NAME_LEN];
        cin >> name1 >> temp >> name2;
        string name1_str = string(name1);
        string name2_str = string(name2);

        transform(name1_str.begin(), name1_str.end(), name1_str.begin(), ::tolower);
        transform(name2_str.begin(), name2_str.end(), name2_str.begin(), ::tolower);
        graf[name2_str].push_back(name1_str);
        if (graf.find(name1_str) == graf.end())  {
            graf[name1_str] = vector<string>();
        }
        used[name2_str] = 0;
        used[name1_str] = 0;
    }
    int depth = 1;
    dfs(first, depth);
    cout << depth_max << "\n";


    return 0;
}
