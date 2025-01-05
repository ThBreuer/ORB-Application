#include "%ORB%/Middleware/MicroPython/monitor.py"
#include "%ORB%/Middleware/MicroPython/motor.py"
#include "%ORB%/Middleware/MicroPython/drive.py"

robo = Drive( motorLeft     = LEGO_Motor( Motor.M1, Motor.REVERSE ),
              motorRight    = LEGO_Motor( Motor.M4, Motor.NORMAL  ),        
              vmax          = 2500,  # Max. Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
              wheelDiameter =   56,  # Durchmesser der Räder (mm)
              trackWidth    =  140   # Abstand der Räder (mm)
             )

if getArg() == 0:
  robo.track( 500, 0 )
else:
  robo.track( 0, 180 )
robo.power( 0, 0 )
