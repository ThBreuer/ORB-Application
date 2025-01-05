//*******************************************************************
/*!
\file   Nxt_Ultrasonic.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _NXT_ULTRASONIC_H
#define _NXT_ULTRASONIC_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief NXT-Ultraschallsensor zur Distanzmessung

*/
class Nxt_Ultrasonic : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
    */
    Nxt_Ultrasonic( SensorPort port )
    : Sensor( port, 0 )
    {
      init();
    }

    //---------------------------------------------------------------
    /*! Initialisierung des Sensors
    */
    virtual void init()
    {
      mode = 0;

      orb.configSensor( port, ORB::I2C, 0, 0 );
      gain = 10.0;
      offset = 0.0;
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Distanz in mm
    */
    virtual int get()
    {
      return( 10*(orb.getSensor(port).value[0] & 0xFFFF) );
    }
};

#endif
