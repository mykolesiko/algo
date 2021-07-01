#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*Входные данные
Размер массива — n и числа x, y, a0, порождающие массив a:

Далее следует количество запросов m и числа z, t, b0, порождающие массив b: .

Массив c строится следующим образом: .

Запросы: i-й из них — найти сумму на отрезке от min(c2i, c2i + 1) до max(c2i, c2i + 1) в массиве a.

Ограничения: 1 ≤ n ≤ 10^7, 0 ≤ m ≤ 10^7. Все числа целые от 0 до 216. t может быть равно  - 1.*/
const long long P2_16 = 65536;
const long long P2_30 = 1073741824;

long long mod_my(long long x, long long d) {
     long long res = x % d;
     if (res < 0) {
        return (res + d);
     }
     else {
       return res;
    }
}

int main()
{
    long long n, x, y, a0;
    long long m, z, t, b0;
    cin >> n >> x >> y >> a0;
    cin >> m >> z >> t >> b0;
    vector<long long> sums;
    sums.push_back(a0);
    long long prev = a0;
    long long sum = prev = a0;
    for (int i = 1; i < n; i++) {
        prev = mod_my((x * prev + y), P2_16);
        sum += prev;
        sums.push_back(sum);
    }
    long long b1 = mod_my((z * b0 + t), P2_30);
    long long c0, c1;
    long long sum_all = 0;
    for (int i = 0; i < m; i++) {
        c0 = mod_my(b0, n);
        c1 = mod_my(b1, n);
        b0 = mod_my((z * b1 + t), P2_30);
        b1 = mod_my((z * b0 + t), P2_30);
        int left = min(c0, c1);
        int right = max(c0, c1);
        if (left == 0) {
           sum_all += sums[right];
        }
        else {
           sum_all += sums[right] - sums[left - 1];
        }
    }
    cout << sum_all;
    return 0;
}

