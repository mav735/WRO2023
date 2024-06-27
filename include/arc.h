#pragma once

const float g_ArcKP = 4;
const float g_ArcKD = 4;
const float g_ArcKI = 0.005;

bool checkEncForArc(float startVA, float startVB, float encA, float encB, float enc) {
    return fabs(encA) + fabs(encB) < enc;
}

bool flagStillMove(float startVA, float startVB, float encA, float encB, float enc, tCDValues *CDSensor, short color = -1, bool align = false){
    if ((color != -2) && (!align)) {
        getCDValues(CDSensor);
        return CDSensor->color != color;
    } else if ((align) && (color != -2)) {
        getCDValues(CDSensor1);
        getCDValues(CDSensor2);
        return (CDSensor1.color != color) && (CDSensor2.color != color);
    }
    return checkEncForArc(startVA, startVB, encA, encB, enc);
}

void arcEnc(float startVA, float startVB, float topVX, float stopVX, float enc, tCDValues *CDSensor = &CDSensor1, short color = -2, float boost = gBoost, bool align = false) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    float ratio = 1;
    if (startVB != 0 && startVA != 0) ratio = fabs(startVA / startVB);
    float sign = -1 * sgn(startVA * startVB);
    float err, u, eold = 0, isum = 0;

    float tempVA, tempVB;
    enc *= 2;

    float encX, excess, smoothStartEncX;
    float maxVX, startVX, signVX;

    int ertSz = 20;
    int ert[20];
    for (int i = 0; i < ertSz; ++i) {
        ert[i] = 0;
    }
    int curErtIdx = 0, nwErtIdx;
    bool isSmoothA;

    startVX = startVB;
    encX = (float)enc / (1 + ratio);
    isSmoothA = false;
    if (ratio > 1 || startVB == 0) {
        startVX = startVA;
        encX = (float)enc / (1 + 1. / ratio);
        isSmoothA = true;
    }
    signVX = sgn(startVX);
    topVX = fabs(topVX) * signVX;
    stopVX = fabs(stopVX) * signVX;
    excess =
        encX - (2 * topVX * topVX - startVX * startVX - stopVX * stopVX) /
                    2 / boost;
    maxVX = min2(
        sqrt(encX * boost + startVX * startVX / 2 + stopVX * stopVX / 2),
        fabs(topVX));
    smoothStartEncX =
        (maxVX * maxVX - startVX * startVX) / 2 / boost + max2(excess, 0);

    if (startVA == 0 || startVB == 0) enc /= 2;

    maxVX *= signVX;

    float curEncA, curEncB;

    while (flagStillMove(
        startVA, startVB, (curEncA = nMotorEncoder[motorA] - MTVarsA.targetEnc),
        (curEncB = nMotorEncoder[motorB] - MTVarsB.targetEnc), enc, CDSensor, color, align)) {

        motorAstop = false;
        motorBstop = false;

        if (isSmoothA) {
            MTVarsA.targetV = smooth(maxVX, stopVX, curEncA - smoothStartEncX * signVX, boost);
            if (fabs(curEncA) <= smoothStartEncX) {
                MTVarsA.targetV = smooth(startVA, maxVX, curEncA, boost);
            }
            MTVarsB.targetV = startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
        } else {
            MTVarsB.targetV = smooth(maxVX, stopVX, curEncB - smoothStartEncX * signVX, boost);
            if (fabs(curEncB) <= smoothStartEncX) {
                MTVarsB.targetV = smooth(startVB, maxVX, curEncB, boost);
            }
            MTVarsA.targetV = startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
        }

        err = curEncA * sign + curEncB * ratio;
        if (startVA == 0) err = curEncA;
        else if (startVB == 0) err = curEncB;

        nwErtIdx = (curErtIdx + ertSz - 1) % ertSz;
        ert[nwErtIdx] = err;
        isum -= ert[curErtIdx];
        isum += ert[nwErtIdx];
        curErtIdx = (curErtIdx + 1) % ertSz;

        u = (err - eold) * stopKD + err * stopKP + isum * stopKI;

        if (startVA == 0) {
            tempVA = -u;
            tempVB = MTVarsB.targetV;
        } else if (startVB == 0) {
            tempVA = MTVarsA.targetV;
            tempVB = -u;
        } else {
            u = (err - eold) * g_ArcKD + err * g_ArcKP + isum * g_ArcKI;
            tempVA = MTVarsA.targetV - u * sign;
            tempVB = MTVarsB.targetV - u;
        }

        saveRatioPID(&tempVA, &tempVB);
        motor[motorA] = tempVA;
        motor[motorB] = tempVB;

        eold = err;
        sleep(1);
    }

    if (color == -2){
        if (startVA == 0)
            MTVarsB.targetEnc += enc * sgn(startVB);
        else if (startVB == 0)
            MTVarsA.targetEnc += enc * sgn(startVA);
        else {
            MTVarsA.targetEnc += (float)enc / (1 + 1. / ratio) * sgn(startVA);
            MTVarsB.targetEnc += (float)enc / (1 + ratio) * sgn(startVB);
        }
    }
    else {
        MTVarsA.targetEnc = nMotorEncoder[motorA];
        MTVarsB.targetEnc = nMotorEncoder[motorB];
    }
}

