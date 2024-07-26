NUMBERS_MAP = dict(IV=4, IX=9, XL=40, XC=90, CD=400, CM=900, I=1, V=5, X=10, L=50, C=100, D=500, M=1000).items()

def to_roman(num: int) -> str:
    roman = ''
    for v, k in sorted(NUMBERS_MAP, key=lambda x: -x[1]):
        roman += num // k * v
        num -= num // k * k
    return roman

def to_arabian(num: str) -> int:
    dec = 0
    for k, v in NUMBERS_MAP:
        oldlen, num = len(num), num.replace(k, '')
        dec += (oldlen - len(num)) * v // len(k)
    return dec
    
[print(to_roman(to_arabian(input()))) for _ in range(int(input()))]
