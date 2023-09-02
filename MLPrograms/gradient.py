import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression

class LinearRegressor:
    def __init__(self, learning_rate=0.0002, iterations=1000000, tolerance=1e-20):
        self.learning_rate = learning_rate
        self.iterations = iterations
        self.tolerance = tolerance

    def fit(self, x, y):
        self.m_ = 0
        self.b_ = 0
        cost_previous = 0
        n = len(x)

        for i in range(self.iterations):
            y_predicted = self.m_ * x + self.b_
            cost = self._compute_cost(y, y_predicted, n)
            md, bd = self._compute_gradients(x, y, y_predicted, n)
            
            self.m_ -= self.learning_rate * md
            self.b_ -= self.learning_rate * bd
            
            if self._has_converged(cost, cost_previous):
                break

            cost_previous = cost
            print(f"m {self.m_}, b {self.b_}, cost {cost}, iteration {i}")

        return self.m_, self.b_

    def _compute_cost(self, y, y_predicted, n):
        return (1/n) * sum((y - y_predicted)**2)

    def _compute_gradients(self, x, y, y_predicted, n):
        md = -(2/n) * sum(x * (y - y_predicted))
        bd = -(2/n) * sum(y - y_predicted)
        return md, bd

    def _has_converged(self, cost, cost_previous):
        return abs(cost - cost_previous) < self.tolerance


def get_data_from_csv(filename):
    df = pd.read_csv(filename)
    return np.array(df.math), np.array(df.cs)

def predict_using_sklearn(x, y):
    model = LinearRegression()
    model.fit(x.reshape(-1, 1), y)
    return model.coef_[0], model.intercept_


if __name__ == "__main__":
    x, y = get_data_from_csv("test_scores.csv")

    regressor = LinearRegressor()
    m, b = regressor.fit(x, y)
    print(f"Using gradient descent function: Coef {m} Intercept {b}")

    m_sklearn, b_sklearn = predict_using_sklearn(x, y)
    print(f"Using sklearn: Coef {m_sklearn} Intercept {b_sklearn}")
