import numpy as np

class NeuralNetwork:
    def __init__(self):
        # Network architecture: 2 inputs -> 2 hidden -> 1 output
        np.random.seed(42)
        self.w1 = np.random.randn(2, 2)  # Input to hidden
        self.w2 = np.random.randn(2, 1)  # Hidden to output
        self.b1 = np.random.randn(2)     # Hidden bias
        self.b2 = np.random.randn(1)     # Output bias
    
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))
    
    def sigmoid_derivative(self, x):
        return x * (1 - x)
    
    def forward(self, X):
        # Hidden layer
        self.z1 = np.dot(X, self.w1) + self.b1
        self.a1 = self.sigmoid(self.z1)
        
        # Output layer
        self.z2 = np.dot(self.a1, self.w2) + self.b2
        self.a2 = self.sigmoid(self.z2)
        
        return self.a2
    
    def backward(self, X, y, output, lr=0.1):
        m = X.shape[0]
        
        # Output layer error
        error2 = y - output
        d_output = error2 * self.sigmoid_derivative(output)
        
        # Hidden layer error
        error1 = d_output.dot(self.w2.T)
        d_hidden = error1 * self.sigmoid_derivative(self.a1)
        
        # Update weights and biases
        self.w2 += self.a1.T.dot(d_output) * lr
        self.b2 += np.sum(d_output, axis=0) * lr
        
        self.w1 += X.T.dot(d_hidden) * lr
        self.b1 += np.sum(d_hidden, axis=0) * lr
    
    def train(self, X, y, epochs=1000, lr=0.1):
        for epoch in range(epochs):
            # Forward pass
            output = self.forward(X)
            
            # Backward pass
            self.backward(X, y, output, lr)
            
            # Print error every 100 epochs
            if epoch % 100 == 0:
                loss = np.mean(np.square(y - output))
                print(f"Epoch {epoch}: Loss = {loss:.4f}")

# XOR problem (non-linear)
X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([[0], [1], [1], [0]])

# Create and train network
print("Backpropagation Neural Network Training")
print("="*40)
nn = NeuralNetwork()
nn.train(X, y, epochs=1000, lr=0.5)

# Test
print("\n" + "="*40)
print("Testing trained network:")
for i in range(4):
    pred = nn.forward(X[i:i+1])
    print(f"Input {X[i]} -> Predicted: {pred[0,0]:.4f}, Actual: {y[i,0]}")
