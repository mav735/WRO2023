#pragma once

int amountReading = 0;
short *readingRes;
int *encValues;
tCDValues * CDSensorPtr = &CDSensor3;
short moveTypeIndex = 0;

short *elementsColToShow;
short amountToShow;

task readingColors() {
    float nowEncWheels[3] = {0, 0, 0};
    
    float oldEncWheels[2] = {nMotorEncoder[motorA],
                             nMotorEncoder[motorB]};

    for(short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++){
        while (nowEncWheels[moveTypeIndex] < encValues[nowEncIndex]){
            nowEncWheels[1] = fabs(nMotorEncoder[motorA] - oldEncWheels[0]);
            nowEncWheels[2] = fabs(nMotorEncoder[motorB] - oldEncWheels[1]); 
            nowEncWheels[0] = (nowEncWheels[1] + nowEncWheels[2]) / 2;
            sleep(1);
        }
        getCDValues(CDSensorPtr);
        //colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    stopTask(readingColors);
}

task showColorsElements(){
    for(short i = 0; i < amountToShow; i++){
        if (elementsColToShow[i] == 0) {
            setLEDColor(ledRed);
        } else if (elementsColToShow[i] == 1) {
            setLEDColor(ledOff);
        } else if (elementsColToShow[i] == 2) {
            setLEDColor(ledRed);
        } else if (elementsColToShow[i] == 3) {
            setLEDColor(ledGreen);
        } else if (elementsColToShow[i] == 4) {
            setLEDColor(ledOrange);
        } else if (elementsColToShow[i] == 5) {
            setLEDColor(ledOff);
        } else {
            setLEDColor(ledOff);
        }
        sleep(300);
        setLEDColor(ledOff);
        sleep(100);
    }
}

// 0 - Both wheels
// 1 - Motor A
// 2 - Motor B
void readColors(int *encRead, short *readingPtr, short amountValues, tCDValues *CDSensorsPTR, short typeMove = 0){
    CDSensorPtr = CDSensorsPTR;
    amountReading = amountValues;
    readingRes = readingPtr;
    encValues = encRead;
    moveTypeIndex = typeMove;
    startTask(readingColors, kLowPriority);
}

void soundColOfElements(short *elements, short amount){
    elementsColToShow = elements;
    amountToShow = amount;
    startTask(showColorsElements, kLowPriority);
}

