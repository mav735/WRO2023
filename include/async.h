int amountReading = 0;
short *readingRes;
int *encValues;
tCDValues * CDSensorPtr = &CDSensor3;
bool readingTask = false;

short baseBlueGreen[2] = {3, 4};
short readingAmountColors = 2;
short *readingGlobal = &baseBlueGreen;

task readingColors() {
    float oldEnc = 0;
    readingTask = true;
    oldEnc = (nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    for(short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++){
        while ((nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - oldEnc < encValues[nowEncIndex]){
            sleep(1);
        }
        getCDValues(CDSensorPtr, readingGlobal, readingAmountColors);
        colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    readingTask = false;
    stopTask(readingColors);
}

void readColors(int *encRead, short *readingPtr, short amountValues, tCDValues *CDSensorsPTR){
    CDSensorPtr = CDSensorsPTR;
    amountReading = amountValues;
    readingRes = readingPtr;
    encValues = encRead;
    startTask(readingColors, kLowPriority);
}
