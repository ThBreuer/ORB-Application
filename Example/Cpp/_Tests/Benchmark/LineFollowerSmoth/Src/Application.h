//*******************************************************************
/*!
\author Nils Hoffmann
\date   15.10.2024
*/

#include "Common/Src/ORB.h"

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

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

      float s = 800.0 * (2.0/3.0);
      int lineRight = 0;
      int lineLeft = 0;

      //0-100 in 95ms
      float smothing = 1.0 / 95.0;
      float percentLeft  = 1.0;
      float percentRight = 1.0;

      int was = orb.getTime();
      int ist = was;

      while( 1 )
      {
        ist = orb.getTime();

        lineRight = !(orb.getSensorValueExt(0, 2));
        lineLeft  = !(orb.getSensorValueExt(0, 3));

        if(lineRight){
            percentLeft = 1.0;
        }else{
            percentLeft  = min(1.0, max(0, percentLeft -  (smothing * (float)(ist-was))));
        }

        if(lineLeft){
            percentRight = 1.0;
        }else{
            percentRight = min(1.0, max(0, percentRight - (smothing * (float)(ist-was))));
        }

        orb.setMotor(port_left, speed_mode,(int) (-1.0 * max(0, (percentLeft  + (1.0/3.0 * percentRight))) * s), 0.0);
        orb.setMotor(port_right, speed_mode,(int) (max(0, (percentRight + (1.0/3.0 * percentLeft))) * s), 0.0);

        was = ist;
      }

    }
};
