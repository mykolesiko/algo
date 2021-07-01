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
    Node(int x): key(x), left(nullptr), right(nullptr), sum(x) {}
    int key;
    int height;
    Node* left;
    Node* right;
    long long sum;
};

class Tree {
public:
    Tree() : root(nullptr) {}
    //~Tree();
    Node* root;
    Node* insert(Node* pnode, int x) {
        if (pnode == NULL) {
            return new Node(x);
        }
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
        }
        else {//  k == p->key
            Node* q = pnode->left;
            Node* r = pnode->right;
            delete pnode;
            if( !r ) return q;
            Node* min = find_min(r);
            min->right = delete_min(r);
            min->left = q;
            return balance(min);
        }
        fix_sum(pnode);
        return pnode;
    } // удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;


    Node* findMax(Node* pnode) {
        while (pnode->right != nullptr) {
            pnode = pnode->right;
        }
        return pnode;
    }

    void print(Node* pnode, string indent) {
        if (pnode == nullptr) return;
        indent += "  ";
        print(pnode->right, indent);
        cout << indent << pnode->key << "("<< pnode->sum << ")" << "\n";
        print(pnode->left, indent);

    }


    int get_height(Node* p)
    {
        return p ? p->height : 0;
    }

    int get_sum(Node* p)
    {
        return p ? p->sum : 0;
    }


    int get_factor(Node* p)
    {
        return get_height(p->right) - get_height(p->left);
    }

    void fix_height(Node* p)
    {
        int hl = get_height(p->left);
        int hr = get_height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    void fix_sum(Node* p)
    {
        int sum_l = get_sum(p->left);
        int sum_r = get_sum(p->right);
        p->sum = sum_l + sum_r + p->key;
    }

    Node* rotate_right(Node* p) // правый поворот вокруг p
    {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        fix_sum(p);
        fix_sum(q);
        return q;
    }
    Node* rotate_left(Node* q) // левый поворот вокруг q
    {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        fix_sum(q);
        fix_sum(p);
        return p;
    }
    Node* balance(Node* p) // балансировка узла p
    {
        fix_height(p);
        fix_sum(p);
        if( get_factor(p) == 2 )
        {
            if( get_factor(p->right) < 0 ) {
                p->right = rotate_right(p->right);
                fix_sum(p);
            }
            return rotate_left(p);
        }
        if( get_factor(p)==-2 )
        {
            if( get_factor(p->left) > 0  ) {
                p->left = rotate_left(p->left);
                fix_sum(p);
            }
            return rotate_right(p);
        }
        fix_sum(p);
        return p; // балансировка не нужна
    }

    Node* delete_min(Node* p) // удаление узла с минимальным ключом из дерева p
    {
        fix_sum(p);
        if( p->left == nullptr )
            return p->right;
        p->left = delete_min(p->left);
        return balance(p);
    }

    long long sum (Node* pnode, int left, int right) {
        if (pnode == nullptr) {
            return (0);
        }
        if (left == LONG_MIN) {
            if (pnode->key > right) {
              return sum(pnode->left, left, right);
            } else if (pnode->key <= right) {
              long long sum_l = get_sum(pnode->left);
              long long sum_r = sum(pnode->right, left, right);
              return (pnode->key + sum_l + sum_r);
            }
        } else if (right == LONG_MAX) {
          if (pnode->key < left) {
            return sum(pnode->right, left, LONG_MAX);
          } else if (pnode->key >= left) {
              long long sum_l = get_sum(pnode->right);
              long long sum_r = sum(pnode->left, left, right);
              return (pnode->key + sum_l + sum_r);
           }
        } else {
          if (pnode->key < left) {
             return sum(pnode->right, left, right);
          } else if ((pnode->key >= left) && (pnode->key <= right)) {
             long long sum_l = sum(pnode->left, left, LONG_MAX);
             long long sum_r = sum(pnode->right, LONG_MIN, right);
             return (pnode->key + sum_l + sum_r);
          } else {
             return sum(pnode->left, left, right);
          }
        }
      }
};

const int PAR_MAX = 1e+9;

using namespace std;
vector<int> test;

int rand_interval(int rmin, int rmax) {
    int r = rand();
    float res = r/(float)RAND_MAX;
    int result =   (int(res * (float)(rmax - rmin + 1)) + rmin);
    if (result > rmax) result = rmax;
    return result;

}

int main()
{
    char query[20];
    string query_prev = "";
    long long key;
    int left, right;
    long long sum;
    Tree tree;
    int n = 10000;
    int s = rand_interval(0, 3);
    if (s > 1) {
        query = "+"
    } else {
        query = "?"
    }

    //cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> query;
        if (string(query) == "+") {
          //cin >> key;
          key = rand_interval(0, PAR_MAX);
          if (query_prev == "?") {
              key += sum;
              key = key % PAR_MAX;
          }
          tree.root = tree.insert(tree.root, key);
          test.push_back(key);
        } else if (string(query) == "?") {
          //cin >> left >> right;
          left = rand_interval(0, PAR_MAX);
          right = rand_interval(0, PAR_MAX);
          long long sum
          for (el : test) {
              if el >= left
          }
          sum = tree.sum(tree.root, left, right);
          cout << sum << "\n";
        }
        query_prev = query;
        string indent = "";
        tree.print(tree.root, indent);
    }
}
