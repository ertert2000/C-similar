#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int>vc;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        vc.push_back(a);
    }
    sort(vc.begin(), vc.end());
    vector<pair<int, int>>sk;
    int ans = 0;
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (a < k) {
            if (a == b) {
                while (k > a) {
                    k -= a;
                }
                if (k == 0) {
                    cout << 0 << '\n';
                    return;
                }
            }
            else {
                sk.emplace_back(a, b);
            }
        }
    }

    return 0;
}
