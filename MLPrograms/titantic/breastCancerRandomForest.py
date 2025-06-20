import pandas as pd
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier  # Random Forest
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
from sklearn.preprocessing import StandardScaler

# 1. Load breast cancer dataset
data = load_breast_cancer()

# 2. Convert to DataFrame for easy handling
df = pd.DataFrame(data.data, columns=data.feature_names)
df['target'] = data.target  # Add target column (0 = malignant, 1 = benign)

# 3. Define features and target
X = df.drop('target', axis=1)  # All 30 features
y = df['target']               # 0 or 1

# 4. Split into train/test sets (80% train, 20% test)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 5. Scale features (important for many ML models, but optional for Random Forest)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 6. Initialize Random Forest
rf = RandomForestClassifier(n_estimators=100, max_depth=5, random_state=42)
# - n_estimators: number of trees in the forest
# - max_depth: limit tree depth (controls overfitting)
# - random_state: ensures same result each run

# 7. Train the model
rf.fit(X_train_scaled, y_train)

# 8. Make predictions
y_pred = rf.predict(X_test_scaled)

# 9. Evaluate the model
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))
