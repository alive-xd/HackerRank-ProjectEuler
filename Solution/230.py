import os

def find_digit(A, B, n):
    lengths = [len(A)]
    if n <= len(A):
        return A[n-1]
    lengths.append(len(B))
    if n <= len(B):
        return B[n-1]

    idx = 1
    # Building up until we hit total digit length n.
    # Only count length though, do not build the actual string!
    while True:
        idx = idx + 1
        lengths.append(lengths[idx-2] + lengths[idx-1])
        if lengths[idx]  >= n:
            break

    # Going back recursively until we know where exactly to 
    # find digit n. Use the fact that 
    # sequence[i] = [sequence[i-2], sequence[i-1]].
    len_diff = n
    while idx > 1:
        if lengths[idx-2] < len_diff:
            # Digit n is in the second part of the sequence  
            # section currently considered.
            len_diff = len_diff - lengths[idx-2]
            idx = idx - 1
        else:
            # Digit n is in first part of the sequence section 
            # currently considered.
            idx = idx - 2

    if idx == 0:
        return A[len_diff-1]
    else:
        return B[len_diff-1]


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    num_tests = int(input().strip())
    tests = []
    for i in range(num_tests):
        A, B, n_str = input().rstrip().split()
        num = find_digit(A, B, int(n_str))
        fptr.write(str(num) + '\n')

    fptr.close()
