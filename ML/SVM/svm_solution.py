import numpy as np
from sklearn.svm import SVC


def train_svm_and_predict(train_features, train_target, test_features):
    result = SVC(kernel="rbf", C=2)
    result.fit(train_features, train_target)
    prediction = result.predict(test_features)
    return prediction
