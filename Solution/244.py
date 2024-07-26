def getNextSteps(currentPosition):
    # Return all possible next steps
    nextSteps = []
    # Previous commands
    cmds = currentPosition[0]
    # Current matrix situation
    matrix = currentPosition[1]
    # White case position
    w = currentPosition[2]
    
    # Try Down move
    if w[0] > 0 and cmds[-1] != "U":
        m1 = matrix.copy()
        m1[w[0]], m1[w[0]-1] = m1[w[0]][:w[1]] + m1[w[0]-1][w[1]] + m1[w[0]][w[1]+1:], m1[w[0]-1][:w[1]] + m1[w[0]][w[1]] + m1[w[0]-1][w[1]+1:]
        nextSteps.append([cmds+"D", m1, [w[0]-1, w[1]]])
    # Try Up move
    if w[0] < n - 1 and cmds[-1] != "D":
        m2 = matrix.copy()
        m2[w[0]], m2[w[0]+1] = m2[w[0]][:w[1]] + m2[w[0]+1][w[1]] + m2[w[0]][w[1]+1:], m2[w[0]+1][:w[1]] + m2[w[0]][w[1]] + m2[w[0]+1][w[1]+1:]
        nextSteps.append([cmds+"U", m2, [w[0]+1, w[1]]])
    # Try Right move
    if w[1] > 0 and cmds[-1] != "L":
        m3 = matrix.copy()
        left = m3[w[0]][w[1]-1]
        right = m3[w[0]][w[1]]
        m3[w[0]] = m3[w[0]][:w[1]-1] + right + left + m3[w[0]][w[1]+1:]
        nextSteps.append([cmds+"R", m3, [w[0], w[1]-1]])
    # Try Left move
    if w[1] < n - 1 and cmds[-1] != "R":
        m4 = matrix.copy()
        left = m4[w[0]][w[1]]
        right = m4[w[0]][w[1]+1]
        m4[w[0]] = m4[w[0]][:w[1]] + right + left + m4[w[0]][w[1]+2:]
        nextSteps.append([cmds+"L", m4, [w[0], w[1]+1]])
    return nextSteps

def addToCheckSum(begin, end):
    # Compute checksum for a path (given the beginning and the end)
    checksum = 0
    for move in begin[0][1:]:
        checksum = (checksum * 243 + ord(move)) % 100000007
    # The end has to be reversed and commands must be inverted (ie: L --> R)
    for move in end[0][1:][::-1]:
        if move == "L":
            checksum = (checksum * 243 + ord("R")) % 100000007
        elif move == "R":
            checksum = (checksum * 243 + ord("L")) % 100000007
        elif move == "U":
            checksum = (checksum * 243 + ord("D")) % 100000007
        else:
            checksum = (checksum * 243 + ord("U")) % 100000007
    return checksum

n = int(input())
S = []
E = []
for i in range(n):
    l = input()
    S.append(l)
    if "W" in l:
        whiteCaseS = [i, l.index("W")]
for i in range(n):
    l = input()
    E.append(l)
    if "W" in l:
        whiteCaseE = [i, l.index("W")]

aPathHasBeenFound = False
nextPathsFromStart = [[' ', S, whiteCaseS]]
nextPathsFromEnd = [[' ', E, whiteCaseE]]
sum_checksum = 0

while not aPathHasBeenFound:
    currentPathsFromStart = nextPathsFromStart
    currentPathsFromEnd = nextPathsFromEnd
    nextPathsFromStart = []
    nextPathsFromEnd = []
    listOfMatrixes = []
    for path in currentPathsFromStart:
        nextSteps = getNextSteps(path)
        for step in nextSteps:
            nextPathsFromStart.append(step)
            for otherStep in currentPathsFromEnd:
                if step[2] == otherStep[2]:
                    if step[1] == otherStep[1]:
                        aPathHasBeenFound = True
                        sum_checksum += addToCheckSum(step, otherStep)
                        sum_checksum %= 100000007
    if not aPathHasBeenFound:
        for path in currentPathsFromEnd:
            nextSteps = getNextSteps(path)
            for step in nextSteps:
                nextPathsFromEnd.append(step)
                for otherStep in nextPathsFromStart:
                    if step[2] == otherStep[2]:
                        if step[1] == otherStep[1]:
                            aPathHasBeenFound = True
                            sum_checksum += addToCheckSum(otherStep, step)
                            sum_checksum %= 100000007
print(sum_checksum)
