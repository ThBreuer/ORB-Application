#include "%ORB%/Middleware/MicroPython/memory.py"
#include "%ORB%/Middleware/MicroPython/monitor.py"
#include "%ORB%/Middleware/MicroPython/motor.py"
#include "%ORB%/Middleware/MicroPython/drive.py"
#include "%ORB%/Middleware/MicroPython/sensor.py"


#********************************************************************
#
# Beispielanwendung
#
#  - 
#
#
#********************************************************************/

import monitor
from monitor import keys
import time

LEFT  = 1
RIGHT = 0
WHITE = 1
BLACK = 0

if getArg() == 0:
  speed = 50
else:
  speed = 120

robo = Drive( motorLeft     = MB_Motor( Motor.M1, Motor.REVERSE ),
              motorRight    = MB_Motor( Motor.M4, Motor.NORMAL  ),        
              vmax          =  10*speed,  # Max. Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
              wheelDiameter =  62,        # Durchmesser der Räder (mm)
              trackWidth    = 92         # Abstand der Räder (mm)
             )

lf = MB_LineFollower( Sensor.S1 )
ab = MB_Ultrasonic  ( Sensor.S4 )

mon = Monitor()
mon.print( 1, "Line-Follower   speed: {:.d}".format(speed) )

while True:
  left  = lf.get(LEFT)
  right = lf.get(RIGHT)
  ahead = ab.get()

  mon.print( 2, "left:    {:4d}   right:{:4d}".format(left,right) )
  mon.print( 3, "ahead:   {:4d}"              .format(ahead) )
  mon.print( 4, "distance:{:4d}   angle:{:4d}".format(robo.distance(),robo.angle()%360) )

  if left == BLACK and right == BLACK:
    robo.speed( speed, speed )

  if left == BLACK and right == WHITE:
    robo.speed( 0.2*speed, speed )

  if left == WHITE and right == BLACK:
    robo.speed( speed, 0.2*speed )

  if left == WHITE and right == WHITE:
    robo.speed( -0.0*speed, -0.0*speed )

  if ahead < 50:
    robo.speed(0,0)
    time.wait( 200 )
    robo.track( -25, 0 )
    robo.track( 0, 180 )
    robo.track( -25, 0 )
