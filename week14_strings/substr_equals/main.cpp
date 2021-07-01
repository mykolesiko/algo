#include <iostream>
#include <vector>
#include <string>

using namespace std;


const long long P = 31;
const long long M = 1063766327;

vector<long long> calc_hashes(string str, vector<long long>& pow_p) {
    vector<long long> result;
    long long cur = (unsigned char)(str[0]);
    result.push_back(cur);
    long long pow_cur = 1;
    pow_p.push_back(pow_cur);

    for (int i = 1; i < str.length(); i++) {
        unsigned char c = str[i];
        cur = (cur * P +  c) % M;
        result.push_back(cur);
        pow_cur = (pow_cur * P) % M;
        pow_p.push_back(pow_cur);

    }
    return result;
}

int main()
{
    string S;
    int n_quests;

    cin >> S;
    cin >> n_quests;
    vector<long long> pow_p;
    vector<long long> hashes = calc_hashes(S, pow_p);

    for (int i = 0; i< n_quests; i++)  {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        int hash1, hash2;
        if (a == 0) {
            hash1 = hashes[b] ;
        }
        else {
          hash1  = (hashes[b]  - ((hashes[a - 1]) * (pow_p[b - a + 1])) % M + M) % M;
        }
        if (c == 0) {
          hash2 = hashes[d] ;
        }
        else {
          hash2  = (hashes[d]  - (hashes[c - 1] * pow_p[d - c + 1]) % M + M) % M;

        }
        if (hash1 == hash2) {
           cout << "Yes" << "\n";
        } else {
           cout << "No" << "\n";
        }
    }
    return 0;

}
\
