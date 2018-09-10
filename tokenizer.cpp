//
// Created by ildar on 09.09.18.
//

#ifndef COMPILERS_HW1_TOKENIZER_H
#define COMPILERS_HW1_TOKENIZER_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class tokenizer {
private:
    vector<char> operator_array;
    string text; // input
    int top; // current iterator

public:
    tokenizer() {
        operator_array = {'+','(', ')', '*',';'};
        clear();
    }

    bool is_operator(char x) { // checking for not being digit
        //  cout << x <<" "<<count(operator_array.begin(),operator_array.end(), x) <<endl;
        return count(operator_array.begin(), operator_array.end(), x);
    }

    void clear() { // delete old text
        top = 0;
        text = "";
    }

    void feed(string input) { // update text
        clear();
        for (char c:input) {
            if (c == ' ') {
                continue;
            }
            text.push_back(c);
        }
    }

    string get_next() { // get next token
        if (top >= text.size()) {
            return "end";
        }
        string res = "";
        res.push_back(text[top++]);
        if (is_operator(res[0]))
            return res;
        for (; top < text.size(); ++top) {
            if (is_operator(text[top]))
                break;
            res.push_back(text[top]);
        }
        return res;
    }
};

#endif //COMPILERS_HW1_TOKENIZER_H