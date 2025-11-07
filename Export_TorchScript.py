# import torch
# from Train_Model_Mood import Net


# #Loading my Train_Model_Mood
# model = Net()
# model.load_state_dict(torch.load("MoodNetModel.pth"))
# model.eval()

# #Creating Dummy inputs based on my Model
# example_input = torch.rand(1,4)

# # Convert to Torch Script
# traced_Model = torch.jit.trace(model, example_input)
# traced_Model.save("MoodNetModel.pt")

# # Print the IR version
# print("Saved TorchScript model as MoodNetModel.pt")



