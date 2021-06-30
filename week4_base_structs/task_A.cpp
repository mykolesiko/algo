#include <iostream>
 
using namespace std;
 
struct node
{
    int value;
    int min_value;
    node* next;
};
 
class list
{
    public:
        list(): first(nullptr) {};
        ~list();
        node* back();
        void push(int value);
        bool pop();
 
 
    private:
        node* first;
 
};
 
list :: ~list() {
 /*   if (first == nullptr) return;
    node* ptr = first;
    while (ptr != nullptr) {
        node* ptr_curr = ptr;
        ptr = ptr_curr->next;
        delete(ptr_curr);
    }*/
}
 
void list :: push(int value_) {
    if (first == nullptr)
    {
        first = new node();
        first->value = value_;
        first->next = nullptr;
        first->min_value = value_;
 
    } else {
        node* first_old = first;
        first = new node();
        first->value = value_;
        first->next = first_old;
        if (value_ < first_old->min_value) {
            first->min_value = value_;
        } else {
            first->min_value = first_old->min_value;
        }
 
    }
    return;
}
 
bool list :: pop() {
    if (first == nullptr) return (false);
    node* first_old = first;
    first = first_old->next;
    delete(first_old);
    return (true);
}
 
node* list :: back() {
    return first;
 
}
 
 
 
int main()
{
    list stek;
    int n_opers;
    scanf("%d", &n_opers);
    for (int i = 0; i < n_opers; i++)
    {
        int id_oper;
        scanf("%d", &id_oper);
        switch (id_oper) {
            case 1:
                int value;
                scanf("%d", &value);
                stek.push(value);
                break;
            case 2:
                stek.pop();
                break;
            case 3:
                //int min_value;
                //stek.minimum(min_value);
                printf("%d\n", stek.back()->min_value);
 
        }
    }
    return 0;
}