// 1 - Red
// 2 - Yellow
// 3 - Green
// 4 - Blue
// 5 - Black
// 6 - White

tCDValues CDSensor4, CDSensor3, CDSensor1, CDSensor2;

void colorDetectInit() {
    CDSensor1.nDeviceIndex = S1;
    CDSensor1.minSatRed = 0.4;
    CDSensor1.maxSatRed = 2;
    CDSensor1.minSatGreen = 0.4;
    CDSensor1.maxSatGreen = 2;
    CDSensor1.minSatBlue = 0.4;
    CDSensor1.maxSatBlue = 2;
    CDSensor1.minSatYellow = 0.4;
    CDSensor1.maxSatYellow = 2;
    CDSensor1.minRed = 22;
    CDSensor1.maxRed = 156;
    CDSensor1.minGreen = 21;
    CDSensor1.maxGreen = 192;
    CDSensor1.minBlue = 21;
    CDSensor1.maxBlue = 136;
    CDSensor1.borderZero = 0;
    CDSensor1.borderValBW = 30;
    CDSensor1.borderSatBW = 0.5;
    CDSensor1.minHueRed1 = 0;
    CDSensor1.maxHueRed1 = 10;
    CDSensor1.minHueYellow = 10;
    CDSensor1.maxHueYellow = 90;
    CDSensor1.minHueGreen = 90;
    CDSensor1.maxHueGreen = 194;
    CDSensor1.minHueBlue = 194;
    CDSensor1.maxHueBlue = 300;
    CDSensor1.minHueRed2 = 300;
    CDSensor1.maxHueRed2 = 360;

    CDSensor2.nDeviceIndex = S2;
    CDSensor2.minSatRed = 0.5;
    CDSensor2.maxSatRed = 2;
    CDSensor2.minSatGreen = 0.5;
    CDSensor2.maxSatGreen = 2;
    CDSensor2.minSatBlue = 0.5;
    CDSensor2.maxSatBlue = 2;
    CDSensor2.minSatYellow = 0.5;
    CDSensor2.maxSatYellow = 2;
    CDSensor2.minRed = 66;
    CDSensor2.maxRed = 346;
    CDSensor2.minGreen = 74;
    CDSensor2.maxGreen = 309;
    CDSensor2.minBlue = 49;
    CDSensor2.maxBlue = 341;
    CDSensor2.borderZero = 0;
    CDSensor2.borderValBW = 30;
    CDSensor2.borderSatBW = 0.5;
    CDSensor2.minHueRed1 = 0;
    CDSensor2.maxHueRed1 = 10;
    CDSensor2.minHueYellow = 10;
    CDSensor2.maxHueYellow = 90;
    CDSensor2.minHueGreen = 90;
    CDSensor2.maxHueGreen = 194;
    CDSensor2.minHueBlue = 194;
    CDSensor2.maxHueBlue = 300;
    CDSensor2.minHueRed2 = 300;
    CDSensor2.maxHueRed2 = 360;

    CDSensor3.nDeviceIndex = S3;
    CDSensor3.minSatRed = 0.4;
    CDSensor3.maxSatRed = 2;
    CDSensor3.minSatGreen = 0.1;
    CDSensor3.maxSatGreen = 2;
    CDSensor3.minSatBlue = 0.2;
    CDSensor3.maxSatBlue = 2;
    CDSensor3.minSatYellow = 0.35;
    CDSensor3.maxSatYellow = 0.95;
    CDSensor3.minRed = 0;
    CDSensor3.maxRed = 255;
    CDSensor3.minGreen = 0;
    CDSensor3.maxGreen = 255;
    CDSensor3.minBlue = 0;
    CDSensor3.maxBlue = 255;
    CDSensor3.borderZero = 6;
    CDSensor3.borderValBW = 50;
    CDSensor3.borderSatBW = 0.3;
    CDSensor3.minHueRed1 = 0;
    CDSensor3.maxHueRed1 = 30;
    CDSensor3.minHueYellow = 30;
    CDSensor3.maxHueYellow = 80;
    CDSensor3.minHueGreen = 80;
    CDSensor3.maxHueGreen = 210;
    CDSensor3.minHueBlue = 210;
    CDSensor3.maxHueBlue = 320;
    CDSensor3.minHueRed2 = 320;
    CDSensor3.maxHueRed2 = 360;

    CDSensor4.nDeviceIndex = S4;
    CDSensor4.minSatRed = 0.5;
    CDSensor4.maxSatRed = 2;
    CDSensor4.minSatGreen = 0.4;
    CDSensor4.maxSatGreen = 2;
    CDSensor4.minSatBlue = 0.6;
    CDSensor4.maxSatBlue = 2;
    CDSensor4.minSatYellow = 0.5;
    CDSensor4.maxSatYellow = 2;
    CDSensor4.minRed = 0;
    CDSensor4.maxRed = 247;
    CDSensor4.minGreen = 0;
    CDSensor4.maxGreen = 400;
    CDSensor4.minBlue = 0;
    CDSensor4.maxBlue = 305;
    CDSensor4.borderZero = 3;
    CDSensor4.borderValBW = 40;
    CDSensor4.borderSatBW = 0.3;
    CDSensor4.minHueRed1 = 0;
    CDSensor4.maxHueRed1 = 10;
    CDSensor4.minHueYellow = 10;
    CDSensor4.maxHueYellow = 90;
    CDSensor4.minHueGreen = 90;
    CDSensor4.maxHueGreen = 194;
    CDSensor4.minHueBlue = 194;
    CDSensor4.maxHueBlue = 300;
    CDSensor4.minHueRed2 = 300;
    CDSensor4.maxHueRed2 = 360;
}

