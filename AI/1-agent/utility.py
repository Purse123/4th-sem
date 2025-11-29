class UtilityBasedAgent:
    def __init__(self):
        self.state = {'battery': 50, 'dirt_level': 5}
    
    def perceive(self, environment):
        return environment
    
    def calculate_utility(self, action):
        if action == 'clean':
            return self.state['dirt_level'] * 2 - (100 - self.state['battery']) * 0.1
        elif action == 'recharge':
            return (100 - self.state['battery']) * 0.3
        else:  # no_op
            return 0
    
    def act(self, percept):
        actions = ['clean', 'recharge', 'no_op']
        best_action = max(actions, key=self.calculate_utility)
        
        # Update state
        if best_action == 'clean':
            self.state['dirt_level'] = max(0, self.state['dirt_level'] - 3)
            self.state['battery'] -= 15
        elif best_action == 'recharge':
            self.state['battery'] = min(100, self.state['battery'] + 25)
        
        return f"Action: {best_action} (Battery: {self.state['battery']}%, Dirt: {self.state['dirt_level']})"

def demo_utility_based():
    print("--- Utility-Based Agent ---")
    agent = UtilityBasedAgent()
    
    environments = [
        "The room is dirty",
    ]
    
    for env in environments:
        percept = agent.perceive(env)
        action = agent.act(percept)
        print(f"Environment: {env}")
        print(f"{action}\n")

demo_utility_based()
