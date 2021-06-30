/*

https://codeforces.com/group/zJTwakJcKM/contest/298483/problem/B

B. Map
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте ассоциативный массив с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put x y — поставить в соответствие ключу x значение y. Если ключ уже есть, то значение необходимо изменить.
delete x — удалить ключ x. Если элемента x нет, то ничего делать не надо.
get x — если ключ x есть в ассоциативном массиве, то выведите соответствующее ему значение, иначе выведите «none».
Ключи и значения — строки из латинских букв длинной не более 20 символов.
Выходные данные
Выведите последовательно результат выполнения всех операций get. Следуйте формату выходного файла из примера.
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
    void delete_w(const string& key_str_);
    bool get(const string& key_str_, string& value);
 private:
    const int M = 1e5;
    const int P = 1859999;
    const int A = 43;

    int hesh(string s);
    vector<list<pair<string, string>>> map_w;

};

Map_by_list :: Map_by_list() {
    for (int i = 0; i < M; i++) {
        map_w.push_back(list<pair<string, string>>());
    }
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
    for (auto it = map_w[index].begin(); it != map_w[index].end(); it++) {
        if (it->first == key_str_) {
            it->second  = value_str_;
            return;
        }
    }
    map_w[index].push_back(make_pair(key_str_, value_str_));
}

void Map_by_list :: delete_w(const string& key_str_) {
    int index = hesh(key_str_);
    for (auto it = map_w[index].begin(); it != map_w[index].end(); it++) {
        if (it->first == key_str_) {
            map_w[index].erase(it);
            return;
        }
    }
}

bool Map_by_list :: get(const string& key_str_, string& value) {
    int index = hesh(key_str_);
    for (auto el : map_w[index]) {
        if (el.first == key_str_) {
            value = el.second;
            return(true);
        }
    }
    return (false);
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
            dict.delete_w(key_str_);
        } else {
            scanf("%s", key_str_);
            string value;
            if (dict.get(key_str_, value)) {
                printf("%s\n", value.c_str());
            } else {
                printf("none\n");
            }
        }
    }
    return 0;
}
