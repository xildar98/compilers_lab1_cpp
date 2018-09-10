//
// Created by ildar on 09.09.18.
//

#include <bits/stdc++.h>
#include "parser.cpp"
using namespace std;

void tokenizer_test1(){
    tokenizer tokenizer1;
    tokenizer1.feed("1+33");
    string a0 = tokenizer1.get_next();
    string a1 = tokenizer1.get_next();
    string a2 = tokenizer1.get_next();
    string a3 = tokenizer1.get_next();
    assert(a0 == "1");
    assert(a1 == "+");
    assert(a2 == "33");
    assert(a3 == "end");
}

void tokenizer_test2(){
    tokenizer tokenizer1;
    tokenizer1.feed("22+*38(0()");
    assert(tokenizer1.get_next() == "22");
    assert(tokenizer1.get_next() == "+");
    assert(tokenizer1.get_next() == "*");
    assert(tokenizer1.get_next() == "38");
    assert(tokenizer1.get_next() == "(");
    assert(tokenizer1.get_next() == "0");
    assert(tokenizer1.get_next() == "(");
    assert(tokenizer1.get_next() == ")");
    assert(tokenizer1.get_next() == "end");
    assert(tokenizer1.get_next() == "end");
}

void tokenizer_test3(){
    tokenizer tokenizer1;
    tokenizer1.feed("1+33");
    tokenizer1.feed("((()))))");
    tokenizer1.feed("(+*)33");
    string a0 = tokenizer1.get_next();
    string a1 = tokenizer1.get_next();
    string a2 = tokenizer1.get_next();
    string a3 = tokenizer1.get_next();
    string a4 = tokenizer1.get_next();
    string a5 = tokenizer1.get_next();
    assert(a0 == "(");
    assert(a1 == "+");
    assert(a2 == "*");
    assert(a3 == ")");
    assert(a4 == "33");
    assert(a5 == "end");
}

void lexical_test1(){
    lexem lex;
    lex.feed_text("0138*(+)");
    assert(lex.get_current().first == "0138" && lex.get_current().second == lexema::Integer);
    lex.move_to_next();
    for(int i=0;i<10;++i){
        assert(lex.get_current().first == "*" && lex.get_current().second == lexema::Times);
    }
    lex.move_to_next();
    assert(lex.get_current().first == "(" && lex.get_current().second == lexema::Lp);
    lex.move_to_next();
    assert(lex.get_current().first == "+" && lex.get_current().second == lexema::Plus);
    lex.move_to_next();
    lex.move_to_next();
    assert(lex.get_current().first == "end" && lex.get_current().second == lexema::End);
    lex.move_to_next();
    assert(lex.get_current().first == "end" && lex.get_current().second == lexema::End);
    lex.move_to_next();
    for(int i=0;i<10;++i){
        assert(lex.get_current().first == "end" && lex.get_current().second == lexema::End);
        lex.move_to_next();
    }

}

void lexical_test2(){
    lexem lex;
    lex.feed_text("+111*22+3");
    assert(lex.get_current().first == "+" && lex.get_current().second == lexema::Plus);
    lex.move_to_next();
    for(int i=0;i<10;++i){
        assert(lex.get_current().first == "111" && lex.get_current().second == lexema::Integer);
    }
    lex.move_to_next();
    assert(lex.get_current().first == "*" && lex.get_current().second == lexema::Times);
    lex.move_to_next();
    assert(lex.get_current().first == "22" && lex.get_current().second == lexema::Integer);
    lex.move_to_next();
    assert(lex.get_current().first == "+" && lex.get_current().second == lexema::Plus);
    lex.move_to_next();
    assert(lex.get_current().first == "3" && lex.get_current().second == lexema::Integer);
    lex.move_to_next();
    assert(lex.get_current().first == "end" && lex.get_current().second == lexema::End);
}

void lexical_test3(){
    lexem lex;
    lex.feed_text("*+()");
    assert(lex.get_current().first == "*" && lex.get_current().second == lexema::Times);
    lex.move_to_next();
    assert(lex.get_current().first == "+" && lex.get_current().second == lexema::Plus);
    lex.move_to_next();
    assert(lex.get_current().first == "(" && lex.get_current().second == lexema::Lp);
    lex.move_to_next();
    assert(lex.get_current().first == ")" && lex.get_current().second == lexema::Rp);
    lex.move_to_next();

}

bool contains_error(string a){
    return a.find("ERROR") < a.size();
}

void parser_test1(){
    parser parser1;
    string input = "1+2;";
    string pattern = "NUM PLUS NUM SEMI EOF";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(res == pattern);
}
void parser_test2(){
    parser parser1;
    string input = "1+2; 1+2*3+2;1+3;";

    string pattern = "NUM PLUS NUM SEMI NUM PLUS NUM TIMES NUM PLUS NUM SEMI NUM PLUS NUM SEMI EOF";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(res == pattern);
}

void parser_test3(){

    parser parser1;
    string input = "1+3++;";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(contains_error(res));
}


void parser_test4(){
    parser parser1;
    string input = "1+3;";

    string pattern = "NUM PLUS NUM SEMI EOF";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(res == pattern);
}

void parser_test5(){

    parser parser1;
    string input = ";";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(contains_error(res));
}



void parser_test6(){

    parser parser1;
    string input = "1+;";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(contains_error(res));
}

void parser_test7(){

    parser parser1;
    string input = "+;";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(contains_error(res));
}


void parser_test8(){
    parser parser1;
    string input = "(2+3)+(1+2);";

    string pattern = "LP NUM PLUS NUM RP PLUS LP NUM PLUS NUM RP SEMI EOF";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(res == pattern);
}


void parser_test9(){
    parser parser1;
    string input = "(2+3)+(1+2);2+2;";

    string pattern = "LP NUM PLUS NUM RP PLUS LP NUM PLUS NUM RP SEMI NUM PLUS NUM SEMI EOF";
    auto res = parser1.get_result(input);
    cout << res <<endl;
    assert(res == pattern);
}


void check_test(void (*pt2Func)(void), int test_number){
    try{
        (*pt2Func)();
        cout <<"test #"<<test_number<<" passed OK "<<endl;
    } catch(...) {
        cout <<"test #"<<test_number<<" FAILED"<<endl;
    }
}


int main(){

    int test_number = 1;
    check_test(tokenizer_test1,test_number++);
    check_test(tokenizer_test2,test_number++);
    check_test(tokenizer_test3,test_number++);

    check_test(lexical_test1,test_number++);
    check_test(lexical_test2,test_number++);
    check_test(lexical_test3,test_number++);


    check_test(parser_test1,test_number++);
    check_test(parser_test2,test_number++);
    check_test(parser_test3,test_number++);
    check_test(parser_test4,test_number++);
    check_test(parser_test5,test_number++);
    check_test(parser_test6,test_number++);
    check_test(parser_test7,test_number++);
    check_test(parser_test8,test_number++);
    check_test(parser_test9,test_number++);


}