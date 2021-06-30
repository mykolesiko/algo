/*
https://codeforces.com/group/zJTwakJcKM/contest/298483/problem/D

–еализуйте множественное отображение с использованием хеш таблиц.

¬ходные данные
¬ходной файл содержит описание операций, их количество не превышает 100000. ¬ каждой строке находитс€ одна из следующих операций:

put x y Ч добавить пару (x,y). ≈сли пара уже есть, то второй раз еЄ добавл€ть не надо.
delete x y Ч удалить пару (x,y). ≈сли пары нет, то ничего делать не надо.
deleteall x Ч удалить все пары с первым элементом x.
get x Ч вывести количество пар с первым элементом x, а затем вторые элементы всех этих пар в произвольном пор€дке.
 лючи и значени€ Ч строки из латинских букв длинной не более 20 символов.
¬ыходные данные
¬ыведите последовательно результат выполнени€ всех операций get. —ледуйте формату выходного файла из примера. √арантируетс€, что размер выходного файла не превысит 10 мегабайт.


ѕример
входные данные—копировать
put a a
put a b
put a c
get a
delete a b
get a
deleteall a
get a
выходные данные—копировать
3 a b c
2 a c
0

*/

 #include <iostream>
#include <vector>
#include <string>
#include <list>
#include <utility>

using namespace std;
const int MAX_LEN_STR = 21;

class Map_by_list {
 public:
    Map_by_list();
    void put(const string& key_str_, const string& value_str_);
    void delete_w(const string& key_str_, const string& value_str_);
    void deleteall(const string& key_str_);
    bool get(const string& key_str_, vector<string>& values);
 private:
    const long long M = 1e5;
    const long long P = 1e9;
    const long long A = 31;
    int hesh(string s);
    vector<list<pair<string, string>>> map_diff;
    vector<list<pair<string, string>>> map_one;
};

Map_by_list :: Map_by_list() {
   map_diff.resize(M);
}

int Map_by_list :: hesh(string s) {
    long long sum = 0;
    for (int i = 0; i < s.length(); i++) {
        sum = (sum * A + s[i]) % P;
    }
    return (sum % M);
}

void Map_by_list :: put(const string& key_str_, const string& value_str_) {
    int index = hesh(key_str_);
    if (map_one[index].size() == 0) {
        map_one[index].push_back(make_pair(key_str_, value_str_));
        return;
    }
    if (map_one[index].front().first == key_str_) {
        map_one[index].push_back(make_pair(key_str_, value_str_));
        return;
    }

    for (auto it = map_diff[index].begin(); it != map_diff[index].end(); it++) {
        if ((it->first == key_str_) && (it->second  == value_str_)) {
            return;
        }
    }
    map_diff[index].push_back(make_pair(key_str_, value_str_));
}

void Map_by_list :: delete_w(const string& key_str_, const string& value_str_) {
    int index = hesh(key_str_);
    for (auto it = map_diff[index].begin(); it != map_diff[index].end(); it++) {
        if ((it->first == key_str_) && (it->second == value_str_)) {
            it = map_diff[index].erase(it);
            return;
        }
    }
}

void Map_by_list :: deleteall(const string& key_str_) {
    int index = hesh(key_str_);
    auto it = map_diff[index].begin();
    while (it != map_diff[index].end()) {
        if (it->first == key_str_) {
            it = map_diff[index].erase(it);
        } else
            it++;
    }
}

bool Map_by_list :: get(const string& key_str_, vector<string>& values) {
    int index = hesh(key_str_);
    for (auto el : map_diff[index]) {
        if (el.first == key_str_) {
            values.push_back(el.second);
        }
    }
    if (values.size() == 0)
        return (false);
    else return(true);
}

int main() {
    Map_by_list dict;
    char qstr[MAX_LEN_STR * 3];
    char key_str_[MAX_LEN_STR];
    char value_str_[MAX_LEN_STR];
    while (cin >> qstr) {
        string quest;
        quest += qstr;
        if (quest == "put") {
            scanf("%s", key_str_);
            scanf("%s", value_str_);
            dict.put(key_str_, value_str_);
        } else if (quest == "delete") {
            scanf("%s", key_str_);
            scanf("%s", value_str_);
            dict.delete_w(key_str_, value_str_);
        } else if (quest == "deleteall") {
            scanf("%s", key_str_);
            dict.deleteall(key_str_);
        } else {
            scanf("%s", key_str_);
            vector<string> values;
            if (dict.get(key_str_, values)) {
                printf("%d ", values.size());
                for (auto it = values.begin(); it != values.end(); it++) {
                    if (it != values.end() - 1)
                        printf("%s ", it->c_str());
                    else
                        printf("%s\n", it->c_str());
                }
            } else {
                printf("0\n");
            }
        }
    }
    return 0;
}
