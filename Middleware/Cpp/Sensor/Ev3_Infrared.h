//*******************************************************************
/*!
\file   Ev2Infrarot.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _EV3_INFRARED_H
#define _EV3_INFRARED_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief EV3-Infrarotsensor zur Distanzmessung

*/
class Ev3_Infrared : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
    */
    Ev3_Infrared( SensorPort port )
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

      orb.configSensor( port, ORB::UART, 0, 0 );
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Distanz
    */
    virtual int get()
    {
      return(orb.getSensor(port).value[0] & 0xFFFF);
    }
};

#endif
