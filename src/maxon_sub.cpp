//
// Created by johnny on 2020/11/24.
//


#include "maxon_sub.h"
#include <iostream>

using namespace std;

maxonsub::maxonsub()
{
    keyHandle=0;
    ErrorCode = 0x00;
    nodeID = 2;

}


maxonsub::maxonsub(void* Handle,unsigned int input_node_Id)
{
    keyHandle=Handle;
    ErrorCode = 0x00;
    nodeID = input_node_Id;
    cout <<"Start sub!" << endl;
}



void maxonsub::closesubDevice()
{
    disablesubDevice();

    unsigned int ErrorCode = 0;

    cout<<"Closing subDevice!"<<endl;

    if(subkeyHandle != 0)
        VCS_CloseSubDevice(subkeyHandle, &ErrorCode);

    VCS_CloseAllSubDevices(keyHandle,&ErrorCode);
}

void maxonsub::enablesubDevice()
{

    unsigned int ErrorCode = 0;
    int IsInFault = FALSE;

    if( VCS_GetFaultState(subkeyHandle, nodeID, &IsInFault, &ErrorCode) )
    {
        if( IsInFault && !VCS_ClearFault(subkeyHandle, nodeID, &ErrorCode) )
        {
            cout << "Clear fault failed! , error code="<<ErrorCode<<endl;
            return;
        }

        int IsEnabled = FALSE;
        if( VCS_GetEnableState(subkeyHandle, nodeID, &IsEnabled, &ErrorCode) )
        {
            if( !IsEnabled && !VCS_SetEnableState(subkeyHandle, nodeID, &ErrorCode) )
            {
                cout << "Set sub enable state failed!, error code="<<ErrorCode<<endl;
            }
            else
            {
                cout << "Enable sub succeeded! " ;
            }
        }
    }
    else
    {
        cout << "Get fault state failed!, error code, error code="<<ErrorCode<<endl;
    }

}
//
void maxonsub::disablesubDevice()
{

    unsigned int ErrorCode = 0;
    int IsInFault = FALSE;

    if( VCS_GetFaultState(subkeyHandle, nodeID, &IsInFault, &ErrorCode) )
    {
        if( IsInFault && !VCS_ClearFault(subkeyHandle, nodeID, &ErrorCode) )
        {
            cout<<"Clear fault failed!, error code="<<ErrorCode<<endl;
            return;
        }

        int IsEnabled = FALSE;
        if( VCS_GetEnableState(subkeyHandle, nodeID, &IsEnabled, &ErrorCode) )
        {
            if( IsEnabled && !VCS_SetDisableState(subkeyHandle, nodeID, &ErrorCode) )
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


void maxonsub::Move(long TargetPosition)
{

    unsigned int errorCode = 0;

    if( VCS_ActivateProfilePositionMode(subkeyHandle, nodeID, &errorCode) )
    {
        int Absolute = TRUE; // FALSE;
        int Immediately = TRUE;

        if( !Absolute )
        {
            int PositionIs = 0;
            if( VCS_GetPositionIs(subkeyHandle, nodeID, &PositionIs, &errorCode) );
        }

        if( !VCS_MoveToPosition(subkeyHandle, nodeID, TargetPosition, Absolute, Immediately, &errorCode) )
        {
            cout << "Move to position failed!, error code="<<errorCode<<endl;

        }
    }
    else
    {
        cout << "Activate profile position mode failed!" << endl;
    }
}


void maxonsub::speed(long Targetspeed,long TargetAcceleration)
{

    unsigned int errorCode = 0;

    if( VCS_ActivateProfileVelocityMode(subkeyHandle, nodeID, &errorCode))
    {
        int Absolute = TRUE; // FALSE;
        int Immediately = TRUE;
        VCS_SetVelocityProfile(subkeyHandle, nodeID, TargetAcceleration, TargetAcceleration, &errorCode);
        if( !Absolute )
        {
            int VelocityIs = 0;
            if( VCS_GetVelocityIs(subkeyHandle, nodeID, &VelocityIs, &errorCode) );
        }

        if( !VCS_MoveWithVelocity(subkeyHandle, nodeID, Targetspeed,&errorCode) )
        {
            cout << "Move to Velocity failed!, error code="<<errorCode<<endl;

        }
    }
    else
    {
        cout << "Activate profile Velocity mode failed!" << endl;
    }
}

void maxonsub::GetCurrentPosition(int& CurrentPosition)
{

    unsigned int errorCode = 0;

    if( !VCS_GetPositionIs(subkeyHandle, nodeID, &CurrentPosition, &errorCode) ){
        cout << " error while getting current position , error code="<<errorCode<<endl;
    }

}

void maxonsub::GetCurrentVelocity(int& CurrentVelocity)
{

    unsigned int errorCode = 0;

    if( !VCS_GetVelocityIs(subkeyHandle, nodeID, &CurrentVelocity, &errorCode) ){
        cout << " error while getting current Velocity , error code="<<errorCode<<endl;
    }

}

void maxonsub::GetCurrentCurrent(short& CurrentCurrent)
{

    unsigned int errorCode = 0;

    if( !VCS_GetCurrentIs(subkeyHandle, nodeID, &CurrentCurrent, &errorCode) ){
        cout << " error while getting current Current , error code="<<errorCode<<endl;
    }

}

void maxonsub::Halt()
{
    unsigned int ErrorCode = 0;

    if( !VCS_HaltPositionMovement(subkeyHandle, nodeID, &ErrorCode) )
    {
        cout<<"Halt position movement failed!, error code="<<ErrorCode<<endl;
    }
}

void maxonsub::activate_device()
{
    // Configuring EPOS for analog motor control
    char DeviceName[]="EPOS2";
    char ProtocolStackName[] = "CANopen";
    unsigned int ErrorCode = 0x00;
    unsigned int baudrate_ = 1000000;


    subkeyHandle = VCS_OpenSubDevice(keyHandle,DeviceName, ProtocolStackName,&ErrorCode);

    if( subkeyHandle == 0 )
    {
        cout<<"Open sub device failure, error code="<<ErrorCode<<endl;
    }
    else
    {
        cout<<"Open sub device success!"<<endl;
    }


    if( !VCS_SetGatewaySettings(keyHandle, baudrate_, &ErrorCode) )
    {
        cout<<"Set gateway settings failed!, error code="<<ErrorCode<<endl;
        closesubDevice();
    }
    VCS_GetGatewaySettings(keyHandle, &baudrate_, &ErrorCode);
    cout<<"baudrate is "<<baudrate_<<endl;
    cout<<subkeyHandle<<endl;



    enablesubDevice();

}


void maxonsub::initializeDevice(){
    closesubDevice();
    activate_device();
}


