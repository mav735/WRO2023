int amountReading = 0;
short *readingRes;
int *encValues;
tCDValues * CDSensorPtr = &CDSensor3;
short moveTypeIndex = 0;

task readingColors() {
    float nowEncWheels[3] = {0, 0, 0};
    
    float oldEncWheels[2] = {nMotorEncoder[motorA],
                             nMotorEncoder[motorB]}

    for(short nowEncIndex = 0; nowEncIndex < amountReading; nowEncIndex++){
        while (nowEncWheels[moveTypeIndex] < encValues[nowEncIndex]){
            nowEncWheels[1] = fabs(nMotorEncoder[motorA] - oldEncWheels[0]);
            nowEncWheels[2] = fabs(nMotorEncoder[motorB] - oldEncWheels[1]); 
            nowEncWheels[0] = (nowEncWheels[1] + nowEncWheels[2]) / 2;
        }
        getCDValues(CDSensorPtr);
        colSound(CDSensorPtr->color);
        readingRes[nowEncIndex] = CDSensorPtr->color;
    }
    stopTask(readingColors);
}

// 0 - Both wheels
// 1 - Motor A
// 2 - Motor B
void readColors(int *encRead, short *readingPtr, short amountValues, tCDValues *CDSensorsPTR, bool typeMove = 0){
    CDSensorPtr = CDSensorsPTR;
    amountReading = amountValues;
    readingRes = readingPtr;
    encValues = encRead;
    moveTypeIndex = typeMove;
    startTask(readingColors, kLowPriority);
}
