import math

(un, b) = map(float, input().split())


def function(x, b):
    return math.floor(2 ** (b - x ** 2)) * 10 ** -9


for _ in range(10 ** 5):
    un1 = un
    un = function(un1, b)

print (un + un1)
