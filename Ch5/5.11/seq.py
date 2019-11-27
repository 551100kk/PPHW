from decimal import *

getcontext().prec = 200

ans = Decimal(0)
for i in range(1000000):
    ans += Decimal(1) / Decimal(i + 1)

print(ans)

