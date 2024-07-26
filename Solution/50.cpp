#include <iostream>
#include <vector>
#include <cmath>

std::vector<unsigned int> prs;
std::vector<unsigned long long> prSum;

unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long mdlo) {
    if (a <= 0xFFFFFFF && b <= 0xFFFFFFF) {
        return (a * b) % mdlo;
    }
    unsigned long long result = 0;
    unsigned long long factor = a % mdlo;
    while (b > 0) {
        if (b & 1) {
            result += factor;
            if (result >= mdlo) {
                result %= mdlo;
            }
        }
        factor <<= 1;
        if (factor >= mdlo) {
            factor %= mdlo;
        }
        b >>= 1;
    }
    return result;
}

unsigned long long powmod(unsigned long long base, unsigned long long expo, unsigned long long mdlo) {
    unsigned long long result = 1;
    while (expo > 0) {
        if (expo & 1) {
            result = mulmod(result, base, mdlo);
        }
        base = mulmod(base, base, mdlo);
        expo >>= 1;
    }
    return result;
}

bool isPrime(unsigned long long p) {
    const unsigned int biPri = (1 << 2) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19) | (1 << 23) | (1 << 29);
    if(p < 31) {
        return (biPri & (1 << p)) != 0;
    }
    if(p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 || p % 11 == 0 || p % 13 == 0 || p % 17 == 0) {
        return false;
    }
    if(p < 17 * 19) {
        return true;
    }
    const unsigned int tesAg1[] = {377687, 0};
    const unsigned int tesAg2[] = {31, 73, 0};
    const unsigned int tesAg3[] = {2, 7, 61, 0};
    const unsigned int tesAg4[] = {2, 13, 23, 1662803, 0};
    const unsigned int tesAg7[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
    const unsigned int* tesAgst = tesAg7;
    
    if (p < 5329) {
        tesAgst = tesAg1;
    } else if(p < 9080191) {
        tesAgst = tesAg2;
    } else if(p < 4759123141ULL) {
        tesAgst = tesAg3;
    } else if(p < 1122004669633ULL) {
        tesAgst = tesAg4;
    }

    auto d = p - 1;
    d >>= 1;
    unsigned int shift = 0;
    while ((d & 1) == 0) {
        shift++;
        d >>= 1;
    }
    do {
        auto x = powmod(*tesAgst++, d, p);
        if (x == 1 || x == (p - 1)) {
            continue;
        }
        bool mPrime = false;
        for(unsigned int r = 0; r < shift; r++) {
            x = powmod(x, 2, p);
            if(x == 1) {
                return false;
            }
            if(x == (p - 1)) {
                mPrime = true;
                break;
            }
        }
        if(!mPrime) {
            return false;
        }
    } while(*tesAgst != 0);
    return true;
}

void morePrimes(unsigned int num) {
    if (prs.empty()) {
        prs.reserve(4 * std::pow(10, 5));
        prSum.reserve(4 * std::pow(10, 5));
        prs.push_back(2);
        prs.push_back(3);
        prSum.push_back(2);
    }
    for (auto i = prs.back() + 2; prs.size() <= num; i += 2) {
        bool isPrime = true;
        for (auto x : prs) {
            if ((x * x) > i) {
                break;
            }
            if ((i % x) == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            prs.push_back(i);
        }
    }
    for (auto i = prSum.size(); i < prs.size(); i++) {
        prSum.push_back(prSum.back() + prs[i]);
    }
}

int main() {
    const unsigned int ppb = std::pow(10, 4);
    morePrimes(ppb);
    unsigned int T;
    std::cin >> T;
    while (T--) {
        unsigned long long N = std::pow(10, 6);
        std::cin >> N;
        unsigned long long best = 2;
        unsigned int maxLength = 0;
        unsigned int start = 0;
        while (prs[start] <= 131 && prs[start] <= N) {
            unsigned long long subtract = 0;
            if (start > 0) {
                subtract = prSum[start - 1];
            }
            unsigned int pos = start + maxLength;
            while (prSum[pos] - subtract <= N) {
                pos++;
                if (pos + 100 >= prs.size()) {
                    morePrimes(prs.size() + ppb);
                }
            }
            pos--;
            while ((pos - start) > maxLength) {
                unsigned long long sum = prSum[pos] - subtract;
                if (isPrime(sum)) {
                    maxLength = pos - start;
                    best = sum;
                    break;
                }
                pos--;
            }
            start++;
        }
        if (best >= 2) {
            maxLength++;
        }
        std::cout << best << " " << maxLength << std::endl;
    }
    return 0;
}
