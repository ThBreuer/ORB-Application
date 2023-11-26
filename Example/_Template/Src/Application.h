/********************************************************************

Vorlage für eigene Projekte

********************************************************************/

//*******************************************************************
class Application : public ApplicationBase
{
  public:
    /* 
    Hier Objekte deklarieren, die ÜBERALL verwendet werden können
    */
//    Nxt_Motor meinMotor;
    
    //---------------------------------------------------------------
    Application(  )
    /* 
    Hier die oben definierten Objekte initialisieren. Wenn mehrere 
    Objekte initialisiert werden müssen, dann durch Komma getrennt 
    auflisten
    */
//    : meinMotor( Motor::M1, ;otor::NORMAL )
    {
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      /* 
      Hier können weitere Objekte erzeugt werden. Diese sind bis 
      zum Verlassen der Funktion gültig
      */
//      Nxt_Touch meinenSensor( Sensor::S1 );
      
      /*
      Hier all das eintragen, was EINMAL am Anfang gemacht werden soll
      */
//      meinMotor.setPower( 0 );

      while( 1 )
      {
        /*
        In der Schleife das eintragen, was WIEDERHOLT gemacht werden soll
        */
//        if( meinSensor.get() == true )
//        {
//          meinMotor.setPower( 75 );
//        }
//        else
//        {
//          meinMotor.setPower( 0 );
//        }
      }
    }
};
