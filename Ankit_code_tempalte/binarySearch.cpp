A teplate for biarys erach on aswers
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int m;

bool poss(int h) {
    long long wood = 0;
    for (int tree : v) {
        if (tree > h) {
            wood += (tree - h);
        }
    }
    return wood >= m;
}

int main() {
    int n;
    cin >> n >> m;
    v.resize(n);
    
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int low = 0, high = 1e9, res = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (poss(mid)) {
            res = mid;
            low = mid + 1;  // Try for a higher height
        } else {
            high = mid - 1; // Reduce height to get more wood
        }
    }
    
    cout << res << "\n";
}
