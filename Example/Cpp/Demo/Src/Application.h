/********************************************************************

********************************************************************/

//*******************************************************************
class Application : public ApplicationBase
{
  public:

    Monitor    monitor;
    Nxt_Touch  startTaste;
    Nxt_Touch  pauseTaste;

    //---------------------------------------------------------------
    Application(  )

    : startTaste( Sensor::S1 ),
      pauseTaste( Sensor::S2 )
    {
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      // ------------------------------------------------------------
      // Stoppuhr
      // ------------------------------------------------------------
      if( para == 0 )
      {
        monitor.print( 1, "Stoppuhr" );
        monitor.print( 2, "Taste an S1: Messen" );
        monitor.print( 3, "Taste an S2: Reset"  );

        stoppuhr();
      }

      // ------------------------------------------------------------
      // Laufzeitmessung
      // ------------------------------------------------------------
      else
      {
        monitor.print( 1, "Laufzeit" );
        monitor.print( 2, "" );
        monitor.print( 3, "Taste an S2: Zwischenzeit" );

        laufzeit();
      }
    }

    //---------------------------------------------------------------
    void stoppuhr()
    {
       while(1)
        {
          monitor.print( 4, "Startbereit!" );
          if( startTaste.get() )
          {
            Timer t;

            monitor.print( 4, "Messung läuft ..." );
            t.wait(100);                               // Taster entprellen
            while( startTaste.get() ) {}
            anzeigen( t.get() );
            while( pauseTaste.get() == false ) {}
          }
        }
    }

    //---------------------------------------------------------------
    void laufzeit()
    {
      Timer t;

      while(1)
      {
        anzeigen( t.get() );
        while( pauseTaste.get() == true ) {}
      }
    }

    //---------------------------------------------------------------
    void anzeigen( DWORD zeit )
    {
      monitor.print( 4, "Laufzeit: %d ms", zeit );
    }

};
