n = int(input())
import math
l = input().split()
s = ''.join(l)
k = ['0'] * (2 * n - 1)
flag = 0
for i in range(0, len(k), 2):
    k[i] = l[flag]
    flag += 1
k = ''.join(k)
k = int(k)
i = int(math.sqrt(k))

while True:
    k = i ** 2
    k = str(k)
    if k[::2] == s:
        print (i)
        break
    i += 1
