import memory

#********************************************************************
class Memory:

  #------------------------------------------------------------------
  _lst = []
  _addr = 0
  
  #------------------------------------------------------------------
  @staticmethod
  def addItem(size,item, addr):
    if addr == 0:
        item.addr = Memory._addr
        Memory._addr = Memory._addr + size + 1
    else:
        item.addr = addr
    Memory._lst.append(item)
  
  #------------------------------------------------------------------
  @staticmethod
  def store():
    memory.clearMemory()
    for item in Memory._lst:
      item.store()

#********************************************************************
class MemoryItem:

  #------------------------------------------------------------------
  def __init__(self, default, addr = 0):
    self.addr = addr
    self.value = 0
    Memory.addItem(9,self, addr)
    
    try:
      b = memory.getMemory(self.addr, 9 )
      self.value = int(b)
    except:
      self.value = default

  #------------------------------------------------------------------
  def store(self):
    #  limt = 2^26 = 67108864  ??? 
    if self.value > +90000000:
      self.value =  +90000000
    if self.value < -90000000:
      self.value =  -90000000
    s = f"{int(self.value):+9.0f}"+";"
    memory.setMemory(self.addr, bytes(s,'utf-8'))
