import numpy as np
from collections import defaultdict


def kfold_split(num_objects, num_folds):
    foldsize = num_objects // num_folds
    remainder = num_objects % num_folds
    foldlist = []
    for i in range(num_folds-1):
        foldlist.append(
            (np.array([j for j in range(num_objects) if j < foldsize*i or j >= (i+1)*foldsize]), np.array([j for j in range(i*foldsize, (i+1)*foldsize)])))
    foldlist.append((np.array([j for j in range((i+1)*foldsize)]), np.array([j for j in range((i+1)*foldsize, num_objects)])))
    return foldlist


def knn_cv_score(X, y, parameters, score_function, folds, knn_class):
    thedict = {}
    Mscore = 0
    for train, test in folds:
        X_train = X[train]
        X_test = X[test]
        y_train = y[train]
        y_test = y[test]
        for normalizer, normalizer_name in parameters["normalizers"]:
            normalized_X_train = X_train
            normalized_X_test = X_test
            if normalizer is not None:
                normalizer.fit(X_train)
                normalized_X_train = normalizer.transform(X_train)
                normalized_X_test = normalizer.transform(X_test)
            for neighbors in parameters["n_neighbors"]:
                for metric in parameters["metrics"]:
                    for weight in parameters["weights"]:
                        KNNModel = knn_class(n_neighbors=neighbors, weights=weight, metric=metric)
                        KNNModel.fit(normalized_X_train, y_train)
                        Prediction = KNNModel.predict(normalized_X_test)
                        Mscore = score_function(y_test, Prediction)
                        if (normalizer_name, neighbors, metric, weight) in thedict:
                            thedict[(normalizer_name, neighbors, metric, weight)] += Mscore
                        else:
                            thedict[(normalizer_name, neighbors, metric, weight)] = Mscore
    thedict = {key: val / len(folds) for key, val in thedict.items()}
    return thedict
