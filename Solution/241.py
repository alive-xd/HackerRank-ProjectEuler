from functools import reduce

def fact(x):
    return sum(set(reduce(list.__add__, ([i, n // i] for i in range(1,
               int(n ** 0.5) + 1) if n % i == 0))))

N = int(input())
res = 0
for n in range(2, N + 1, 2):
    p = fact(n) / n
    if str(p).split('.')[1] == '5':
        res += n
print (res)
