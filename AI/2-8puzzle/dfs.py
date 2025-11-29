def dfs_8puzzle(start, goal):
    def get_neighbors(state):
        neighbors = []
        zero_index = state.index(0)
        row, col = zero_index // 3, zero_index % 3
        
        moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        for dr, dc in moves:
            new_row, new_col = row + dr, col + dc
            if 0 <= new_row < 3 and 0 <= new_col < 3:
                new_index = new_row * 3 + new_col
                new_state = list(state)
                new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index]
                neighbors.append(tuple(new_state))
        
        return neighbors
    
    def dfs(current_state, path, visited, max_depth=20):
        if len(path) > max_depth:
            return None
            
        if current_state == goal:
            return path + [current_state]
        
        visited.add(current_state)
        
        for neighbor in get_neighbors(current_state):
            if neighbor not in visited:
                result = dfs(neighbor, path + [current_state], visited.copy(), max_depth)
                if result:
                    return result
        
        return None
    
    return dfs(start, [], set())

def print_puzzle(state):
    for i in range(0, 9, 3):
        print(state[i:i+3])
    print()

def demo_8puzzle_dfs():
    print("=== 8-Puzzle Solver using DFS ===")

    start = (1, 2, 3, 4, 0, 5, 6, 7, 8)
    goal = (1, 2, 3, 4, 5, 6, 7, 8, 0)
    
    print("Start state:")
    print_puzzle(start)
    
    print("Goal state:")
    print_puzzle(goal)
    
    solution = dfs_8puzzle(start, goal)
    
    if solution:
        print(f"Solution found in {len(solution) - 1} moves!")
        print("\nSolution path:")
        for i, state in enumerate(solution):
            print(f"Step {i}:")
            print_puzzle(state)
    else:
        print("No solution found!")

demo_8puzzle_dfs()
