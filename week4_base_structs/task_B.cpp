#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

const int N_CAPACITY = 100;

class Vector_my {
 public:
        Vector_my(int capacity_): elements(new int[capacity_]), \
                  capacity(capacity_), size(0) {}
        ~Vector_my();
        void push(int value);
        bool pop(int& value);
 private:
        int* elements;
        int size;
        int capacity;
};

Vector_my :: ~Vector_my() {
    if (elements != nullptr) delete elements;
}

void Vector_my :: push(int value_) {
    if (size + 1 >= capacity) {
        capacity = capacity * 2;
        int* elements_new = new int[capacity];
        memcpy(elements_new, elements, sizeof(int) * size);
        delete [] elements;
        elements = elements_new;
    }
    elements[size] = value_;
    size++;
}

bool Vector_my :: pop(int& last) {
    if (size == 0) return (false);
    last = elements[size - 1];
    size--;
    if (size <= capacity / 4) {
        int* elements_new = new int[capacity / 2];
        memcpy(elements_new, elements, sizeof(int) * size);
        delete [] elements;
        elements = elements_new;
    }
}

bool is_number(string str, int& number) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return (false);
    }
    number = atoi(str.c_str());
    return (true);
}

int main() {
    Vector_my stek(N_CAPACITY);
    string operand;
    int number;
    int number1, number2;
    while (cin >> operand) {
       if (is_number(operand, number))  {
           stek.push(number);
       } else {
           stek.pop(number2);
           stek.pop(number1);
           if (operand == "+") {
               stek.push(number1 + number2);
           } else if (operand == "-") {
               stek.push(number1 -  number2);
           } else {
               stek.push(number1 * number2);
           }
       }
    }
    stek.pop(number);
    printf("%d\n", number);
    return 0;
}
