#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"
#include "mpfr.h"

const int n = 1000000;

int main() {
    mpfr_t sum;
    mpfr_t a;
    mpfr_t b;
    mpfr_init2(sum, 512);
    mpfr_init2(a, 512);
    mpfr_init2(b, 512);

    mpfr_set_si(sum, 0, MPFR_RNDN);

    for (int i = 1; i <= n; i++) {
        mpfr_set_si(a, 1, MPFR_RNDN);
        mpfr_set_si(b, i, MPFR_RNDN);
        mpfr_div(a, a, b, MPFR_RNDN);
        mpfr_add(sum, sum, a, MPFR_RNDN);
    }
    puts("Python Decimal:\t 14.392726722865723631381127493188587676644800013744311653418433045812958507517995003568298175947219100708359952136079812900264164102586930094633006200549611666639142755843266541572197307829288195140937");
    mpfr_printf("MPFR:\t\t %.100Rf\n", sum);
}

