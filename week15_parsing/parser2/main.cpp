#include <iostream>
#include <vector>
#include <cctype>
#include <exception>
#include <math.h>

using namespace std;

enum tokens {
    PLUS           = 0,
    MINUS          = 1,
    MULTIPLY       = 2,
    BRACKET_BEGIN  = 3,
    BRACKET_END    = 4,
    POINT          = 5,
    PODAROK_BRACKET_BEGIN = 6,
    SNEGUROCHKA    = 7,
    MOROZ          = 8,
    DEDMOROZ       = 9,
    DIVIDE         = 10,
    NUMBER         = 11
};

const string token_values[11] = {"+", "-", "*", "(", ")", ".", "Podarok(", "Snegurochka", "Moroz", "Ded Moroz", "\\"};

class Lexer {
  public:
    Lexer(string input_) : input(input_), pointer(0) {};
    string input;
    int pointer;
    vector<string> tokens;
    string nextToken(bool look) {
        int pointer_old = pointer;
        string next = input.substr(pointer, 1);
        if ((next == token_values[PLUS]) ||
           (next == token_values[MINUS]) ||
           (next == token_values[MULTIPLY]) ||
           (next == token_values[DIVIDE]) ||
           (next == token_values[BRACKET_BEGIN]) ||
           (next == token_values[BRACKET_END]))
        {
            string token = string(next);
            tokens.push_back(token);
            if (!look) {
                pointer++;
            }
            return token;
        } else if (next == token_values[POINT]) {
          return "";
        } else
        {
            if (!isdigit(next[0])) {
                if (next == "S") {
                  size_t pos =  input.find(token_values[SNEGUROCHKA], pointer_old);
                  if (pos != string::npos) {
                      if (!look) {
                          pointer += token_values[SNEGUROCHKA].length();
                      }
                      return ("10");// (token_values[SNEGUROCHKA]);
                  } else {
                      throw (out_of_range(next));
                  }
                } else if (next == "M") {
                    size_t pos =  input.find(token_values[MOROZ], pointer_old);
                    if (pos != string::npos) {
                        if (!look) {
                            pointer += token_values[MOROZ].length();
                        }
                        return ("-30");//(token_values[MOROZ]);
                    } else {
                        throw (out_of_range(next));
                    }
                } else if (next == "D") {
                    size_t pos =  input.find(token_values[DEDMOROZ], pointer_old);
                    if (pos != string::npos) {
                        if (!look) {
                            pointer += token_values[DEDMOROZ].length();
                        }
                        return ("2020"); //(token_values[DEDMOROZ]);
                    } else {
                        throw (out_of_range(next));
                    }
                } else if (next == "P") {
                    size_t pos =  input.find(token_values[PODAROK_BRACKET_BEGIN], pointer_old);
                    if (pos != string::npos) {
                        if (!look) {
                            pointer += token_values[PODAROK_BRACKET_BEGIN].length();
                        }
                        return (token_values[PODAROK_BRACKET_BEGIN]);
                    } else {
                        throw (out_of_range(next));
                    }
                } else
                  throw (out_of_range(next));
            } else {
                string number;
                int ndigits = 0;
                while (isdigit(next[0])) {
                    number = number + next;
                    pointer++;
                    next = input.substr(pointer, 1);
                }
                if (look) {
                    pointer = pointer_old;
                }
                return number;
            }
        }
    }
};

class Wrong {
};

class Parser {
 public:
    Parser(Lexer lex_): lex(lex_) {};
    Lexer lex;
    bool finished;
   // long long expr();
    long long factor() {
        string next = lex.nextToken(false);
        long long answer;
        if (next == token_values[BRACKET_BEGIN]) {
            //pos++;
            // если выражение в скобках, то рекурсивно переходим на обработку подвыражения типа Е
            long long answer = expr();
            string closingBracket;
            string next = lex.nextToken(false);
            if (next != "") {
                closingBracket = next;
            } else {
                throw new Wrong();
            }
            if (closingBracket == token_values[BRACKET_END]) {
                //pos++;
                return answer;
            }
            throw new Wrong();
        }

        if (next == token_values[PODAROK_BRACKET_BEGIN]) {
            //pos++;
            // если выражение в скобках, то рекурсивно переходим на обработку подвыражения типа Е
            long long answer = expr();
            string closingBracket;
            string next = lex.nextToken(false);
            if (next != "") {
                closingBracket = next;
            } else {
                throw new Wrong();
            }
            if (closingBracket == token_values[BRACKET_END]) {
                //pos++;
                if (answer > 0) {
                    return (answer + 5);
                }
                else {
                    return (-answer);
                }
            }
            throw new Wrong();
        }

        //pos++;
        // в противном случае токен должен быть числом

        return (stoll(next, nullptr, 10));
    }

    long long term() {
        long long first = factor();
        string token;
        while ((token = lex.nextToken(true)) != "") {
            if ((token != token_values[MULTIPLY]) && (token != token_values[DIVIDE])) {
                break;
            }
            lex.nextToken(false);
            long long second = factor();
            if (token == token_values[MULTIPLY]) {
                first *= second;
            } else {
                first /= second;
            }
        }
        return first;

    }

    long long expr() {
        long long first = term();
        string token;
        while ((token = lex.nextToken(true)) != "") {
            if ((token != token_values[PLUS]) && (token != token_values[MINUS])) {
                break;
            }
            lex.nextToken(false);
            long long second = term();
            if (token == token_values[PLUS]) {
                first += second;
            } else {
                first -= second;
            }
        }
        return first;
    }

    long long parse() {
        //Lexer lex(input);
        long long answer = expr();
        string next = lex.nextToken(true);
        if (next != "") {
            throw new Wrong();
        }
        return answer;
    }

};

int main() {
    string input;
    getline(cin, input);

    Lexer lexer(input);
    Parser parser(lexer);
    long long result;
    try {
        result  = parser.parse();
    }
    catch (...) {
        cout << "WRONG";
        return (0);
    }
    cout << result;
    return (0);
}



