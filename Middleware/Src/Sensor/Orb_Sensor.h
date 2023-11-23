//*******************************************************************
/*!
\file   Orb_Sensor.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _SENSOR_EXTRA_H
#define _SENSOR_EXTRA_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Erfassen zusätzlicher Messwerte (analog/digital) zu einem Sensor-Port

    Unabhängig von der Konfiguration eines Sensor-Ports (siehe Sensor)
    können die Zustände der Port-Pins digital (Pin 2, 5 und 6) bzw.
    der Analogeingang erfasst werden.

    Für jeden dieser Kanäle kann ein Objekt dieser Klasse erstellt werden.
*/
class Orb_Sensor : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensor-Typ: Beschreibt hier, welcher Kanal (digitaler Pin/Analogeingang)
        erfasst werden soll.
    */
    typedef enum
    {
      ANALOG_A  = 0, //!< Analogkanal Pin 1
      ANALOG_B  = 1, //!< Analogkanal Pin 2
      DIGITAL_A = 2,   //!< Digitaler Pin 5
      DIGITAL_B = 3,   //!< Digitaler Pin 6
    } SensorType;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein SonsorExtra-Objekt

        \param port Sensor-Port S1 bis S4
        \param type Sensortyp (ANALOG, DIGITAL_A,...,_C)
    */
    Orb_Sensor( SensorPort port, SensorType type )
    : Sensor( port, type, type+1)
    {
		init(mode);
    }

  private:
    //---------------------------------------------------------------
    /*  Initialisierung des Sensors im angegebenen Modus
        \param type Sensormode
    */
    void init(unsigned char type)
    {
      mode = type;

      gain   = (kalib0!=kalib1)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
      
      /*! \todo Wenn sich mehrere Sensoren einen Port teilen, darf die Pin-Konfiguration nicht überschrieben werden!
	  
	  GGf über 3. parameter (mode) den Pin angeben, shift dann später ...
	  */
	  
      switch( mode )
      {
        case ANALOG_A:  orb.configSensor( port, ORB::ANALOG, 0, 0 ); break;
        case ANALOG_B:  orb.configSensor( port, ORB::ANALOG, 0, 0 ); break;
        case DIGITAL_A: orb.configSensor( port, ORB::ANALOG, 0, 0x02<< 8 ); break;
        case DIGITAL_B: orb.configSensor( port, ORB::ANALOG, 0, 0x02<<12 ); break;
      }
    }

  public:
    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "100" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void calibrationMax()
    {
      kalib1 = orb.getSensorValueExt(port,mode)&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "0" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void calibrationMin()
    {
      kalib0 = orb.getSensorValueExt(port,mode)&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

  public:
    //---------------------------------------------------------------
    /*! Liefert Sensorwert für den konfigurierten Mode
        \return <table>
		  <tr> <td>Sensor-Typ </td> <td>Wert</td>  </tr>
		  <tr> <td> ANALOG_A  </td> <td>analog, Pin 1</td>  </tr>
		  <tr> <td> ANALOG_B  </td> <td>analog, Pin 2</td>  </tr>
		  <tr> <td> DIGITAL_A </td> <td>digital, Pin 5</td> </tr>
		  <tr> <td> DIGITAL_B </td> <td>digital, Pin 6</td> </tr>
		</table>

    */
    virtual int get( void )
    {
      switch( mode )
      {
        case ANALOG_A:  return( gain*((float)(orb.getSensorValueExt(port,0)&0xFFF)-offset)  );
        case ANALOG_B:  return( gain*((float)(orb.getSensorValueExt(port,1)&0xFFF)-offset)  );
        case DIGITAL_A: return( orb.getSensorValueExt(port,2) );
        case DIGITAL_B: return( orb.getSensorValueExt(port,3) );
        default:        return( 0 );
      }
    }

};

#endif
