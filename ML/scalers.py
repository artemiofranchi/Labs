import numpy as np


class MinMaxScaler:
    def fit(self, data):
        self.min = data.min(axis=0)
        self.max = data.max(axis=0)

    def transform(self, data):
        transformedarray = np.zeros((data.shape[0], data.shape[1]))
        for i in range(data.shape[0]):
            for j in range(data.shape[1]):
                transformedarray[i][j] = (data[i][j] - self.min[j]) / (self.max[j]-self.min[j])
        return transformedarray


class StandardScaler:
    def fit(self, data):
        self.mathexp = np.mean(data, axis=0)
        self.deviation = np.std(data, axis=0)

    def transform(self, data):
        transformedarray = np.zeros((data.shape[0], data.shape[1]))
        for i in range(data.shape[0]):
            for j in range(data.shape[1]):
                transformedarray[i][j] = (data[i][j] - self.mathexp[j]) / self.deviation[j]
        return transformedarray
