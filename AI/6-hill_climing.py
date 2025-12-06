import random

class BlockWorld:
    def __init__(self, initial_state):
        self.state = initial_state
        self.goal = [['A', 'B', 'C']]  # All blocks stacked in order
    
    def print_state(self, state=None):
        if state is None:
            state = self.state
        print("Current state:")
        for i, stack in enumerate(state):
            print(f"Stack {i+1}: {stack}")
        print()
    
    def heuristic(self, state):
        """Heuristic: Count blocks in wrong position"""
        score = 0
        
        # Points for each block in correct goal stack
        for stack in state:
            if stack == ['A', 'B', 'C']:
                score += 10  # Perfect stack
        
        # Points for correct order in any stack
        for stack in state:
            if len(stack) >= 1 and stack[0] == 'A':
                score += 5
            if len(stack) >= 2 and stack[1] == 'B':
                score += 3
            if len(stack) >= 3 and stack[2] == 'C':
                score += 1
        
        return score
    
    def get_neighbors(self, state):
        """Generate all possible moves"""
        neighbors = []
        
        # For each stack, try moving top block to another stack
        for i, stack1 in enumerate(state):
            if stack1:  # If stack is not empty
                for j, stack2 in enumerate(state):
                    if i != j:  # Can't move to same stack
                        new_state = [list(stack) for stack in state]
                        block = new_state[i].pop(0)  # Take from top
                        new_state[j].insert(0, block)  # Place on top
                        
                        # Remove empty stacks
                        new_state = [stack for stack in new_state if stack]
                        neighbors.append(new_state)
        
        return neighbors
    
    def hill_climbing(self, max_iterations=100):
        current_state = self.state
        current_score = self.heuristic(current_state)
        
        print("Initial state:")
        self.print_state(current_state)
        print(f"Initial heuristic score: {current_score}\n")
        
        for iteration in range(max_iterations):
            neighbors = self.get_neighbors(current_state)
            
            if not neighbors:
                break
            
            # Find best neighbor
            best_neighbor = None
            best_score = current_score
            
            for neighbor in neighbors:
                neighbor_score = self.heuristic(neighbor)
                if neighbor_score > best_score:
                    best_score = neighbor_score
                    best_neighbor = neighbor
            
            # If no better neighbor found
            if best_score <= current_score:
                print(f"Reached local optimum at iteration {iteration}")
                break
            
            # Move to best neighbor
            current_state = best_neighbor
            current_score = best_score
            
            print(f"Iteration {iteration + 1}:")
            self.print_state(current_state)
            print(f"Heuristic score: {current_score}\n")
            
            # Check if goal reached
            if current_score >= 19:  # Max possible score
                print("Goal state reached!")
                return current_state
        
        return current_state

def demo_block_world():
    print("=== Block World Problem using Hill Climbing ===")
    
    # Initial state: all blocks on table separately
    initial_state = [['A'], ['B'], ['C']]
    
    # Or try a more complex initial state
    # initial_state = [['C', 'A'], ['B']]
    
    problem = BlockWorld(initial_state)
    
    print("Goal: Stack all blocks with A on top, then B, then C")
    print()
    
    final_state = problem.hill_climbing()
    
    print("\n=== Final Result ===")
    problem.print_state(final_state)
    print(f"Final heuristic score: {problem.heuristic(final_state)}")

# Run the demo
demo_block_world()
