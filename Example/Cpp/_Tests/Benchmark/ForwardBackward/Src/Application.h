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

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
        Nxt_Light colorLeft = Nxt_Light(Sensor::SensorPort::S1, Nxt_Light::LIGHT_ON);
        Nxt_Light colorRight = Nxt_Light(Sensor::SensorPort::S2, Nxt_Light::LIGHT_ON);

// setCalibration is not longer part of the middleware, use a real calibration instead!
// see: calibrationWhite() and calibrationBlack()

        colorLeft.setCallibration(1600, 2600);
        colorRight.setCallibration(1600, 2600);

        Monitor m = Monitor();

        int m_speed = 300;
        int runFor = 60 * 1000 * 20;
        int start = orb.getTime();
        int line_count = 0;

        orb.configMotor(0,72, 25, 50, 30);
        orb.configMotor(1,72, 25, 50, 30);

        orb.setMotor(0, 2, m_speed, 0);
        orb.setMotor(1, 2, m_speed, 0);

        while((orb.getTime() - start) < runFor){
            if(colorLeft.get() > 80 || colorRight.get() > 80){
                line_count++;
                orb.setMotor(0, 2, -m_speed, 0);
                orb.setMotor(1, 2, -m_speed, 0);
                orb.wait(250);
            }else{
                orb.setMotor(0, 2, m_speed, 0);
                orb.setMotor(1, 2, m_speed, 0);
            }
            m.print(1, "Linecount: %d", line_count);
        }
        orb.setMotor(0, 2, 0, 0);
        orb.setMotor(1, 2, 0, 0);
        while(true){}
    }
};
