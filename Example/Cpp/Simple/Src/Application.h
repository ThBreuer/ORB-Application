/********************************************************************

Beispielanwendung

Je nach Start (kurzer/langer Tastendruck) f�hrt der Roboter ein 
Strecke von 100 mm geradeaus oder dreht sich um 180�.

Mit diesem Programm l��t sich auch der Raddurchmesser und der Radabstand 
genau kalibrieren:
   - Zun�chst Roboter geradeaus fahren lassen und m�glichst genau die 
     zur�ckgelegte Strecke messen.
   - Der Raddurchmesser kann dann aus der tats�chlichen Strecke und dem 
     eingestellten Raddurchmesser bestimmt werden:
   
                         GemesseneStrecke
      NeuerDurchmesser = ---------------- * EingestellterDurchmesser
                             100 mm

  - Einstellung des Raddurchmessers in der Software korrigieren und 
    testen. Wenn die gemessene Strecke noch nicht stimmt, Vorgang wiederholen
 
Erst wenn der Raddurchmesser stimmt, kann auch der Radabstand kalibriert werden:
  - Roboter drehen lassen und mit einem Winkelmesser den tats�chlichen Drehwinkel 
    bestimmen.
  - Der Radabstand kann aus gemessenem Drehwinkel und eingestelltem Radabstand 
    berechnet werden:

                         180�
      NeuerAbstand = ---------------- * EingestellterAbstand
                     GemessenerWinkel

  - Einstellung des Radabstandes in der Software korrigieren und 
    testen. Wenn der gemessene Winkel noch nicht stimmt, Vorgang wiederholen

********************************************************************/

//*******************************************************************
class Application : public ApplicationBase
{
  public:
    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      LEGO_Motor  motorLi( Motor::M1, Motor::NORMAL );
      LEGO_Motor  motorRe( Motor::M4, Motor::NORMAL  );

      Drive      robo   ( motorLi,
                          motorRe,
                             2500,  // Max. Geschwindigkeit (1/1000 Umdrehungen pro Sekunde)
                             56.0,  // Durchmesser der R�der (mm)
                            140.0   // Abstand der R�der (mm)
                         );

      if( para == 0 )
      {
        robo.track( 500, 0 );
      }
      else
      {
        robo.track( 0, 180 );
      }
      robo.power( 0, 0 );
    }
};
