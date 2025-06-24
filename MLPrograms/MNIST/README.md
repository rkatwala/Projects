
## 📄 README.md

````markdown
# MNIST Digit Classification

This project applies two different machine learning models to the MNIST handwritten digit dataset:

1. **Logistic Regression**
2. **Convolutional Neural Network (CNN) using PyTorch**

---

## 📊 Dataset: MNIST

- **Images**: 28×28 grayscale
- **Classes**: 10 digits (0 through 9)
- **Samples**: 60,000 training and 10,000 testing
- Automatically downloaded using `fetch_openml` (for sklearn) or `torchvision.datasets.MNIST` (for PyTorch)

---

## 📁 Files

### ✅ `logistic_mnist.py`
- Implements multinomial logistic regression using `scikit-learn`
- Preprocesses the data using `StandardScaler`
- Trains the model with `LogisticRegression(solver='saga', multi_class='multinomial')`
- Evaluates performance with accuracy, classification report, and confusion matrix
- Displays 10 test images with predicted labels

### ✅ `cnn_mnist_pytorch.py`
- Implements a CNN using `torch.nn.Conv2d` and `torch.nn.Linear`
- Architecture:
  - Conv2D → ReLU → Conv2D → ReLU → MaxPool → FC → ReLU → FC
- Trained for 5 epochs using Adam optimizer
- Evaluated using total accuracy on test set
- Visualizes 10 predictions with actual test images

---

## 🧪 Model Comparison

| Metric              | Logistic Regression | CNN              |
|---------------------|---------------------|------------------|
| Framework           | scikit-learn        | PyTorch          |
| Feature Extraction  | Manual (flattened)  | Automatic (CNN)  |
| Accuracy (expected) | ~92%                | ~98–99%          |
| Suitable For        | Simple models       | Deep learning    |

---

## ⚙️ Setup

### Python Requirements

```bash
pip install numpy matplotlib scikit-learn torch torchvision
````

---

## 🚀 Running the Models

### Logistic Regression

```bash
python logistic_mnist.py
```

### CNN (PyTorch)

```bash
python cnn_mnist_pytorch.py
```

---

## 📌 Notes

* Logistic Regression flattens images and uses no spatial context.
* CNN uses convolution and pooling layers to learn image features hierarchically.
* Logistic Regression is great for fast training; CNNs perform much better for images.

---

## 📚 License

This project is released under the MIT License.

```

---

Let me know if you'd like to include:
- File size/runtime benchmarks
- Accuracy graphs across epochs
- Model saving/loading functionality in PyTorch
```
