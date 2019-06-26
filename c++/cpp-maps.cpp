#include <iostream>
#include <map>

using namespace std;

int main() {
    int q, type, marks;
    string name;
    map<string, int> mp;

    cin >> q;

    while(q) {
        cin >> type;

        if(type == 1) {
            cin >> name >> marks;
            auto it = mp.find(name);
            if(it != mp.end())
                it->second += marks;
            else
                mp.insert(make_pair(name, marks));
        } else {
            cin >> name;
            if(type == 2) {
                auto it = mp.find(name);
                if(it != mp.end())
                    it->second = 0;
            } else {
                auto it = mp.find(name);
                if(it != mp.end())
                    cout << it->second << endl;
                else
                    cout << 0 << endl;
            }
        }

        q--;
    }
    return 0;
}
