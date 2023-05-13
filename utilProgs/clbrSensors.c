#pragma config(Sensor, S1, sensorLeft, sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2, sensorRight, sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorI2CCustom9V)
#pragma config(Sensor, S4,     ,               sensorI2CCustom9V)
#pragma config(Motor, motorA, motorLeftWheel, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorB, motorRightWheel, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, motorLeftGrabber, tmotorEV3_Medium, openLoop,encoder)
#pragma config(Motor, motorD, motorRightGrabber, tmotorEV3_Medium, openLoop,encoder)

#define WRITE
#include "../include/includes.h"

task main (){
	initAll();
    sleep(2000);
    motor[motorA] = 0;
    motor[motorB] = 0;
    motor[motorC] = 0;
    motor[motorD] = 0;

    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);
    setMotorBrakeMode(motorC, motorCoast);

    long maxR = 0, maxG = 0, maxB = 0;
    long minR = 1000, minG = 1000, minB = 1000;

    tCDValues *mass[4];
    mass[0] = &CDSensor1;
    mass[1] = &CDSensor2;
    mass[2] = &CDSensor3;
    mass[3] = &CDSensor4;

    for(short j = 0; j < 4; j++){
        string senType;

        if (SensorType[mass[j]->nDeviceIndex] == 40){
            senType = "HTColor";
        }
        else{
            senType = "EVColor";
        }

        displayCenteredBigTextLine(2, "%s: %d", senType, j + 1);

        maxR = 0;
        maxG = 0;
        maxB = 0;

        minR = 1000;
        minG = 1000;
        minB = 1000;
        
        while (!getButtonPress('C')) {
            getCDValues(mass[j]);
            if (SensorType[mass[j]->nDeviceIndex] == 40){
                mass[j]->maxRed =   256;
                mass[j]->maxGreen = 256;
                mass[j]->maxBlue =  256;

                mass[j]->minRed =   -1;
                mass[j]->minGreen = -1;
                mass[j]->minBlue =  -1;

                maxR = 0;
                maxG = 0;
                maxB = 0;

                minR = 255;
                minG = 255;
                minB = 255;
            }
            else {
                minR = min2(minR, mass[j]->rawRed);
                minG = min2(minG, mass[j]->rawGreen);
                minB = min2(minB, mass[j]->rawBlue);

                maxR = max2(maxR, mass[j]->rawRed);
                maxG = max2(maxG, mass[j]->rawGreen);
                maxB = max2(maxB, mass[j]->rawBlue);

                mass[j]->maxRed =   maxR + 1;
                mass[j]->maxGreen = maxG + 1;
                mass[j]->maxBlue =  maxB + 1;

                mass[j]->minRed =   minR - 1;
                mass[j]->minGreen = minG - 1;
                mass[j]->minBlue =  minB - 1;
            }

            displayCenteredTextLine(6, "RGB_min: %d %d %d", minR, minG, minB);
            displayCenteredTextLine(7, "RGB_max: %d %d %d", maxR, maxG, maxB);
            displayCenteredTextLine(9, "RGB_normed: %d %d %d", mass[j]->normRed, mass[j]->normGreen, mass[j]->normBlue);

            sleep(50);
        }

        writeRGB(mass[j]->maxRed, mass[j]->maxGreen, mass[j]->maxBlue);
        writeRGB(mass[j]->minRed, mass[j]->minGreen, mass[j]->minBlue);

        sleep(500);

        flushButtonMessages();
        sleep(50);
        flushButtonMessages();

        playSound(soundShortBlip);
    }
    fileClose(fileHandle);
}
