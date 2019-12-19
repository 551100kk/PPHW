import random
import sys

n = int(sys.argv[1])
m = int(sys.argv[2])

print(n, m)
for i in range(n):
    for j in range(m):
        print(random.choice('.*'), end='')
    print()