/*

–еализуйте прошитый ассоциативный массив с использованием хеш таблицы.

¬ходные данные
¬ходной файл содержит описание операций, их количество не превышает 100000. ¬ каждой строке находитс€ одна из следующих операций:

put x y Ч поставить в соответствие ключу x значение y. ≈сли элемент уже есть, то значение необходимо изменить.
delete x Ч удалить ключ x. ≈сли элемента x нет, то ничего делать не надо.
get x Ч если ключ x есть в множестве выведите соответствующее ему значение, если нет выведите Ђnoneї.
prev x Ч вывести значение соответствующее ключу наход€щемус€ в ассоциативном массиве, который был вставлен позже всех, но до x или Ђnoneї, если такого нет или в массиве нет x.
next x Ч вывести значение соответствующее ключу наход€щемус€ в ассоциативном массиве, который был вставлен раньше всех, но после x или Ђnoneї, если такого нет или в массиве нет x.
 лючи и значени€ Ч строки из латинских букв длинной не более 20 символов.
¬ыходные данные
¬ыведите последовательно результат выполнени€ всех операций get, prev, next. —ледуйте формату выходного файла из примера.
*/


#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <utility>

using namespace std;
const int MAX_LEN_STR = 21;

struct Node
{
    string key;
    string value;
    struct Node* next;
    struct Node* prev;
};

class Map_by_list {
 public:
    Map_by_list();
    void put(const string& key_str_, const string& value_str_);
    void delete_w(const string& key_str_);
    bool get(const string& key_str_, Node& node);
    string prev(const string& x);
    string next(const string& x);
 private:
    const int M = 1e5;
    const int P = 1859999;
    const int A = 43;
    int hesh(string s);
    vector<list<Node>> map_w;
    Node* begin_seq = nullptr;
    Node* end_seq = nullptr;
};

Map_by_list :: Map_by_list() {

    map_w.resize(M);
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
        if (it->key == key_str_) {
            it->value  = value_str_;
            return;
        }
    }
    Node node;
    node.key = key_str_;
    node.value = value_str_;
    node.next = nullptr;
    node.prev = end_seq;
    map_w[index].push_back(node);
    end_seq = &(map_w[index].back());
    if (node.prev != nullptr) {
        node.prev->next = end_seq;
    }
}

void Map_by_list :: delete_w(const string& key_str_) {
    int index = hesh(key_str_);
    for (auto it = map_w[index].begin(); it != map_w[index].end(); it++) {
        if (it->key == key_str_) {
            Node* prev = it->prev;
            Node* next = it->next;
            if (prev != nullptr) {
                prev->next = next;
            } else {
                begin_seq = next;
            }
            if (next != nullptr) {
                next->prev = prev;
            } else {
                end_seq = prev;
            }
            map_w[index].erase(it);
            return;
        }
    }
}

bool Map_by_list :: get(const string& key_str_, Node& node) {
    int index = hesh(key_str_);
    for (auto el : map_w[index]) {
        if (el.key == key_str_) {
            node = el;
            return(true);
        }
    }
    return (false);
}

string Map_by_list :: prev(const string& key_str_) {
    Node node;
    if (!get(key_str_, node)) return("none");
    else {
        if (node.prev == nullptr) {
            return ("none");
        } else {
            return node.prev->value;
        }
    }
}

string Map_by_list :: next(const string& key_str) {
    Node node;
    if (!get(key_str, node)) return("none");
    else {
        if (node.next == nullptr) {
            return ("none");
        } else {
            return node.next->value;
        }

    }
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
        } if (quest == "get") {
            scanf("%s", key_str_);
            Node node;
            if (dict.get(key_str_, node)) {
                printf("%s\n", node.value.c_str());
            } else {
                printf("none\n");
            }
        } else if (quest == "prev") {
            scanf("%s", key_str_);
            printf("%s\n", dict.prev(key_str_).c_str());
        } else if (quest == "next") {
            scanf("%s", key_str_);
            printf("%s\n", dict.next(key_str_).c_str());
        }
    }
    return 0;
}
