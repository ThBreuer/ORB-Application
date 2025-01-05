//*******************************************************************
/*!
\author Nils Hoffmann
\date   15.10.2024
*/

#include "Common/Src/ORB.h"

//*******************************************************************
class Application : public ApplicationBase
{
  public:
    Application(){}

    int port_left = 0;
    int port_right = 1;
    int speed_mode = 2;

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      orb.configSensor(0, ORB::ANALOG, 0, 0x2222);
      orb.configMotor(port_left,144,50,50,30);
      orb.configMotor(port_right,144,50,50,30);

      int s = 2000.0;
      int lineRight = 0;
      int lineLeft = 0;

      while( 1 )
      {
        lineRight = !(orb.getSensorValueExt(0, 2));
        lineLeft  = !(orb.getSensorValueExt(0, 3));
        orb.setMotor(port_left, speed_mode, -1 * s * lineRight, 0);
        orb.setMotor(port_right, speed_mode, s * lineLeft, 0 );
      }

    }
};
