# Enter your code here. Read input from STDIN. Print output to STDOUT
from random import randrange

# Contains the possibilites for each digit of the 12-digits solution
possibilities = [[str(i) for i in range(10)] for i in range(12)]
attempts = {}
n = input()

# Avoid problem with test case 3
if n != "":
    n = int(n)
else : 
    n = int(input())
    
# Fill an object containing the test cases in list, key is their score
# Ex : attempts = { "0" : ["123456789012", "234567890123"], "1" : [...] until "3"}
for i in range(n):
    attempt, success = input().split()
    try:
        attempts[success].append(attempt)        
    except KeyError:
        attempts[success] = [attempt]

# If one test case has score 0, all of its digits can be removed from the possibilities
# at the corresponding index
if "0" in attempts:
    for attempt in attempts["0"]:
        for i, e in enumerate(attempt):
            if e in possibilities[i]:
                possibilities[i].remove(e)

# Starting at "000000000000" or better if test cases with 0 were found
string = "".join([p[-1] for p in possibilities])
bestScore = 100

# While we don't have the solution (matching the same difference scores as with test cases)
while bestScore > 0:
    intermediate_best_score, intermediate_best_string = 100, ""
    # We try to change one digit, the one who gives the best score
    # At each step, we check the score of each string if we change only one of its digits
    # Using the digits available in possibilities
    for i in range(12):
        for j in possibilities[i]:
            stringToTest = string[:i] + j + string[i+1:]
            score = 0
            for k in range(1, 4):
                if str(k) in attempts:
                    attempt = attempts[str(k)]
                    for testCase in attempt:
                        intermediateScore = sum([1 for i in range(12) if testCase[i] == stringToTest[i]])
                        score += abs(intermediateScore - k)
                        if score >= intermediate_best_score:
                            break # to gain time and pass the last test cases
                    if score >= intermediate_best_score:
                        break # to gain time and pass the last test cases
            if score < intermediate_best_score:
                intermediate_best_score = score
                intermediate_best_string = stringToTest
    # if the best score does not change (ie: local mininum), we go from a random new combination, and do everything again (at least 10 * 12 = 120 score computations...)
    if intermediate_best_score == bestScore:
        string = "".join([p[randrange(len(p))] for p in possibilities])
    # else, we go on with the changed digit until we get the good solution
    else:
        bestScore = intermediate_best_score
        string = intermediate_best_string

print(string)
