                              #include <iostream>

using std::cin;
using std::cout;
using std::string;

const int N_CAPACITY = 100000;

class Deque_my {
 public:
    Deque_my(int capacity_):  begin(nullptr), \
        begin_capacity(new int[capacity_]), \
        end(nullptr), size(0), capacity(capacity_) {}
    ~Deque_my();
    void push(int value);
    bool pop(int& value);
 private:
    int* begin_capacity;
    int* begin;
    int* end;
    int size;
    int capacity;
};

Deque_my :: ~Deque_my() {
    if (begin_capacity != nullptr) delete [] begin_capacity;
}

void Deque_my :: push(int value_) {
    if (size >= capacity) {
        int* begin_capacity_new = new int[capacity * 2];
        if (end - begin <=0) {
            int size2 = (end - begin_capacity);
            int size1 = size - size2;
            memcpy(begin_capacity_new, begin, sizeof(int) * size1);
            memcpy(begin_capacity_new + size1, begin_capacity, \
                   sizeof(int) * size2);
        } else {
            memcpy(begin_capacity_new, begin, sizeof(int) * size);
        }
        capacity = capacity * 2;
        delete [] begin_capacity;
        begin = begin_capacity = begin_capacity_new;
        *(begin_capacity + size) = value_;
        size++;
        end = begin_capacity + size;
    } else {
       if (size == 0) {
           begin = end = begin_capacity;
       }
       (*end) = value_;
       size++;
       end  = begin + size % capacity;
    }
}

bool Deque_my :: pop(int& last) {
    if (size == 0) return (false);
    /*if (size <= capacity / 4) {
        capacity = capacity / 2;
        int* begin_capacity_new = new int[capacity];
        memcpy(begin_capacity_new, begin_capacity, sizeof(int) * capacity);
        begin = begin_capacity_new + (begin - begin_capacity);
        end = begin_capacity_new + (end - begin_capacity);
        delete [] begin_capacity;
        begin_capacity = begin_capacity_new;
    }*/
    last = (*begin);
    begin = begin_capacity + (begin -  begin_capacity + 1) % capacity;
    size--;
}

int main() {
     int n_opers;
     Deque_my deq(N_CAPACITY);
     scanf("%d", &n_opers);
     for (int i = 0 ; i < n_opers; i++) {
         char oper;
         cin >> oper;
         if (oper == '+') {
           int value_;
           cin >> value_;
           deq.push(value_);
         } else {
            int value_;
            deq.pop(value_);
            printf("%d\n", value_);
         }
     }
}