void arcSec(float startVA, float startVB, float topVX, float stopVX, float enc, float sec, tCDValues *CDSensor = &CDSensor1, short color = -2, float boost = gBoost, bool align = false) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    float ratio = 1;
    if (startVB != 0 && startVA != 0) ratio = fabs(startVA / startVB);
    float sign = -1 * sgn(startVA * startVB);
    float err, u, eold = 0, isum = 0;

    float tempVA, tempVB;
    enc *= 2;

    float encX, excess, smoothStartEncX;
    float maxVX, startVX, signVX;

    int ertSz = 20;
    int ert[20];
    for (int i = 0; i < ertSz; ++i) {
        ert[i] = 0;
    }
    int curErtIdx = 0, nwErtIdx;
    bool isSmoothA;

    startVX = startVB;
    encX = (float)enc / (1 + ratio);
    isSmoothA = false;
    if (ratio > 1 || startVB == 0) {
        startVX = startVA;
        encX = (float)enc / (1 + 1. / ratio);
        isSmoothA = true;
    }
    signVX = sgn(startVX);
    topVX = fabs(topVX) * signVX;
    stopVX = fabs(stopVX) * signVX;
    excess =
        encX - (2 * topVX * topVX - startVX * startVX - stopVX * stopVX) /
                    2 / boost;
    maxVX = min2(
        sqrt(encX * boost + startVX * startVX / 2 + stopVX * stopVX / 2),
        fabs(topVX));
    smoothStartEncX =
        (maxVX * maxVX - startVX * startVX) / 2 / boost + max2(excess, 0);

    if (startVA == 0 || startVB == 0) enc /= 2;

    maxVX *= signVX;

    float curEncA, curEncB;
    int prt = nPgmTime;
    while (nPgmTime - prt < sec) {
        curEncA = nMotorEncoder[motorA] - MTVarsA.targetEnc;
        curEncB = nMotorEncoder[motorB] - MTVarsB.targetEnc;
        motorAstop = false;
        motorBstop = false;

        if (isSmoothA) {
            MTVarsA.targetV = smooth(maxVX, stopVX, curEncA - smoothStartEncX * signVX, boost);
            if (fabs(curEncA) <= smoothStartEncX) {
                MTVarsA.targetV = smooth(startVA, maxVX, curEncA, boost);
            }
            MTVarsB.targetV = startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
        } else {
            MTVarsB.targetV = smooth(maxVX, stopVX, curEncB - smoothStartEncX * signVX, boost);
            if (fabs(curEncB) <= smoothStartEncX) {
                MTVarsB.targetV = smooth(startVB, maxVX, curEncB, boost);
            }
            MTVarsA.targetV = startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
        }

        err = curEncA * sign + curEncB * ratio;
        if (startVA == 0) err = curEncA;
        else if (startVB == 0) err = curEncB;

        nwErtIdx = (curErtIdx + ertSz - 1) % ertSz;
        ert[nwErtIdx] = err;
        isum -= ert[curErtIdx];
        isum += ert[nwErtIdx];
        curErtIdx = (curErtIdx + 1) % ertSz;

        u = (err - eold) * stopKD + err * stopKP + isum * stopKI;

        if (startVA == 0) {
            tempVA = -u;
            tempVB = MTVarsB.targetV;
        } else if (startVB == 0) {
            tempVA = MTVarsA.targetV;
            tempVB = -u;
        } else {
            u = (err - eold) * g_ArcKD + err * g_ArcKP + isum * g_ArcKI;
            tempVA = MTVarsA.targetV - u * sign;
            tempVB = MTVarsB.targetV - u;
        }

        saveRatioPID(&tempVA, &tempVB);
        motor[motorA] = tempVA;
        motor[motorB] = tempVB;

        eold = err;
        sleep(1);
    }


    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}


void arcColor2Sensors(float startVA, float startVB, float topVX, float stopVX, float encoder, short color = -2, float boost = gBoost){
    arcEnc(startVA, startVB, topVX, stopVX, encoder, &CDSensor1, color, boost, true);
}

void arcAngle(float startVA, float startVB, float topVX, float stopVX, float angle, tCDValues *CDSensor = &CDSensor1, short color = -2, float boost = gBoost) {
    arcEnc(startVA, startVB, topVX, stopVX, angleToEnc(startVA, startVB, angle), CDSensor, color, boost);
}

