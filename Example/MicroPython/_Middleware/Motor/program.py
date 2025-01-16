#include "%ORB%\Middleware\MicroPython\drive.py"
#include "%ORB%\Middleware\MicroPython\motor.py"
#include "%ORB%\Middleware\MicroPython\monitor.py"

from devices import motor
import time
import monitor
from monitor import keys
import time
import memory
import math

m1 = MB_Motor(port=0,orientation=1)

s = m1.getPosition()

mon = Monitor()
mon.print(0,"Motor v00.96")

while True:

  e = mon.getKeyEvent()
  if e == keys.A1:
    s = s + 1000
    print("moveto:"+str(s))

  if e == keys.A2:
    s = s - 1000
    print("moveto:"+str(s))

  mon.print(1,"Power="+str(m1.getPower()))
  mon.print(2,"Speed="+str(m1.getSpeed()))
  mon.print(3,"Pos  ="+str(m1.getPosition())+" ("+str(s)+")")

  m1.setPosition(2000,s)
  

