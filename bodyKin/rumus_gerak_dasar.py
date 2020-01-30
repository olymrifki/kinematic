'''
OUTPUT: POSISI KAKI YANG BELUM DIINVERSE
'''
from sympy import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as math
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')




x = Symbol('x')
y = Symbol('y')
z = Symbol('z')

H = Symbol('H')

F = Symbol('F')
T = Symbol('T')
t1= Symbol('t1')
t2= Symbol('t2')
t3 = Symbol('t3')
t11= Symbol('t11')
t22= Symbol('t22')
t33 = Symbol('t33')

X = Matrix([[1, 0, 0],
            [0, cos(t1), -sin(t1)],
            [0, sin(t1), cos(t1)]])
Y = Matrix([[cos(t1),0, sin(t1)],
            [0, 1, 0],
            [-sin(t1), 0, cos(t1)]])
Z = Matrix([[cos(t1), -sin(t1), 0],
            [sin(t1), cos(t1), 0],
            [0, 0, 1]])



V = Matrix([x, y, H])

print((X*V).subs([(t1, t11)]) - X*V)
print((Y*V).subs([(t2, t22)]) - Y*V)
print((Z*V).subs([(t3, t33)]) - Z*V)


sudutlamax = 0
sudutlamay = 0
sudutlamaz = 0
i =0
##posisi tiap kaki dari tengah
L1 = V.subs([(H, -56), (y, 50), (x, -30)])
L2 = V.subs([(H, -56), (y, 0), (x, -30)])
L3 = V.subs([(H, -56), (y, -50), (x, -30)])
R1 = V.subs([(H, -56), (y, 50), (x, 30)])
R2 = V.subs([(H, -56), (y, 0), (x, 30)])
R3 = V.subs([(H, -56), (y, -50), (x, 30)])
L11 = V.subs([(H, -56), (y, 50), (x, -30)])
L22 = V.subs([(H, -56), (y, 0), (x, -30)])
L33 = V.subs([(H, -56), (y, -50), (x, -30)])
R11 = V.subs([(H, -56), (y, 50), (x, 30)])
R22 = V.subs([(H, -56), (y, 0), (x, 30)])
R33 = V.subs([(H, -56), (y, -50), (x, 30)])

dL1 = V.subs([(H, 72), (y, -63), (x, 63)])
dLtengah = V.subs([(H, 72), (y, 0), (x, 89)]) 
dL3 = V.subs([(H, 72), (y, -63), (x, 63)])
dR1 = V.subs([(H, 72), (y, -63), (x, 63)])
dRtengah = V.subs([(H, 72), (y, 0), (x, 89)])
dR3 = V.subs([(H, 72), (y, -63), (x, 63)])


