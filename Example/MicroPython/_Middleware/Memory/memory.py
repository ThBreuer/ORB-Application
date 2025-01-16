#include "%ORB%\Middleware\MicroPython\monitor.py"
#include "%ORB%\Middleware\MicroPython\memory.py"

import monitor
from monitor import keys

mon = Monitor()
mon.print(1,"Memory v00.98")

item1 = MemoryItem(2**26)
item2 = MemoryItem(1)
item3 = MemoryItem(True)

if item1.value == 0:
  mon.print(2,"clearing ...")
  memory.clearMemory()
else:
  mon.print(2, str(item1.value))
  mon.print(3, str(item2.value))
  mon.print(4, str(bool(item3.value)))

  item1.value = -item1.value/2
  item2.value = -item2.value*2
  item3.value = not item3.value

  Memory.store()

while mon.getKeyState() != keys.C1:
  pass
