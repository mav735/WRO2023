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
        while (fabs((nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - oldEnc) < encValues[nowEncIndex]){
            sleep(1);
        }
        getCDValues(CDSensorPtr, readingGlobal, readingAmountColors);
        // colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    readingTask = false;
    stopTask(readingColors);
}

task readingColors_OneWheel() {
    float oldEnc = 0;
    readingTask = true;
    oldEnc = nMotorEncoder[motorA];
    for (short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++) {
        while (fabs(nMotorEncoder[motorA] - oldEnc) < encValues[nowEncIndex]) {
            sleep(1);
        }
        getCDValues(CDSensorPtr, readingGlobal, readingAmountColors);
        // colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    readingTask = false;
    stopTask(readingColors_OneWheel);
}

void readColors(int *encRead, short *readingPtr, short amountValues, tCDValues *CDSensorsPTR, bool oneWheel = 0){
    CDSensorPtr = CDSensorsPTR;
    amountReading = amountValues;
    readingRes = readingPtr;
    encValues = encRead;
    if (!oneWheel){
        startTask(readingColors, kLowPriority);
    }
    else{
        startTask(readingColors_OneWheel, kLowPriority);
    }
}
