from Train_Model_Mood import Net
import torch
import json
import time
import os


#Loading my Train_Model_Mood
model = Net()
state_dict = torch.load("MLBridge/MoodNetModel.pth", map_location=torch.device("cpu"))
model.load_state_dict(state_dict)
model.eval()

print("Mood Net Model Loaded and ready")

while True:
    if os.path.exists("MLBridge/input.json"):
        try:
            with open("MLBridge/input.json", "r") as f:
                content = f.read().strip()
            if not content:
                raise ValueError("File is Empty")
            data = json.loads(content)

            features = torch.tensor([
                [data["PlayerVelocity"], data["Jumping"], data["Sprinting"], data["Health"]]
            ], dtype=torch.float32)

            with torch.no_grad():
                output = model(features)
                predicted = torch.argmax(output, dim=1).item()
            
            with open("MLBridge/output.json", "w") as f_out:
                json.dump({"Mood": int(predicted)}, f_out)

        except json.JSONDecodeError as e:
            print("Error reading input.json", e)
        except ValueError as e:
            print("Error:", e)
        except Exception as e:
            print("An unexpected error occurred", e)
    
    time.sleep(0.1)
    continue
