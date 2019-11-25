#左手系(绕轴旋转必须遵循左手系）
#欧拉角（不是所有的欧拉角都可以转换成功，尽量避免万向锁）转四元数
import math as mt
import numpy as np

print("\nAll of the rotation value is based on left-hand system\n")
x_ratio = input("x_ration(radians)-Raw")#raw
z_ratio = input("z_ration(radians)-Pitch")#pitch
y_ratio = input("y_ration(radians)-Yaw")#yaw
x_ratio = mt.radians(float(x_ratio))
y_ratio = mt.radians(float(y_ratio))
z_ratio = mt.radians(float(z_ratio))


cy = mt.cos(y_ratio/2)
sy = mt.sin(y_ratio/2)

sx = mt.sin(x_ratio/2)
cx =mt.cos(x_ratio/2)

cz = mt.cos(z_ratio/2)
sz = mt.sin(z_ratio/2)


x = cy*sx*cz + sy*cx*sz
y = sy*cx*cz - cy*sx*sz
z = -sy*sx*cz + cy*cx*sz
w = cy*cx*cz + sy*sx*sz

print("\nRotation axis: x={} y={} z={} w={}".format(x,y,z,w))

print("ratation theta:",2*mt.degrees(mt.acos(w)))

print("validation:x^2+y^2+z^2+w^2 = ",mt.pow(x,2)+mt.pow(y,2)+mt.pow(z,2)+mt.pow(w,2))

#Calculate Rotation Matrix
r11 = 1-2*mt.pow(y,2)-2*mt.pow(z,2)
r12 = 2*x*y + 2*w*z
r13 = 2*x*z - 2*w*y

r21 = 2*x*y - 2*w*z
r22 = 1-2*mt.pow(x,2)-2*mt.pow(z,2)
r23 = 2*y*z + 2*w*x

r31 = 2*x*z + 2*w*y
r32 = 2*y*z - 2*w*x
r33 = 1-2*mt.pow(x,2)-2*mt.pow(y,2)

R = np.array([[ r11, r12, r13],
              [ r21, r22, r23],
              [ r31, r32, r33]]).astype('float64')

X = np.array([[1],
                      [0],
                       [0]]).astype('float64')
#Output  the value of vector [1,0,0] 
print("\n[1,0,0] relating->\n",np.matmul(R, X))


