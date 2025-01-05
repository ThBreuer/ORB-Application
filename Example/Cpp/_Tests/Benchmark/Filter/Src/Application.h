//*******************************************************************
/*!
\author Nils Hoffmann
\date   15.10.2024
*/

#include "Common/Src/ORB.h"

//*******************************************************************
class Application : public ApplicationBase
{
  public:
    Application(){}

    int port = 0;

    float coeffitient = 0.005;
    int spike = 20000;
    int dipp = 2000;
    int interrations = 1000;

    //this might not be nice code, but it is meant to have the same structure as the python code to be comparable
    float readSensorWithFilter(){
      float filtered_val = 0;
      float val = 0;
      int actual_interrations = interrations;

      int current_val = 0;
      for(int i=0;i<interrations;i++){
          current_val = orb.getSensor(port).value[0]&0xFFF;
          if(current_val > spike || current_val < dipp){
                actual_interrations--;
                continue;
          }
          filtered_val = coeffitient * current_val + (1 - coeffitient) * filtered_val;
          val += filtered_val;
      }
      if (actual_interrations == 0){
          return 0;
      }

      float average_value = val/float(actual_interrations);
      return average_value;
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
      orb.configSensor(port, ORB::ANALOG, 0, (0x08|0x07)<<8 );
      Monitor m = Monitor();

      int start = orb.getTime();
      int ist = start;
      int war = ist;

      int sum = 0;
      int count = 0;

      while( 1 )
      {
        ist = orb.getTime();
        float val = readSensorWithFilter();
        int deltaTime = (ist - war);
        sum += deltaTime;
        count++;
        m.print(1, "FilteredValue: %d", val);
        m.print(2, "DeltaTime: %d", deltaTime);
        m.print(3, "AvgTime: %d", (sum/count));
        war = ist;
      }

    }
};
