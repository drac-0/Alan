import matplotlib.pyplot as plt
import ctypes


lib = ctypes.CDLL("./import.so")

class csvData(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int),
                ("y", ctypes.c_float)
                ]

class mainData(ctypes.Structure):
    _fields_ = [("Data",ctypes.POINTER(csvData)),
                ("length", ctypes.c_uint)
                ]

class LinearRes(ctypes.Structure):
    _fields_ = [("Slope", ctypes.c_float),
                ("Bias", ctypes.c_float),
                ("Lireg",ctypes.c_float),
                ("MSE",ctypes.c_float),
                ("MAE",ctypes.c_float),
                ("RMSE",ctypes.c_float),
                ("mainData", csvData),
                ("Y_Predict", ctypes.POINTER(ctypes.c_float))
                ]

dataPtr = ctypes.POINTER(csvData)
mainPtr = ctypes.POINTER(mainData)
ResPtr = ctypes.POINTER(LinearRes)

getCSV = lib.readCSVpy
getCSV.argtypes = [ctypes.c_char_p]
getCSV.restype = mainPtr
pCSVdat = lib.readCSVpy(b"./slr_data.csv");

ActData = pCSVdat.contents.Data
dataLen = pCSVdat.contents.length

X_Val = [ActData[i].x for i in range(dataLen)]
Y_Val = [ActData[i].y for i in range(dataLen)]

Lireg = lib.assembled
Lireg.argtypes = [ctypes.c_char_p]
Lireg.restype = ResPtr
pLireg = lib.assembled(b"./slr_data.csv")

PtrPr = pLireg.contents.Y_Predict
YPredict = [PtrPr[x] for x in range(dataLen)]

plt.scatter(X_Val, Y_Val)
plt.plot(X_Val, YPredict, color='red', linewidth = 2)
plt.legend()
plt.show()
