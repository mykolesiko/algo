/*

https://codeforces.com/group/zJTwakJcKM/contest/300637/problem/C
C. RSQ
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Входные данные
В первой строке находится число n — размер массива. (1≤n≤500000) Во второй строке находится n чисел ai — элементы массива. Далее содержится описание операций, их количество не превышает 1000000. В каждой строке находится одна из следующих операций:

set i x — установить a[i] в x.
sum i j — вывести значение суммы элементов в массиве на отрезке с i по j, гарантируется, что (1≤i≤j≤n).
Все числа во входном файле и результаты выполнения всех операций не превышают по модулю 1018.
Выходные данные
Выведите последовательно результат выполнения всех операций sum. Следуйте формату выходного файла из примера.

*/
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
    void update(int i, int u, int level);
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
        new_otr.sum = (build(begin, centre, 2 * level)+build(centre + 1, end, 2 * level + 1));
        new_otr.tl = begin;
        new_otr.tr = end;
        derevo_[level - 1] = new_otr;
        return(new_otr.sum);
    }
}

void Derevo_otrezkov::calc(int begin, int end, int level, long long& sum) {
    int tl = (derevo_)[level - 1].tl;
    int tr = (derevo_)[level - 1].tr;
    if ((begin == tl) && (end == tr)) {
        sum+=(derevo_)[level-1].sum;
        return;
    }
    int centre = (tl + tr) / 2;
    if (begin >centre)  {
        calc(begin, end, 2 * level + 1,sum);
    } else if (end <= centre) {
        calc(begin, end, 2 * level, sum);
    } else {
        calc(begin, centre, 2 * level,sum);
        calc(centre+1, end, 2 * level + 1,sum);
    }
}


void Derevo_otrezkov::update(int i, int u, int level) {
    int tl = (derevo_)[level - 1].tl;
    int tr = (derevo_)[level - 1].tr;
    if ((tl== i) && (tr == i)) {
        (derevo_)[level - 1].sum = u;
        return;
    }
    int centre = (tl + tr) / 2;
    if (i >centre) {
         update(i, u, 2 * level + 1);
    } else if (i <= centre) {
        update(i, u, 2 * level);
    }
    (derevo_)[level-1].sum = (derevo_)[2 * level - 1].sum + (derevo_)[2 * level + 1 - 1].sum;
}



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    int e;
    int q;
    vector<long long> V;
    cin >> n;
    long long sum;

    for (int i=0; i<n; i++)  {
        cin >> e;
        V.push_back(e);
    }

    Derevo_otrezkov* dd = new Derevo_otrezkov(V);
    dd->build(0,V.size()-1, 1);
    string query;
    int n1;
    int n2;
    while (cin >> query >> n1 >> n2) {
        if (query == "set") {
            dd->update(n1-1, n2, 1);
        }
        if (query == "sum") {
            sum = 0;
            dd->calc(n1-1, n2-1, 1, sum);
            cout << sum << "\n";
        }
    }
    return 0;
}
