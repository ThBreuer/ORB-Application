/********************************************************************

Beispielanwendung

"Start"
  Einfache Linienverfolgung mit zwei Lichtsensoren, schwarze Linie auf weissem Grund

"Kalibration"
  - Einstellung der Geschwindigkeit
  - Kalibration der Lichtsensoren
  - Fernsteuerung


********************************************************************/

//*******************************************************************
class cApplication : public cApplicationBase
{
  private:
    Monitor    monitor;

    MB_Motor      motorLi;
    MB_Motor      motorRe;
    Drive      robo;

    MB_LineFollower mbLF;

    MB_Ultrasonic   mbUS;

    Timer      timer;

    Memory::Item speed;
    Memory::Item diff;

  public:
    //---------------------------------------------------------------
    cApplication(  )

    : motorLi( Motor::M1, Motor::REVERSE )
    , motorRe( Motor::M4, Motor::NORMAL  )

    , robo( motorLi,
            motorRe,
            3000,  // Max Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
            67.6, //41,    // Durchmesser der Räder (mm)
            135)//170 )  // Abstand der Räder (mm)

    , mbLF ( Sensor::S1 )
    , mbUS ( Sensor::S2 )

    {
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      // ------------------------------------------------------------
      // Start
      // ------------------------------------------------------------
      if( para == 0 )
      {
        monitor.print(1, "Start (%.6s,%.5s)",__DATE__,__TIME__);
        timer.wait( 1000 );

        while(1)
        {
          int li = mbLF.get(MB_LineFollower::SENSOR_2);
          int re = mbLF.get(MB_LineFollower::SENSOR_1);

          monitor.print( 1, "Speed: %5d", (int)speed );
          monitor.print( 2, "Diff:  %5d", (int)diff  );
          monitor.print( 3, "LineFolower: %1d %1d ", li , re );
          monitor.print( 4, "US:          %5d "    , mbUS.get() );

          switch( monitor.getKeyEvent() )
          {
            case Monitor::Taste_A3: speed = (speed <  500) ? speed + 25 : 1000; break;
            case Monitor::Taste_A7: speed = (speed >   25) ? speed - 25 :    0; break;

            case Monitor::Taste_A4: diff = (diff <  100) ? diff + 10 : 100; break;
            case Monitor::Taste_A8: diff = (diff >    0) ? diff - 10 :   0; break;

            case Monitor::Taste_C1: robo.speed( 0, 0 );
                                    Memory::store();                        break;
          }

       int back = speed*(1-0.01*diff);

      if( mbUS.get() < 50 )
      {
        robo.track( -100,   0 );
        robo.track(    0, 180 );
        robo.track( -100,   0 );
      }
      else
      {
        if( li && !re )      // nur links weiss
        {
        // rechts weiter ...
        robo.speed( speed, back );
        }
        else if( !li && re ) // nur rechts weiss
        {
        // geradeaus
        robo.speed( back, speed );
        }
        else if( li && re ) // beide weiss
        {
        robo.speed( -0.2*speed, -0.2*speed );
        }
        else                // beide schwarz
        {
        robo.speed( speed, speed );
        }
      }
        } // ende der while-Schleife
      }

      // ------------------------------------------------------------
      // Kalibration
      // ------------------------------------------------------------
      else
      {
        monitor.print(1, "Kalibration (%.6s,%.5s)",__DATE__,__TIME__);
        timer.wait( 2000 );

        Drive::Odometrie odo( robo );

        while(1)
        {
          monitor.print(1, "Speed:   %5d",              (int)speed                                  );
          monitor.print(2, "Diff:    %5d",              (int)diff                                   );
          monitor.print(3, "Strecke: %5d Winkel:  %5d",    odo.getDistance(), 
                                                           odo.getAngle() );
          monitor.print(4, "LineFolower: %1d %1d US: %5d", mbLF.get(MB_LineFollower::SENSOR_1), 
                                                           mbLF.get(MB_LineFollower::SENSOR_2), 
                                                           mbUS.get() );

          switch( monitor.getKeyEvent() )
          {
            case Monitor::Taste_A1: robo.track(    0, +90 ); break;
            case Monitor::Taste_A5: robo.track(    0, -90 ); break;
            case Monitor::Taste_A2: robo.track( +100,   0 ); break;
            case Monitor::Taste_A6: robo.track( -100,   0 ); break;

            case Monitor::Taste_A3: speed = (speed <  500) ? speed + 25 : 1000; break;
            case Monitor::Taste_A7: speed = (speed >   25) ? speed - 25 :    0; break;

            case Monitor::Taste_A4: diff = (diff <  100) ? diff + 10 : 100; break;
            case Monitor::Taste_A8: diff = (diff >    0) ? diff - 10 :   0; break;

            case Monitor::Taste_C1: Memory::store();                        break;
          }

          switch( monitor.getKeyState() )
          {
            case Monitor::Keine_Taste: robo.speed(0,0); break;
            case Monitor::Taste_B1:    robo.speed(       0,   +speed ); break;
            case Monitor::Taste_B2:    robo.speed( 2*speed,  2*speed ); break;
            case Monitor::Taste_B3:    robo.speed(  +speed,        0 ); break;
            case Monitor::Taste_B4:    robo.speed(  -speed,   +speed ); break;
            case Monitor::Taste_B5:    robo.speed(  +speed,   +speed ); break;
            case Monitor::Taste_B6:    robo.speed(  +speed,   -speed ); break;
            case Monitor::Taste_B7:    robo.speed(  -speed,        0 ); break;
            case Monitor::Taste_B8:    robo.speed(  -speed,   -speed ); break;
            case Monitor::Taste_B9:    robo.speed(       0,   -speed ); break;
          }
        }
      }
    }
};
