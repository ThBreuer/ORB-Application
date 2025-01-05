/********************************************************************

Beispielanwendung

  - Fernsteuerung


********************************************************************/

//*******************************************************************
class Application : public ApplicationBase
{
  public:
    //---------------------------------------------------------------
    Monitor    monitor;

    LEGO_Motor   motorLi;
    LEGO_Motor   motorRe;
    Drive      robo;

    Memory::Item speed;

    //---------------------------------------------------------------
    Application(  )

    : motorLi( Motor::M1, Motor::NORMAL )
    , motorRe( Motor::M4, Motor::NORMAL )

    , robo( motorLi,
            motorRe,
               2000,   // Max Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
                 56,   // Durchmesser der Räder (mm)
                140 )  // Abstand der Räder (mm)

    {
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      monitor.print(1, "Remote (%.6s,%.5s)",__DATE__,__TIME__);

      Drive::Odometrie odo( robo );
      
      if( speed == -1 ) // speed never set
      {
        speed = 50;
      }

      while(1)
      {
        monitor.print(2, "Speed:   %5d mm/s",  (int)speed        );
        monitor.print(3, "Strecke: %5d mm"  ,  odo.getDistance() );
        monitor.print(4, "Winkel:  %5d °"   ,  odo.getAngle()    );

        switch( monitor.getKeyEvent() )
        {
          case Monitor::Taste_A1: robo.track(    0, +90 ); break;
          case Monitor::Taste_A5: robo.track(    0, -90 ); break;
          case Monitor::Taste_A2: robo.track( +100,   0 ); break;
          case Monitor::Taste_A6: robo.track( -100,   0 ); break;

          case Monitor::Taste_A3: speed = (speed <  500) ? speed + 25 : 1000; break;
          case Monitor::Taste_A7: speed = (speed >   25) ? speed - 25 :    0; break;

          case Monitor::Taste_C1: Memory::store();                            break;
        }

        switch( monitor.getKeyState() )
        {
          case Monitor::Keine_Taste: robo.speed(       0,         0); break;
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
};
