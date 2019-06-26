#include <iostream>
#include <set>

using namespace std;

int main() {
    int q, type, val;
    set<int> s;

    cin >> q;

    while(q){
        cin >> type >> val;
        if(type == 1)
            s.insert(val);
        else if(type == 2)
            s.erase(val);
        else {
            auto it = s.find(val);
            if(it != s.end())
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        q--;
    }
    return 0;
}
