//
// Created by johnny on 2020/11/24.
//

#include "maxon_master.h"
#include <iostream>

using namespace std;

maxonmaster::maxonmaster()
{
    PortName = "USB0";
    ErrorCode = 0x00;
    nodeID = 1;

}


maxonmaster::maxonmaster(char* portNamestr, unsigned int input_node_Id)
{
    PortName = portNamestr;
    ErrorCode = 0x00;
    nodeID = input_node_Id;
    cout <<"Start master!" << endl;
}



void maxonmaster::closeDevice()
{
    disableDevice();

    unsigned int ErrorCode = 0;

    cout<<"Closing Device!"<<endl;

    if(keyHandle != 0)
        VCS_CloseDevice(keyHandle, &ErrorCode);

    VCS_CloseAllDevices(&ErrorCode);
}

void maxonmaster::enableDevice()
{

    unsigned int ErrorCode = 0;
    int IsInFault = FALSE;

    if( VCS_GetFaultState(keyHandle, nodeID, &IsInFault, &ErrorCode) )
    {
        if( IsInFault && !VCS_ClearFault(keyHandle, nodeID, &ErrorCode) )
        {
            cout << "Clear fault failed! , error code="<<ErrorCode<<endl;
            return;
        }

        int IsEnabled = FALSE;
        if( VCS_GetEnableState(keyHandle, nodeID, &IsEnabled, &ErrorCode) )
        {
            if( !IsEnabled && !VCS_SetEnableState(keyHandle, nodeID, &ErrorCode) )
            {
                cout << "Set enable state failed!, error code="<<ErrorCode<<endl;
            }
            else
            {
                cout << "Enable succeeded!" << endl;
            }
        }
    }
    else
    {
        cout << "Get fault state failed!, error code, error code="<<ErrorCode<<endl;
    }

}

void maxonmaster::disableDevice()
{

    unsigned int ErrorCode = 0;
    int IsInFault = FALSE;

    if( VCS_GetFaultState(keyHandle, nodeID, &IsInFault, &ErrorCode) )
    {
        if( IsInFault && !VCS_ClearFault(keyHandle, nodeID, &ErrorCode) )
        {
            cout<<"Clear fault failed!, error code="<<ErrorCode<<endl;
            return;
        }

        int IsEnabled = FALSE;
        if( VCS_GetEnableState(keyHandle, nodeID, &IsEnabled, &ErrorCode) )
        {
            if( IsEnabled && !VCS_SetDisableState(keyHandle, nodeID, &ErrorCode) )
            {
                cout<<"Set disable state failed!, error code=" <<ErrorCode<<endl;
            }
            else
            {
                cout<<"Set disable state succeeded!"<<endl;
            }
        }
    }
    else
    {
        cout<<"Get fault state failed!, error code="<<ErrorCode<<endl;
    }
}


void maxonmaster::Move(long TargetPosition)
{

    unsigned int errorCode = 0;

    if( VCS_ActivateProfilePositionMode(keyHandle, nodeID, &errorCode) )
    {
        int Absolute = TRUE; // FALSE;
        int Immediately = TRUE;

        if( !Absolute )
        {
            int PositionIs = 0;
            if( VCS_GetPositionIs(keyHandle, nodeID, &PositionIs, &errorCode) );
        }

        if( !VCS_MoveToPosition(keyHandle, nodeID, TargetPosition, Absolute, Immediately, &errorCode) )
        {
            cout << "Move to position failed!, error code="<<errorCode<<endl;

        }
    }
    else
    {
        cout << "Activate profile position mode failed!" << endl;
    }
}

void maxonmaster::speed(long Targetspeed,long TargetAcceleration)
{

    unsigned int errorCode = 0;

    if( VCS_ActivateProfileVelocityMode(keyHandle, nodeID, &errorCode))
    {
        int Absolute = TRUE; // FALSE;
        int Immediately = TRUE;
        VCS_SetVelocityProfile(keyHandle, nodeID, TargetAcceleration, TargetAcceleration, &errorCode);
        if( !Absolute )
        {
            int VelocityIs = 0;
            if( VCS_GetVelocityIs(keyHandle, nodeID, &VelocityIs, &errorCode) );
        }

        if( !VCS_MoveWithVelocity(keyHandle, nodeID, Targetspeed,&errorCode) )
        {
            cout << "Move to Velocity failed!, error code="<<errorCode<<endl;

        }
    }
    else
    {
        cout << "Activate profile Velocity mode failed!" << endl;
    }

}


void maxonmaster::GetCurrentPosition(int& CurrentPosition)
{

    unsigned int errorCode = 0;

    if( !VCS_GetPositionIs(keyHandle, nodeID, &CurrentPosition, &errorCode) ){
        cout << " error while getting current position , error code="<<errorCode<<endl;
    }

}

void maxonmaster::GetCurrentVelocity(int& CurrentVelocity)
{

    unsigned int errorCode = 0;

    if( !VCS_GetVelocityIs(keyHandle, nodeID, &CurrentVelocity, &errorCode) ){
        cout << " error while getting current Velocity , error code="<<errorCode<<endl;
    }

}

void maxonmaster::GetCurrentCurrent(short& CurrentCurrent)
{

    unsigned int errorCode = 0;

    if( !VCS_GetCurrentIs(keyHandle, nodeID, &CurrentCurrent, &errorCode) ){
        cout << " error while getting current Current , error code="<<errorCode<<endl;
    }

}

void maxonmaster::Halt()
{
    unsigned int ErrorCode = 0;

    if( !VCS_HaltPositionMovement(keyHandle, nodeID, &ErrorCode) )
    {
        cout<<"Halt position movement failed!, error code="<<ErrorCode<<endl;
    }
}

void maxonmaster::activate_device()
{
    char DeviceName[]="EPOS2";
    char ProtocolStackName[] = "MAXON SERIAL V2";
    char InterfaceName[] = "USB";
    unsigned int ErrorCode = 0x00;
    unsigned long timeout_ = 500;
    unsigned long baudrate_ = 1000000;


    keyHandle = VCS_OpenDevice(DeviceName,ProtocolStackName,InterfaceName,PortName,&ErrorCode);
    cout<<"keyHandle"<<keyHandle<<endl;
    if( keyHandle == 0 )
    {
        cout<<"Open device failure, error code="<<ErrorCode<<endl;
    }
    else
    {
        cout<<"Open device success!"<<endl;
    }


    if( !VCS_SetProtocolStackSettings(keyHandle, baudrate_, timeout_, &ErrorCode) )
    {
        cout<<"Set protocol stack settings failed!, error code="<<ErrorCode<<endl;
        closeDevice();
    }

    enableDevice();

}


void maxonmaster::initializeDevice(){
    closeDevice();
    activate_device();
}
