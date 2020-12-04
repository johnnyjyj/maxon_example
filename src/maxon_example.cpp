//
// Created by johnny on 2020/11/24.
//

#include <iostream>
#include <maxon_sub.h>
#include <maxon_master.h>


using namespace std;

int main(int argc, char *argv[]) {
    maxonmaster motor("USB0", 1);
    motor.initializeDevice();
    maxonsub submotor(motor.keyHandle, 2);
    submotor.initializeDevice();

    //easy
    long TargetPosition1 = -20000000;
    int CurrentPosition1 = 0;
    long TargetPosition2 = -20000000;
    int CurrentPosition2 = 0;
    int dd=0;
    motor.Move(TargetPosition1);
    submotor.Move(TargetPosition2);
    while(CurrentPosition1!=TargetPosition1) {
        motor.GetCurrentPosition(CurrentPosition1);
        submotor.GetCurrentPosition(CurrentPosition2);
        cout << "Current Position: " << CurrentPosition1 << " ； "<<CurrentPosition2<<endl;
        dd++;
        if (dd>=2000)break;

    }


    //pid
    int kpp=100;
    int kip=10;
    int kdp=50;
    int kpv=100;
    int kiv=10;
    int kdv=50;
    int lasterrp=0;
    int lasterrv=0;
    int errp=0;
    int errv=0;
    int sumerrp=0;
    int sumerrv=0;
    TargetPosition1 = 20000000;
    long Targetspeed1=0;
    long TargetAcceleration1=0;
    int Currentspeed1 = 0;
    dd=0;
    while(dd<=10000)
    {
        motor.GetCurrentPosition(CurrentPosition1);
        errp=TargetPosition1-CurrentPosition1;
        sumerrp+=errp;
        Targetspeed1=kpp*errp+kip*sumerrp+kdp*(errp-lasterrp);
        lasterrp=errp;
        motor.GetCurrentVelocity(Currentspeed1);
        errv=Targetspeed1-Currentspeed1;
        sumerrv+=errv;
        TargetAcceleration1=abs(kpv*errv+kiv*sumerrv+kdv*(errv-lasterrv));
        lasterrp=errp;
        motor.speed(Targetspeed1,TargetAcceleration1);
        dd++;
    }


    submotor.closesubDevice();
    motor.closeDevice();

    return 0;
}
