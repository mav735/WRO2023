// 1 - Red
// 2 - Yellow
// 3 - Green
// 4 - Blue
// 5 - Black
// 6 - White

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

    CDSensor1.white[0] = 20;
    CDSensor1.white[1] = 0.03;
    CDSensor1.white[2] = 255;

    CDSensor1.black[0] = 80;
    CDSensor1.black[1] = 0.;
    CDSensor1.black[2] = 0;

    CDSensor1.red[0] = 345;
    CDSensor1.red[1] = 0.95;
    CDSensor1.red[2] = 225;

    CDSensor1.green[0] = 140;
    CDSensor1.green[1] = 0.6019;
    CDSensor1.green[2] = 115;

    CDSensor1.blue[0] = 204;
    CDSensor1.blue[1] = 0.8523;
    CDSensor1.blue[2] = 80;

    CDSensor1.yellow[0] = 20;
    CDSensor1.yellow[1] = 0.8523;
    CDSensor1.yellow[2] = 255;





    CDSensor2.nDeviceIndex = S2;

    CDSensor2.minRed = 0;
    CDSensor2.maxRed = 346;
    CDSensor2.minGreen = 0;
    CDSensor2.maxGreen = 309;
    CDSensor2.minBlue = 0;
    CDSensor2.maxBlue = 341;

    CDSensor1.white[0] = 20;
    CDSensor1.white[1] = 0.03;
    CDSensor1.white[2] = 255;

    CDSensor1.black[0] = 80;
    CDSensor1.black[1] = 0.;
    CDSensor1.black[2] = 0;

    CDSensor1.red[0] = 345;
    CDSensor1.red[1] = 0.95;
    CDSensor1.red[2] = 225;

    CDSensor1.green[0] = 140;
    CDSensor1.green[1] = 0.6019;
    CDSensor1.green[2] = 115;

    CDSensor1.blue[0] = 204;
    CDSensor1.blue[1] = 0.8523;
    CDSensor1.blue[2] = 80;

    CDSensor1.yellow[0] = 20;
    CDSensor1.yellow[1] = 0.8523;
    CDSensor1.yellow[2] = 255;






    CDSensor3.nDeviceIndex = S3;

    CDSensor3.minRed = 0;
    CDSensor3.maxRed = 255;
    CDSensor3.minGreen = 0;
    CDSensor3.maxGreen = 255;
    CDSensor3.minBlue = 0;
    CDSensor3.maxBlue = 255;

    CDSensor3.white[0] = 50;
    CDSensor3.white[1] = 0.1058;
    CDSensor3.white[2] = 255;

    CDSensor3.black[0] = 300;
    CDSensor3.black[1] = 0.0909;
    CDSensor3.black[2] = 38;

    CDSensor3.red[0] = 12;
    CDSensor3.red[1] = 0.8114;
    CDSensor3.red[2] = 175;

    CDSensor3.green[0] = 130;
    CDSensor3.green[1] = 0.2413;
    CDSensor3.green[2] = 70;

    CDSensor3.blue[0] = 220;
    CDSensor3.blue[1] = 0.6060;
    CDSensor3.blue[2] = 132;

    CDSensor3.yellow[0] = 36;
    CDSensor3.yellow[1] = 0.6730;
    CDSensor3.yellow[2] = 255;






    CDSensor4.nDeviceIndex = S4;

    CDSensor4.minRed = 0;
    CDSensor4.maxRed = 255;
    CDSensor4.minGreen = 0;
    CDSensor4.maxGreen = 255;
    CDSensor4.minBlue = 0;
    CDSensor4.maxBlue = 255;

    CDSensor4.white[0] = 50;
    CDSensor4.white[1] = 0.1058;
    CDSensor4.white[2] = 255;

    CDSensor4.black[0] = 300;
    CDSensor4.black[1] = 0.0909;
    CDSensor4.black[2] = 38;

    CDSensor4.red[0] = 12;
    CDSensor4.red[1] = 0.8114;
    CDSensor4.red[2] = 175;

    CDSensor4.green[0] = 130;
    CDSensor4.green[1] = 0.2413;
    CDSensor4.green[2] = 70;

    CDSensor4.blue[0] = 220;
    CDSensor4.blue[1] = 0.6060;
    CDSensor4.blue[2] = 132;

    CDSensor4.yellow[0] = 36;
    CDSensor4.yellow[1] = 0.6730;
    CDSensor4.yellow[2] = 255;

}

float calculateDistance(float *hsv_now, float *hsv_need){
    float dh = min2(fabs(hsv_need[0] - hsv_now[0]), 360 - fabs(hsv_need[0] - hsv_now[0])) / 180.0;
    float ds = abs(hsv_need[1] - hsv_now[1]);
    float dv = abs(hsv_need[2] - hsv_now[2]) / 255.0;
    return 1 - sqrt(dh * dh + ds * ds + dv * dv); //
}

void getCDValues(tCDValues *CDSensor, short *colorIndexies=baseColors, short amountColors=6) {
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

    float hsv_now[3] = {CDSensor->hue, CDSensor->sat, CDSensor->val};

    CDSensor->color = -1;

    if (CDSensor->val > 5){
        float white_p = calculateDistance(hsv_now, CDSensor->white);
        float black_p = calculateDistance(hsv_now, CDSensor->black);
        float red_p = calculateDistance(hsv_now, CDSensor->red);
        float green_p = calculateDistance(hsv_now, CDSensor->green);
        float blue_p = calculateDistance(hsv_now, CDSensor->blue);
        float yellow_p = calculateDistance(hsv_now, CDSensor->yellow);

        float all_p[6] = {white_p, black_p, red_p, green_p, blue_p, yellow_p};
        float max_p = -100;

        #ifdef SHOWDIST
            displayCenteredTextLine(1, "white_p: %f", white_p);
            displayCenteredTextLine(2, "black_p: %f", black_p);
            displayCenteredTextLine(4, "red_p:   %f", red_p);
            displayCenteredTextLine(6, "green_p: %f", green_p);
            displayCenteredTextLine(8, "blue_p:  %f", blue_p);
            displayCenteredTextLine(10, "yellow_p:%f", yellow_p);
        #endif

        for (short i = 0; i < amountColors; i++){
            if (max_p < all_p[colorIndexies[i]]){
                CDSensor->color = colorIndexies[i];
                max_p = all_p[colorIndexies[i]];
            }
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
