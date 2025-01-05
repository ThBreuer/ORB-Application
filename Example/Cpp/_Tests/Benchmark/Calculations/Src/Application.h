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

    float sin_approx(float x){
        x = x * (M_PI/180);
        x = fmod(x, (2*M_PI));
        int i = 1;
        float cur = x;
        float acc = 1;
        float fact = 1;
        float pow = x;
        while(abs(acc) > 1e-8 && i < 5){
            fact *= (2 * i) * (2 * i + 1);
            pow *= -1 * x * x;
            acc = pow / fact;
            cur += acc;
            i += 1;
        }

        return cur;
    }

    void squared(){
        int square = 0;
        for(int i=0;i<10000;i++){
                square = i*i;
        }
    }

    void sqrt(){
        for(int i=0;i<1000;i++){
            sqrt_newton(i);
        }
    }

    double sqrt_newton(double number) {
        if (number == 0) return 0;

        double estimate = number;
        double tolerance = 1e-10;

        while (true) {
            double next_estimate = (estimate + number / estimate) / 2;
            if (fabs(next_estimate - estimate) < tolerance) {
                break;
            }
            estimate = next_estimate;
        }

        return estimate;
    }

    //the ORB-Python vm does pretty much this but less complex, we only print this for debugging anyways for calc uncomment
    char* format_float_to_string(float value) {
        static char formatted_string[128];
        snprintf(formatted_string, sizeof(formatted_string), "%.2f", value);
        return formatted_string;
    }

    //---------------------------------------------------------------
    virtual void run( BYTE para )
    {
        Monitor m = Monitor();
        float i = 0;
        int start = orb.getTime();
        while(i <= 360){
            //this is for debugging we dont print for benchmark
            //m.print(1, "sin(%s) = %s", format_float_to_string(i), format_float_to_string(sin_approx(i)));
            i += 0.025;
        }
        int finish = orb.getTime();
        m.print(1,"sin(0-360): %dms",(finish-start));

        start = orb.getTime();
        squared();
        finish = orb.getTime();
        m.print(2, "squares: %dms",(finish-start));

        start = orb.getTime();
        sqrt();
        finish = orb.getTime();
        m.print(3, "sqrt_newton: %dms",(finish-start));

        while(true){}
    }
};
