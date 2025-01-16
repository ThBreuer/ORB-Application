#include "%ORB%\Middleware\MicroPython\monitor.py"

import monitor
from monitor import keys

lable = ["none",
         "A1","A2","A3","A4","A5","A6","A7","A8",
         "B1","B2","B3","B4","B5","B6","B7","B8","B9","B10","B11","B12",
         "C1"]

def getLable(key):
  if key<len(lable):
    return lable[key]
  else:
    return "..."

mon = Monitor()
mon.print(0,"Monitor v00.98")
while True:
    state = mon.getKeyState()
    mon.print(2,"KeyState: "+str(state)+" "+getLable(state))
    
    event = mon.getKeyEvent()
    if event != 0:
        mon.print(3,"KeyEvent: "+str(event)+" "+getLable(event))
        print("KeyEvent: \2"+str(event)+" \3"+getLable(event))
