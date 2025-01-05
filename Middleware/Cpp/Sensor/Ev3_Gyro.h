//*******************************************************************
/*!
\file   Ev2_Gyro.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _EV3_GYRO_H
#define _EV3_GYRO_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief EV3-Rotationssensor

*/
class Ev3_Gyro : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensormode
    */
    typedef enum
    {
      ANGLE = 0,  //!< Messung des Drehwinkels (in Grad)
      RATE  = 1   //!< Messung der Drehgeshwindigkeit ( in Grad/sec)
    } Mode;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
        \param mode Sensormode
    */
    Ev3_Gyro( SensorPort port, Mode mode = ANGLE )
    : Sensor( port, mode )
    {
      init( mode );
    }

    //---------------------------------------------------------------
    /*! Initialisierung des Sensors im angegebenen Modus
       \param mode Sensormode
    */
    virtual void init( Mode mode )
    {
      this->mode = mode;
      orb.configSensor( port, ORB::UART, mode, 0 );
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert. 
	
	    \return Abhängig vom eingestellten Modus
		\see Mode
    */
    virtual int get()
    {
      return( orb.getSensor(port).value[0] & 0xFFFF );
    }
};

#endif
