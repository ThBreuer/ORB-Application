#include "%ORB%\Middleware\MicroPython\drive.py"
#include "%ORB%\Middleware\MicroPython\motor.py"
#include "%ORB%\Middleware\MicroPython\monitor.py"

from devices import motor
from monitor import keys
import time
import monitor
import memory
import math

drive = Drive( motorLeft     = MB_Motor( Motor.M1, Motor.REVERSE ),
               motorRight    = MB_Motor( Motor.M4, Motor.NORMAL  ),        
               vmax          = 1000, 
               wheelDiameter =  40,
               trackWidth    =  144)
 
mon = Monitor()
mon.setText(0,"Drive v00.98")

while True:
  event = mon.getKeyEvent()
  if event == keys.A1:
    drive.track(+100,+90)
    drive.power(0,0)

  if event == keys.A5:
    drive.track(distance=-100,angle=-90)
    drive.brake()

  if event == keys.A2:
    drive.track(distance=100,angle=0)

  if event == keys.A6:
    drive.track(distance=-100,angle=0)

  if event == keys.A4:
    while True:
      drive.track(distance=-100,angle=0)
      drive.track(distance=0,angle=+90)
      drive.track(distance=0,angle=-90)
      drive.track(distance=+100,angle=0)

  if event == keys.A7:
    drive.speed(100,100)
    time.wait(1000) 
    mon.setText(1,"d="+str(int(drive.distance()))+" w="+str(int(drive.angle())))
    d=drive.distance()
    drive.track(distance=-d,angle=0)

  mon.setText(1,"d="+str(int(drive.distance()))+" w="+str(int(drive.angle())))
