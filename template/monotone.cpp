#include <bits/stdc++.h>
using namespace std;

template <class T>
void monotone(const vector<T>& a) {
    vector<int> st;

    for (int i = 0; i < (int)a.size(); ++i) {
        while (!st.empty() && a[st.back()] > a[i]) {  // 클 때 pop -> 스택은 감소하지 않음(증가상태 유지)
            int j = st.back();
            // pop 직전 처리. ex: int x = a[j];
            st.pop_back();

            // pop 직후 처리. ex: ans[j] = a[i]; / ans_idx[j] = i;
        }
        // push 직전/직후 처리
        st.push_back(i);
    }
}