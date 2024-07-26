def compute(n, k):

    (subsets, offsets) = ([0] * k, [0] * k)

    for i in range(1, n + 1):
        subsets[pow(i, i, k)] += 1

    offsets[0] = 1
    for i in range(k):
        for j in range(subsets[i]):
            offsets = [(offsets[j] + offsets[j - i]) % 10 ** 9 for j in
                       range(k)]

    return str(offsets[0] - 1)


if __name__ == '__main__':

    (n, k) = map(int, input().split(' '))
    print compute(n, k)
