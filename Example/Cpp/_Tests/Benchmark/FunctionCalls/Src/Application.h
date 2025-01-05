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

    const int iterations = 10000;

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      Monitor m = Monitor();
      orb.configSensor(0,0,0,0);
      orb.configMotor(0,0,0,0,0);
      int start = 0;
      int finish = 0;

      start = orb.getTime();
      for(int i=0;i<iterations;i++){
            orb.getSensor(0);
      }
      finish = orb.getTime();
      m.print(1, "getSensor(): %d ms", (finish - start));

      start = orb.getTime();
      for(int i=0;i<iterations;i++){
            orb.getSensorDigital(0);
      }
      finish = orb.getTime();
      m.print(2, "getSensorDigital(): %d ms", (finish - start));

      start = orb.getTime();
      for(int i=0;i<iterations;i++){
            orb.setMotor(0,0,0,0);
      }
      finish = orb.getTime();
      m.print(3, "setMotor(): %d ms", (finish - start));

      start = orb.getTime();
      for(int i=0;i<iterations;i++){
            orb.getMotor(0);
      }
      finish = orb.getTime();
      m.print(4, "getMotor(): %d ms", (finish - start));

      while( 1 )
      {
      }

    }
};
