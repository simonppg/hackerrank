#include <sstream>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

vector<int> parseInts(string stdin_str) {
    vector<int> v;
    char *str = new char [ stdin_str.length() + 1];
    strcpy(str, stdin_str.c_str());
    char *token = strtok(str, ",");
    while(token != 0){
        v.push_back(stoi(token));
        token = strtok(NULL, ",");
    }
    delete [] str;
    return v;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(unsigned int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }

    return 0;
}


