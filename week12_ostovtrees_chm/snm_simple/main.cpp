#include <iostream>
#include <vector>

using namespace std;
vector<struct info_t> cnm;

struct info_t {
    info_t() : max_el(0), min_el(0), number(0), rang(0), pred(0) {};
    int max_el;
    int min_el;
    int number;
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
    if (y->max_el < x->max_el) {
        y->max_el = x->max_el;
    }
    if (y->min_el > x->min_el) {
        y->min_el = x->min_el;
    }
    y->number += x->number;
    x->pred = j;

}




int main()
{
    int n;
    cin >> n;

    struct info_t info;
    cnm.resize(n, info);
    for (int i = 0; i < n; i++) {
        cnm[i].pred = cnm[i].max_el = cnm[i].min_el = i;
        cnm[i].number = cnm[i].rang = 1;
    }
    char query[20];
    while (cin >> query) {
        string query_s(query);
        if (query_s == "union") {
            int i, j;
            cin >> i;
            cin >> j;
            join (i - 1, j - 1);

        } else if (query_s == "get") {
            int i;
            cin >> i;
            struct info_t info = cnm[get(i - 1)];
            cout << info.min_el + 1 << " " << info.max_el + 1 << " " << info.number << "\n";
        } else {

        }

    }
    return 0;
}
