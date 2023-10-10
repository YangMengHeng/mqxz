import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import plotly
import plotly.graph_objs as go
from LinearRegression import LinearRegression

plotly.offline.init_notebook_mode()

if __name__ == '__main__':
    data = pd.read_csv('./external/data/world-happiness-report-2017.csv')
    trainData = data.sample(frac = 0.8)
    testData = data.drop(trainData.index)

    inputParaName = ['Economy..GDP.per.Capita.', 'Freedom']
    outputParaName = 'Happiness.Score'

    # xTrain = trainData[[inputParaName[0], inputParaName[1]]].values
    xTrain = trainData[[x for x in inputParaName]].values
    yTrain = trainData[[outputParaName]].values

    xTest = testData[[x for x in inputParaName]].values
    yTest = testData[[outputParaName]].values

    plotTrainTrace =go.Scatter3d(
        x = xTrain[:, 0].flatten(),
        y = xTrain[:, 1].flatten(),
        z = yTrain.flatten(),
        name = 'Traning Set',
        mode = 'markers',
        marker = {
            'size': 10,
            'opacity': 1,
            'line': {
                'color': 'rgb(255,255,255)',
                'width': 1
            },
        }
    )

    plotTestTrace = go.Scatter3d(
        x = xTest[:, 0].flatten(),
        y = xTest[:, 1].flatten(),
        z = yTest.flatten(),
        name='Test Set',
        mode='markers',
        marker={
            'size': 10,
            'opacity': 1,
            'line': {
                'color': 'rgb(255, 255, 255)',
                'width': 1
            },
        }
    )

    plotLayout = go.Layout(
        title='Date Sets',
        scene={
            'xaxis': {'title': inputParaName[0]},
            'yaxis': {'title': inputParaName[1]},
            'zaxis': {'title': outputParaName}
        },
        margin={'l': 0, 'r': 0, 'b': 0, 't': 0}
    )

    plotData = [plotTrainTrace, plotTestTrace]
    plotFigure = go.Figure(data=plotData, layout=plotLayout)
    plotly.offline.plot(plotFigure)

    numIterations = 500
    learningRate = 0.01
    Lr = LinearRegression(xTrain, yTrain)
    (theta, costHistory) = Lr.train(learningRate, numIterations)
    print('const history first : ', costHistory[0])
    print('const history last  : ', costHistory[-1])

    predictNums = 10
    # xPredictions = np.zeros((predictNums ** 2, 2))
    x_predictions = np.zeros((predictNums ** 2, 1))
    y_predictions = np.zeros((predictNums ** 2, 1))

    x_min = xTrain[:, 0].min()
    x_max = xTrain[:, 0].max()
    y_min = xTrain[:, 1].min()
    y_max = xTrain[:, 1].max()
    x_axis = np.linspace(x_min, x_max, predictNums)
    y_axis = np.linspace(y_min, y_max, predictNums)

    x_y_index = 0
    for x_index, x_value in enumerate(x_axis):
        for y_index, y_value in enumerate(y_axis):
            x_predictions[x_y_index] = x_value
            y_predictions[x_y_index] = y_value
            x_y_index += 1

    z_predictions = Lr.predict(np.hstack((x_predictions, y_predictions)))

    plot_predictions_trace = go.Scatter3d(
        x=x_predictions.flatten(),
        y=y_predictions.flatten(),
        z=z_predictions.flatten(),
        name='Prediction Plane',
        mode='markers',
        marker={
            'size': 1,
        },
        opacity=0.8,
        surfaceaxis=2,
    )

    plot_data = [plotTrainTrace, plotTestTrace, plot_predictions_trace]
    plot_figure = go.Figure(data=plot_data, layout=plotLayout)
    plotly.offline.plot(plot_figure)

    # for i in range(len(inputParaName)):
    #     xMin = xTrain[:, i].min()
    #     xMax = xTrain[:, i].max()
    #     # xPredictions = np.linspace(xMin, yMin, predictNums).reshape(predictNums, 1)
    #     xAxis = np.linspace(xMin, xMax, predictNums)
    #     XIndex = 0
    #     for xIndex, xValue in enumerate(xAxis):
    #         xPredictions[i, XIndex] = xValue
    #         XIndex += 1
    #
    # zPredictions = Lr.predict(np.hstack((x for x in xPredictions)))
    #
    # plotPredictionsTrace = go.Scatter3d(
    #     x = xPredictions[0].flatten(),
    #     y = xPredictions[1].flatten(),
    #     z = zPredictions.flatten(),
    #     name='Prediction Plane',
    #     mode='markers',
    #     marker={
    #         'size': 1,
    #     },
    #     opacity=0.8,
    #     surfaceaxis=2,
    # )
    #
    # plot_data = [plotTrainTrace, plotTestTrace, plotPredictionsTrace]
    # plot_figure = go.Figure(data=plot_data, layout=plotLayout)
    # plotly.offline.plot(plot_figure)