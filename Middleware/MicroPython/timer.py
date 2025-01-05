import time

class Timer:
  startTime  = 0
  timeoutTime = 0
  isRunning  = False

  def __init__(self, duration = 0):
    self.timeoutTime = duration
    self.start( duration )

  def get(self):
    return time.getTime() - self.startTime

  def reset(self):
    self.startTime = time.getTime()

  def start(self, duration = 0):
    self.reset()
    if duration > 0:
      self.timeoutTime = duration
    if self.timeoutTime > 0:
      self.isRunning = True
    else:
      self.isRunning = False

  def stop(self):
    self.isRunning = False

  def timeout(self):
    if self.isRunning == True:
      if self.get() >= self.timeoutTime:
        self.start()
        return True
    return False

  def wait(self, duration):
    time.wait( duration )
