#include <iostream>
#include <string>
#include <time.h>
#include <random>

/*Реализуйте сбалансированное двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 105. В каждой строке находится одна из следующих операций:

insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо;
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;
exists x — если ключ x есть в дереве выведите «true», если нет «false»;
next x — выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;
prev x — выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.

*/

using namespace std;

class Node {
 public:
    Node(int x): key(x), left(nullptr), right(nullptr) {
        prior = create_prior();
    }
    int create_prior() {
        return (rand());
    }
    int key;
    int prior;
    Node* left;
    Node* right;
};

class Tree {
 public:
    Tree() : root(nullptr) {}
    Node* root;

    Node* insert(Node* pnode, int x) {
        pair<Node*, Node*> result = split(pnode, x);
        Node* t1 = merge(result.first, new Node(x));
        Node* root = merge(t1, result.second);
        return root;
    };


    pair<Node*, Node*> split(Node* pnode, int x) {
        if (pnode == nullptr) {
            return make_pair(nullptr, nullptr);
        }

        if (pnode->key > x) {
            pair<Node*, Node*> result = split(pnode->left, x);
            pnode->left = result.second;
            return (make_pair(result.first, pnode));
        } else {
            pair<Node*, Node*> result = split(pnode->right, x);
            pnode->right = result.first;
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
            return t1;
        } else {
            t2->left = merge(t1, t2->left);
            return (t2);
        }

    }

    Node* delete_key(Node* pnode, int x) {
        pair<Node*, Node*> result1 = split(pnode, x);
        pair<Node*, Node*> result2 = split(result1.first, x - 1);
        Node* root = merge(result2.first, result1.second);
        return root;

    } // удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;

    Node* findMax(Node* pnode) {
        while (pnode->right != nullptr) {
            pnode = pnode->right;
        }
        return pnode;
    }

    Node* exists(Node* pnode, int x) { // если ключ x есть в дереве выведите «true», если нет «false»;
       if (pnode == nullptr) {
           return (nullptr);
       }
       if (pnode->key == x) {
           return(pnode);
       } else if (x < pnode->key) {
           return exists(pnode->left, x);
       } else {
           return exists(pnode->right, x);
       }
    }

    void print(Node* pnode) {
        if (pnode == nullptr) return;
        print(pnode->left);
        cout << pnode->key << " ";
        print(pnode->right);
    }

    bool next(int x, int& value) {
       Node* pnode  = root;
       Node* result = nullptr;
       while (pnode != nullptr) {
           if (pnode->key > x) {
               result = pnode;
               pnode = pnode->left;
           } else {
               pnode = pnode->right;
           }
       }
       if (result == nullptr) {
           return false;
       }
       value = result->key;
       return(true);
    } // выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;

    bool prev(int x, int& value) {
       Node* pnode  = root;
       Node* result = nullptr;
       while (pnode != nullptr) {
           if (pnode->key < x) {
               result = pnode;
               pnode = pnode->right;
           } else {
               pnode = pnode->left;
           }
       }
       if (result == nullptr) {
           return false;
       }
       value = result->key;
       return(true);
    } // выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
};

int main()
{
    char query[20];
    int key;
    Tree tree;
    srand(time(NULL));
    while (cin >> query >> key) {
        //tree.print(tree.root);
        if (string(query) == "insert") {
          tree.root = tree.insert(tree.root, key);
        } else if (string(query) == "delete") {
          tree.root = tree.delete_key(tree.root, key);
        } else if (string(query) == "exists") {
            if (tree.exists(tree.root, key)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        } else if (string(query) == "next") {
          int value;
          if (!tree.next(key, value)) {
              printf("none\n");
          } else {
              printf("%d\n", value);
          }
        } else if (string(query) == "prev") {
            int value;
            if (!tree.prev(key, value)) {
                printf("none\n");
            } else {
                printf("%d\n", value);
            }
        }
    }
}
