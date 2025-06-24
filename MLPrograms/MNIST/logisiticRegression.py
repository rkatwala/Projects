import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import fetch_openml
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# 1. Load the MNIST dataset from OpenML
print("Loading MNIST...")
mnist = fetch_openml('mnist_784', version=1, as_frame=False)
X, y = mnist.data, mnist.target.astype('int')

# 2. Split into training and testing sets (e.g., 60k train / 10k test)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.142857, random_state=42)

# 3. Scale the pixel values (important for logistic regression)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train.astype(np.float64))
X_test_scaled = scaler.transform(X_test.astype(np.float64))

# 4. Train logistic regression
print("Training Logistic Regression...")
model = LogisticRegression(
    multi_class='multinomial',
    solver='saga',
    max_iter=100,     # Try increasing to 200+ if convergence warning appears
    verbose=1
)
model.fit(X_train_scaled, y_train)

# 5. Predict on test set
y_pred = model.predict(X_test_scaled)

# 6. Evaluate
print("\nAccuracy:", accuracy_score(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))

# 7. Visualize some predictions
plt.figure(figsize=(10, 4))
for i in range(10):
    plt.subplot(2, 5, i + 1)
    plt.imshow(X_test[i].reshape(28, 28), cmap='gray')
    plt.title(f"Pred: {y_pred[i]}")
    plt.axis('off')
plt.tight_layout()
plt.show()
