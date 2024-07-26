n = int(input())

# a , b =0

a = 0
for i in range(n):
    for j in range(n):
        p = pow(i, j)

        # print (p)

        p = str(p)
        p = list(p)

        q = 0

        for k in range(len(p)):
            q = q + int(p[k])

        if a < q:
            a = q

print(a)
