/********************************************************************


********************************************************************/

//*******************************************************************
class cApplication : public cApplicationBase
{
  private:
    Monitor    mon;
    ModelServo s1;
    ModelServo s2;

  public:
    //---------------------------------------------------------------
    cApplication(  )
    
    : s1( ModelServo::S1, 90 )
    , s2( ModelServo::S2, 90 )

    {
    }

    //---------------------------------------------------------------
    void test( Motor *m )
    {
      int   speed = 400;

      while(1)
      {
        for( int i=0;i<4;i++)
        {
          mon.print(i+1,"M%d:  %7d %5d %5d",i+1,
                                            m[i].getPosition(), 
                                            m[i].getSpeed(), 
                                            m[i].getPower() );
        }
        
        switch( mon.getKeyEvent() )
        {
            case Monitor::Taste_A3: m[2].setPosition( speed, 1000 ); m[3].setPosition( speed, 1000 ); break;
            case Monitor::Taste_A4: m[2].setPosition( speed,    0 ); m[3].setPosition( speed,    0 ); break;
            case Monitor::Taste_A7: m[2].setPower( 0 );              m[3].setPower( 0 );              break;
            case Monitor::Taste_A8: m[2].brake();                    m[3].brake();                    break;
          
            case Monitor::Taste_A1: s1.set( 90,  50 );                   break;
            case Monitor::Taste_A2: s2.set( 90,  50 );                   break;
            case Monitor::Taste_A5: s1.set(  0, 200 ); s2.set( 0, 200 ); break;
            case Monitor::Taste_A6: s1.halt();         s2.halt();        break;
        }

        switch( mon.getKeyState() )
        {
          case Monitor::Keine_Taste: m[0].setSpeed(       0   ); m[1].setSpeed(       0   ); break;
          case Monitor::Taste_B2:    m[0].setSpeed( 2*speed   ); m[1].setSpeed( 2*speed   ); break;
          case Monitor::Taste_B4:    m[0].setSpeed(  -speed   ); m[1].setSpeed(  +speed   ); break;
          case Monitor::Taste_B8:    m[0].setSpeed(  -speed/2 ); m[1].setSpeed(  -speed/2 ); break;
          case Monitor::Taste_B6:    m[0].setSpeed(  +speed   ); m[1].setSpeed(  -speed   ); break;
        }
      } // ende der while-Schleife
    }
    
    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      int   speed = 400;
      Timer t;

      while(1)
      {
        mon.print(1, "Motor Test (%.6s,%.5s)",__DATE__,__TIME__);
        mon.print(3, "Select Motor-Type");

        switch( mon.getKeyEvent() )
        {
          case Monitor::Taste_B10:
          {
            mon.print(3, "Motor-Type: LEGO");
            t.wait(2000);

            Motor m[4] = { LEGO_Motor( Motor::M1, Motor::NORMAL ),
                           LEGO_Motor( Motor::M2, Motor::NORMAL ),
                           LEGO_Motor( Motor::M3, Motor::NORMAL ),
                           LEGO_Motor( Motor::M4, Motor::NORMAL ) };
            test( m );
            break;
          }
            
          case Monitor::Taste_B11:
          {
            mon.print(3, "Motor-Type: Makeblock");
            t.wait(2000);
            Motor m[4] = { MB_Motor( Motor::M1, Motor::REVERSE ),
                           MB_Motor( Motor::M2, Motor::NORMAL  ),
                           MB_Motor( Motor::M3, Motor::REVERSE ),
                           MB_Motor( Motor::M4, Motor::NORMAL  ) };
            test( m );
            break;
          }
        }
      } // ende der while-Schleife
    }
};
