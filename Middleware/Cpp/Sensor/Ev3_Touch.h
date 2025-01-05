//*******************************************************************
/*!
\file   Ev3_Touch.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _EV3_TOUCH_H
#define _EV3_TOUCH_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief EV3-Touchsensor

*/
class Ev3_Touch : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
    */
    Ev3_Touch( SensorPort port )
    : Sensor( port, 0 )
    {
      this->mode = 0;
      init();
    }

    //---------------------------------------------------------------
    /*! Initialisierung des Sensors
    */
    void init()
    {
       orb.configSensor( port, ORB::TOUCH, 0, 0 );
    }

    //---------------------------------------------------------------
    /*! Liefert Sensorwert
        \return 0: nicht betätigt, 1: betätigt
    */
    virtual int get( void )
    {
      return( orb.getSensor(port).value[0] );
    }
};

#endif
