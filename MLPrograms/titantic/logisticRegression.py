import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# 1. Load the Titanic dataset
df = pd.read_csv("titanic.csv")  # Make sure the file is in your working directory

# 2. Select useful columns and remove rows with missing values
df = df[['Pclass', 'Sex', 'Age', 'SibSp', 'Parch', 'Fare', 'Embarked', 'Survived']]
df = df.dropna()  # Drops rows with any NaN values

# 3. Encode categorical variables
df['Sex'] = LabelEncoder().fit_transform(df['Sex'])         # 'male' -> 1, 'female' -> 0
df['Embarked'] = LabelEncoder().fit_transform(df['Embarked'])  # 'C', 'Q', 'S' -> numbers

# 4. Split into features (X) and target (y)
X = df.drop('Survived', axis=1)  # All predictors
y = df['Survived']               # Target: 0 = died, 1 = survived

# 5. Split into training and testing sets (80/20)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# 6. Feature scaling (important for logistic regression)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 7. Train logistic regression model
log_reg = LogisticRegression(max_iter=1000)  # Increase max_iter to ensure convergence
log_reg.fit(X_train_scaled, y_train)

# 8. Make predictions
y_pred = log_reg.predict(X_test_scaled)

# 9. Evaluate the model
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))

# 10. Predict class probabilities (optional)
y_proba = log_reg.predict_proba(X_test_scaled)
print("\nFirst 5 predicted probabilities:\n", y_proba[:5])
