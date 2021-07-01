#include <iostream>
#include <string>

/*
Напишите программу, реализующую структуру данных, позволяющую добавлять и удалять элементы, а также находить k-й максимум.

Входные данные
Первая строка входного файла содержит натуральное число n — количество команд (n≤100000). Последующие n строк содержат по одной команде каждая. Команда записывается в виде двух чисел ci и ki — тип и аргумент команды соответственно (|ki|≤109). Поддерживаемые команды:

+1 (или просто 1): Добавить элемент с ключом ki.
 0: Найти и вывести ki-й максимум.
-1: Удалить элемент с ключом ki.
Гарантируется, что в процессе работы в структуре не требуется хранить элементы с равными ключами или удалять несуществующие элементы. Также гарантируется, что при запросе ki-го максимума, он существует.

Выходные данные
Для каждой команды нулевого типа в выходной файл должна быть выведена строка, содержащая единственное число — ki-й максимум.
*/

using namespace std;

class Node {
 public:
    Node(int x): key(x), left(nullptr), right(nullptr), size(1) {}
    int key;
    int height;
    Node* left;
    Node* right;
    int size;
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
        fix_size(pnode);
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
        cout << indent << pnode->key << "("<< pnode->size << ")" << "\n";
        print(pnode->left, indent);
    }

    int get_height(Node* p) {
        return p ? p->height : 0;
    }

    int get_size(Node* p) {
        return p ? p->size : 0;
    }


    int get_factor(Node* p) {
        return get_height(p->right) - get_height(p->left);
    }

    void fix_height(Node* p) {
        int hl = get_height(p->left);
        int hr = get_height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    void fix_size(Node* p) {
        int size_l = get_size(p->left);
        int size_r = get_size(p->right);
        p->size = size_l + size_r + 1;
    }

    Node* rotate_right(Node* p) { // правый поворот вокруг p
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        fix_size(p);
        fix_size(q);
        return q;
    }

    Node* rotate_left(Node* q) {// левый поворот вокруг q
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        fix_size(q);
        fix_size(p);
        return p;
    }
    Node* balance(Node* p) { // балансировка узла p
        fix_height(p);
        fix_size(p);
        if( get_factor(p) == 2 )
        {
            if( get_factor(p->right) < 0 ) {
                p->right = rotate_right(p->right);
                fix_size(p);
            }
            return rotate_left(p);
        }
        if( get_factor(p)==-2 )
        {
            if( get_factor(p->left) > 0  ) {
                p->left = rotate_left(p->left);
                fix_size(p);
            }
            return rotate_right(p);
        }
        fix_size(p);
        return p; // балансировка не нужна
    }

    Node* delete_min(Node* p) {// удаление узла с минимальным ключом из дерева p
        fix_size(p);
        if( p->left == nullptr )
            return p->right;
        p->left = delete_min(p->left);
        return balance(p);
    }

    int get_k_max(Node* pnode, int k) {
        int size_r = get_size(pnode->right);
        if (size_r == k - 1) return pnode->key;
        if (size_r > k - 1) {
            return (get_k_max(pnode->right, k));
        } else {
            return(get_k_max(pnode->left, k - 1 - size_r));
        }
    }
};


int main()
{
    int query;
    int key;
    Tree tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> query >> key;
        //tree.print(tree.root);
        if (query == 1) {
          tree.root = tree.insert(tree.root, key);
        } else if (query == -1) {
          tree.root = tree.delete_key(tree.root, key);
        } else {

            cout << tree.get_k_max(tree.root, key) << "\n";
        }
        //string indent = "";
        //tree.print(tree.root, indent);
    }
}
