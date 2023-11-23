/********************************************************************


********************************************************************/

//*******************************************************************
class cApplication : public cApplicationBase
{
  private:
    Monitor  mon;
      Timer t;   

  public:
    //---------------------------------------------------------------
    cApplication(  )
    {
    }

    //---------------------------------------------------------------
    virtual void runTestSuite_A( void )
    {
      mon.print(1, "Sensor Test A" );
      t.wait(2000);

      Ev3_Color       ev3Color( Sensor::S1, Ev3_Color::COLOR );
      Ev3_Gyro        ev3Gyro ( Sensor::S2, Ev3_Gyro::ANGLE );
      Ev3_Infrared    ev3IR   ( Sensor::S3 );
      Ev3_Ultrasonic  ev3US   ( Sensor::S4 );

      BYTE ev3ColorMode = Ev3_Color::LIGHT;
      BYTE ev3GyroMode  = Ev3_Gyro::ANGLE;

      while(1)
      {
        char *colorMode[] = { "LIGHT", "AMBIENT", "COLOR" };
        char *gyroMode[]  = { "ANGLE", "RATE" };
        
        mon.print( 1, "S1 EV3-Color:%5d (%s) ", ev3Color.get(),  colorMode[ev3ColorMode] );
        mon.print( 2, "S2 EV3-Gyro :%5d (%s) ", ev3Gyro.get(), gyroMode [ ev3GyroMode] );
        mon.print( 3, "S3 EV3-IR   :%5d "     , ev3IR.get() );
        mon.print( 4, "S4 EV3-US   :%5d "     , ev3US.get() );

        switch( mon.getKeyEvent() )
        {
          case Monitor::Taste_A2: ev3ColorMode = (ev3ColorMode+1)%3;
                                  ev3Color.init( (Ev3_Color::Mode)ev3ColorMode );               break;

          case Monitor::Taste_A6: ev3GyroMode = (ev3GyroMode+1)%3;
                                  ev3Gyro.init( (Ev3_Gyro::Mode)ev3GyroMode );                  break;
          
          case Monitor::Taste_A4: ev3Color.calibrationBlack();                                  break;
          case Monitor::Taste_A8: ev3Color.calibrationWhite();                                  break;
          
          case Monitor::Taste_C1: Memory::store();                                              break;
        }
      }
    }

    //---------------------------------------------------------------
    virtual void runTestSuite_B( void )
    {
      mon.print(1, "Sensor Test B" );
      t.wait(2000);

      Nxt_Light       nxtLight( Sensor::S1, Nxt_Light::LIGHT_ON );
      Nxt_Ultrasonic  nxtUS   ( Sensor::S2 );
      Nxt_Touch       nxtTouch( Sensor::S3 );
      Ev3_Touch       ev3Touch( Sensor::S4 );
      
      Nxt_Light::Mode nxtLightMode = Nxt_Light::LIGHT_ON;

      while(1)
      {
        mon.print( 1, "S1 Light:    %5d (%s) ", nxtLight.get(), nxtLightMode==nxtLight.LIGHT_ON?"ON":"OFF" );
        mon.print( 2, "S2 US:       %5d "     , nxtUS.get()    );
        mon.print( 3, "S3 NXT-Touch:%5d "     , nxtTouch.get() );
        mon.print( 4, "S4 EV3-Touch:%5d "     , ev3Touch.get() );

        switch( mon.getKeyEvent())
        {
          case Monitor::Taste_A1: nxtLightMode = nxtLight.LIGHT_OFF;
                                  nxtLight.init( nxtLightMode );         break;

          case Monitor::Taste_A5: nxtLightMode = nxtLight.LIGHT_ON;
                                  nxtLight.init( nxtLightMode  );        break;
          
          case Monitor::Taste_A4: nxtLight.calibrationBlack();           break;
          case Monitor::Taste_A8: nxtLight.calibrationWhite();           break;
          
          case Monitor::Taste_C1: Memory::store();                       break;
          
        }
      }
    }

