int amountReading = 0;
int encValues[100];
int readingRes[100];
tCDValues * CDSensorPtr = &CDSensor3;
bool readingTask = false;

task readingColors() {
    float oldEnc = 0;
    readingTask = true;
    oldEnc = (nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    for(short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++){
        while ((nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - oldEnc < encValues[nowEncIndex]){
            // sleep(1);
        }
        getCDValues(CDSensorPtr);
        colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    readingTask = false;
    stopTask(readingColors);
}

void readColors(int *encRead, short amountValues, tCDValues *CDSensorsPTR){
    CDSensorPtr = CDSensorsPTR;
    amountReading = amountValues;
    for(short i = 0; i < amountValues; i++){
        encValues[i] = encRead[i];
    }
    startTask(readingColors, kLowPriority);
}

void readColors(int encRead, tCDValues *CDSensorsPTR){
    CDSensorPtr = CDSensorsPTR;
    amountReading = 1;
    encValues[0] = encRead;
    startTask(readingColors, kLowPriority);
}
