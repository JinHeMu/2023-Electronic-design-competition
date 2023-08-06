#线性拟合：y=a+bx
import numpy as np
x_array = np.array([
37,
30,
47,
70,
82,
96,
109,
90,
72





])#x_array,y_array是我们要拟合的数据
y_array = np.array([
95,
96,
92,
87,
84,
81,
78,
83,
86







])
m = len(x_array) #方程个数
 
sum_x = np.sum(x_array)
sum_y = np.sum(y_array)
sum_xy = np.sum(x_array * y_array)
sum_xx = np.sum(x_array **2 )
a=(sum_y*sum_xx-sum_x*sum_xy)/(m*sum_xx-(sum_x)**2)
b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-(sum_x)**2)
print("p = {:.4f} + {:.4f}x".format(a,b))