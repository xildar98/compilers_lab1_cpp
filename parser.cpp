//
// Created by ildar on 09.09.18.
//

#ifndef COMPILERS_HW1_PARSER_H
#define COMPILERS_HW1_PARSER_H

#include "lex.cpp"

class parser {
private:
    lexem lex;
    string result = "";

    void advance(){
        lex.move_to_next();
    }

    void expression() {
        term();
        expr_prime();
        /** YOUR CODE HERE */
    }

    void term() {
        factor();
        term_prime();

    }



    void expr_prime() {
        /* expression' -> PLUS term expression'
         *              | epsilon
         */
        if (lex.get_current_lexema() == lexema::Plus) {
            result+="PLUS ";
            advance();
            term();
            expr_prime();
        }

        /** YOUR CODE HERE */
    }

    void term_prime() {
        /* term' -> TIMES factor term'
         *       |   epsilon
         */
        if (lex.get_current_lexema() == lexema::Times) {
            result+="TIMES ";
            advance();
            factor();
            term_prime();
        }


        /** YOUR CODE HERE */
    }

    void factor() {
        /* factor   ->    NUM_OR_ID
         *          |     LP expression RP
         */
        if (lex.get_current_lexema() == lexema::Integer) {
            result+="NUM ";
            advance();
        } else if (lex.get_current_lexema() == lexema::Lp) {
            result+="LP ";
            advance();
            expression();

            if (lex.get_current_lexema() == lexema::Rp) {
                result+="RP ";
                advance();
            } else {
                result+="ERROR ";
            }

        } else {
            result+="ERROR ";
        }
        /** YOUR CODE HERE */
    }

    void statements() {

        expression();

        if (lex.get_current_lexema() == lexema::Semi) {
            result+="SEMI ";
            advance();

            if(lex.get_current_lexema() == lexema::End){
                result+="EOF";
            } else{
                statements();
            }
        } else{
            result+="ERROR ";
            return;
        }
    }

public:
    string get_result(string input){
        lex.feed_text(input);
        result = "";

        statements();
        return result;
    }
};

#endif //COMPILERS_HW1_PARSER_H
