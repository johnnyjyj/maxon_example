//
// Created by johnny on 2020/11/24.
//

#ifndef MAXON_SUB_H
#define MAXON_SUB_H


#include "Definitions.h"

#define TRUE 1
#define FALSE 0


class maxonsub
{
private:
    unsigned int ErrorCode;
    unsigned short nodeID;
    void *keyHandle;
    void *subkeyHandle;

public:
    maxonsub();
    maxonsub(void* ,unsigned int );

    void initializeDevice();

    void closesubDevice();
    void enablesubDevice();
    void disablesubDevice();
    void Move(long TargetPosition);
    void GetCurrentPosition(int& CurrentPosition);
    void speed(long Targetspeed,long TargetAcceleration);
    void Halt();
    void GetCurrentVelocity(int& CurrentVelocity);
    void GetCurrentCurrent(short& CurrentCurrent);
    void activate_device();
};

#endif


