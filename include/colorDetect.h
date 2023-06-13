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
    CDSensor1.h_min_blue = 210;
    CDSensor1.h_max_blue = 240;
    CDSensor1.s_min_blue = 0.7;
    CDSensor1.s_max_blue = 0.92;
    CDSensor1.h_min_green = 140;
    CDSensor1.h_max_green = 170;

    CDSensor2.nDeviceIndex = S2;
    CDSensor2.minRed = 0;
    CDSensor2.maxRed = 346;
    CDSensor2.minGreen = 0;
    CDSensor2.maxGreen = 309;
    CDSensor2.minBlue = 0;
    CDSensor2.maxBlue = 341; // change HT values
    CDSensor2.h_min_blue = 210;
    CDSensor2.h_max_blue = 240;
    CDSensor2.h_min_green = 140;
    CDSensor2.h_max_green = 170;



    CDSensor3.nDeviceIndex = S3;
    CDSensor3.minRed = 0;
    CDSensor3.maxRed = 255;
    CDSensor3.minGreen = 0;
    CDSensor3.maxGreen = 255;
    CDSensor3.minBlue = 0;
    CDSensor3.maxBlue = 255;

    CDSensor3.h_min_blue = 191;
    CDSensor3.h_max_blue = 360;

    CDSensor3.h_min_green = 0;
    CDSensor3.h_max_green = 190;


    CDSensor4.nDeviceIndex = S4;
    CDSensor4.minRed = 0;
    CDSensor4.maxRed = 255;
    CDSensor4.minGreen = 0;
    CDSensor4.maxGreen = 255;
    CDSensor4.minBlue = 0;
    CDSensor4.maxBlue = 255;
    CDSensor4.h_min_blue = 200;
    CDSensor4.h_max_blue = 250;
    CDSensor4.h_min_green = 140;
    CDSensor4.h_max_green = 170;
}

void getCDValues(tCDValues *CDSensor, short *colorIndexies=baseColors, short amountColors=6) {
    if (SensorType[CDSensor->nDeviceIndex] != 40) {
        getColorRawRGB(CDSensor->nDeviceIndex, CDSensor->rawRed, CDSensor->rawGreen,
                   CDSensor->rawBlue);
    }
    else {
        readHTrgb(CDSensor);
    }

    #ifdef CALIBRATION
        CDSensor->normRed = 1;
        CDSensor->normGreen = 1;
        CDSensor->normBlue = 1;

        if ((CDSensor->maxRed - CDSensor->minRed) != 0){
            CDSensor->normRed = (float)(CDSensor->rawRed - CDSensor->minRed) /
                                (CDSensor->maxRed - CDSensor->minRed) * 255;
        }

        if ((CDSensor->maxGreen - CDSensor->minGreen) != 0){
            CDSensor->normGreen = (float)(CDSensor->rawGreen - CDSensor->minGreen) /
                                (CDSensor->maxGreen - CDSensor->minGreen) * 255;
        }

        if ((CDSensor->maxBlue - CDSensor->minBlue) != 0){
        CDSensor->normBlue = (float)(CDSensor->rawBlue - CDSensor->minBlue) /
                            (CDSensor->maxBlue - CDSensor->minBlue) * 255;
        }

    #endif

    #ifndef CALIBRATION
        CDSensor->normRed = (float)(CDSensor->rawRed - CDSensor->minRed) /
                            (CDSensor->maxRed - CDSensor->minRed) * 255;
        CDSensor->normGreen = (float)(CDSensor->rawGreen - CDSensor->minGreen) /
                            (CDSensor->maxGreen - CDSensor->minGreen) * 255;
        CDSensor->normBlue = (float)(CDSensor->rawBlue - CDSensor->minBlue) /
                            (CDSensor->maxBlue - CDSensor->minBlue) * 255;
    #endif

    RGBtoHSV(CDSensor->normRed, CDSensor->normGreen, CDSensor->normBlue,
             &(CDSensor->hue), &(CDSensor->sat), &(CDSensor->val));

    float hsv_now[3] = {CDSensor->hue, CDSensor->sat, CDSensor->val};

    float ratioRed = 0;
    float ratioGreen = 0;
    float ratioBlue = 0;

    if ((CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) != 0){
        ratioRed = CDSensor->normRed / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100;
        ratioGreen = CDSensor->normGreen / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100;
        ratioBlue = CDSensor->normBlue / (CDSensor->normGreen + CDSensor->normBlue + CDSensor->normRed) * 100;
    }

    float max3rat = max3(ratioBlue, ratioGreen, ratioRed);
    float min3rat = min3(ratioBlue, ratioGreen, ratioRed);
    float max3rgb = max3(CDSensor->normRed, CDSensor->normGreen, CDSensor->normBlue);

    #ifdef DEBUG_COLOR_RATIO
        displayCenteredTextLine(2, "ratioRed: %f", ratioRed);
        displayCenteredTextLine(4, "ratioGreen: %f", ratioGreen);
        displayCenteredTextLine(6, "ratioBlue: %f", ratioBlue);
    #endif

    #ifdef DEBUG_HSV
        displayCenteredTextLine(2, "hue: %f", CDSensor->hue);
        displayCenteredTextLine(4, "sat: %f", CDSensor->sat);
        displayCenteredTextLine(6, "val: %f", CDSensor->val);
    #endif

    // 0 - White
    // 1 - Black
    // 2 - Red
    // 3 - Green
    // 4 - Blue
    // 5 - Yellow

    CDSensor->color = -1;
    if (CDSensor->sat <= 0) {
        CDSensor->color = 0;
    }
    if ((CDSensor->h_min_blue <= CDSensor->hue) && (CDSensor->hue <= CDSensor->h_max_blue)){
        CDSensor->color = 4;
    }
    else if ((CDSensor->h_min_green <= CDSensor->hue) && (CDSensor->hue <= CDSensor->h_max_green)){
        CDSensor->color = 3;
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
