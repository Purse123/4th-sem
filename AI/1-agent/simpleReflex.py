class SimpleReflexAgent:
    def __init__(self):
        self.rules = {
            'dirty': 'clean',
        }
    
    def perceive(self, environment):
        return environment
    
    def act(self, percept):
        for condition, action in self.rules.items():
            if condition in percept:
                return f"Action: {action}"
        return "Action: no_op"

def demo_simple_reflex():
    print("--- Simple Reflex Agent ---")
    agent = SimpleReflexAgent()
    
    environments = [
        "The room is dirty",
    ]
    
    for env in environments:
        percept = agent.perceive(env)
        action = agent.act(percept)
        print(f"Environment: {env}")
        print(f"{action}\n")

demo_simple_reflex()
