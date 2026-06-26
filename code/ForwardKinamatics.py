import math
import numpy as np

L=150
l=300
a =58.32
b=((math.sqrt(3))/2)*(45-103.32)
c=(45-103.32)/2    
wb = 103.32               # Base side
ue = 45                   # End effector side              # Upper arm length
we = ue/2
sb = 2 * (math.sqrt(3)) * wb  # Base triangle side-to-side
se = 2 * (math.sqrt(3)) * (ue / 2)

pi = math.pi

def delta_calcForward(theta1, theta2, theta3):
    dtr = pi / 180.0
    theta1 *= dtr
    theta2 *= dtr
    theta3 *= dtr

    # Joint coordinates
    x1 = 0
    y1 = -(wb + L * np.cos(theta1)) + ue
    z1 = -L * np.sin(theta1)

    y2 = 0.5 * (wb + L * np.cos(theta2))- we
    x2 = (np.sqrt(3)/2) * (wb + L * np.cos(theta2)) - se/2
    z2 = -L * np.sin(theta2)

    y3 = 0.5 * (wb + L * np.cos(theta3)) - we
    x3 = -(np.sqrt(3)/2) * (wb + L * np.cos(theta3)) + se/2
    z3 = -L * np.sin(theta3)

    dnm = (y2 - y1) * x3 - (y3 - y1) * x2

    w1 = y1**2 + z1**2
    w2 = x2**2 + y2**2 + z2**2
    w3 = x3**2 + y3**2 + z3**2

    a1 = (z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1)
    b1 = -((w2 - w1) * (y3 - y1) - (w3 - w1) * (y2 - y1)) / 2.0

    a2 = -(z2 - z1) * x3 + (z3 - z1) * x2
    b2 = ((w2 - w1) * x3 - (w3 - w1) * x2) / 2.0

    a = a1**2 + a2**2 + dnm**2
    b = 2 * (a1 * b1 + a2 * (b2 - y1 * dnm) - z1 * dnm**2)
    c = (b2 - y1 * dnm)**2 + b1**2 + dnm**2 * (z1**2 - l**2)

    d = b**2 - 4 * a * c
    if d < 0:
        return -1, None, None, None

    z0 = -0.5 * (b + math.sqrt(d)) / a
    x0 = (a1 * z0 + b1) / dnm
    y0 = (a2 * z0 + b2) / dnm

    return 0, x0, y0, z0



def angle_1(x,y,z):
    
     u1 = 2 * 150 * (y + a)
     v1 = 2 * L * z
     w1 = math.pow(x, 2) + math.pow(y, 2) + math.pow(z, 2) + math.pow(a, 2) + math.pow(L, 2) + (2 * y * a) - math.pow(l, 2)
     t1 = (-v1 - math.sqrt(math.pow(u1, 2) + math.pow(v1, 2) - math.pow(w1, 2))) / (w1 - u1)
     a1 = 2 * (math.atan(t1) * (180 / math.pi))
     return a1
    
def angle_2( x,  y,  z):
    
    u2 = -150 * (math.sqrt(3) * (x + b) + y + c)
    v2 = 2 * L * z
    w2 = math.pow(x, 2) + math.pow(y, 2) + math.pow(z, 2) + math.pow(b, 2) + math.pow(c, 2) + math.pow(L, 2) + (2 * x * b) + (2 * y * c) - math.pow(l, 2)
    t2 = (-v2 - math.sqrt(math.pow(u2, 2) + math.pow(v2, 2) - math.pow(w2, 2))) / (w2 - u2)
    a2 = 2 * (math.atan(t2) * (180 / math.pi))
    return a2
    
def angle_3( x,  y,  z):
    
    u3 = 150 * (math.sqrt(3) * (x - b) - y - c)
    v3 = 2 * L * z
    w3 = math.pow(x, 2) + math.pow(y, 2) + math.pow(z, 2) + math.pow(b, 2) + math.pow(c, 2) + math.pow(L, 2) - (2 * x * b) + (2 * y * c) - math.pow(l, 2)
    t3 = (-v3 - math.sqrt(math.pow(u3, 2) + math.pow(v3, 2) - math.pow(w3, 2))) / (w3 - u3)
    a3 = 2 * (math.atan(t3) * (180 / math.pi))
    return a3

# Test angles
x0,y0,z0=-50,100,-400
status, x, y, z = delta_calcForward(angle_1(x0,y0,z0),angle_2(x0,y0,z0),angle_3(x0,y0,z0))

if status == 0:
    print(f"End effector position: x={x:.2f}, y={y:.2f}, z={z:.2f}")
else:
    print("No valid position for given angles.")


