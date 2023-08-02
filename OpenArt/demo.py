#线性拟合：y=a+bx
import numpy as np
x_array = np.array([119,
129,
145,
157,
164,
167,
174,
138,
134,
130,
122


])#x_array,y_array是我们要拟合的数据
y_array = np.array([97,
94,
91,
88,
86,
85,
84,
93,
93,
95,
96


])
m = len(x_array) #方程个数
 
sum_x = np.sum(x_array)
sum_y = np.sum(y_array)
sum_xy = np.sum(x_array * y_array)
sum_xx = np.sum(x_array **2 )
a=(sum_y*sum_xx-sum_x*sum_xy)/(m*sum_xx-(sum_x)**2)
b=(m*sum_xy-sum_x*sum_y)/(m*sum_xx-(sum_x)**2)
print("p = {:.4f} + {:.4f}x".format(a,b))