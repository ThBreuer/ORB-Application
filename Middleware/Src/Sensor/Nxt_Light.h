//*******************************************************************
/*!
\file   Nxt_Light.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _NXT_LIGHT_H
#define _NXT_LIGHT_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief NXT-Helligkeitssensor

*/
class Nxt_Light : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensormode

    */
    typedef enum
    {
      LIGHT_OFF = 0,  //!< LED aus
      LIGHT_ON  = 1,  //!< LED ein
    } Mode;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
        \param mode Sensormode
    */
    Nxt_Light( SensorPort port, Mode mode = LIGHT_ON )
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
      gain   = (kalib0!=kalib1)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;

      switch( mode )
      {
        default:
        case LIGHT_OFF: orb.configSensor( port, ORB::ANALOG, 0, (0x00|0x07)<<8 ); break;
        case LIGHT_ON:  orb.configSensor( port, ORB::ANALOG, 0, (0x08|0x07)<<8 ); break;
      }
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Helligkeitswert
    */
    virtual int get()
    {
			return(gain*((float)(orb.getSensor(port).value[0]&0xFFF)-offset));
    }
		
		    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "100" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void calibrationWhite()
    {
      kalibHundert();
    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "0" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void calibrationBlack()
    {
      kalibNull();
    }
};

#endif
