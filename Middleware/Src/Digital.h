//*******************************************************************
/*!
\file   Digital.h
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#ifndef _DIGITAL_H
#define _DIGITAL_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Zustand der zusätzlichen Digitaleingänge erfassen

    Ein Objekt dieser Klasse erlaubt das Einlesen der Digitaleingänge
*/
class Digital
{
  public:
    //---------------------------------------------------------------
    /*! Digital-Port
    */
    typedef enum
    {
      D1 = 0, //!< Digitalport 1
      D2 = 1  //!< Digitalport 2
    } DigitalPort;

    //---------------------------------------------------------------
    /*! Sensormode
    */
    typedef enum
    {
      NORMAL  = 0,  //!< Logischer Zustand entspricht pyhsikalischem Zustand
      INVERS  = 1   //!< Logischer Zustand <b>invertiert</b> zum pyhsikalischen Zustand
    } Mode;

  private:
    //---------------------------------------------------------------
    Mode  mode;
    BYTE  port;
    ORB  &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Objekt
        \param port Digitalport D1, D2
    */
    Digital( DigitalPort port, Mode mode = NORMAL )
    : orb( *orbPtr )
    {
      this->port = port;
      this->mode = mode;
    }

  public:
    //---------------------------------------------------------------
    /*! Liefert (logischen) Zustand des Digitalports
        \return true: Eingang offen, false: Eingang geschlossen
    */
    virtual bool get( void )
    {
      return( orb.getSensorDigital( port ) != mode );
    }

};

#endif
