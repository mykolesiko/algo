#include <iostream>
#include <string>

/*
Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:

 — добавить в множество S число i (если он там уже есть, то множество не меняется);
 — вывести сумму всех элементов x из S, которые удовлетворяют неравенству l ≤ x ≤ r.
Входные данные
Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1 ≤ n ≤ 300 000).Следующие n строк
содержат операции. Каждая операция имеет вид либо «+ i», либо «? l r». Операция «? l r» задает запрос .

Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию . Если же она идет
после запроса «?», и результат этого запроса был y, то выполняется операция .

Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 109.

Выходные данные
Для каждого запроса выведите одно число — ответ на запрос..
*/

const int PAR_MAX = 1e+9;
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

    int get_height(Node* p)  {
        return p ? p->height : 0;
    }

    long long get_sum(Node* p) {
        return p ? p->sum : 0;
    }

    int get_factor(Node* p) {
        return get_height(p->right) - get_height(p->left);
    }

    void fix_height(Node* p) {
        int hl = get_height(p->left);
        int hr = get_height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    void fix_sum(Node* p) {
        long long sum_l = get_sum(p->left);
        long long sum_r = get_sum(p->right);
        p->sum = sum_l + sum_r + p->key;
    }

    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        fix_sum(p);
        fix_sum(q);
        return q;
    }

    Node* rotate_left(Node* q) {// левый поворот вокруг q
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        fix_sum(q);
        fix_sum(p);
        return p;
    }

    Node* balance(Node* p) {// балансировка узла p
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

    Node* delete_min(Node* p) { // удаление узла с минимальным ключом из дерева p
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

int main()
{
    char query[20];
    string query_prev = "";
    long long key;
    int left, right;
    long long sum;
    Tree tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> query;
        if (string(query) == "+") {
          cin >> key;
          if (query_prev == "?") {
              key += sum;
              key = key % PAR_MAX;
          }
          tree.root = tree.insert(tree.root, key);
        } else if (string(query) == "?") {
          cin >> left >> right;
          sum = tree.sum(tree.root, left, right);
          cout << sum << "\n";
        }
        query_prev = query;
        //string indent = "";
        //tree.print(tree.root, indent);
    }
}
