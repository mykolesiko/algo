#include <iostream>
#include <vector>
#include <random>
#include <time.h>

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
    bool rev = false;
};




class Tree {
 public:
    Tree() : root(nullptr) {}
    Node* root;

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


    void push(Node *p) {
        if (!p) {
            return;
        }
        if (p->rev) {
            swap(p->left, p->right);
            if (p->left) {
                p->left->rev ^= 1;
            }
            if (p->right) {
                p->right->rev ^= 1;
            }
            p->rev = false;
        }
    }

    void reverse(Node *t) {
        if (t) {
            t->rev ^= 1;
        }
    }


    pair<Node*, Node*> split(Node* pnode, int index) {
        if (pnode == nullptr) {
            //fix_size(pnode);
            return make_pair(nullptr, nullptr);
        }
        push(pnode);
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
        push(t1);
        push(t2);
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

    void make_reverse(Node* pnode, int l, int r) {
        pair<Node*, Node*> result1 = split(pnode, l - 1);
        pair<Node*, Node*> result2 = split(result1.second, r - l + 1);
        reverse(result2.first);
        Node* root1 = merge(result2.first, result2.second);
        root = merge(result1.first, root1);
    }

    void print(Node* pnode) {
        if (pnode == nullptr) return;
        push(pnode);
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
    int n, m;
    cin >> n >> m;
    int index;
    for (index= 0; index < n; index++) {
        tree.root = tree.add(tree.root, index, index + 1);
    }
    //tree.print(tree.root);
    //cout << "\n";
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        tree.make_reverse(tree.root, l, r);
        //tree.print(tree.root);
        //cout << "\n";
    }
    //cout << tree.get_size(tree.root) << "\n";
    tree.print(tree.root);
    cout << "\n";
}
