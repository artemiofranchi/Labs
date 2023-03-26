import numpy as np


class Preprocessor:

    def __init__(self):
        pass

    def fit(self, X, Y=None):
        pass

    def transform(self, X):
        pass

    def fit_transform(self, X, Y=None):
        pass


class MyOneHotEncoder(Preprocessor):

    def __init__(self, dtype=np.float64):
        super(Preprocessor).__init__()
        self.dtype = dtype

    def fit(self, X, Y=None):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: unused
        """
        self.signs = []
        self.signs_len = []
        for i in X.columns:
            self.signs.append(sorted(X[i].unique()))
            self.signs_len.append(len(X[i].unique()))

    def transform(self, X):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        returns: transformed objects, numpy-array, shape [n_objects, |f1| + |f2| + ...]
        """
        ret_mas = np.zeros((X.shape[0], sum(self.signs_len)), dtype=self.dtype)
        for obj in range(X.shape[0]):
            temp = 0
            for i in range(len(self.signs)):
                for j in range(self.signs_len[i]):
                    if X.iloc[obj][X.columns[i]] == self.signs[i][j]:
                        ret_mas[obj][temp + j] = 1
                        break
                temp += self.signs_len[i]
        return ret_mas

    def fit_transform(self, X, Y=None):
        self.fit(X)
        return self.transform(X)

    def get_params(self, deep=True):
        return {"dtype": self.dtype}


class SimpleCounterEncoder:

    def __init__(self, dtype=np.float64):
        self.dtype = dtype

    def fit(self, X, Y):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: target for training objects, pandas-series, shape [n_objects,]
        """
        self.list_signs = []
        for i in X.columns:
            temp = {}
            temp_name = X[i]
            for j in X[i].unique():
                temp[j] = (np.mean(Y[temp_name == j]), len(Y[temp_name == j]) / len(Y))
            self.list_signs.append(temp)

    def transform(self, X, a=1e-5, b=1e-5):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        param a: constant for counters, float
        param b: constant for counters, float
        returns: transformed objects, numpy-array, shape [n_objects, 3]
        """
        ret_mas = np.zeros((X.shape[0], X.shape[1] * 3), dtype=self.dtype)
        col = list(X.columns)
        for i in range(len(col)):
            for key, value in self.list_signs[i].items():
                ret_mas[X[col[i]] == key, 3 * i] = value[0]
                ret_mas[X[col[i]] == key, 3 * i + 1] = value[1]
                ret_mas[X[col[i]] == key, 3 * i + 2] = (value[0] + a) / (value[1] + b)
        return ret_mas

    def fit_transform(self, X, Y, a=1e-5, b=1e-5):
        self.fit(X, Y)
        return self.transform(X, a, b)

    def get_params(self, deep=True):
        return {"dtype": self.dtype}


def group_k_fold(size, n_splits=3, seed=1):
    idx = np.arange(size)
    np.random.seed(seed)
    idx = np.random.permutation(idx)
    n_ = size // n_splits
    for i in range(n_splits - 1):
        yield idx[i * n_: (i + 1) * n_], np.hstack((idx[:i * n_], idx[(i + 1) * n_:]))
    yield idx[(n_splits - 1) * n_:], idx[:(n_splits - 1) * n_]


class FoldCounters:

    def __init__(self, n_folds=3, dtype=np.float64):
        self.dtype = dtype
        self.n_folds = n_folds

    def fit(self, X, Y, seed=1):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: target for training objects, pandas-series, shape [n_objects,]
        param seed: random seed, int
        """
        self.fold = [(i[0], i[1]) for i in group_k_fold(len(X), self.n_folds, seed)]
        self.list_coder = [SimpleCounterEncoder() for i in range(self.n_folds)]
        for i, j in enumerate(self.fold):
            self.list_coder[i].fit(X.iloc[j[1]], Y.iloc[j[1]])

    def transform(self, X, a=1e-5, b=1e-5):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        param a: constant for counters, float
        param b: constant for counters, float
        returns: transformed objects, numpy-array, shape [n_objects, 3]
        """
        ret_mas = np.zeros((X.shape[0], X.shape[1] * 3), dtype=self.dtype)
        for i, j in enumerate(self.fold):
            ret_mas[j[0]] = self.list_coder[i].transform(X.iloc[j[0]], a, b)
        return ret_mas

    def fit_transform(self, X, Y, a=1e-5, b=1e-5):
        self.fit(X, Y)
        return self.transform(X, a, b)


def weights(x, y):
    """
    param x: training set of one feature, numpy-array, shape [n_objects,]
    param y: target for training objects, numpy-array, shape [n_objects,]
    returns: optimal weights, numpy-array, shape [|x unique values|,]
    """
    ret_list = np.zeros(len(np.unique(x)), dtype=np.float64)
    for i, j in enumerate(np.unique(x)):
        if len(y[x == j]) == sum(y[x == j]):
            ret_list[i] = 1
        elif sum(y[x == j]) == 0:
            ret_list[i] = 0
        else:
            ret_list[i] = sum(y[x == j]) / (len(y[x == j]))
    return ret_list
