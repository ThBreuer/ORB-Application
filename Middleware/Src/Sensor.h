//*******************************************************************
/*!
\file   Sensor.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _SENSOR_H
#define _SENSOR_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Memory.h"

//*******************************************************************
/*! \brief Sensoren konfigurieren, kalibrieren und auslesen

    Ein Objekt dieser Klasse erlaubt die Verwendung von Sensoren
*/
class Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensor-Port
    */
    typedef enum
    {
      S1 = 0, //!< Sensorport 1
      S2,     //!< Sensorport 2
      S3,     //!< Sensorport 3
      S4      //!< Sensorport 4
    } SensorPort;

  protected:
    //---------------------------------------------------------------
    ORB  &orb;

    BYTE port;
    BYTE mode;

    float gain;
    float offset;

    Memory::Item kalib0;
    Memory::Item kalib1;

  protected:
    //---------------------------------------------------------------
    /*  Erzeugt ein Sensor-Objekt

        Es werden auch die zuletzt gespeicherten Kalibrationsdaten
        abgerufen
        \param port Sensor-Port S1 bis S4
        \param mode Sensortyp und Sensormode (EV3)
    */
    Sensor( SensorPort port, BYTE mode, WORD memOffs = 0 )
    : orb( *orbPtr ),
      kalib0(0x1000 + port*0x10 + memOffs*0x100               ),
      kalib1(0x1000 + port*0x10 + memOffs*0x100 + sizeof(int) )
    {
      this->port = port;
      this->mode = mode;
    }

  protected:
    //---------------------------------------------------------------
    /*  Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "100" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibHundert()
    {
      kalib1 = orb.getSensor(port).value[0]&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

    //---------------------------------------------------------------
    /*  Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "0" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibNull()
    {
      kalib0 = orb.getSensor(port).value[0]&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

  public:
    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Messwert
    */
    virtual int get() = 0;

};

#endif
