#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>


const long long P = 31;
const long long M = 1063766327;
#define LEFT  0
#define RIGHT  1
using namespace std;

vector<long long> calc_powp(int len_powp) {
    vector<long long> pow_p;
    int pow_cur = 1;
    pow_p.push_back(pow_cur);
    //print(pow_cur)
    for (int i = 0; i< (len_powp); i++) {
        pow_cur = (pow_cur * P) % M;
        pow_p.push_back(pow_cur);
        //print(pow_cur)
    }
    return pow_p;
}

vector<long long> calc_hashes(string str) {
    vector<long long> result;
    //print(string[0])
    long long cur = (unsigned char)(str[0]);
    result.push_back(cur);

    for (int i = 1; i < str.length(); i++) {
        cur = (cur * P + int(str[i]) ) % M;
        result.push_back(cur);
    }
    return result;
}

set<long long> get_hashes_of_substrs_len(string str, vector<long long> hashes_one_string, vector<long long> pow_p, int len_common_str) {

    set<long long> set_cur;
    for (int i = 0; i < ((str.length()) - len_common_str + 1); i++) {
            int right = i + len_common_str - 1;
            int left = i;
            if (left == 0) {
                int sum = hashes_one_string[right];
                set_cur.insert(sum);
            }
            else {
                int sum  = ((hashes_one_string[right] - (hashes_one_string[left - 1] * pow_p[right - left + 1]) % M) + M) % M;
                set_cur.insert(sum);
            }
    }

    return (set_cur);
}


bool is_pivot_len_ok(vector<string>& strings, vector<vector<long long>>& hashes, vector<long long>& pow_p, int pivot_len, pair<long long, int>& common) {

    set<long long> set_hashes = get_hashes_of_substrs_len(strings[0], hashes[0], pow_p, pivot_len);

    for (int i = 1; i <(hashes.size()); i++) {
        auto set_cur = get_hashes_of_substrs_len(strings[i], hashes[i], pow_p, pivot_len);
        set<long long> intersect;
        set_intersection(set_hashes.begin(),set_hashes.end(), set_cur.begin(),set_cur.end(),
                          std::inserter(intersect,intersect.begin()));

        set_hashes = intersect;
    }
    if (set_hashes.size() == 0) {
        return false;
    }
    else {
        common.first = (*set_hashes.begin());
        common.second = pivot_len;
        return true;
   }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int K;
    cin >> K;
    vector<string> strings;
    int min_len = 1e5;
    int max_len = 0;
    for (int i = 0; i < K ; i++) {
        string temp;
        cin >> temp;
        strings.push_back(temp);
        if ((temp.length()) < min_len) {
            min_len = temp.length();
        }
        if ((temp.length()) > max_len)  {
            max_len = temp.length();
        }
    }

    vector<long long> pow_p = calc_powp(max_len);
    int left = 0;
    int right = min_len;
    vector<vector<long long>>hashes;
    for (int i = 0; i< (K); i++) {
        vector<long long> hashes_one_string = calc_hashes(strings[i]);
        //print(hashes_one_string)
        hashes.push_back(hashes_one_string);
    }

    //print(hashes)
    pair<long long, int> common;
    string temp_str = "";
    while  (abs(left - right) > 1) {
        int pivot_len = (-left + right) / 2 + left;
        //print(pivot_len)
        int result =  is_pivot_len_ok(strings, hashes, pow_p, pivot_len, common);
        if (result == true)
            left = pivot_len;
        else
            right = pivot_len;
    }

    bool result = is_pivot_len_ok(strings, hashes, pow_p, right, common);

    if (common.first != 0) {
       long long hash = common.first;
       int len_common_str = common.second;
       for (int i = 0; i < ((strings[0].length()) - len_common_str + 1); i++) {
            int right = i + len_common_str - 1;
            int left = i;
            long long sum;
            if (left == 0) {
                sum = hashes[0][right];

            }
            else {
                sum  = ((hashes[0][right] - (hashes[0][left - 1] * pow_p[right - left + 1]) % M) + M) % M;

            }
            if (sum == hash) {
                cout << strings[0].substr(i,  len_common_str);
                return (0);
            }
       }
    }
    return (0);
    //cout << common_str;
}

