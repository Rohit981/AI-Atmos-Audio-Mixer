#Train model for AI Atmos Mixer
import pandas as pd
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader, TensorDataset, random_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
import torch.optim as optim
from tqdm import tqdm
import seaborn as sns
import matplotlib.pyplot as plt


#=== Device Setup for the GPU
device = torch.device("cuda:0")

#=== Load & Preprocess Data
data = pd.read_csv("MLData_New.csv")
data.columns = data.columns.str.strip()

# print(data.drop_duplicates().shape[0], "unique rows out of", data.shape[0])

# print(data['CurrentMood'].value_counts())
# print(data['Jumping'].value_counts())
# print(data['Sprinting'].value_counts())
# print(data['Health'].value_counts())

# sns.pairplot(data, hue='CurrentMood')
# plt.show()


#==== Setup Data values
X = data[['PlayerVelocity','Jumping','Sprinting','Health', 'PlayerLocationX', 'PlayerLocationY']].values
y = data['CurrentMood'].values

#=== Encode Mood Labels
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)

#=== Normalize numeric features
scaler = StandardScaler()
X = scaler.fit_transform(X)

# print("Mean:", scaler.mean_)
# print("Scale:", scaler.scale_)

#=== Convert to Tensor
X_tensor = torch.tensor(X, dtype=torch.float32)
y_tensor = torch.tensor(y, dtype=torch.long)

dataset = TensorDataset(X_tensor, y_tensor)


#=== Split dataset (80% Train, 20% Test)
train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_data, test_data = random_split(dataset, [train_size, test_size])

train_loader = DataLoader(train_data, batch_size=16, shuffle=True)
test_loader = DataLoader(test_data, batch_size=16)

#===== Define Neural Network ====
class Net(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(6,64)
        self.fc2 = nn.Linear(64,32)
        self.fc3 = nn.Linear(32,16)
        self.fc4 = nn.Linear(16,3)

        self.relu = nn.ReLU()
        self.dropout = nn.Dropout(0.1)
    
    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.dropout(self.relu(self.fc3(x)))
        x = self.fc4(x)
        return F.log_softmax(x, dim=1)

model = Net().to(device)

# criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

#==== Train ====
EPOCHS = 100
for epoch in range(EPOCHS):
    model.train()
    running_loss = 0.0
    train_total, train_correct = 0,0

    for inputs, labels in tqdm(train_loader):
        inputs, labels = inputs.to(device), labels.to(device)

        optimizer.zero_grad()
        outputs = model(inputs)
        loss = F.nll_loss(outputs,labels)
        loss.backward()
        optimizer.step()
        running_loss += loss.item()

#======= TEST OUT TRAINING ACCURACY    ========
        _, predicted = torch.max(outputs, 1)
        train_total += labels.size(0)
        train_correct += (predicted == labels).sum().item()

    # print(f"Epoch [{epoch+1}]/{EPOCHS}, Loss: {running_loss/len(train_loader): .4f}")
    
print("Train Accuracy:", round(train_correct/train_total, 3))


#==== Test ====
model.eval()
correct, total = 0,0

with torch.no_grad():
    for inputs, labels in tqdm(test_loader):

        inputs, labels = inputs.to(device), labels.to(device)

        outputs = model(inputs)
        _, predicted = torch.max(outputs, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

print("Test Accuracy:", round(correct/total, 3))

torch.save(model.state_dict(), "MLBridge/MoodNetModel.pth")
print("Model saved as MoodNetModel.pth")
    







