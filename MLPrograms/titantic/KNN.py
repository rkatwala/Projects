import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# 1. Load dataset
df = pd.read_csv("train.csv")

# 2. Select relevant features and drop rows with missing values
df = df[['Pclass', 'Sex', 'Age', 'SibSp', 'Parch', 'Fare', 'Embarked', 'Survived']]
df = df.dropna()  # Drop rows with missing values

# 3. Encode categorical features
df['Sex'] = LabelEncoder().fit_transform(df['Sex'])         # 'male' = 1, 'female' = 0
df['Embarked'] = LabelEncoder().fit_transform(df['Embarked'])  # Encode port as 0, 1, 2

# 4. Define features and target
X = df.drop('Survived', axis=1)
y = df['Survived']

# 5. Split into train/test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 6. Scale features (important for KNN since it uses distances)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 7. Initialize and train KNN model
knn = KNeighborsClassifier(n_neighbors=5)  # Try 5 neighbors
knn.fit(X_train_scaled, y_train)

# 8. Make predictions
y_pred = knn.predict(X_test_scaled)

# 9. Evaluate the model
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))
