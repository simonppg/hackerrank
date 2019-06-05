#include <iostream>
#include <string>

using namespace std;

int main() {
    string str_a, str_b;
    cin >> str_a;
    cin >> str_b;
    cout << str_a.length() << " " << str_b.length() << endl;
    cout << str_a + str_b << endl;
    str_a[0] = str_a[0] + str_b[0];
    str_b[0] = str_a[0] - str_b[0];
    str_a[0] = str_a[0] - str_b[0];
    cout << str_a << " " << str_b << endl;
    return 0;
}
