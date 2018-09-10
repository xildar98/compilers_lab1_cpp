//
// Created by ildar on 09.09.18.
//

#ifndef COMPILERS_HW1_LEX_H
#define COMPILERS_HW1_LEX_H

#include <iostream>
#include <cassert>
#include "tokenizer.cpp"

using namespace std;
enum class lexema { // type of token
    Integer, Plus, Times, Lp, Rp, Semi,  End
};

class lexem {
private:
    tokenizer tokeniz; // tokenizer
    string cur_token; // last token


    bool is_integer(string &value) {
        if (!value.empty()) {
            for (char c:value) {
                if (c >= '0' && c <= '9') {
                    continue;
                }
                return false;
            }
            return true;
        }
        return false;
    }

    bool is_lp(string &value) {
        return value == "(";
    }
    bool is_rp(string &value) {
        return value == ")";
    }
    bool is_semi(string &value) {
        return value == ";";
    }

    bool is_plus(string &value) {
        return value == "+";
    }

    bool is_times(string &value) {
        return value == "*";
    }

    bool is_end(string &value) {
        return value == "end";
    }


public:


    lexem() {

    }

    void clear() { // delete text
        tokeniz.clear();
    }

    void feed_text(string text) { // feed new input
        tokeniz.feed(text);
        move_to_next();
    }


    void move_to_next() { // move iterator to next token
        cur_token = tokeniz.get_next();
    }

    pair<string, lexema> get_current() { // get current token and its lexema type
        string value = cur_token;
        lexema type;
        if (is_integer(value)) {
            type = lexema::Integer;
        } else if (is_times(value)) {
            type = lexema::Times;
        } else if (is_plus(value)) {
            type = lexema::Plus;
        } else if (is_end(value)) {
            type = lexema::End;
        } else if (is_lp(value)) {
            type = lexema::Lp;
        } else if (is_rp(value)) {
            type = lexema::Rp;
        } else if (is_semi(value)) {
            type = lexema::Semi;
        } else {
            cerr << "No such type of lexema " << value << endl;
            exit(1);
        }
        return {value, type};
    }

    lexema get_current_lexema() {
        return get_current().second;
    }


};


#endif //COMPILERS_HW1_LEX_H