#include <iostream>
#include <string>

/*
Реализуйте сбалансированное двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 100. В каждой строке находится одна из следующих операций:

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
    Node(int x): key(x), left(nullptr), right(nullptr) {}
    int key;
    unsigned char height;
    Node* left;
    Node* right;
};

class Tree {
public:
    Tree() : root(nullptr) {}
    Node* root;
    Node* insert(Node* pnode, int x) {
        if (pnode == NULL) return new Node(x);
        if (x < pnode->key) {
          pnode->left = insert(pnode->left, x);
        } else if (x > pnode->key) {
          pnode->right = insert(pnode->right, x);
        }
        return balance(pnode);
    };

    Node* find_min(Node* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left ? find_min(p->left) : p;
    }

    Node* delete_key(Node* pnode, int x) {
        if (pnode == nullptr) {
            return nullptr;
        }
        if (x < pnode->key) {
            pnode->left = delete_key(pnode->left, x);
        } else if (x > pnode->key) {
            pnode->right = delete_key(pnode->right, x);
        } else {//  k == p->key
            Node* q = pnode->left;
            Node* r = pnode->right;
            delete pnode;
            if( !r ) return q;
            Node* min = find_min(r);
                min->right = delete_min(r);
                min->left = q;
                return balance(min);
        }
        return pnode;
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

    unsigned char get_height(Node* p)
    {
        return p ? p->height : 0;
    }

    int get_factor(Node* p)
    {
        return get_height(p->right) - get_height(p->left);
    }

    void fix_height(Node* p)
    {
        unsigned char hl = get_height(p->left);
        unsigned char hr = get_height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotate_right(Node* p) // правый поворот вокруг p
    {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }
    Node* rotate_left(Node* q) // левый поворот вокруг q
    {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        return p;
    }
    Node* balance(Node* p) // балансировка узла p
    {
        fix_height(p);
        if( get_factor(p) == 2 )
        {
            if( get_factor(p->right) < 0 )
                p->right = rotate_right(p->right);
            return rotate_left(p);
        }
        if( get_factor(p)==-2 )
        {
            if( get_factor(p->left) > 0  )
                p->left = rotate_left(p->left);
            return rotate_right(p);
        }
        return p; // балансировка не нужна
    }

    Node* delete_min(Node* p) // удаление узла с минимальным ключом из дерева p
    {
        if( p->left==0 )
            return p->right;
        p->left = delete_min(p->left);
        return balance(p);
    }
};

int main()
{
    char query[20];
    int key;
    Tree tree;
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
        //tree.print(tree.root);
    }
}
