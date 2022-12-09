import matplotlib.pyplot as plt
import numpy as np 

def readfile(filename,end):
    with open(filename,"r+") as f:
        lines = f.readlines()
        A=[]
		#end = len(lines)
        for i in range(len(lines)):
            A.append([float(j) for j in lines[i].split()])
        del lines
        return A

def zeromatrix(m,n):
        p= [[0 for i in range(n)] for j in range(m)]
        return(p)

def transpose(A):
        if not isinstance(A[0],list):
                A = [A]

        r = len(A)
        c = len(A[0])
        AT = zeromatrix(c, r)
        #Copy values from A to it's transpose AT
        for i in range(r):
                for j in range(c):
                        AT[j][i] = A[i][j]
        return AT

# x2 = [i for i in range(1024)]
# x1 = [i for i in range(2048)]
wo_fc = readfile("wo_fc.txt",2048)
wo_fc = transpose(wo_fc)
w_fc = readfile("w_fc.txt",1024)
w_fc = transpose(w_fc)
print(sum(wo_fc[0])/3, sum(w_fc[0])/15)
# print(len(w_fc[0]))
# for i in range(1024):
# 	w_fc[0][i] = w_fc[0][i]/15
# for i in range(2048):
# 	wo_fc[0][i] = wo_fc[0][i]/3


# plt.plot(x1,wo_fc[0],label="W/o faraday cage")
# plt.plot(x2,w_fc[0],label="With Faraday cage")
# plt.yscale("log")
# plt.grid()
# plt.xlabel("ADC ch (a.u.)")
# plt.ylabel("Count rate (Hz)")
# plt.legend()
# plt.show()