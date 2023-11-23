//*******************************************************************
/*!
\file   MB_LineFollower.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _MB_LINE_FOLLOWER_H
#define _MB_LINE_FOLLOWER_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Sensor.h"

//*******************************************************************
/*! \brief Makeblock Liniefollower-Sensor

    Sensor für die Linienverfolgung, bestehend aus zwei 
    Reflexionslichschranken
*/
class MB_LineFollower : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensor-ID

        Siehe Kennzeichnung auf dem Sensor
    */
    typedef enum
    {
      SENSOR_1 = 0, //!< Sensor1
      SENSOR_2 = 1  //!< Sensor2
    } Sensor_ID;

    //---------------------------------------------------------------
    /*! Erzeugt ein Sonsor-Objekt
        \param port Sensor-Port
    */
    MB_LineFollower( SensorPort port )
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
      orb.configSensor( port, ORB::ANALOG, 0, 0x2222 );
    }

  public:
    //---------------------------------------------------------------
    /*! Liefert Sensorwert
        \return <table>
          <tr><td></td> <td>Sensor1</td> <td>Sensor2</td> </tr>
          <tr> <td> 0 </td>         <td>schwarz</td> <td>schwarz</td> </tr>
          <tr> <td> 1 </td>         <td>weiß</td>    <td>schwarz</td> </tr>
          <tr> <td> 2 </td>         <td>schwarz</td> <td>weiß</td>    </tr>
          <tr> <td> 3 </td>         <td>weiß</td>    <td>weiß</td>    </tr>
        </table>
    */
    virtual int get( void )
    {
      return( (get(SENSOR_1)?0x01:0) | (get(SENSOR_2)?0x02:0) );
    }

    //---------------------------------------------------------------
    /*! Liefert Sensorwert
        \param id Sensor-ID
        \return 0:schwarz, 1:weiß
    */
    virtual int get( Sensor_ID id )
    {
      switch( id )
      {
        case SENSOR_1:  return( orb.getSensorValueExt(port,2) );
        case SENSOR_2:  return( orb.getSensorValueExt(port,3) );
        default: return( 0 );
      }
    }

};
#endif
