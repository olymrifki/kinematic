from sympy import *

'''''''''''''''''
berlaku untuk selain kaki tengah
'''''''''''''''''


x = Symbol('x')
C = Symbol('C')
F = Symbol('F')
T = Symbol('T')
t1= Symbol('t1')
t2= Symbol('t2')
t3 = Symbol('t3')
print (2*x)

H1 = Matrix([[cos(t1), 0, sin(t1) , C*cos(t1)],
            [sin(t1), 0, -cos(t1), C*sin(t1)],
            [0, 1, 0, 0],
            [0, 0, 0, 1]])
H2 = Matrix([[cos(t2), -sin(t2), 0 , F*cos(t2)],
            [sin(t2), cos(t2), 0, F*sin(t2)],
            [0, 0, 1, 0],
            [0, 0, 0, 1]])
H3 = Matrix([[cos(t3), -sin(t3), 0 , T*sin(t3)],
            [sin(t3), cos(t3), 0, -T*cos(t3)],
            [0, 0, 1, 0],
            [0, 0, 0, 1]])

p = Matrix([0, 0, 0, 1])

x = (H1*H2*H3*p).row(0)
y = (H1*H2*H3*p).row(1)
z = (H1*H2*H3*p).row(2)
print (x)
print (y)
print (z)
while true:
    t11 = input("t11 = ")
    t22 = input("t22 = ")
    t33 = input("t33 = ")
    mode = input("mode: ")
    t11 = float(t11)
    t22 = float(t22)
    t33 = float(t33)
    
    x1 = x.subs([(t1, t11*3.14159/180), (t2, -1*t22*3.14159/180), (t3, t33*3.14159/180),
                   (C, 30), (F, 59), (T, 72)])
    
    y1 = y.subs([(t1, t11*3.14159/180), (t2, -1*t22*3.14159/180), (t3, t33*3.14159/180),
                   (C, 30), (F, 59), (T, 72)])


    if (mode == "l1") :
        x2 = (x1+y1)*sqrt(2)/2
        y2 = (y1-x1)*sqrt(2)/2
    elif (mode == "l2") :
        x2 = x1
        y2 = y1
    print ("hasil x: ")
    print (x2.evalf())
    print ("hasil y: ")
    print (y2.evalf())
    print ("hasil z: ")
    print (-1*z.subs([(t1, t11*3.14159/180), (t2, -1*t22*3.14159/180), (t3, t33*3.14159/180),
                   (C, 30), (F, 59), (T, 72)]))


"""
forward kinematic lama
H1 = Matrix([[cos(t1), 0, sin(t1) , 0],
            [sin(t1), 0, -cos(t1), 0],
            [0, 1, 0, -C],
            [0, 0, 0, 1]])
H2 = Matrix([[cos(t2), -sin(t2), 0 , F*cos(t2)],
            [sin(t2), cos(t2), 0, F*sin(t2)],
            [0, 0, 1, 0],
            [0, 0, 0, 1]])
H3 = Matrix([[cos(t3), -sin(t3), 0 , T*sin(t3)],
            [sin(t3), cos(t3), 0, -T*cos(t3)],
            [0, 0, 1, 0],
            [0, 0, 0, 1]])
print(H1*H2*H3)

Matrix([[-sin(t2)*sin(t3)*cos(t1) + cos(t1)*cos(t2)*cos(t3), -sin(t2)*cos(t1)*cos(t3) - sin(t3)*cos(t1)*cos(t2), sin(t1), F*cos(t1)*cos(t2) + T*sin(t2)*cos(t1)*cos(t3) + T*sin(t3)*cos(t1)*cos(t2)],
        [-sin(t1)*sin(t2)*sin(t3) + sin(t1)*cos(t2)*cos(t3), -sin(t1)*sin(t2)*cos(t3) - sin(t1)*sin(t3)*cos(t2), -cos(t1), F*sin(t1)*cos(t2) + T*sin(t1)*sin(t2)*cos(t3) + T*sin(t1)*sin(t3)*cos(t2)],
        [sin(t2)*cos(t3) + sin(t3)*cos(t2), -sin(t2)*sin(t3) + cos(t2)*cos(t3), 0, -C + F*sin(t2) + T*sin(t2)*sin(t3) - T*cos(t2)*cos(t3)],
        [0, 0, 0, 1]])
"""
