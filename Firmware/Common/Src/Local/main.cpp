//*******************************************************************
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "Common/Src/ORBlocal.h"

//*******************************************************************
static ORBlocal *orbPtr;

//*******************************************************************
class ApplicationBase
{
public:
  ORB &orb;
  virtual void run(BYTE para) = 0;

  ApplicationBase()
  : orb( *orbPtr )
  {
  }
};

//*******************************************************************
//-------------------------------------------------------------------
// Actuator
//-------------------------------------------------------------------
#include "ModelServo.h"

#include "Motor.h"
#include "Motor/MB_Motor.h"
#include "Motor/LEGO_Motor.h"
#include "Motor/GenericMotor.h"

#include "EncoderServo.h"
#include "Drive.h"

//-------------------------------------------------------------------
// Sensor
//-------------------------------------------------------------------
#include "Digital.h"

#include "Sensor.h"
#include "Sensor/Ev3_Color.h"
#include "Sensor/Ev3_Gyro.h"
#include "Sensor/Ev3_Infrared.h"
#include "Sensor/Ev3_Touch.h"
#include "Sensor/Ev3_Ultrasonic.h"

#include "Sensor/MB_LineFollower.h"
#include "Sensor/MB_Ultrasonic.h"

#include "Sensor/Nxt_Light.h"
#include "Sensor/Nxt_Ultrasonic.h"
#include "Sensor/Nxt_Touch.h"

#include "Sensor/Orb_Sensor.h"

//-------------------------------------------------------------------
// Sonstiges
//-------------------------------------------------------------------
#include "Memory.h"
#include "Timer.h"
#include "Monitor.h"

//-------------------------------------------------------------------
#include "Application.h"

//*******************************************************************
int Main( BYTE para, ORBlocal &orb )
{
  orbPtr = &orb;

  Memory::clean();
  Application app;
  app.run( para );
  return(0);
}

//EOF
