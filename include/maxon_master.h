//
// Created by johnny on 2020/11/24.
//

#ifndef MAXONMOTOR_H
#define MAXONMOTOR_H

#include "Definitions.h"

#define TRUE 1
#define FALSE 0


class maxonmaster
{
private:
    char* PortName;
    unsigned int ErrorCode;
    unsigned short nodeID;

public:
    void *keyHandle;

    maxonmaster();
    maxonmaster(char[], unsigned int );

    void initializeDevice();

    void closeDevice();
    void enableDevice();
    void disableDevice();
    void Move(long TargetPosition);
    void speed(long Targetspeed,long TargetAcceleration);
    void GetCurrentPosition(int& CurrentPosition);
    void GetCurrentVelocity(int& CurrentVelocity);
    void GetCurrentCurrent(short& CurrentCurrent);
    void Halt();
    void activate_device();
};

#endif
