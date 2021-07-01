#include <iostream>
#include <vector>
#include <cctype>
#include <exception>

using namespace std;
enum tokens {
    PLUS           = 0,
    MINUS          = 1,
    MULTIPLY       = 2,
    BRACKET_BEGIN  = 3,
    BRACKET_END    = 4,
    POINT          = 5,
    NUMBER         = 6
};

const string token_values[6] = {"+", "-", "*", "(", ")", "."};

class Lexer {
  public:
    Lexer(string input_) : input(input_), pointer(0) {};
    string input;
    int pointer;
    vector<string> tokens;
    string nextToken() {
        //if (pointer == input.size()) return "";
        string next = input.substr(pointer, 1);
        if ((next == token_values[PLUS]) ||
           (next == token_values[MINUS]) ||
           (next == token_values[MULTIPLY]) ||
           (next == token_values[BRACKET_BEGIN]) ||
           (next == token_values[BRACKET_END]))
        {
            string token = string(next);
            tokens.push_back(token);
            pointer++;
            return token;
        } else if (next == token_values[POINT]) {
          return "";
        } else
        {
            if (!isdigit(next[0])) {
                throw (out_of_range(next));
            } else {
                string number;
                int ndigits = 0;
                while (isdigit(next[0])) {
                    number = number + next;
                    pointer++;
                    next = input.substr(pointer, 1);
                }
                tokens.push_back(number);
                return number;
            }

        }

    }
};




int main()
{
    string str;
    cin >> str;
    Lexer lexer(str);
    string token;
    while ((token = lexer.nextToken()) != "") {
        cout << token << "\n";
    }
    return 0;
}
