//*******************************************************************
/*!
\file   Drive.h
\author Thomas Breuer
\date	22.11.2023
*/

//*******************************************************************
#ifndef _DRIVE_H
#define _DRIVE_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

//*******************************************************************
/*! \brief Steuerung eines Roboter-Fahrwerks mit zwei Motoren (Differential-Drive)

  <UL>
  <LI>Geschwindigkeit in mm/s</LI>
  <LI>Strecke in mm</LI>
  <LI>Winkel in Grad</LI>
  <LI>Positive Werte: Bewegung nach vorne bzw. rechts</LI>
  <LI>Negative Werte: Bewegung nach hinten bzw. links</LI>
  </UL>

*/
class Drive
{
  public:
    //---------------------------------------------------------------
    /*! \brief Bewegungsmessung eines Roboters

        Zur Bewegungsmessung werden die Daten der Encoder-Motoren benötigt
    */
    class Odometrie
    {
      private:
        //***********************************************************
        class Distance
        {
          private:
            int offset;
            Drive &robo;
            Distance( Drive &r) : robo(r) { reset(); }
            void reset() { offset = robo.distance();}
          public:
            virtual int get()  { return(robo.distance() - offset ); }
          friend class Odometrie;
        };

        //***********************************************************
        class Angle
        {
          private:
            int offset;
            Drive &robo;
            Angle( Drive &r) : robo(r) { reset(); }
            void reset() { offset = robo.angle();}
          public:
            virtual int get()  { return(robo.angle() - offset ); }
          friend class Odometrie;
        };

      public:
        //-----------------------------------------------------------
        /*! Erzeugt ein Objekt zur Bewegungsmessung. Zur Messung
            unterschiedlicher Bewegungsabschnitte können auch mehrere Objekte
            erzeugt und gleichzeitig verwendet werden
            \param roboter Ein Roboter-Objekt, dessen Bewegungen
            gemessen werden sollen
        */
        Odometrie( Drive &roboter )
        : angle( roboter ),
          distance( roboter )
        {
          reset();
        }

        //-----------------------------------------------------------
        /*! Setzt Bewegungsmessung zurück
        */
        void reset( void )
        {
          distance.reset();
          angle.reset();
        }

        //-----------------------------------------------------------
        /*! Liefert die zurückgelegte Strecke (in mm) seit letztem
            Reset der Messung
        */
        int getDistance( void )
        {
          return( distance.get() );
        }

        //-----------------------------------------------------------
        /*! Liefert den Drehwinkel (in Grad) seit letztem
            Reset der Messung
        */
        int getAngle( void )
        {
          return( angle.get() );
        }

      private:
        //-----------------------------------------------------------
        Angle  angle;
        Distance distance;
    };

  private:
    //---------------------------------------------------------------
    ORB  &orb;

    float vmax;
    float faktorMM2Tics;
    float faktorWinkel2Diff;

    Motor &mLi;
    Motor &mRe;

    int dLi;
    int dRe;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Drive-Objekt
        \param motorLeft Objekt für den linken Motor
        \param motorRight Objekt für den rechten Motor
        \param vmax Maximale Geschwindigkeit während der Positionierung
        \param wheelDiameter Durchmesser der Antriebsräder
        \param trackWidth Abstand der Räder (rechts-links)
    */
    Drive( Motor  &motorLeft,
           Motor  &motorRight,
           int     vmax,
           float   wheelDiameter,
           float   trackWidth )

    : orb( *orbPtr    )
    , mLi( motorLeft  )
    , mRe( motorRight )

    {
      this->vmax = (float)vmax;

      // abgeleitete Groessen:
      faktorMM2Tics     = 1000.0f/(M_PI*(float)wheelDiameter);
      faktorWinkel2Diff = (float)trackWidth*M_PI/360.0f;

      dLi = mLi.getPosition();
      dRe = mRe.getPosition();
    }

  private:
    //---------------------------------------------------------------
    virtual void fahre( int li, int re )
    {
      mLi.setSpeed( 0 );
      mRe.setSpeed( 0 );

      orb.wait( 20 );

      int targetLi = mLi.getPosition() + li;
      int targetRe = mRe.getPosition() + re;

      // Passe Geschwindigkeit der beiden Raeder so an,
      // dass diese gleichzeitig ihr Ziel erreichen
      float dges  = (fabs((float)li) + fabs((float)re));

      if( dges != 0 )
      {
        mLi.setPosition(  vmax * (float)li/dges, targetLi );
        mRe.setPosition(  vmax * (float)re/dges, targetRe );

        orb.wait( 20 );

        while(   fabs( (float)mLi.getPosition() - targetLi ) > 1
              || fabs( (float)mRe.getPosition() - targetRe ) > 1 )
        {
        }

        orb.wait( 20 );
      }
    }

  private:
    //---------------------------------------------------------------
    virtual void distanceReset( void )
    {
      dLi = mLi.getPosition();
      dRe = mRe.getPosition();
    }

    //---------------------------------------------------------------
    virtual int distance( void )
    {
      int li = mLi.getPosition()-dLi;
      int re = mRe.getPosition()-dRe;

      return( 0.5*(li + re)/faktorMM2Tics+0.5 );
    }

    //---------------------------------------------------------------
    virtual int angle( void )
    {
      int li = mLi.getPosition()-dLi;
      int re = mRe.getPosition()-dRe;

      return( (int)(0.5*(li - re)/(faktorMM2Tics*faktorWinkel2Diff)+0.5) );
    }

  public:
    //---------------------------------------------------------------
    /*! Fahre eine Strecke

       Die Funktion blockiert solange, bis das Fahrziel erreicht wurde
       \param distance Länge des Bogens
       \param angle Winkel, um den sich die Fahrtrichtung ändern soll
    */
    virtual void track( float distance, float angle )
    {
      float li = distance + faktorWinkel2Diff*angle;
      float re = distance - faktorWinkel2Diff*angle;

      fahre( faktorMM2Tics*li, faktorMM2Tics*re );
    }

    //---------------------------------------------------------------
    /*! Fahre mit konstanter <b>Geschwindigkeit</b>
        \param li Geschwindigkeit linker Motor
        \param re Geschwindigkeit rechter Motor
    */
    virtual void speed( float left, float right )
    {
      mLi.setSpeed( faktorMM2Tics*left );
      mRe.setSpeed( faktorMM2Tics*right );
    }

    //---------------------------------------------------------------
    /*! Fahre mit konstanter <b>Leistung</b>
        \param li Geschwindigkeit linker Motor
        \param re Geschwindigkeit rechter Motor
    */
    virtual void power( float left, float right )
    {
      mLi.setPower( left );
      mRe.setPower( right );
    }

    //---------------------------------------------------------------
    /*! Bremst den Roboter (Kurzschlussbremse)
    */
    virtual void brake( void )
    {
      mLi.brake();
      mRe.brake();
    }

    virtual void setVmax(int vmax)
    {
      this->vmax = vmax;
    }

};
#endif