void arcAccelEnc(float startVA, float startVB, float topVX, float stopVX, float encoder, float encoderStop, float boost = gBoost) {
    arcEnc(startVA, startVB, topVX, stopVX, encoder - encoderStop, &CDSensor1, -2, boost);
    arcEnc(MTVarsA.targetV, MTVarsB.targetV, stopVX, stopVX, encoderStop, &CDSensor1, -2, boost);
}

void arcAccelAngle(float startVA, float startVB, float topVX, float stopVX, float encoder, float encoderStop, float boost = gBoost) {
    arcAngle(startVA, startVB, topVX, stopVX, encoder - encoderStop, &CDSensor1, -2, boost);
    arcAngle(MTVarsA.targetV, MTVarsB.targetV, stopVX, stopVX, encoderStop, &CDSensor1, -2, boost);
}

void smartTurnLeft(float startV, float topV, float stopV, float angle=90) {
    arcAngle(-startV, -startV, -topV, -stopV, angle, &CDSensor2, 1);
}

void smartTurnRight(float startV, float topV, float stopV, float angle=90) {
    arcAngle(startV, startV, topV, stopV, angle, &CDSensor1, 1);
}

void reactiveTurnRight() {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    motor[motorA] = 100;
    motor[motorB] = 100;
    getCDValues(&CDSensor2);
    unsigned long tt = nPgmTime;
    bool flag = true;
    motorAstop = false;
    motorBstop = false;

    while (nMotorEncoder[motorB] - MTVarsB.targetEnc < 90 || CDSensor2.color != 1){
        getCDValues(&CDSensor2);
        if (flag && nPgmTime - tt >= 200) {
            flag = false;
            stopMoveA();
        }
        sleep(1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void reactiveTurnLeft() {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    motor[motorA] = -100;
    motor[motorB] = -100;
    getCDValues(&CDSensor1);
    unsigned long tt = nPgmTime;
    bool flag = true;
    motorAstop = false;
    motorBstop = false;

    while (-nMotorEncoder[motorA] + MTVarsA.targetEnc < 90 || CDSensor1.color != 1){
        getCDValues(&CDSensor1);
        if (flag && nPgmTime - tt >= 200) {
            flag = false;
            stopMoveB();
        }
        sleep(1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void arcToBase(int startV, int topV, int endV) {
    arcEnc(-startV, startV, topV, endV, g_distBetweenSensorsAndWheelBase);
}


void lineAligning(int startSpeed, int topSpeed, int stopSpeed, int encoder, float targetAngle, bool type = true, int color = 1){
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    arcColor2Sensors(-startSpeed, startSpeed, topSpeed, stopSpeed, encoder, color);
    playSound(soundException);
    float zeroEnc = (fabs(nMotorEncoder[motorB]) + fabs(nMotorEncoder[motorA])) / 2;
    bool flag = true;

    tCDValues *lastSensor = &CDSensor1;
    if (CDSensor1.color == color){
        lastSensor = &CDSensor2;
        flag = false;
    }

    arcEnc(-stopSpeed, stopSpeed, stopSpeed, stopSpeed, 10, lastSensor, color);
    float angle = radiansToDegrees(atan(((fabs(nMotorEncoder[motorB]) + fabs(nMotorEncoder[motorA])) / 2. - zeroEnc) / (float)g_distBetweenSensors));

    stopMove(500);
    displayCenteredTextLine(2, "%f", angle);
    stopMove(2000);

    if (flag){
        angle = 360 - angle;
    }

    float w_angle = 0;
    if (targetAngle - angle != 0)
    {
        if (targetAngle == 360)
        {
            if (fabs(targetAngle - angle) < fabs(0 - angle))
            {
                w_angle = targetAngle - angle;
            }
            else
            {
                w_angle = 0 - angle;
            }
        }
        else
        {
            if (angle == 360)
            {
                if (fabs(targetAngle - 360) < fabs(targetAngle))
                {
                    w_angle = targetAngle - 360;
                }
                else
                {
                    w_angle = targetAngle;
                }
            }
            else
            {
                w_angle = targetAngle - angle;
            }
        }
    }

    if (type){
        if (w_angle > 0){
            arcAngle(-stopSpeed, 0, stopSpeed, stopSpeed, fabs(w_angle));
        }
        else if (w_angle < 0){
            arcAngle(0, stopSpeed, stopSpeed, stopSpeed, fabs(w_angle));
        }
    }
    else{
        arcEnc(-stopSpeed, stopSpeed, stopSpeed, 20, (g_distBetweenSensorsAndWheelBase) / g_wheelDiameter / PI * 360);
        stopMove(200);
        if (w_angle > 0){
            arcAngle(-20, -20, 80, 20, fabs(w_angle));
        }
        else if (w_angle < 0){
            arcAngle(20, 20, 80, 20, fabs(w_angle));
        }
    }
}