void getCDValues(tCDValues *CDSensor) {
    if (SensorType[CDSensor->nDeviceIndex] != 40){
        getColorRawRGB(CDSensor->nDeviceIndex, CDSensor->rawRed, CDSensor->rawGreen,
                   CDSensor->rawBlue);
    }
    else{ //40 == sensorI2CCustom9V
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
    if (CDSensor->borderZero != 0) {
        if (CDSensor->val <= CDSensor->borderZero) {
            CDSensor->color = 0;
        } else if (CDSensor->sat >= CDSensor->minSatBlue &&
                   CDSensor->sat <= CDSensor->maxSatBlue &&
                   CDSensor->hue >= CDSensor->minHueBlue &&
                   CDSensor->hue < CDSensor->maxHueBlue) {
            CDSensor->color = 4;
        } else if (CDSensor->sat >= CDSensor->minSatGreen &&
                   CDSensor->sat <= CDSensor->maxSatGreen &&
                   CDSensor->hue >= CDSensor->minHueGreen &&
                   CDSensor->hue < CDSensor->maxHueGreen) {
            CDSensor->color = 3;
        } else if (CDSensor->sat >= CDSensor->minSatYellow &&
                   CDSensor->sat <= CDSensor->maxSatYellow &&
                   CDSensor->hue >= CDSensor->minHueYellow &&
                   CDSensor->hue < CDSensor->maxHueYellow) {
            CDSensor->color = 2;
        } else if ((CDSensor->sat >= CDSensor->minSatRed &&
                    CDSensor->sat <= CDSensor->maxSatRed &&
                    CDSensor->hue >= CDSensor->minHueRed1 &&
                    CDSensor->hue < CDSensor->maxHueRed1) ||
                   (CDSensor->sat >= CDSensor->minSatRed &&
                    CDSensor->sat <= CDSensor->maxSatRed &&
                    CDSensor->hue >= CDSensor->minHueRed2 &&
                    CDSensor->hue <= CDSensor->maxHueRed2)) {
            CDSensor->color = 1;
        } else {
            if (CDSensor->val >= CDSensor->borderValBW ||
                (CDSensor->sat <= CDSensor->borderSatBW &&
                 CDSensor->val < CDSensor->borderValBW)) {
                CDSensor->color = 6;
            } else {
                CDSensor->color = 5;
            }
        }
    } else {
        if (CDSensor->val <= CDSensor->borderValBW) {
            CDSensor->color = 5;
        } else if (CDSensor->sat >= CDSensor->minSatBlue &&
                   CDSensor->sat <= CDSensor->maxSatBlue &&
                   CDSensor->hue >= CDSensor->minHueBlue &&
                   CDSensor->hue < CDSensor->maxHueBlue) {
            CDSensor->color = 4;
        } else if (CDSensor->sat >= CDSensor->minSatGreen &&
                   CDSensor->sat <= CDSensor->maxSatGreen &&
                   CDSensor->hue >= CDSensor->minHueGreen &&
                   CDSensor->hue < CDSensor->maxHueGreen) {
            CDSensor->color = 3;
        } else if (CDSensor->sat >= CDSensor->minSatYellow &&
                   CDSensor->sat <= CDSensor->maxSatYellow &&
                   CDSensor->hue >= CDSensor->minHueYellow &&
                   CDSensor->hue < CDSensor->maxHueYellow) {
            CDSensor->color = 2;
        } else if ((CDSensor->sat >= CDSensor->minSatRed &&
                    CDSensor->sat <= CDSensor->maxSatRed &&
                    CDSensor->hue >= CDSensor->minHueRed1 &&
                    CDSensor->hue < CDSensor->maxHueRed1) ||
                   (CDSensor->sat >= CDSensor->minSatRed &&
                    CDSensor->sat <= CDSensor->maxSatRed &&
                    CDSensor->hue >= CDSensor->minHueRed2 &&
                    CDSensor->hue <= CDSensor->maxHueRed2)) {
            CDSensor->color = 1;
        } else {
            CDSensor->color = 6;
        }
    }
}

void displayValues(tCDValues *CDSensor) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);

    while (1){
        getCDValues(CDSensor);
        displayCenteredTextLine(1, "RGB_raw: %d %d %d", CDSensor->rawRed,
                                CDSensor->rawGreen, CDSensor->rawBlue);
        displayCenteredTextLine(3, "RGB_norm: %d %d %d", CDSensor->normRed,
                                CDSensor->normGreen, CDSensor->normBlue);
        displayCenteredTextLine(5, "HSV: %f %f %f", CDSensor->hue,
                                CDSensor->sat, CDSensor->val);
        displayBigStringAt(125, 20, "%d", CDSensor->color);
        setSoundVolume(30);
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
