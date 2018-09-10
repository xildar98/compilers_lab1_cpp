#include <iostream>
#include <bits/stdc++.h>
#include "parser.cpp"
using namespace std;

int main() {
    if(freopen("../in.txt","r",stdin) == nullptr){
        cerr <<"no file input"<<endl;
        exit(1);
    }
    freopen("../out.txt","w",stdout);
    string text;
    parser parser1; // create parser
    while( getline(cin,text) ){ //read each test
        string result = parser1.get_result(text); // calculate answer
        cout << result<<endl; // print answer
    }

    return 0;
}