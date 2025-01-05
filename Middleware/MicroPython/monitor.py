import monitor
from monitor import keys

class Monitor:
  lastEvent = 0

  def __init__(self):
    self.clear()
          
  def clear(self):
    monitor.setText(0,"")
    monitor.setText(1,"")
    monitor.setText(2,"")
    monitor.setText(3,"")
     
  def setText(self,line,string):
    monitor.setText(line-1,string)
     
  def getKeyState(self):
    return monitor.getKey()

  def getKeyEvent(self):
    event = monitor.getKey()
    if event != self.lastEvent:
      self.lastEvent = event
      return event
    return 0
