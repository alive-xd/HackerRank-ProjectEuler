#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cmath>

unsigned int N = 7;
unsigned int K = 3;
unsigned int L = 7;
std::map < std::string, std::vector < unsigned int >> M;
unsigned int smPrime = 99999999;

void match(unsigned int num, std::string & regex, unsigned int dig, unsigned int howOften, unsigned int startPos = 0) {
  char asDig = dig + '0';
  for (unsigned int i = startPos; i < N; i++) {
    if (regex[i] != asDig) {
      continue;
    }
    if (i == 0 && asDig == '0') {
      continue;
    }
    regex[i] = '.';
    if (howOften == 1) {
      auto & addTo = M[regex];
      addTo.push_back(num);
      if (addTo.size() >= L && addTo.front() < smPrime) {
        smPrime = addTo.front();
      }
    } else {
      match(num, regex, dig, howOften - 1, i + 1);
    }
    regex[i] = asDig;
  }
}

int main() {
  std::cin >> N >> K >> L;
  unsigned int minNum = 1;
  for (unsigned int i = 1; i < N; i++) {
    minNum *= 10;
  }
  unsigned int maxNum = minNum * 10 - 1;
  std::vector < bool > primes(maxNum, true);
  primes[0] = primes[1] = false;
  for (unsigned int i = 2;
    (i * i) <= maxNum; i++) {
    if (primes[i]) {
      for (unsigned j = 2 * i; j <= maxNum; j += i) {
        primes[j] = false;
      }
    }
  }
  for (unsigned int i = minNum; i <= maxNum; i++) {
    if (primes[i]) {
      auto strNum = std::to_string(i);
      for (unsigned int dig = 0; dig <= 9; dig++) {
        match(i, strNum, dig, K);
      }
      if (N == 7) {
        if (K == 1 && i > 2 * std::pow(10, 6)) {
          break;
        }
        if (K == 2 && i > 3 * std::pow(10, 6)) {
          break;
        }
      }
    }
  }
  std::string mini;
  for (auto m: M) {
    if (m.second.size() < L) {
      continue;
    }
    if (m.second.front() != smPrime) {
      continue;
    }
    std::string s;
    for (unsigned i = 0; i < L; i++) {
      s += std::to_string(m.second[i]) + " ";
    }
    if (mini > s || mini.empty()) {
      mini = s;
    }
  }
  std::cout << mini << std::endl;
  return 0;
}