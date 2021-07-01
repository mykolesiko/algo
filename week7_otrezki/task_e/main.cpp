#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include<algorithm>
#include<string>
#include <set>
#include <fstream>

using namespace std;

struct Otr {
    int min;
    int tl;
    int tr;
};

struct Query {
    int left;
    int right;
    int el_min;
};

class Derevo_otrezkov {
public:
    Derevo_otrezkov(vector<int>* V) : V_(V) {
        derevo_.resize((*V).size() * 4);
    };
    vector<int >* V_;
    vector<Otr> derevo_;
    int build(int begin, int end, int level);
    void calc(int begin, int end, int level, int& sum);
};

int Derevo_otrezkov::build(int begin, int end, int level) {
    Otr new_otr;
    if (begin == end) {
        new_otr.min =(*V_)[begin];
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = (new_otr);
        return((*V_)[begin]);
    }
    else {
        int centre = (begin + end)/2;
        new_otr.min = min(build(begin, centre, 2 * level),build(centre + 1, end, 2 * level + 1));
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = new_otr;
        return(new_otr.min);
    }
}

void Derevo_otrezkov::calc(int begin, int end, int level, int& elmin) {
    int tl = (derevo_)[level - 1].tl;
    int tr = (derevo_)[level - 1].tr;
    if ((begin == tl) && (end == tr)) {
        elmin = min(elmin, (derevo_)[level - 1].min);
        return;
    }
    int centre = (tl + tr) / 2;
    if (begin >centre) {
        calc(begin, end, 2 * level + 1,elmin);
    } else if (end <= centre) {
        calc(begin, end, 2 * level, elmin);
    } else  {
        calc(begin, centre, 2 * level,elmin);
        calc(centre+1, end, 2 * level + 1, elmin);

    }
}

int main() {
    std::ifstream in;
    in.open("rmq.in");
    int n_elems;
    int n_queries;
    vector<Query> queries;

    in >> n_elems;
    in >> n_queries;
    vector<int> elems(n_elems, 0);
    vector<vector<int>> lsegments(n_elems, vector<int>());
    vector<vector<int>> rsegments(n_elems, vector<int >());
    for (int i=0; i<n_queries; i++) {
        struct Query q;
        in >> q.left >> q.right >> q.el_min;
        q.left--;
        q.right--;
        queries.push_back(q);
        lsegments[q.left].push_back(q.el_min);
        rsegments[q.right].push_back(q.el_min);
    }
    in.close();
    std::ofstream out;
    out.open("rmq.out");
    multiset<int> el_mins;
    for (int i=0; i<n_elems; i++) {
        for (int j = 0; j < lsegments[i].size(); j++) {
            el_mins.insert(lsegments[i][j]);
        }
        if (i != 0) {
            for (int j = 0; j < rsegments[i - 1].size(); j++) {
                auto it = el_mins.find(rsegments[i - 1][j]);
                el_mins.erase(it);
            }
        }
        if (el_mins.size() != 0) {
            int elmin = (*std::prev(el_mins.end()));
            elems[i] = elmin;
            //elems[i].push_back((*(std::prev(el_mins.end()))));
        }
    }

    Derevo_otrezkov* dd = new Derevo_otrezkov(&elems);
    dd->build(0,elems.size() - 1, 1);
    int result_min;
    for (int i=0; i < n_queries; i++) {
        result_min = elems[queries[i].left];
        dd->calc(queries[i].left, queries[i].right, 1, result_min);
        if (result_min != queries[i].el_min) {
            out << "inconsistent" << endl;
            delete(dd);
            return (0);
        }
    }
    out << "consistent" << endl;
    for (int i=0; i<n_elems; i++) {
        if (i < n_elems - 1) {
            //printf("%d ", elems[i]);
            out << elems[i] << " ";
        } else {
            out << elems[i] << endl;
           //printf("%d", elems[i]);
        }
    }
    delete(dd);
    return 0;
}
