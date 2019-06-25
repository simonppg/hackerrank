#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, val;
    int q1;
    int q2_begin, q2_end;
    vector<int> v;
    cin >> n;
    while(n) {
        cin >> val;
        v.push_back(val);
        n--;
    }
    cin >> q1;
    v.erase(v.begin() + q1 - 1);
    cin >> q2_begin;
    cin >> q2_end;
    v.erase(v.begin() + q2_begin - 1, v.begin() + q2_end - 1);
    cout << v.size() << endl;
    for(auto it = v.begin(); it != v.end(); it++){
        cout << *it << " ";
    }

    return 0;
}
