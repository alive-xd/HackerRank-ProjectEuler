from math import ceil, floor

def balance_check(num, b):
    remainder_list = list()
    while num != 0:
        (quotient, r) = divmod(num, b)
        remainder_list.insert(0, r)
        num = quotient
    l1 = len(remainder_list)
    if sum(remainder_list[:int(ceil(l1 / 2))]) \
        == sum(remainder_list[int(floor(l1 / 2)):]):  # sum_first == sum_last
        return True
    return False

B, L = map(int, input().split())
n_digits = list(map(int, input().split()))
n_digits = n_digits[::-1]
num_in_base_10 = 0

for _ in range(len(n_digits)):
    num_in_base_10 += n_digits[_] * (B ** _)

sum_of_balanced_numbers = 0
num_of_balanced_numbers = 0

for i in range(1, num_in_base_10 + 1):
    check = balance_check(i, B)

    if check:
        sum_of_balanced_numbers += i
        num_of_balanced_numbers += 1

modulo = 1004535809

print(num_of_balanced_numbers % modulo, sum_of_balanced_numbers % modulo, end="")
