#include "%ORB%/Middleware/MicroPython/monitor.py"
#include "%ORB%/Middleware/MicroPython/motor.py"
#include "%ORB%/Middleware/MicroPython/drive.py"
#include "%ORB%/Middleware/MicroPython/memory.py"

#********************************************************************
#
# Beispielanwendung
#
#  - Fernsteuerung
#
#
#********************************************************************/

import monitor
from monitor import keys

mon = Monitor()
mon.print( 1, "Remote v00.98" )

robo = Drive( motorLeft     = MB_Motor( Motor.M1, Motor.REVERSE ),
              motorRight    = MB_Motor( Motor.M4, Motor.NORMAL  ),        
              vmax          = 1500,  # Max. Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
              wheelDiameter =   64,  # Durchmesser der Räder (mm)
              trackWidth    =   92   # Abstand der Räder (mm)
             )

_speed = MemoryItem(50)
speed = _speed.value

while True:
  mon.print( 2, "Speed:   "+str(speed)          +" mm/s" )
  mon.print( 3, "Strecke: "+str(robo.distance())+" mm"   )
  mon.print( 4, "Winkel:  "+str(robo.angle())   +" °"    )

  event = mon.getKeyEvent()
  if event == keys.A1:
    robo.track(    0, +90 )
  if event == keys.A5:
    robo.track(    0, -90 )
  if event == keys.A2: 
    robo.track( +100,   0 )
  if event == keys.A6:
    robo.track( -100,   0 )
  if event == keys.A3: 
    if speed <  500:
      speed = speed + 25
    else:
      speed = 1000
  if event == keys.A7:
    if speed >   25:
      speed = speed - 25
    else: 
      speed = 0

  if event == keys.C1: 
    _speed.value = speed
    Memory.store()

  state = mon.getKeyState()
  if state == 0: 
    robo.speed(       0,         0)
  if state == keys.B1:
    robo.speed(       0,   +speed )
  if state == keys.B2:
    robo.speed( 2*speed,  2*speed )
  if state == keys.B3:
    robo.speed(  +speed,        0 )
  if state == keys.B4:
    robo.speed(  -speed,   +speed )
  if state == keys.B5:
    robo.speed(  +speed,   +speed )
  if state == keys.B6:
    robo.speed(  +speed,   -speed )
  if state == keys.B7:
    robo.speed(  -speed,        0 )
  if state == keys.B8:
    robo.speed(  -speed,   -speed )
  if state == keys.B9:
    robo.speed(       0,   -speed )
