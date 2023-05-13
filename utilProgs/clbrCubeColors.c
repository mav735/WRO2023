#pragma config(Sensor, S1, sensorLeft, sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2, sensorRight, sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorI2CCustom9V)
#pragma config(Sensor, S4,     ,               sensorI2CCustom9V)
#pragma config(Motor, motorA, motorLeftWheel, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorB, motorRightWheel, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, motorLeftGrabber, tmotorEV3_Medium, openLoop,encoder)
#pragma config(Motor, motorD, motorRightGrabber, tmotorEV3_Medium, openLoop,encoder)

// 0 - White
// 1 - Black
// 2 - Red
// 3 - Green
// 4 - Blue
// 5 - Yellow

#define READ
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

    tCDValues *mass[4];
    mass[0] = &CDSensor1;
    mass[1] = &CDSensor2;
    mass[2] = &CDSensor3;
    mass[3] = &CDSensor4;

    string colorNames[6] = {"White", "Black", "Red", "Green", "Blue", "Yellow"};
    for(short j = 0; j < 4; j++){
        string senType = "";
        if (SensorType[mass[j]->nDeviceIndex] == 40){
            senType = "HTColor";
        }
        else{
            senType = "EVColor";
        }
        displayCenteredBigTextLine(2, "%s: %d", senType, j + 1);

        displayCenteredTextLine(6, "Press Any button");
        waitForButtonPress();
        flushButtonMessages();
        sleep(50);
        eraseDisplay()

        /*
        Use RIGHT button to interate to next color
        Use LEFT button to iterate to previous color
        Use ENTER button to choose color
        */

        int calibrationInd = 0;
        displayCenteredBigTextLine(2, "%s: %d", senType, j + 1);
        bool flagApply = 0;
        while (!flagApply) {
            displayCenteredTextLine(4, "Now calibration color: %s", colorNames[calibrationInd])
            waitForButtonPress();

            if (getButtonPress(buttonRight)){
                calibrationInd++;
            }
            else if(getButtonPress(buttonLeft)){
                calibrationInd--;
            }
            else if(getButtonPress(buttonEnter)){
                flagApply = 1;
            }

            if (calibrationInd > 5){
                calibrationInd = 5;
            }
            else if (calibrationInd < 0)
            {
                calibrationInd = 0;
            }

            flushButtonMessages();
            sleep(50);
        }

        /*
        Use UP button to update hsv for this color
        Use DOWN button to show probability of each color
        Use ENTER to apply changes
        */

        flagApply = 0;
        while (!flagApply) {
            getCDValues(mass[j]);
            displayCenteredTextLine(5, "HSV: %d %.3f %d", mass[j]->hue, mass[j]->sat, mass[j]->val);
            sleep(50);
            if (getButtonPress(buttonUp)){
                flagApply = 1;
            }
        }
    }
    fileClose(fileHandle);
}
