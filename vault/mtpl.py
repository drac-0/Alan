import matplotlib.pyplot as plt
import numpy
import csv
import pandas
import ctypes
from sklearn.linear_model import LinearRegression

csv = pandas.read_csv("../slr_data.csv")

numX = csv["x"].to_numpy()
numY = csv["y"].to_numpy()

numX = numX.reshape(-1, 1)
numY = numY.reshape(-1, 1)

model = LinearRegression()
model.fit(numX, numY)

Prediction = model.predict(numX)

plt.scatter(list(csv["x"]), list(csv["y"]))
plt.plot(numX, Prediction, color='red', linewidth = 2)
plt.legend()
plt.show()
