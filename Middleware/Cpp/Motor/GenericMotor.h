//*******************************************************************
/*!
\file   GenericMotor.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _GENERIC_MOTOR_H
#define _GENERIC_MOTOR_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "Motor.h"

//*******************************************************************
/*! \brief Steuerung eines allgemeinen Encoder-Motors

    Mit einem Objekt dieser Klasse kann ein einzelner Motor gesteuert werden.
    Es sind verschiedene Betriebsarten möglich.
*/
class GenericMotor : public Motor
{
  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Motor-Objekt
        \param port Motor-Port M1 bis M4
        \param orientation Einbaurichtung des Motors, legt positiven Drehsinn fest
        \param ticsPerRotation 1/10 Anzahl Encoder-Tics pro Umdrehuung
        \param acc Beschleunigung im Betriebsmodus setPosition() (1)
        \param Kp PI-Geschwindigkeitsregler, Proportionalanteil (1)
        \param Ki PI-Geschwindigkeitsregler, Integralalanteil (1)
        \n(1): Relative Größen im Bereich 0,..,255
     */
    GenericMotor( Port_type        port,
                  Orientation_type orientation,
                  WORD ticsPerRotation,
                  BYTE acc,
                  BYTE Kp,
                  BYTE Ki  )

    : Motor( port, orientation )
    {
       orb.configMotor( port,  ticsPerRotation, acc, Kp, Ki );
    }
};
#endif
