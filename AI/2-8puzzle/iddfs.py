def iddfs(start, goal):
    def neighbors(s):
        z = s.index(0)
        r, c = z//3, z%3
        moves = []
        for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
            nr, nc = r+dr, c+dc
            if 0<=nr<3 and 0<=nc<3:
                ns = list(s)
                nz = nr*3+nc
                ns[z], ns[nz] = ns[nz], ns[z]
                moves.append(tuple(ns))
        return moves
    
    def dls(s, path, d):
        if s == goal: return path+[s]
        if d <= 0: return None
        for n in neighbors(s):
            if n not in path:
                res = dls(n, path+[s], d-1)
                if res: return res
        return None
    
    for d in range(31):
        sol = dls(start, [], d)
        if sol: return sol
    return None

def show(state):
    for i in range(0,9,3):
        print(state[i:i+3])

start = (1,2,3,4,0,5,6,7,8)
goal = (1,2,3,4,5,6,7,8,0)

print("Start:"); show(start)
print("\nGoal:"); show(goal)

sol = iddfs(start, goal)
if sol:
    print(f"\nSolution in {len(sol)-1} moves:")
    for i,s in enumerate(sol):
        print(f"Step {i}:"); show(s); print()
else:
    print("No solution")
