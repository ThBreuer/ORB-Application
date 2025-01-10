#include "%ORB%\Middleware\MicroPython\timer.py"

t   = Timer()
t2  = Timer(2000)
cnt = 0

while True:

    if t2.timeout():

        print(str(t.get())+" timeout ("+str(cnt)+")")
        t2.wait(1000)
        print(str(t.get())+" ready")

        cnt = cnt + 1
        if cnt >= 3:

            t2.stop()
            print("\3"+str(t.get())+" timeout stopped")

            t2.wait(2000)
            print("\3"+str(t.get())+" timeout started")

            print("\2restart timer")            
            t2.start()
            t.reset()
            
            cnt = 0
