#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 각 조건 집합들의 교집합 크기를 계산하는 함수만 문제별로 바꾸면 됨.
ll intersection_size(const vector<int>& idx) {
    // 예시용 더미
    // 실제 문제에 맞게 구현
    return 0;
}

ll inclusion_exclusion(int m) {
    ll ans = 0;

    for (int mask = 1; mask < (1 << m); mask++) {
        vector<int> idx;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) idx.push_back(i);
        }

        ll val = intersection_size(idx);
        if ((int)idx.size() % 2 == 1) ans += val;
        else ans -= val;
    }
    return ans;
}

int main() {

}