#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, val;
    vector<int> v;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &val);
        v.push_back(val);
    }

    sort(v.begin(), v.end());

    for(auto i = v.cbegin(); i != v.cend(); ++i) {
        printf("%d ", *i);
    }
    return 0;
}

