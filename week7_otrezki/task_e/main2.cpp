#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include<algorithm>
#include<string>
#include <set>

using namespace std;


struct otr
{
    int min;
    int tl;
    int tr;
};

class derevo_otrezkov
{
public:
    derevo_otrezkov(vector<int>& V) : V_(V)
    {
        derevo_.resize(V.size()*4);
        //derevo_.assign(derevo_.size(), 0);
    };
    vector<int >& V_;
    vector<struct otr> derevo_;
    int build(int begin, int end, int level);
    //void update(int i, int u, int level);
    void calc(int begin, int end, int level, int& sum);
};


int derevo_otrezkov::build(int begin, int end, int level)
{
    otr new_otr;
    if (begin == end) {

        new_otr.min =V_[begin];
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = (new_otr);
        return(V_[begin]);
    }
    else
    {
        int centre = (begin + end)/2;

        new_otr.min = min(build(begin, centre, 2*level),build(centre+1, end, 2*level+1));
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = new_otr;
        return(new_otr.min);

    }
}

void derevo_otrezkov::calc(int begin, int end, int level, int& elmin)
{
    int tl = (derevo_)[level-1].tl;
    int tr = (derevo_)[level-1].tr;
    if ((begin == tl) && (end == tr))
    {
        elmin = min(elmin, (derevo_)[level-1].min);
        return;
    }
    int centre = (tl + tr)/2;
    if (begin >centre)
    {
        calc(begin, end, 2*level+1,elmin);
    } else if (end <= centre)
    {
        calc(begin, end, 2*level, elmin);

    } else
    {
        calc(begin, centre, 2*level,elmin);
        calc(centre+1, end, 2*level+1, elmin);

    }
}


/*void derevo_otrezkov::update(int i, int u, int level)
{
    int tl = (derevo_)[level-1].tl;
    int tr = (derevo_)[level-1].tr;
    if ((tl== i) && (tr == i))
    {
        (derevo_)[level-1].sum = u;
        return;
    }
    int centre = (tl + tr)/2;
    if (i >centre)
    {

         update(i, u, 2*level+1);

    } else if (i <= centre)
    {
        update(i, u, 2*level);


    }
    (derevo_)[level-1].sum = (derevo_)[2 * level-1].sum + (derevo_)[2 * level + 1 -1].sum;
}*/


/*derevo_otrezkov::derevo_otrezkov(vector<int>& V)
{
    V_ = V;
}*/


struct query {
    int left;
    int right;
    int el_min;
};

int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    int n_elems;
    int n_queries;
    vector<query> queries;

    cin >> n_elems;
    cin >> n_queries;
    vector<int> elems(n_elems, 0);
    vector<vector<int>> lsegments(n_elems, vector<int>());
    vector<vector<int>> rsegments(n_elems, vector<int >());
    for (int i=0; i<n_queries; i++) {
        struct query q;
        cin >> q.left >> q.right >> q.el_min;
        q.left--;
        q.right--;
        queries.push_back(q);
        lsegments[q.left].push_back(q.el_min);
        rsegments[q.right].push_back(q.el_min);
    }

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

    derevo_otrezkov* dd = new derevo_otrezkov(elems);
    dd->build(0,elems.size()-1, 1);
    int result_min;
    for (int i=0; i<n_queries; i++) {
        result_min = elems[queries[i].left];
        dd->calc(queries[i].left, queries[i].right, 1, result_min);
        if (result_min != queries[i].el_min) {
            printf("inconsistent\n");
            delete(dd);
            return (0);
        }
    }
    printf("consistent\n");
    for (int i=0; i<n_elems; i++) {
        if (i < n_elems - 1) {
            printf("%d ", elems[i]);
        } else {
           printf("%d", elems[i]);
        }
    }
    delete(dd);
    return 0;
}
