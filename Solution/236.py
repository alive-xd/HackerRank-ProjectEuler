from itertools import *
import math

n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
n_a = []
n_b = []
sa = sum(a)
sb = sum(b)
flag = 0
for i in range(n):
    n_a.append(list(range(1, a[i] + 1)))
    n_b.append(list(range(1, b[i] + 1)))

for i in product(*n_a):
    for j in product(*n_b):
        count = 0
        p = sum(i) * sb
        q = sum(j) * sa
        m = math.gcd(p, q)
        (p, q) = (p // m, q // m)

        if p / q <= 1:
            continue

        for k in range(n):
            r = j[k] * a[k]
            s = i[k] * b[k]

            t = math.gcd(r, s)
            (r, s) = (r // t, s // t)

            if r != p or s != q:
                break
            else:
                count += 1

            if count == n:
                flag = 1
                print '{}/{}'.format(r, s)
                break

        if flag == 1:
            break

    if flag == 1:
        break