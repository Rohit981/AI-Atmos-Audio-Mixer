#Train model for AI Atmos Mixer
import pandas as pd
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader, TensorDataset, random_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
import torch.optim as optim

#=== Device Setup for the GPU
device = torch.device("cuda:0")

#=== Load & Preprocess Data
data = pd.read_csv("MLData.csv")
data.columns = data.columns.str.strip()

#==== Setup Data values
X = data[['PlayerVelocity','Jumping','Sprinting','Health']].values
y = data['CurrentMood'].values

#=== Encode Mood Labels
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)

#=== Normalize numeric features
scaler = StandardScaler()
X = scaler.fit_transform(X)

#=== Convert to Tensor
X_tensor = torch.tensor(X, dtype=torch.float32)
y_tensor = torch.tensor(y, dtype=torch.long)

dataset = TensorDataset(X_tensor, y_tensor)


#=== Split dataset (80% Train, 20% Test)
train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_data, test_data = random_split(dataset, [train_size, test_size])

train_loader = DataLoader(train_data, batch_size=16, shuffle=True)
test_loader = DataLoader(test_data, batch_size=16, shuffle=True)

#===== Define Neural Network ====
class Net(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(4,32)
        self.fc2 = nn.Linear(32,64)
        self.fc3 = nn.Linear(64,16)
        self.fc4 = nn.Linear(16,3)

        self.relu = nn.ReLU()
        self.dropout = nn.Dropout(0.2)
    
    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.dropout(self.relu(self.fc3(x)))
        x = self.fc4(x)
        return x

model = Net().to(device)

# X = torch.rand(1,4).to(device)
# print(X.shape)

# output = model(X)
# print(output)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

#==== Train ====
EPOCHS = 50
for epoch in range(EPOCHS):
    model.train()
    running_loss = 0.0

    







