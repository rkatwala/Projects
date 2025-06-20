import pandas as pd  # For data manipulation and loading CSV
from sklearn.model_selection import train_test_split  # For splitting data
from sklearn.tree import DecisionTreeClassifier, plot_tree  # Classifier and visualization
from sklearn.preprocessing import LabelEncoder  # To convert categorical variables to numeric
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix  # Evaluation metrics
import matplotlib.pyplot as plt  # For plotting the decision tree

# 1. Load the Titanic dataset
df = pd.read_csv("train.csv")  # Make sure titanic.csv is in the same folder

# 2. Select relevant features and drop rows with missing values
df = df[['Pclass', 'Sex', 'Age', 'SibSp', 'Parch', 'Fare', 'Embarked', 'Survived']]
df = df.dropna()  # Removes rows with any missing values to avoid errors

# 3. Convert categorical features ('Sex', 'Embarked') into numeric form using LabelEncoder
le_sex = LabelEncoder()
df['Sex'] = le_sex.fit_transform(df['Sex'])  # 'male' -> 1, 'female' -> 0

le_embarked = LabelEncoder()
df['Embarked'] = le_embarked.fit_transform(df['Embarked'])  # 'S' -> 2, 'C' -> 0, etc.

# 4. Define features (X) and target (y)
X = df.drop('Survived', axis=1)  # All columns except the target
y = df['Survived']  # Target column: 1 = survived, 0 = did not survive

# 5. Split the data into training and testing sets (80% train, 20% test)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# 6. Create a decision tree classifier with max_depth=4 to prevent overfitting
clf = DecisionTreeClassifier(max_depth=4, random_state=42)

# 7. Train the decision tree on the training data
clf.fit(X_train, y_train)

# 8. Use the trained model to make predictions on the test data
y_pred = clf.predict(X_test)

# 9. Evaluate the model’s performance
print("Accuracy:", accuracy_score(y_test, y_pred))  # Overall correctness
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))  # TP, TN, FP, FN
print("\nClassification Report:\n", classification_report(y_test, y_pred))  # Precision, recall, F1

# 10. Visualize the trained decision tree
plt.figure(figsize=(20, 10))  # Set figure size for readability
plot_tree(
    clf,
    feature_names=X.columns,
    class_names=["Died", "Survived"],
    filled=True  # Fill colors based on class purity
)
plt.show()
