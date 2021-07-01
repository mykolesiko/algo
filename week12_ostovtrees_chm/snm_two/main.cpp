#include <iostream>
#include <vector>

using namespace std;
vector<struct info_t> cnm;

struct info_t {
    int rang;
    int money;
    int pred;
};



int get(int i, int* money = NULL) {
    if (money) {
      (*money) += cnm[i].money;
      //cout << i << " " << cnm[i].money << "\n";
    }


    if (cnm[i].pred != i) {
        //cnm[i].pred = get(cnm[i].pred, money);
        //if money {
        //    (*money) += cnm[i].money;
        //}
        int old_par = cnm[i].pred;
        if (cnm[cnm[i].pred].pred == cnm[i].pred) {
            old_par = -1;
        }
        cnm[i].pred = get(cnm[i].pred, money);
        if (old_par != -1) {
            cnm[i].money += cnm[old_par].money;
        }
    }
    //return (cnm[i].pred);
    return cnm[i].pred;
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
    x->pred = j;
    x->money -= y->money;

}


void add (int i, int money) {
    int root = get(i);
    cnm[root].money += money;
}


int main()
{
    int n, m;
    cin >> n >> m;

    struct info_t info;
    cnm.resize(n, info);
    for (int i = 0; i < n; i++) {
        cnm[i].pred = i;
        cnm[i].rang = 1;
        cnm[i].money = 0;
    }
    char query[20];
    for (int s = 0; s < m; s++) {
        cin >> query;
        string query_s(query);
        if (query_s == "join") {
            int i, j;
            cin >> i;
            cin >> j;
            join (i - 1, j - 1);

        } else if (query_s == "get") {
            int i;
            int money = 0;
            cin >> i;
            int root = get(i - 1, &money);
            //if (root != i - 1) {
            //   cnm[i - 1].money = money - cnm[root].money;
            //}
            cout << money << "\n";
        } else {
            int i, money;
            cin >> i >> money;
            add(i - 1, money);
        }
    }
    return 0;
}
