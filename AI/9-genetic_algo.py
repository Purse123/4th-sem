import random

# GA Parameters
pop_size = 4
chrom_len = 6
generations = 5

# Create initial population
pop = [[random.randint(0,1) for _ in range(chrom_len)] for _ in range(pop_size)]

print("Initial Population:")
for i, chrom in enumerate(pop):
    print(f"{i}: {chrom} -> Fitness: {sum(chrom)}")

for gen in range(generations):
    print(f"\nGeneration {gen+1}:")
    
    # Select parents (tournament selection)
    parents = []
    for _ in range(pop_size):
        # Pick 2 random, keep better one
        a, b = random.sample(pop, 2)
        parents.append(a if sum(a) > sum(b) else b)
    
    # Create children (crossover)
    children = []
    for i in range(0, pop_size, 2):
        p1, p2 = parents[i], parents[i+1]
        point = random.randint(1, chrom_len-1)
        c1 = p1[:point] + p2[point:]
        c2 = p2[:point] + p1[point:]
        children.extend([c1, c2])
    
    # Mutation
    for chrom in children:
        for j in range(chrom_len):
            if random.random() < 0.1:  # 10% mutation rate
                chrom[j] = 1 - chrom[j]
    
    pop = children
    
    # Show results
    for i, chrom in enumerate(pop):
        print(f"{i}: {chrom} -> Fitness: {sum(chrom)}")
    
    best = max(pop, key=lambda x: sum(x))
    print(f"Best: {best} (Fitness: {sum(best)})")
