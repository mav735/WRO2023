#pragma config(Sensor, S1,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Motor,  motorA,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)

#define READ

#include "include/includes.h"

task main(){
    initAll();
    stopMove(700);
    unsigned long varPgmTime = nPgmTime;
    float now = getBatteryVoltage();
    now = getBatteryVoltage();

    if (now < 7.6){
        playSound(soundException);
    }

    setRightSensorBlackLineBlackStop(1, 0);
    lineFollowEncoder(20, 100, 20, 10000);
    stopMove(500);
    lineAligning(20, 40, 20, 300, 90, false);
    stopMove(500);

    displayCenteredTextLine(2, "%d", nPgmTime - varPgmTime);

    stopMove(20000);
    fileClose(fileHandle);
}