    //---------------------------------------------------------------
    virtual void runTestSuite_C( void )
    {
      mon.print(1, "Sensor Test C" );
      t.wait(2000);

      MB_LineFollower mbLF( Sensor::S1 );
      MB_Ultrasonic   mbUS( Sensor::S2 );
      Digital         d1  ( Digital::D1 );
      Digital         d2  ( Digital::D2 );

      while(1)
      {
        mon.print( 1, "S1 LineFolower: %5d ", mbLF.get() );
        mon.print( 2, "S2 US:          %5d ", mbUS.get() );
        mon.print( 3, "D1 Digital:     %5d ", d1.get()   );
        mon.print( 4, "D2 Digital:     %5d ", d2.get()   );
      }
    }

    //---------------------------------------------------------------
    virtual void runTestSuite_D( void )
    {
      mon.print(1, "Sensor Test D" );
      t.wait(2000);
      
      Orb_Sensor  s1_a1 ( Orb_Sensor::S1, Orb_Sensor::ANALOG_A  );
      Orb_Sensor  s1_a2 ( Orb_Sensor::S1, Orb_Sensor::ANALOG_B  );
      Orb_Sensor  s1_d5 ( Orb_Sensor::S1, Orb_Sensor::DIGITAL_A );
      Orb_Sensor  s1_d6 ( Orb_Sensor::S1, Orb_Sensor::DIGITAL_B );
        
      Orb_Sensor  s2_a1 ( Orb_Sensor::S2, Orb_Sensor::ANALOG_A  );
      Orb_Sensor  s2_a2 ( Orb_Sensor::S2, Orb_Sensor::ANALOG_B  );
      Orb_Sensor  s2_d5 ( Orb_Sensor::S2, Orb_Sensor::DIGITAL_A );
      Orb_Sensor  s2_d6 ( Orb_Sensor::S2, Orb_Sensor::DIGITAL_B );
        
      Orb_Sensor  s3_a1 ( Orb_Sensor::S3, Orb_Sensor::ANALOG_A  );
      Orb_Sensor  s3_a2 ( Orb_Sensor::S3, Orb_Sensor::ANALOG_B  );
      Orb_Sensor  s3_d5 ( Orb_Sensor::S3, Orb_Sensor::DIGITAL_A );
      Orb_Sensor  s3_d6 ( Orb_Sensor::S3, Orb_Sensor::DIGITAL_B );
        
      Orb_Sensor  s4_a1 ( Orb_Sensor::S4, Orb_Sensor::ANALOG_A  );
      Orb_Sensor  s4_a2 ( Orb_Sensor::S4, Orb_Sensor::ANALOG_B  );
      Orb_Sensor  s4_d5 ( Orb_Sensor::S4, Orb_Sensor::DIGITAL_A );
      Orb_Sensor  s4_d6 ( Orb_Sensor::S4, Orb_Sensor::DIGITAL_B );

      while(1)
      {
        mon.print( 1, "S1 %5d %5d %1d %1d", s1_a1.get(), s1_a2.get(), s1_d5.get(), s1_d6.get() );
        mon.print( 2, "S2 %5d %5d %1d %1d", s2_a1.get(), s2_a2.get(), s2_d5.get(), s2_d6.get() );
        mon.print( 3, "S3 %5d %5d %1d %1d", s3_a1.get(), s3_a2.get(), s3_d5.get(), s3_d6.get() );
        mon.print( 4, "S4 %5d %5d %1d %1d", s4_a1.get(), s4_a2.get(), s4_d5.get(), s4_d6.get() );
      }
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      mon.print(1, "Sensor Test 1 (%.6s,%.5s)",__DATE__,__TIME__);
      mon.print(3, "Select Test Suite");
      t.wait(2000);

      while(1)
      {
        switch( mon.getKeyEvent() )
        {
          case Monitor::Taste_B1:  runTestSuite_A(); break;
          case Monitor::Taste_B4:  runTestSuite_B(); break;
          case Monitor::Taste_B7:  runTestSuite_C(); break;
          case Monitor::Taste_B10: runTestSuite_D(); break;
        }
      }
    }
};
