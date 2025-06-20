# Titanic Survival Classification

This project implements multiple supervised machine learning models to predict passenger survival on the Titanic. The dataset is sourced from the [Kaggle Titanic Competition](https://www.kaggle.com/c/titanic/data).

---

## 📊 Dataset

The Titanic dataset includes information such as:

- Passenger class (`Pclass`)
- Gender (`Sex`)
- Age
- Number of siblings/spouses aboard (`SibSp`)
- Number of parents/children aboard (`Parch`)
- Fare
- Port of embarkation (`Embarked`)
- Survival status (`Survived` - 1 = Survived, 0 = Did not survive)

---

## 🧪 Models Implemented

### 1. `logistic_titanic.py` — Logistic Regression
- Encodes `Sex` and `Embarked`
- Scales features using `StandardScaler`
- Fits a `LogisticRegression` model
- Outputs accuracy, confusion matrix, classification report, and predicted probabilities

### 2. `decision_tree_titanic.py` — Decision Tree
- Uses `DecisionTreeClassifier` with `max_depth=4`
- Encodes categorical features
- No scaling needed (tree-based model)
- Includes visualization of the decision tree using `plot_tree`

### 3. `knn_titanic.py` — K-Nearest Neighbors
- Scales features using `StandardScaler` (KNN is distance-based)
- Uses `KNeighborsClassifier` with `n_neighbors=5`
- Predicts and evaluates with accuracy and confusion matrix

### 4. `random_forest_titanic.py` — Random Forest
- Uses `RandomForestClassifier` with 100 trees and `max_depth=5`
- Optional scaling included
- Outputs accuracy and classification report
- Displays feature importance bar chart

---

## 📁 File Structure

