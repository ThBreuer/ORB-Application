from devices import sensor

#********************************************************************
class Sensor:
  S1 = sensor.S1
  S2 = sensor.S2
  S3 = sensor.S3
  S4 = sensor.S4
  
  def __init__(self,port,type, mode,option):
    self._s = sensor(port = port, type = type, mode = mode, option = option)
    self.gain = 1
    self.offset = 0
    self.kalib0 = MemoryItem(default=  0,addr = 0x1000 + port*0x20)
    self.kalib1 = MemoryItem(default=100,addr = 0x1000 + port*0x20 + 0x10)
    self.gain = 1
    self.offset = 0
    self.kalib()

  def kalib(self):
    self.gain = 1.0
    if self.kalib0.value!=self.kalib1.value:
       self.gain = 100.0/float(self.kalib1.value-self.kalib0.value)
    self.offset = self.kalib0.value;

  def get(self):
    return int(self.gain* self.getRaw() - self.offset)

  def kalibHundert(self):
      print("kalibHundert")
      self.kalib1.value = 1 #self.getRaw()
      self.kalib()
 
  def kalibNull(self):
      print("kalibNull")
      self.kalib0.value = -1 #self.getRaw()
      self.kalib()

#********************************************************************
class  Ev3_Color(Sensor):
  
  LIGHT   = 0
  AMBIENT = 1
  COLOR   = 2
 
  NONE   = 0
  BLACK  = 1
  BLUE   = 2
  GREEN  = 3
  YELLOW = 4
  RED    = 5
  WHITE  = 6
  BROWN  = 7
 
  def __init__(self,port,mode = LIGHT):
    Sensor.__init__(self,port,type = sensor.UART, mode = mode, option = 0) 
  
  def setMode( self, mode ):
    self._s.config( mode = mode )
    if mode == self.COLOR:
        self.gain = 1
        self.offset = 0
    else:
        self.kalib()
    
  def getRaw(self):
    return 1 #self._s.get()["values"][0]
  
  def calibrationWhite(self):
    Sensor.kalibHundert(self)

  def calibrationBlack(self):
    Sensor.kalibNull(self)
    


#********************************************************************
class Ev3_Gyro(Sensor):
    
  ANGLE = 0
  RATE  = 1
    
  def __init__(self,port,mode=ANGLE):
    Sensor.__init__(self,port,type = sensor.UART, mode = mode, option = 0) 
    
  def setMode( self, mode ):
    self._s.config( mode = mode )

  def getRaw(self):
    return self._s.get()["values"][0]

#********************************************************************
class Ev3_Infrared(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.UART, mode = 0, option = 0) 
    
  def get(self):
    return self._s.get()["values"][0]

#********************************************************************
class Ev3_Touch(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.Touch, mode = 0, option = 0) 
    
  def get(self):
    return self._s.get()["values"][0]

#********************************************************************
class Ev3_Ultrasonic(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.UART, mode = 0, option = 0) 
    
  def get(self):
    return self._s.get()["values"][0]

#********************************************************************
class MB_LineFollower(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.Analog, mode = 0, option = 0x2222)
    
  def get(self):
    return self._s.getValueExt(2) | (self._s.getValueExt(3)<<1)
    
#********************************************************************
class MB_Ultrasonic(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.TOF, mode = 0, option = 0)
    self.gain   = 0.170 # c = 2*x/t => x = 1/2*c*t = (0.5*0.340mm/µs)*t
    self.offset = 30    # 5mm/0.17
    
  def getRaw(self):
    return self._s.get()["values"][0] & 0xFFF
    
#********************************************************************
class Nxt_Light(Sensor):
  def __init__(self,port,light):
    if light == True:
        Sensor.__init__(self,port,type = sensor.Analog, mode = 0, option = (0x08|0x07)<<8)
    else:
       Sensor.__init__(self,port,type = sensor.Analog, mode = 0, option = (0x00|0x07)<<8)

  def setMode(self, mode ):
    self._s.config(mode)
    
  def getRaw(self):
    return 1 # self._s.get()["values"][0] & 0xFFF
  
  def calibrationWhite(self):
    Sensor.kalibHundert(self)

  def calibrationBlack(self):
    Sensor.kalibNull(self)
    
#********************************************************************
class Nxt_Touch(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.Touch, mode = 0, option = 0)
    
  def get(self):
    return self._s.get()["values"][0]
    
#********************************************************************
class Nxt_Ultrasonic(Sensor):
  def __init__(self,port):
    Sensor.__init__(self,port,type = sensor.I2C, mode = 0, option = 0) 
    self.gain = 10
    self.offset = 0
    
  def getRaw(self):
    return self._s.get()["values"][0]
    
