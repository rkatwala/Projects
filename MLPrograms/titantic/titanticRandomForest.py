import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# 1. Load Titanic dataset
df = pd.read_csv("train.csv")

# 2. Select relevant features and drop rows with missing values
df = df[['Pclass', 'Sex', 'Age', 'SibSp', 'Parch', 'Fare', 'Embarked', 'Survived']]
df = df.dropna()  # Remove rows with any missing values

# 3. Encode categorical columns
df['Sex'] = LabelEncoder().fit_transform(df['Sex'])         # 'male' = 1, 'female' = 0
df['Embarked'] = LabelEncoder().fit_transform(df['Embarked'])  # 'S', 'C', 'Q' → integers

# 4. Define features and target
X = df.drop('Survived', axis=1)
y = df['Survived']

# 5. Split into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# 6. (Optional) Scale features — not required for trees but kept for consistency
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 7. Initialize and train Random Forest Classifier
rf = RandomForestClassifier(
    n_estimators=100,      # Number of trees
    max_depth=5,           # Max depth of each tree (prevents overfitting)
    random_state=42
)
rf.fit(X_train_scaled, y_train)

# 8. Make predictions
y_pred = rf.predict(X_test_scaled)

# 9. Evaluate the model
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))

# 10. Optional: Feature importance
import matplotlib.pyplot as plt

importances = rf.feature_importances_
features = X.columns

plt.figure(figsize=(10, 5))
plt.bar(features, importances)
plt.title("Feature Importances")
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
