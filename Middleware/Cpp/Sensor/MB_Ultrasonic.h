//*******************************************************************
/*!
\file   MB_Ultrasonic.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _MB_ULTRASONIC_H
#define _MB_ULTRASONIC_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief Makeblock Ultraschallsensor zur Distanzmessung

*/
class MB_Ultrasonic : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
    */
    MB_Ultrasonic( SensorPort port )
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

      gain   = 0.170;  // c = 2*x/t => x = 1/2*c*t = (0.5*0.340mm/µs)*t
      offset = 30;     // = 5mm/0.17

      orb.configSensor( port, ORB::TOF, 0, 0 );
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Distanz in mm
    */
    virtual int get()
    {
      return( gain*((float)orb.getSensor(port).value[0] - offset) );
    }
};

#endif
