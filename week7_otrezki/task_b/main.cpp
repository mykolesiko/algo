#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include<algorithm>
#include<string>

using namespace std;


struct Otr
{
    long long sum;
    int tl;
    int tr;
};

class Derevo_otrezkov
{
public:
    Derevo_otrezkov(vector<long long>& V) : V_(V) {
        derevo_.resize(V.size() * 4);
    };
    vector<long long>& V_;
    vector<Otr> derevo_;
    long long build(int begin, int end, int level);
    void calc(int begin, int end, int level, long long& sum);
};


long long Derevo_otrezkov::build(int begin, int end, int level) {
    Otr new_otr;
    if (begin == end) {
        new_otr.sum =V_[begin];
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = (new_otr);
        return(V_[begin]);
    }
    else {
        int centre = (begin + end)/2;
        new_otr.sum = min(build(begin, centre, 2 * level),build(centre + 1, end, 2 * level + 1));
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = new_otr;
        return(new_otr.sum);
    }
}

void Derevo_otrezkov::calc(int begin, int end, int level, long long& elmin) {
    int tl = (derevo_)[level - 1].tl;
    int tr = (derevo_)[level - 1].tr;
    if ((begin == tl) && (end == tr)) {
        elmin =min(elmin, (derevo_)[level-1].sum);
        return;
    }
    int centre = (tl + tr) / 2;
    if (begin >centre)  {
        calc(begin, end, 2 * level + 1,elmin);
    } else if (end <= centre) {
        calc(begin, end, 2 * level, elmin);
    } else {
        calc(begin, centre, 2 * level,elmin);
        calc(centre+1, end, 2 * level + 1,elmin);
    }
}



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    long long a0;
    vector<long long> a;
    cin >> n >> m >> a0;
    long long sum;

    a.push_back(a0);
    for (int i = 1; i < n; i++)  {
        long long temp = (a[i-1] * 23 + 21563) % 16714589;
        a.push_back(temp);
    }
    long long u1, v1;
    cin >> u1 >> v1;

    Derevo_otrezkov* dd = new Derevo_otrezkov(a);
    dd->build(0,a.size() - 1, 1);

    int t1, t2;
    long long r1;
    int v11;
    int u11;
    for (int i = 0; i < m; i++)  {
        t1 = min(u1, v1);
        t2 = max(u1, v1);
        t1--;
        t2--;
        r1 = a[t1];
        dd->calc(t1, t2, 1, r1);
        long long u2=(17 * u1 + 751 + r1 + 2 * (i + 1)) % n + 1;
        long long v2=(13 * v1 + 593 +  r1 + 5 * (i + 1)) % n + 1;
        v11 = v1;
        u11 = u1;
        v1 = v2;
        u1 = u2;



    }
    cout << u11 << " " << v11 << " " << r1;
    return 0;
}
