//*******************************************************************
/*!
\file   MB_Motor.h
\author Thomas Breuer
\date	22.11.2023
*/

//*******************************************************************
#ifndef _MB_MOTOR_H
#define _MB_MOTOR_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Motor.h"

//*******************************************************************
/*! \brief Steuerung eines Makeblock Encoder-Motors

    Mit einem Objekt dieser Klasse kann ein einzelner Motor gesteuert werden.\n
    Es sind verschiedene Betriebsarten möglich.
*/
class MB_Motor : public Motor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Motor-Objekt
        \param port Motor-Port M1 bis M4
        \param orientation Einbaurichtung des Motors, legt positiven Drehsinn fest
     */
    MB_Motor( Port_type        port,
              Orientation_type orientation )
    : Motor( port, orientation )
    {
      orb.configMotor( port, 144, 50, 50, 30 );
    }
};
#endif
