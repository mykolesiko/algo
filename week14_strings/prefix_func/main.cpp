#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<int> pfunction (string str) {
    int str_len = str.length();
    vector<int> p(str_len);
    for (int i = 1; i < str_len; ++i) {
        int j = p[i - 1];
        while ((j > 0) && (str[i] != str[j])) {
            j = p[j - 1];
        }
        if (str[i] == str[j]){
            ++j;
        }
        p[i] = j;
    }
    return p;
}


int main()
{
    string p, t;
    cin >> p >> t;
    string str = p + '#' + t;
    vector<int> pfunc = pfunction(str);
    int tsize = t.length();
    int psize = p.length();
    vector<int> result;
    for (int i = psize + 1; i < psize + tsize + 1; i++) {
       if (pfunc[i] == psize) {
           result.push_back(i - 2 * psize + 1);
       }
    }
    cout << result.size() << "\n";
    for (auto el : result) {
        cout << el << " ";
    }

    return 0;
}
