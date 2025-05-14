# Color & Light
#--------------

#include "%ORB%\Middleware\MicroPython\monitor.py"
#include "%ORB%\Middleware\MicroPython\memory.py"
#include "%ORB%\Middleware\MicroPython\sensor.py"

import monitor
from monitor import keys

mon = Monitor()

#********************************************************************
def testColorLight():
     
    s1 = Ev3_Color(port = Sensor.S1, mode = Ev3_Color.COLOR)
    s2 = Nxt_Light(port = Sensor.S2, light=True)
       
    m1 = Ev3_Color.COLOR
    m2 = 1
   

    while True:
        event = mon.getKeyEvent()
        
        if event == keys.B12:
            break

        if event == keys.B1:
            m1 = (m1+1)%3
            s1.setMode(m1)

        if event == keys.B4:
            m2 = not m2
            s2.setMode(m2)
        
        if event == keys.A1:
            s1.calibrationWhite()
            s2.calibrationWhite()
        if event == keys.A5:
            s1.calibrationBlack()
            s2.calibrationBlack()
        if event == keys.C1:
            Memory.store()
            
        mon.print(1,"Ev3_Color ("+str(m1)     +"): "+str(s1.get()))
        mon.print(2,"Nxt_Light ("+str(int(m2))+"): "+str(s2.get()))

#********************************************************************
def testDistance():

    s1 = Ev3_Infrared   (port = Sensor.S1)
    s2 = Ev3_Ultrasonic (port = Sensor.S2)
    s3 = MB_Ultrasonic  (port = Sensor.S3)
    s4 = Nxt_Ultrasonic (port = Sensor.S4)

    while True:
        event = mon.getKeyEvent()
        
        if event == keys.B12:
            break
            
        mon.print(1,"Ev3_Infrared:   "+str(s1.get()))
        mon.print(2,"Ev3_Ultrasonic: "+str(s2.get()))
        mon.print(3,"MB_Ultrasonic:  "+str(s3.get()))
        mon.print(4,"Nxt_Ultrasonic: "+str(s4.get()))

#********************************************************************
def testGyroTouch():

    s1 = Ev3_Gyro       (port = Sensor.S1, mode = Ev3_Gyro.ANGLE)
    s2 = Ev3_Touch      (port = Sensor.S2)
    s3 = MB_LineFollower(port = Sensor.S3)
    s4 = Nxt_Touch      (port = Sensor.S4)
    
    m1 = Ev3_Gyro.ANGLE

    while True:
        event = mon.getKeyEvent()

        if event == keys.B12:
            break
            
        if event == keys.B1:
            m1 = (m1+1)%2
            s1.setMode(m1)
         
        mon.print(1,"Ev3_Gyro ("+str(m1)+")   : "+str(s1.get()))
        mon.print(2,"Ev3_Touch      : "               +str(s2.get()))
        mon.print(3,"MB_LineFollower: "               +str(s3.get(0))+","+str(s3.get(1)))
        mon.print(4,"Nxt_Touch      : "               +str(s4.get()))


#********************************************************************
def testDigital():

    while True:
        event = mon.getKeyEvent()

        if event == keys.B12:
            break
            
        #s = sensor() #.getDigital() 
        mon.print(1,"D1  : "+str(sensor.getDigital(0)))
        mon.print(2,"D2  : "+str(sensor.getDigital(1)))


#********************************************************************
while True:
    mon.print(1,"A - Color + Light")
    mon.print(2,"B - Distance")
    mon.print(3,"C - Gyro + Touch")
    mon.print(4,"D - Digital D1/D2")
        
    event = mon.getKeyEvent()
    
    if event != 0:
        mon.clear()
        
    if event == keys.B2:
        testColorLight()
        
    if event == keys.B5:
        testDistance()
        
    if event == keys.B8:
        testGyroTouch()
        
    if event == keys.B11:
        testDigital()
        

        