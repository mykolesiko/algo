#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


const int LETTERS_MAX = 40; //максимальное число букв
const int NODES_MAX =  1e6;
const int WORD_LEN_MAX = 30;


struct node {
    int next[LETTERS_MAX];
    int is_terminal = 0;
};

node bor[NODES_MAX];
int sz = 1;
vector<bool> is_in_text;

void insert(const string& str, int index) {
    int v = 0;
    for (int i = 0; i < str.length(); i++) {
       char c = str[i] - 'a';
       if (bor[v].next[c] == -1) {
           fill(bor[sz].next, bor[sz].next + LETTERS_MAX, -1);
           bor[v].next[c] = sz++;
       }
       v = bor[v].next[c];
    }
    bor[v].is_terminal = index;
}

void contains(const string& str) {
    int v = 0;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i] - 'a';
        int index = bor[v].is_terminal;
        if (index > 0) {
            is_in_text[index - 1] = true;
        }
        if (bor[v].next[c] == -1) {
           return;
        }
        v = bor[v].next[c];
    }
    int index = bor[v].is_terminal;
    if (index > 0) {
        is_in_text[index - 1] = true;
    }
}



int main()
{
    string Text;
    int nwords;
    vector<string> words;
    cin >> Text;
    cin >> nwords;
    is_in_text.resize(nwords, 0);
    fill(bor[0].next, bor[0].next + LETTERS_MAX, -1);

    for (int i = 0; i < nwords; i++) {
      string temp;
      cin >>  temp;
      words.push_back(temp);
      insert(temp, words.size());
    }

    int word_min_len = WORD_LEN_MAX;
    for (int i = 0; i < Text.length(); i++) {
        string substr = Text.substr(i, (size_t)(min(Text.length() - i, word_min_len)));
        contains(substr);
    }

    for (int i = 0; i < nwords; i++) {
        if (is_in_text[i]) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << " \n";
        }
    }

    return 0;
}
