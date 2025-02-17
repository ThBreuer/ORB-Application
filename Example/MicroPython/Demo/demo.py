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
#    Nxt_Touch  startTaste;Sensor::S1
#    Nxt_Touch  pauseTaste;Sensor::S2

#-------------------------------------------------------------
def anzeigen( zeit ):
  mon.print( 4, "Laufzeit: "+str(zeit)+" ms")

#-------------------------------------------------------------
def stoppuhr():
  while True:
    mon.print( 4, "Startbereit!" )
    if mon.getKeyState() == keys.A1: ## startTaste.get():
      tim.reset()
      mon.print( 4, "Messung l�uft ..." )
      tim.wait(100);  # Taster entprellen
      while mon.getKeyState() == keys.A1: #startTaste.get() == False:
        pass
      anzeigen( tim.get() )
      while mon.getKeyState() != keys.A2: # pauseTaste.get() == False:
        pass

#-------------------------------------------------------------
def laufzeit():
  while True:
    anzeigen( tim.get() )
    while mon.getKeyState() == keys.A2: ##pauseTaste.get() == True:
      pass

#-------------------------------------------------------------
if getArg() == 0: # Stoppuhr
  mon.print( 1, "Stoppuhr" )
  mon.print( 2, "Taste an S1: Messen" )
  mon.print( 3, "Taste an S2: Reset"  )
  stoppuhr()

else: # Laufzeitmessung
  mon.print( 1, "Laufzeit" );
  mon.print( 2, "" );
  mon.print( 3, "Taste an S2: Zwischenzeit" );
  laufzeit()
