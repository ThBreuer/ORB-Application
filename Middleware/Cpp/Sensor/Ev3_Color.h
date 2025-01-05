//*******************************************************************
/*!
\file   Ev2_Color.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _EV3_COLOR_H
#define _EV3_COLOR_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief EV3-Farbsensor

*/
class Ev3_Color : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensormode
    */
    typedef enum
    {
      LIGHT   = 0,  //!< Messung des reflektierten Lichts mit
                    //	 Kalibration (0 = schwarz, 100 = weiss)
      AMBIENT = 1,  //!< Umgebungslicht 
      COLOR   = 2,  //!< Farbmessung \see Color
    } Mode;

  public:
    //---------------------------------------------------------------
    /*! Rückgabewerte im Modus 'COLOR'
    */
    typedef enum
    {
      NONE   = 0,
      BLACK  = 1,  //!<.
      BLUE   = 2,  //!<.
      GREEN  = 3,  //!<.
      YELLOW = 4,  //!<.
      RED    = 5,  //!<.
      WHITE  = 6,  //!<.
      BROWN  = 7,  //!<.
 
    } Color;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Object
	    \param port Sensor-Port
        \param mode Sensormode
    */
    Ev3_Color( SensorPort port, Mode mode = LIGHT )
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

      orb.configSensor( port, ORB::UART, mode, 0 );
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert. 
	
	    \return Abhängig vom eingestellten Modus
		\see Mode
	*/
    virtual int get()
    {
      switch( mode )
      {
        default:
        case LIGHT:  
          return(gain*((float)orb.getSensor(port).value[0]-offset));

        case AMBIENT:
        case COLOR:       
          return(orb.getSensor(port).value[0] & 0xFFFF);
      }
    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur im Modus 'LIGHT'), s.d. aktueller 
        Sensorwert als "Weiss" = 100 ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void calibrationWhite()
    {
      kalibHundert();
    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur im Modus 'LIGHT'), s.d. aktueller 
        Sensorwert als "Schwarz" = 0 ausgegeben wird.

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
