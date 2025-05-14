#include "%ORB%/Middleware/MicroPython/monitor.py"
#include "%ORB%/Middleware/MicroPython/timer.py"

#********************************************************************

#********************************************************************

#********************************************************************
import monitor
from monitor import keys
import time

mon = Monitor()
tim = Timer(duration=0)

#-------------------------------------------------------------
def anzeigen( zeit ):
  mon.print( 4, "Laufzeit: "+str(zeit)+" ms")

#-------------------------------------------------------------
def stoppuhr():
  mon.print( 4, "Startbereit!" )
  while True:
    if mon.getKeyEvent() == keys.A1: # start
      tim.reset()
      while not mon.getKeyEvent() == keys.A2: # stop
        anzeigen( tim.get() )

#-------------------------------------------------------------
def laufzeit():
  while True:
    anzeigen( tim.get() )
    while mon.getKeyState() == keys.A2: ##pauseTaste.get() == True:
      pass

#-------------------------------------------------------------
if getArg() == 0: # Stoppuhr
  mon.print( 1, "Stoppuhr" )
  mon.print( 2, "Taste \"start\" oder \"stop\"" )
  stoppuhr()

else: # Laufzeitmessung
  mon.print( 1, "Laufzeit" )
  mon.print( 2, "Taste \"stop\": Zwischenzeit" )
  laufzeit()
