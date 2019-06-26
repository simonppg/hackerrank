#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

void format1(double val){
    val = val - ((int)-val + val);
    int temp = val;
    vector<int> v;

    while(val > 16) {
        v.push_back(temp % 16);
        val /= 16;
    }
    if(val > 0)
        v.push_back(val);

    cout << "0x";
    for(auto it = v.rbegin(); it != v.rend(); it++) {
        if(*it < 9)
            cout << *it;
        else
            cout << (char)(*it +87);
    }
    cout << endl;
}

void format2(double val) {
    val = (int)(val * 100 + .5);
    val /= 100;
    std::ostringstream streamObj;
    streamObj.precision(2);
    streamObj << fixed << val;
    string str = streamObj.str();
    int len = 14 - str.length();
    while(len) {
        cout << "_";
        len--;
    }
    cout << (signbit(val) == 0 ? "+" : "-");
    cout << str << endl;
}

void format3(double val) {
    std::ostringstream streamObj;
    streamObj.precision(9);
    streamObj << fixed << scientific << uppercase << val;
    string str = streamObj.str();
    cout << str << endl;
}

int main() {
    int t;
    double a, b, c;

    cin >> t;

    while(t--) {
        cin >> a >> b >> c;
        format1(a);
        format2(b);
        format3(c);
		cout << endl;

cout << hex << left << showbase << nouppercase;
        cout << (long long) a << endl;
        cout << dec << right << setw(15) << setfill('_') << showpos << fixed << setprecision(2);
        cout << b << endl;
        cout << scientific << uppercase << noshowpos << setprecision(9);
        cout << c << endl;
    }

    return 0;
}
