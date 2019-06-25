#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, q, val;
    vector<int> v;
    cin >> n;
    while(n) {
        cin >> val;
        v.push_back(val);
        n--;
    }

    cin >> q;

    vector<int>::iterator it;
    while(q){
        cin >> val;
        it = lower_bound(v.begin(), v.end(), val);
        if(val == *it)
            cout << "Yes ";
        else
            cout << "No ";
        cout << (it - v.begin() + 1) << endl;
        
        q--;
    }

    return 0;
}
