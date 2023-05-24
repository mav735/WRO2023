// 0 - White 
// 1 - Black 
// 2 - Red 
// 3 - Green 
// 4 - Blue 
// 5 - Yellow

tCDValues CDSensor4, CDSensor3, CDSensor1, CDSensor2;
short baseColors[6] = {0, 1, 2, 3, 4, 5};

void colorDetectInit() {
    CDSensor1.nDeviceIndex = S1;

    CDSensor1.minRed = 0;
    CDSensor1.maxRed = 156;
    CDSensor1.minGreen = 0;
    CDSensor1.maxGreen = 192;
    CDSensor1.minBlue = 0;
    CDSensor1.maxBlue = 136;


    CDSensor2.nDeviceIndex = S2;

    CDSensor2.minRed = 0;
    CDSensor2.maxRed = 346;
    CDSensor2.minGreen = 0;
    CDSensor2.maxGreen = 309;
    CDSensor2.minBlue = 0;
    CDSensor2.maxBlue = 341;


    CDSensor3.nDeviceIndex = S3;

    CDSensor3.minRed = 0;
    CDSensor3.maxRed = 255;
    CDSensor3.minGreen = 0;
    CDSensor3.maxGreen = 255;
    CDSensor3.minBlue = 0;
    CDSensor3.maxBlue = 255;


    CDSensor4.nDeviceIndex = S4;

    CDSensor4.minRed = 0;
    CDSensor4.maxRed = 255;
    CDSensor4.minGreen = 0;
    CDSensor4.maxGreen = 255;
    CDSensor4.minBlue = 0;
    CDSensor4.maxBlue = 255;

}

float calculateDistance(float *hsv_now, float *hsv_need){
    float dh = min2(fabs(hsv_need[0] - hsv_now[0]), 360 - fabs(hsv_need[0] - hsv_now[0])) / 180.0;
    float ds = hsv_need[1] - hsv_now[1];
    float dv = hsv_need[2] - hsv_now[2] / 255.0;
    return 1 - sqrt(dh * dh + ds * ds); //+ dv * dv;
}

void getCDValues(tCDValues *CDSensor, short *colorIndexies=baseColors, short amountColors=6) {
    if (SensorType[CDSensor->nDeviceIndex] != 40) {
        getColorRawRGB(CDSensor->nDeviceIndex, CDSensor->rawRed, CDSensor->rawGreen,
                   CDSensor->rawBlue);
    }
    else {
        readHTrgb(CDSensor);
    }

    CDSensor->normRed = (float)(CDSensor->rawRed - CDSensor->minRed) /
                        (CDSensor->maxRed - CDSensor->minRed) * 255;
    CDSensor->normGreen = (float)(CDSensor->rawGreen - CDSensor->minGreen) /
                          (CDSensor->maxGreen - CDSensor->minGreen) * 255;
    CDSensor->normBlue = (float)(CDSensor->rawBlue - CDSensor->minBlue) /
                         (CDSensor->maxBlue - CDSensor->minBlue) * 255;

    RGBtoHSV(CDSensor->normRed, CDSensor->normGreen, CDSensor->normBlue,
             &(CDSensor->hue), &(CDSensor->sat), &(CDSensor->val));
             
    float hsv_now[3] = {CDSensor->hue, CDSensor->sat, CDSensor->val};

    CDSensor->color = -1;


    float ratioRed = CDSensor->normRed / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100;
    float ratioGreen = CDSensor->normGreen / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100; 
    float ratioBlue = CDSensor->normBlue / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100;

    float max3rat = max3(ratioBlue, ratioGreen, ratioRed);
    float min3rat = min3(ratioBlue, ratioGreen, ratioRed);

    // displayCenteredTextLine(2, "ratioRed: %f", ratioRed);
    // displayCenteredTextLine(4, "ratioGreen: %f", ratioGreen);
    // displayCenteredTextLine(6, "ratioBlue: %f", ratioBlue);

    // 0 - White 
    // 1 - Black 
    // 2 - Red 
    // 3 - Green 
    // 4 - Blue 
    // 5 - Yellow
    if ((ratioRed > 35) && (ratioGreen < 30)){
        CDSensor->color = 2;
    }
    else if ((ratioRed > 40) && (15 < ratioGreen < 40)){
        CDSensor->color = 5;
    }
    else if (((ratioGreen > 31) && (ratioBlue < 45) && (ratioRed < 35))){ //  && ((max3rat - min3rat) > 5)
        CDSensor->color = 3;
    }
    else if ((ratioBlue > 45) && (ratioRed < 30)){
        CDSensor->color = 4;
    }
    if ((((CDSensor->normBlue + CDSensor->normGreen + CDSensor->normRed) / 3) > 120) && ((max3rat - min3rat) < 10)){
            CDSensor->color = 0;
    }
    else if (((ratioBlue > ratioRed) && (ratioRed > ratioGreen)) || ((max3rat - min3rat) < 5)){
        if (((CDSensor->normBlue + CDSensor->normGreen + CDSensor->normRed) < 60) || (max3rat == ratioBlue)){
            CDSensor->color = 1;
        }
        else if ((max3rat == ratioRed) || (max3rat == ratioGreen)){
            CDSensor->color = 0;
        }
    }
}

void displayValues(tCDValues *CDSensor) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);
    setSoundVolume(5);
    while (1){
        getCDValues(CDSensor);
        displayCenteredTextLine(1, "RGB_raw: %d %d %d", CDSensor->rawRed,
                                CDSensor->rawGreen, CDSensor->rawBlue);
        displayCenteredTextLine(3, "RGB_norm: %d %d %d", CDSensor->normRed,
                                CDSensor->normGreen, CDSensor->normBlue);
        displayCenteredTextLine(5, "HSV: %f %f %f", CDSensor->hue,
                                CDSensor->sat, CDSensor->val);
        displayBigStringAt(125, 20, "%d", CDSensor->color);
        clearSounds();
        if (CDSensor->color == 1) {
            playSoundFile("Right");
        } else if (CDSensor->color == 2) {
            playSoundFile("Yellow");
        } else if (CDSensor->color == 3) {
            playSoundFile("Green");
        } else if (CDSensor->color == 4) {
            playSoundFile("Blue");
        } else if (CDSensor->color == 5) {
            playSoundFile("Black");
        } else if (CDSensor->color == 6) {
            playSoundFile("White");
        } else {
            playSoundFile("Uh-oh");
        }
        sleep(400);
        eraseDisplay();
    }
}
