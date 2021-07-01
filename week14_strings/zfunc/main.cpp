#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> zfunction (string s) {
    int str_len = s.length();
    vector<int> z(str_len);
    int left = 0;
    int right = 0;
    for (int i = 1 ; i < str_len; ++i) {
        if (i <= right)
            z[i] = min (right - i + 1, z[i - left]);
        while (i + z[i] < str_len && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > right)
            left = i,  right = i + z[i] - 1;
    }
    return z;
}


int main() {
    string str;
    cin >> str;
    vector<int> result = zfunction(str);
    int n = str.length();
    if (n == 1) {
        cout << " ";
    }
    for (int i = 1 ; i < n ; i++) {
        cout << result[i] << " ";
    }
    return 0;
}