while i < 18:
    
    i +=1
    '''
    ##geser kaki ujung
    dx = float(input('dx: '))
    dy = float(input('dy: '))
    dz = float(input('dz: '))
    delta = V.subs([(H, dz), (y, dy), (x, dx)])
    print('Delta : ')
    print(delta+d)
    print('Delta tengah : ')
    print(delta+dtengah)
'''##rotate perkaki
    mode = (input('mode :' ))   
    ##4 mode: x(pitch), y(roll), z (yaw), r (reset)

    if mode == 'x':
        sudutbaru = float(input('sudut akhir: '))
        deltaL1 = (X*L11).subs([(t1, (sudutbaru)*math.pi/180)])-(L1)
        deltaL2 = (X*L22).subs([(t1, (sudutbaru)*math.pi/180)])-(L2)            
        deltaL3 = (X*L33).subs([(t1, (sudutbaru)*math.pi/180)])-(L3)
        deltaR1 = (X*R11).subs([(t1, (sudutbaru)*math.pi/180)])-(R1)
        deltaR2 = (X*R22).subs([(t1, (sudutbaru)*math.pi/180)])-(R2)
        deltaR3 = (X*R33).subs([(t1, (sudutbaru)*math.pi/180)])-(R3)
        
    
                     
        L11 = (X*L11).subs([(t1, sudutbaru*math.pi/180)])
        L22 = (X*L22).subs([(t1, sudutbaru*math.pi/180)])            
        L33 = (X*L33).subs([(t1, sudutbaru*math.pi/180)])
        R11 = (X*R11).subs([(t1, sudutbaru*math.pi/180)])
        R22 = (X*R22).subs([(t1, sudutbaru*math.pi/180)])
        R33 = (X*R33).subs([(t1, sudutbaru*math.pi/180)])        
   
        print('Delta L1 : ')
        print(deltaL1+dL1)
        print('Delta L2 : ')
        print(deltaL2+dLtengah)
        print('Delta L3 : ')
        print(deltaL3+dL3)
        print('Delta R1 : ')
        print(deltaR1+dR1)
        print('Delta R2 : ')
        print(deltaR2+dRtengah)
        print('Delta R3 : ')
        print(deltaR3+dR3)
            
    
    if mode == 'y':
        sudutbaru = float(input('sudut akhir: '))
        deltaL1 = (Y*L11).subs([(t1, (sudutbaru)*math.pi/180)])-(L1)
        deltaL2 = (Y*L22).subs([(t1, (sudutbaru)*math.pi/180)])-(L2)            
        deltaL3 = (Y*L33).subs([(t1, (sudutbaru)*math.pi/180)])-(L3)
        deltaR1 = (Y*R11).subs([(t1, (sudutbaru)*math.pi/180)])-(R1)
        deltaR2 = (Y*R22).subs([(t1, (sudutbaru)*math.pi/180)])-(R2)
        deltaR3 = (Y*R33).subs([(t1, (sudutbaru)*math.pi/180)])-(R3)
        
    
        sudutlamay+=sudutbaru             
        L11 = (Y*L11).subs([(t1, sudutbaru*math.pi/180)])
        L22 = (Y*L22).subs([(t1, sudutbaru*math.pi/180)])            
        L33 = (Y*L33).subs([(t1, sudutbaru*math.pi/180)])
        R11 = (Y*R11).subs([(t1, sudutbaru*math.pi/180)])
        R22 = (Y*R22).subs([(t1, sudutbaru*math.pi/180)])
        R33 = (Y*R33).subs([(t1, sudutbaru*math.pi/180)])        
   
        print('Delta L1 : ')
        print(deltaL1+dL1)
        print('Delta L2 : ')
        print(deltaL2+dLtengah)
        print('Delta L3 : ')
        print(deltaL3+dL3)
        print('Delta R1 : ')
        print(deltaR1+dR1)
        print('Delta R2 : ')
        print(deltaR2+dRtengah)
        print('Delta R3 : ')
        print(deltaR3+dR3)

    if mode == 'z':
        sudutbaru = float(input('sudut akhir: '))
        deltaL1 = (Z*L11).subs([(t1, (sudutbaru)*math.pi/180)])-(L1)
        deltaL2 = (Z*L22).subs([(t1, (sudutbaru)*math.pi/180)])-(L2)            
        deltaL3 = (Z*L33).subs([(t1, (sudutbaru)*math.pi/180)])-(L3)
        deltaR1 = (Z*R11).subs([(t1, (sudutbaru)*math.pi/180)])-(R1)
        deltaR2 = (Z*R22).subs([(t1, (sudutbaru)*math.pi/180)])-(R2)
        deltaR3 = (Z*R33).subs([(t1, (sudutbaru)*math.pi/180)])-(R3)
        
    
        sudutlamaz+=sudutbaru             
        L11 = (Z*L11).subs([(t1, sudutbaru*math.pi/180)])
        L22 = (Z*L22).subs([(t1, sudutbaru*math.pi/180)])            
        L33 = (Z*L33).subs([(t1, sudutbaru*math.pi/180)])
        R11 = (Z*R11).subs([(t1, sudutbaru*math.pi/180)])
        R22 = (Z*R22).subs([(t1, sudutbaru*math.pi/180)])
        R33 = (Z*R33).subs([(t1, sudutbaru*math.pi/180)])        
   
        print('Delta L1 : ')
        print(deltaL1+dL1)
        print('Delta L2 : ')
        print(deltaL2+dLtengah)
        print('Delta L3 : ')
        print(deltaL3+dL3)
        print('Delta R1 : ')
        print(deltaR1+dR1)
        print('Delta R2 : ')
        print(deltaR2+dRtengah)
        print('Delta R3 : ')
        print(deltaR3+dR3)

        
    if mode == 'r':
        sudutlamax = 0
        sudutlamay = 0
        sudutlamaz = 0
        L11 = V.subs([(H, -56), (y, 50), (x, -30)])
        L22 = V.subs([(H, -56), (y, 0), (x, -30)])
        L33 = V.subs([(H, -56), (y, -50), (x, -30)])
        R11 = V.subs([(H, -56), (y, 50), (x, 30)])
        R22 = V.subs([(H, -56), (y, 0), (x, 30)])
        R33 = V.subs([(H, -56), (y, -50), (x, 30)])

