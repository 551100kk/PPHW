#include <bits/stdc++.h>
using namespace std;

const int n = 1000000;

long double f(int i) {
    long double x;
    x = (long double) i / (long double) n;
    return 4.0 / (1.0 + x * x);
}

int main() {
    long double area = f(0) - f(n);
    for (int i = 1; i <= n / 2; i++)
        area += 4.0 * f(2 * i - 1) + 2 * f(2 * i);
    area /= (3.0 * n);
    puts("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");
    printf("%.30Lf\n", area);
}
