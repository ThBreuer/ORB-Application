//*******************************************************************
/*!
\file   Nxt_Touch.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _NXT_TOUCH_H
#define _NXT_TOUCH_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief NXT-Touchsensor

*/
class Nxt_Touch : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
    */
    Nxt_Touch( SensorPort port )
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
