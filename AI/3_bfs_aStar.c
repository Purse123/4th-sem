import heapq

# Map graph: node -> {neighbor: cost}
graph = {
    'A': {'B': 4, 'C': 2},
    'B': {'D': 5},
    'C': {'D': 8, 'E': 10},
    'D': {'F': 3},
    'E': {'F': 2},
    'F': {}
}

# Heuristic (straight-line distance to goal F)
heuristic = {
    'A': 10, 'B': 8, 'C': 6, 'D': 4, 'E': 3, 'F': 0
}

def greedy_bfs(start, goal):
    """Best-First Search (Greedy)"""
    print("\nGreedy Best-First Search:")
    
    pq = [(heuristic[start], start, [start])]
    visited = set()
    
    while pq:
        _, node, path = heapq.heappop(pq)
        
        if node in visited:
            continue
        visited.add(node)
        
        if node == goal:
            return path
        
        for neighbor in graph[node]:
            if neighbor not in visited:
                heapq.heappush(pq, (heuristic[neighbor], neighbor, path + [neighbor]))
    
    return None

def astar(start, goal):
    """A* Search"""
    print("\nA* Search:")
    
    # (f_score, node, path, g_score)
    pq = [(heuristic[start], start, [start], 0)]
    visited = set()
    
    while pq:
        f, node, path, g = heapq.heappop(pq)
        
        if node in visited:
            continue
        visited.add(node)
        
        if node == goal:
            return path, f  # Return path and total cost
        
        for neighbor, cost in graph[node].items():
            if neighbor not in visited:
                new_g = g + cost
                new_f = new_g + heuristic[neighbor]
                heapq.heappush(pq, (new_f, neighbor, path + [neighbor], new_g))
    
    return None, float('inf')

# Run searches
print("Map: A->B(4), A->C(2), B->D(5), C->D(8), C->E(10), D->F(3), E->F(2)")

path_bfs = greedy_bfs('A', 'F')
print(f"Path: {path_bfs}")

path_astar, cost_astar = astar('A', 'F')
print(f"Path: {path_astar}, Cost: {cost_astar}")
