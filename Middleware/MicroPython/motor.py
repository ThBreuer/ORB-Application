from devices import motor

class Motor:
  NORMAL  = 1
  REVERSE =-1
  M1 = motor.M1
  M2 = motor.M2
  M3 = motor.M3
  M4 = motor.M4
  
  def __init__(self,port,orientation):
    self._orientation = orientation
    self._orientationInv = 1/orientation
    self._m = motor(port = port)
    self._m.set(mode = motor.POWER_MODE, speed = 0)

  def brake(self):
    self._m.set(mode = motor.BRAKE_MODE)

  def setSpeed(self,speed):
    self._m.set(mode = motor.SPEED_MODE, speed = self._orientation*speed)

  def setPower(self,power):
    self._m.set(mode = motor.POWER_MODE, speed = self._orientation*power)

  def setPosition(self,speed,position):
    self._m.set(mode = motor.MOVETO_MODE, speed = speed, position = self._orientation*position)

  def getPower(self):
    return self._orientationInv*self._m.get()["power"]

  def getSpeed(self):
    return self._orientationInv*self._m.get()["speed"]

  def getPosition(self):
    return self._orientationInv*self._m.get()["position"]

class MB_Motor(Motor):
  def __init__(self,port,orientation):
    Motor.__init__(self,port,orientation)
    self._m.config(ticks = 144, acc = 30,kp = 25, ki = 25)

class LEGO_Motor(Motor):
  def __init__(self,port,orientation):
    Motor.__init__(self,port,orientation)
    self._m.config(ticks = 72, acc = 40,kp = 40, ki = 25)
