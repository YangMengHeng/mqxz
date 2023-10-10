import numpy as np
from external.utils.features import prepare_for_training as pft

class LinearRegression:
    def __init__(self, data, labels, polynomial_degree=0, sinusoid_degree=0, normalize_data=True):
        (dataProcessed, featuresMean, featuresDeviation) = pft(data, polynomial_degree, sinusoid_degree, normalize_data)
        self.data = dataProcessed
        self.labels = labels
        self.featuresMean = featuresMean
        self.featuresDeviation = featuresDeviation
        self.polynomial_degree = polynomial_degree
        self.sinusoid_degree = sinusoid_degree
        self.normalize_data = normalize_data

        numFeatures = self.data.shape[1]
        self.theta = np.zeros((numFeatures, 1))

    def train(self, alpha, numItreations = 500):
        costHistory = self.gradientDescent(alpha, numItreations)

        return self.theta, costHistory

    def gradientDescent(self, alpha, numItreations = 500):
        costHistory = []
        for _ in range(numItreations):
            self.gradientStep(alpha)
            costHistory.append(self.costFunction(self.data, self.labels))

        return costHistory

    def gradientStep(self, alpha):
        numExamples = self.data.shape[0]
        prediction = LinearRegression.hypothesis(self.data, self.theta)
        delta = prediction - self.labels
        newTheta = self.theta
        newTheta = newTheta - alpha * (1 / numExamples) * (np.dot(delta.T, self.data)).T
        self.theta = newTheta

    def costFunction(self, data, labels):
        numExamples = data.shape[0]
        delta = LinearRegression.hypothesis(self.data, self.theta) - labels
        cost = (1 / 2) * np.dot(delta.T, delta) / numExamples

        return cost[0][0]

    def getCost(self, data, labels):
        dataProcessed = pft(data, self.polynomial_degree, self.sinusoid_degree, self.normalize_data)[0]

        return self.costFunction(dataProcessed, labels)

    def predict(self, data):
        dataProcessed = pft(data, self.polynomial_degree, self.sinusoid_degree, self.normalize_data)[0]
        predictions = LinearRegression.hypothesis(dataProcessed, self.theta)
        return predictions

    @staticmethod
    def hypothesis(data, theta):
        predictions = np.dot(data, theta)

        return predictions