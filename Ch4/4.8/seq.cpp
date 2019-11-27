#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> is(1000005);
    for (int i = 2; i <= sqrt(1000000) + 1; i++) {
        if (is[i]) continue;
        for (int j = i + i; j <= 1000000; j += i) {
            is[j] = 1;
        }
    }
    int cnt = 0;
    for (int i = 2; i <= 1000000; i++) {
        if (!is[i] && !is[i + 2]) 
            cnt++;
    }
    printf("%d\n", cnt);
}
