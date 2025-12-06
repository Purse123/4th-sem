import numpy as np

# AND Gate data
X = np.array([[0,0], [0,1], [1,0], [1,1]])
y = np.array([0, 0, 0, 1])

# 1. Hebbian Network
print("=== Hebbian Network ===")
w = np.array([0.0, 0.0])
b = 0.0

for i in range(4):
    w += X[i] * y[i]
    b += y[i]
    print(f"Input: {X[i]}, Target: {y[i]}, Weights: {w}, Bias: {b}")

print(f"\nFinal: w={w}, b={b}")

# Test
for i in range(4):
    out = 1 if np.dot(X[i], w) + b > 0 else 0
    print(f"Input {X[i]} -> {out}")

# 2. Perceptron Network
print("\n=== Perceptron Network ===")
w = np.array([0.0, 0.0])
b = 0.0
lr = 0.1

for epoch in range(10):
    error = 0
    for i in range(4):
        # Calculate output
        net = np.dot(X[i], w) + b
        out = 1 if net >= 0 else 0
        
        # Update if wrong
        if out != y[i]:
            error += 1
            w += lr * (y[i] - out) * X[i]
            b += lr * (y[i] - out)
    
    if error == 0:
        print(f"Converged in {epoch+1} epochs")
        break

print(f"Final: w={w}, b={b}")

# Test
for i in range(4):
    net = np.dot(X[i], w) + b
    out = 1 if net >= 0 else 0
    print(f"Input {X[i]} -> {out}")
