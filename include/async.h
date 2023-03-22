int amountReading = 0;
short *readingRes;
int *encValues;
tCDValues * CDSensorPtr = &CDSensor3;
bool readingTask = false;

task readingColors() {
    float oldEnc = 0;
    readingTask = true;
    oldEnc = (nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    displayCenteredTextLine(2, "%d %d", encValues[0], encValues[1]);
    for(short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++){
        while ((nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - oldEnc < encValues[nowEncIndex]){
            //sleep(1);
        }
        getCDValues(CDSensorPtr);
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
    displayCenteredTextLine(1, "%d %d", encValues[0], encValues[1]);
    startTask(readingColors, kLowPriority);
}
