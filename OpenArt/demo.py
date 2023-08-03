#线性拟合：y=a+bx
import numpy as np
x_array = np.array([
159,
123,
114,
150,
133,
135,
146,
159,
157



])#x_array,y_array是我们要拟合的数据
y_array = np.array([
82,
92,
94,
83,
88,
88,
84,
81,
82





])
m = len(x_array) #方程个数
 
sum_x = np.sum(x_array)
sum_y = np.sum(y_array)
sum_xy = np.sum(x_array * y_array)
sum_xx = np.sum(x_array **2 )
a=(sum_y*sum_xx-sum_x*sum_xy)/(m*sum_xx-(sum_x)**2)
b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-(sum_x)**2)
print("p = {:.4f} + {:.4f}x".format(a,b))