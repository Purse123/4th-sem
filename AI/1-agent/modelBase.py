class ModelBasedReflexAgent:
    def __init__(self):
        self.rules = {
            'dirty': 'clean',
        }
        self.internal_state = {'battery': 20, 'location': 'room1'}
    
    def perceive(self, environment):
        return environment
    
    def act(self, percept):
        self.internal_state['battery'] -= 5
        
        for condition, action in self.rules.items():
            if condition in percept and self.internal_state['battery'] > 20:
                return f"Action: {action} (Battery: {self.internal_state['battery']}%)"
        
        if self.internal_state['battery'] <= 20:
            return f"Action: recharge (Battery: {self.internal_state['battery']}%)"
        
        return "Action: no_op"

def demo_model_based():
    print("--- Mode-Based Reflex Agent ---")
    agent = ModelBasedReflexAgent()
    
    environments = [
        "The room is dirty",
    ]
    
    for env in environments:
        percept = agent.perceive(env)
        action = agent.act(percept)
        print(f"Environment: {env}")
        print(f"{action}\n")

demo_model_based()
