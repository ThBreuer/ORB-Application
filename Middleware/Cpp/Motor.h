//*******************************************************************
/*!
\file   Motor.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _MOTOR_H
#define _MOTOR_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Basisklasse zur Steuerung eines Encoder-Motors

    Mit einem Objekt dieser Klasse kann ein einzelner Motor gesteuert werden.
    Es sind verschiedene Betriebsarten möglich.
*/
class Motor
{
  public:
    //---------------------------------------------------------------
    /*! Motor-Port
    */
    typedef enum
    {
      M1  = 0x00, //!< Motor Port 1
      M2,         //!< Motor Port 2
      M3,         //!< Motor Port 3
      M4          //!< Motor Port 4
    } Port_type;

    //---------------------------------------------------------------
    /*! Orientierung/Einbaulage des Motors
    */
    typedef enum
    {
      NORMAL = 0,      //!< Normaler Drehsinn des Motors
      REVERSE = 0x80   //!< Invertierter Drehsinn des Motors
    } Orientation_type;

  protected:
    //---------------------------------------------------------------
    BYTE   port;
    float  orientation;
    ORB   &orb;

  protected:
    //---------------------------------------------------------------
    /*  Erzeugt ein Motor-Objekt
        \param port Motor-Port M1 bis M4
        \param orientation Einbaurichtung des Motors, legt positiven Drehsinn fest
        \param type Motor-Typ (LEGO, Makeblock, Faulhaber)
     */
    Motor( Port_type        port,
           Orientation_type orientation )
    : orb( *orbPtr )
    {
      this->port        = port;
      this->orientation = (orientation==NORMAL)?+1.0:-1.0;
    }

  public:
    //---------------------------------------------------------------
    /*! Motor bremst (Kurzschlussbremse), s.d. Motor schwergängig ist,
        sich aber nicht eigenständig dreht
    */
    virtual void brake( void )
    {
      orb.setMotor( port, ORB::BRAKE_MODE, 0, 0 );
    }

    //---------------------------------------------------------------
    /*! Stellt die Leistung des Motors ein.
        \param power Leistung 0 (Leerlauf) bis 1000 (Maximum)
    */
    virtual void setPower( short power )
    {
      orb.setMotor( port, ORB::POWER_MODE, orientation*power, 0 );
    }

    //---------------------------------------------------------------
    /*! Stellt die Drehgeschwindigkeit eines Motors ein
        \param speed Drehzahl, 0 (Stillstand), ansonsten beliebiger Wert.
        Einheit: 1000 entspricht einer Umdrehung pro Sekunde
    */
    virtual void setSpeed( short speed )
    {
      orb.setMotor( port, ORB::SPEED_MODE, orientation*speed, 0 );
    }

    //---------------------------------------------------------------
    /*! Setzt Zielposition für Positionierung
        \param speed Geschwindigkeit, mit der Ziel erreicht werden soll
        \param position Position, die angefahren werden soll, Einheit: 1000 = 1 Umdrehung.
        Die Position wird absolut angegeben, also seit Start des Controllers
    */
    virtual void setPosition( short speed, int position )
    {
      orb.setMotor( port, ORB::MOVETO_MODE,orientation*speed, orientation*position );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Leistung
        \return Aktuelle Motorleistung, 0 = Leerlauf, 1000 = Maximum
    */
    virtual short getPower( void )
    {
     
      return( orientation*orb.getMotor(port).pwr );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Drehgeschwindigkeit
        \return Aktuelle Drehgeschwindigkeit, 1000 = 1 Umdrehung po Sekunde
    */
    virtual short getSpeed( void )
    {
      return( orientation*orb.getMotor(port).speed );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Position des Motors
        \return Aktuelle Position, 1000 = 1 Umdrehung
    */
    virtual int getPosition( void )
    {
      return( orientation*orb.getMotor(port).pos );
    }
};
#endif
