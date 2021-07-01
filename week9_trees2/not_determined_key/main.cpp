#include <iostream>
#include <string>
#include <time.h>
#include <random>

/*
 * Научитесь быстро делать две операции с массивом:
 * add i x — добавить после i-го элемента x (0 ≤ i ≤ n)
 * del i — удалить i-й элемент (1 ≤ i ≤ n)

Входные данные
На первой строке n0 и m (1 ≤ n0, m ≤ 105) — длина исходного массива и количество запросов.
На второй строке n0 целых чисел от 0 до 109 - 1 — исходный массив. Далее m строк, содержащие запросы.
Гарантируется, что запросы корректны: например, если просят удалить i-й элемент, он точно есть.

Выходные данные
Выведите конечное состояние массива. На первой строке количество элементов, на второй строке сам массив.
*/

using namespace std;

class Node {
 public:
    Node(int value_): value(value_), left(nullptr), right(nullptr), size(1) {
        prior = create_prior();
    }
    int create_prior() {
        return (rand());
    }
    int prior;
    int value;
    Node* left;
    Node* right;
    int size;
};

class Tree {
 public:
    Tree() : root(nullptr) {}
    Node* root;

    /*Node* insert(Node* pnode, int x) {
        pair<Node*, Node*> result = split(pnode, x);
        Node* t1 = merge(result.first, new Node(x));
        Node* root = merge(t1, result.second);
        return root;
    };*/
    Node* add(Node* pnode, int index, int value) {
        pair<Node*, Node*> result = split(pnode, index);
        Node* t1 = merge(result.first, new Node(value));
        Node* root = merge(t1, result.second);
        return root;
    }


    int get_size(Node* p) {
        return p ? p->size : 0;
    }

    void fix_size(Node* p) {
        if (p == nullptr) return;
        int size_l = get_size(p->left);
        int size_r = get_size(p->right);
        p->size = size_l + size_r + 1;
    }

    pair<Node*, Node*> split(Node* pnode, int index) {
        if (pnode == nullptr) {
            //fix_size(pnode);
            return make_pair(nullptr, nullptr);
        }
        if (get_size(pnode->left) >= index) {
            pair<Node*, Node*> result = split(pnode->left, index);
            pnode->left = result.second;
            fix_size(pnode);
            return (make_pair(result.first, pnode));
        } else {
            pair<Node*, Node*> result = split(pnode->right, index - get_size(pnode->left) - 1);
            pnode->right = result.first;
            fix_size(pnode);
            return (make_pair(pnode, result.second));
        }
    }

    Node* merge(Node* t1, Node* t2) {
        if (t1 == nullptr) {
            return t2;
        }
        if (t2 == nullptr) {
            return t1;
        }
        if (t1->prior > t2->prior) {
            t1->right = merge(t1->right, t2);
            fix_size(t1);
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            fix_size(t2);
            return (t2);
        }

    }

    Node* delete_index(Node* pnode, int index) {
        pair<Node*, Node*> result1 = split(pnode, index);
        pair<Node*, Node*> result2 = split(result1.first, index - 1);
        Node* root = merge(result2.first, result1.second);
        return root;

    } // удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;




    void print(Node* pnode) {
        if (pnode == nullptr) return;
        print(pnode->left);
        cout << pnode->value << " ";
        print(pnode->right);
    }


};

int main() {
    char query[20];
    int key;
    Tree tree;
    srand(time(NULL));
    int n0, m;
    cin >> n0 >> m;
    int index;
    for (index = 0; index < n0; index++) {
        int temp;
        cin >> temp;
        tree.root = tree.add(tree.root, index, temp);
    }
    //tree.print(tree.root);
    for (int i = 0; i < m; i++) {
        int value;
        cin >> query;
        //tree.print(tree.root);
        if (string(query) == "add") {
          cin >> index >>  value;
          tree.root = tree.add(tree.root, index, value);
        } else if (string(query) == "del") {
          cin >> index;
          tree.root = tree.delete_index(tree.root, index);
        }
        //tree.print(tree.root);
        //cout << "\n";
    }
    cout << tree.get_size(tree.root) << "\n";
    tree.print(tree.root);
}
