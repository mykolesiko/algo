#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::swap;

struct oper_value {
    int n_oper;
    int value;
};

class prior_queue {
 public:
    vector<oper_value> prior;
    vector<int> nomer_oper;
    void add(int value);
    bool extract_min(struct oper_value* result);
    void decrease(int oper, int diff);

 private:
    void recalc_up(int icur);
    void recalc_down(int icur);
    int parent(int i);
    int left(int i);
    int right(int i);
    int oper_cur = 0;
};

void prior_queue :: add (int value) {
    oper_value quest;
    quest.n_oper = oper_cur;
    quest.value = value;
    prior.push_back(quest);

    int icur = prior.size() - 1;
    nomer_oper.push_back(icur);
    oper_cur++;
    recalc_up(icur);

}

int prior_queue ::parent(int i) {
    if (i == 0) return (-1);
    return ((i + 1)/2 - 1);
}

int prior_queue ::left (int i) {
    int left = ((i + 1) * 2 - 1);
    if (left > prior.size() - 1 ) return -1;
    else return left;

}

int prior_queue ::right(int i) {
    int right = ((i + 1) * 2);
    if (right > prior.size() - 1 ) return -1;
    else return right;
}

bool prior_queue :: extract_min(struct oper_value* result) {

    nomer_oper.push_back(-1);
    oper_cur++;
    if (prior.size() == 0) return (0);
    (*result) = (prior[0]);
    if (prior.size() == 1) {
        prior.pop_back();
        return (1);
    }

    prior[0] = prior[prior.size() - 1];
    prior.pop_back();
    nomer_oper[prior[0].n_oper] = 0;
    nomer_oper[result->n_oper] = -1;
    recalc_down(0);

    return (1);
}

void prior_queue :: recalc_up (int icur) {
    int ipar = parent(icur);
    while ((ipar != -1) && (prior[ipar].value > prior[icur].value)) {
        swap(prior[ipar], prior[icur]);
        swap(nomer_oper[prior[icur].n_oper], nomer_oper[prior[ipar].n_oper]);
        icur = ipar;
        ipar = parent(icur);
    }
}

void prior_queue :: recalc_down (int icur) {
    //bool check = true;
    //int icur = 0;
    int iswap = 0;
    while (true) {
        int ileft = left(icur);
        int iright = right(icur);
        if (ileft == -1) {
            if (iright == -1) return;
            else if (prior[iright].value < prior[icur].value) {
                iswap = iright;
            } else return;
        } else if (iright == -1) {
            if (prior[ileft].value < prior[icur].value)
                iswap = ileft;
            else return;
        } else {
            if (prior[iright].value < prior[ileft].value)
                iswap = iright;
            else iswap = ileft;
            if (prior[iswap].value >= prior[icur].value) return;
            swap(prior[iswap], prior[icur]);
            swap(nomer_oper[prior[icur].n_oper], nomer_oper[prior[iswap].n_oper]);
            icur = iswap;
         }
     }
}


void prior_queue ::decrease(int oper, int diff) {
   int icur = nomer_oper[oper];
   prior[icur].value = diff;
   recalc_up(icur);
   nomer_oper.push_back(-1);
   oper_cur++;
}

int main()
{
    char qstr[100];
    string qstring;

    int value;
    prior_queue queue;


    while (scanf("%s", qstr)) {
        string qstring;
        qstring = string(qstr);
        if (qstring == "push") {
          scanf("%d", &value);
          queue.add(value);

        } else if (qstring == "extract-min") {
            oper_value result;
          if (queue.extract_min(&result))
             printf("%d %d\n", result.value, result.n_oper + 1);
          else
             printf("*\n");
        }
        else {
            int oper;
            int diff;
            //cin >> oper >> diff;
            scanf("%d", &oper);
            scanf("%d", &diff);
            queue.decrease(oper - 1, diff);
        }

    }
    return (0);
}
