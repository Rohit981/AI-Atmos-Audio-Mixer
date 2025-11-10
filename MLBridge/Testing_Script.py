import pandas as pd
import random
import os

# === 1️⃣ Locate your original dataset ===
file_path = "MLData.csv"
balanced_path = "MLData_balanced.csv"

if not os.path.exists(file_path):
    raise FileNotFoundError(f"File not found: {file_path}")

df = pd.read_csv(file_path)
print(f"Original dataset size: {len(df)} rows")

# === 2️⃣ Generate synthetic 'Action' samples ===
new_rows = []
for _ in range(150):  # add 150 synthetic rows
    row = {
        "Velocity": random.uniform(400, 900),
        "IsJumping": random.choice([0, 1]),
        "IsSprinting": random.choice([0, 1]),
        "Health": random.uniform(0, 40),
        "Mood": "EAudioMood::Action"
    }
    new_rows.append(row)

new_df = pd.DataFrame(new_rows)
print(f"Generated {len(new_df)} new Action samples")

# === 3️⃣ Combine and save ===
combined_df = pd.concat([df, new_df], ignore_index=True)
combined_df.to_csv(balanced_path, index=False)

print(f"✅ Saved balanced dataset as {balanced_path}")
print(f"New total rows: {len(combined_df)}")
print(combined_df["Mood"].value_counts())