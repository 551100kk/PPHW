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
    int maxval = 1;
    for (int i = 3; i <= 1000000; i++) {
        if (is[i]) continue;
        for (int j = i + 2; j <= 1000000; j += 2) {
            if (is[j]) continue;
            maxval = max(maxval, j - i);
            break;
        }
    }
    printf("%d\n", maxval);
}
