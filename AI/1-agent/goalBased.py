class GoalBasedAgent:
    def __init__(self):
        self.goal = "clean"
    
    def perceive(self, environment):
        return environment
    
    def act(self, percept):
        if "dirty" in percept:
            return f"Action: clean (Goal: {self.goal})"
        elif "clean" in percept:
            return f"Action: no operation (Goal: {self.goal} achieved!)"
        else:
            return f"Action: explore (Goal: {self.goal})"

def demo_goal_based():
    print("--- Goal-Based Agent ---")
    agent = GoalBasedAgent()
    
    environments = [
        # "The room is dirty",
        "The room is clean",
    ]
    
    for env in environments:
        percept = agent.perceive(env)
        action = agent.act(percept)
        print(f"Environment: {env}")
        print(f"{action}\n")

demo_goal_based()
