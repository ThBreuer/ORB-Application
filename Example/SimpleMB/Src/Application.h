/********************************************************************

Beispielanwendung

********************************************************************/

//*******************************************************************
class cApplication : public cApplicationBase
{
  public:
    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
        Monitor    monitor;

        MB_Motor   motorLi( Motor::M1, Motor::REVERSE );
        MB_Motor   motorRe( Motor::M4, Motor::NORMAL  );

        Drive      robo   ( motorLi,
                            motorRe,
                            2500,  // Max Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
                              41,  // Durchmesser der Räder (mm)
                             197   // Abstand der Räder (mm)
                          );

      monitor.print( 0, "Demo  (%.6s,%.5s)", __DATE__ , __TIME__ );
      while(1)
      {
        robo.track( 500,   0 );
        robo.track(    0, 180 );
      }
    }
};
