const float g_ArcKP = 3;
const float g_ArcKD = 6;
const float g_ArcKI = 0.05;

bool checkEncForArc(float startVA, float startVB, float encA, float encB,
                    float enc) {
    if (startVA == 0 && startVB < 0) return -encB < enc;
    if (startVA == 0 && startVB > 0) return encB < enc;
    if (startVB == 0 && startVA < 0) return -encA < enc;
    if (startVB == 0 && startVA > 0) return encA < enc;
    if (startVA < 0 && startVB < 0) return -encA - encB < enc;
    if (startVA < 0 && startVB > 0) return encB - encA < enc;
    if (startVA > 0 && startVB < 0) return encA - encB < enc;
    return encA + encB < enc;
}

void arcEnc(float startVA, float startVB, float topVX, float stopVX, float enc,
            float boost = gBoost) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);

    float ratio = 1;
    if (startVB != 0 && startVA != 0) ratio = fabs(startVA / startVB);
    float sign = fabs(startVA * startVB - 1) - fabs(startVA * startVB);

    float err, u;
    float eold = 0, isum = 0;

    float tempVA, tempVB;

    enc *= 2;

    float encX;
    float excess;
    float smoothStartEncX;
    float maxVX;
    float startVX;
    short signVX;

    int ertSz = 20;
    int ert[20];
    for (int i = 0; i < ertSz; ++i) {
        ert[i] = 0;
    }
    int curErtIdx = 0;
    int nwErtIdx;

    bool isSmoothA;

    if (ratio > 1 || startVB == 0) {
        startVX = startVA;
        if (sgn(startVA) != sgn(topVX)) {
            topVX *= -1;
            stopVX *= -1;
        }
        signVX = sgn(startVA);
        encX = (float)enc / (1 + 1. / ratio);
        excess =
            encX - (2 * topVX * topVX - startVA * startVA - stopVX * stopVX) /
                       2 / boost;
        maxVX = min2(
            sqrt(encX * boost + startVA * startVA / 2 + stopVX * stopVX / 2),
            fabs(topVX));
        smoothStartEncX =
            (maxVX * maxVX - startVA * startVA) / 2 / boost + max2(excess, 0);
        isSmoothA = true;
    } else {
        startVX = startVB;
        if (sgn(startVB) != sgn(topVX)) {
            topVX *= -1;
            stopVX *= -1;
        }
        signVX = sgn(startVB);
        encX = (float)enc / (1 + ratio);
        excess =
            encX - (2 * topVX * topVX - startVB * startVB - stopVX * stopVX) /
                       2 / boost;
        maxVX = min2(
            sqrt(encX * boost + startVB * startVB / 2 + stopVX * stopVX / 2),
            fabs(topVX));
        smoothStartEncX =
            (maxVX * maxVX - startVB * startVB) / 2 / boost + max2(excess, 0);
        isSmoothA = false;
    }

    if (startVA == 0 || startVB == 0) enc /= 2;

    maxVX *= signVX;

    // if (fabs(maxVX) < fabs(startVX)) {
    //     maxVX = startVX;
    //     smoothStartEncX = 0;
    //     boost = (maxVX * maxVX - stopVX * stopVX) / 2 / encX;
    // }

    float curEncA, curEncB;

    while (checkEncForArc(
        startVA, startVB, (curEncA = nMotorEncoder[motorA] - MTVarsA.targetEnc),
        (curEncB = nMotorEncoder[motorB] - MTVarsB.targetEnc), enc)) {

        motorAstop = false;
        motorBstop = false;

        if (isSmoothA) {
            if (fabs(curEncA) <= smoothStartEncX) {
                MTVarsA.targetV = smooth(startVA, maxVX, curEncA, boost);
                MTVarsB.targetV =
                    startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
            } else {
                MTVarsA.targetV = smooth(
                    maxVX, stopVX, curEncA - smoothStartEncX * signVX, boost);
                MTVarsB.targetV =
                    startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
            }
        } else {
            if (fabs(curEncB) <= smoothStartEncX) {
                MTVarsB.targetV = smooth(startVB, maxVX, curEncB, boost);
                MTVarsA.targetV =
                    startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
            } else {
                MTVarsB.targetV = smooth(
                    maxVX, stopVX, curEncB - smoothStartEncX * signVX, boost);
                MTVarsA.targetV =
                    startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
            }
        }

        if (startVA == 0)
            err = curEncA;
        else if (startVB == 0)
            err = curEncB;
        else
            err = curEncA * sign + curEncB * ratio;

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

    if (startVA == 0)
        MTVarsB.targetEnc += enc * sgn(startVB);
    else if (startVB == 0)
        MTVarsA.targetEnc += enc * sgn(startVA);
    else {
        MTVarsA.targetEnc += (float)enc / (1 + 1. / ratio) * sgn(startVA);
        MTVarsB.targetEnc += (float)enc / (1 + ratio) * sgn(startVB);
    }
}

void arcAngle(float startVA, float startVB, float topVX, float stopVX,
              float angle, float boost = gBoost) {
    arcEnc(startVA, startVB, topVX, stopVX, angleToEnc(startVA, startVB, angle),
           boost);
}

void arcColor_enc(float startVA, float startVB, float topVX, float stopVX, float enc, tCDValues *CDSensor, short color, float boost = gBoost) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);

    float ratio = 1;
    if (startVB != 0 && startVA != 0) ratio = fabs(startVA / startVB);
    float sign = fabs(startVA * startVB - 1) - fabs(startVA * startVB);

    float err, u;
    float eold = 0, isum = 0;

    float tempVA, tempVB;

    enc *= 2;

    float encX;
    float excess;
    float smoothStartEncX;
    float maxVX;
    float startVX;
    short signVX;

    int ertSz = 20;
    int ert[20];
    for (int i = 0; i < ertSz; ++i) {
        ert[i] = 0;
    }
    int curErtIdx = 0;
    int nwErtIdx;

    bool isSmoothA;

    if (ratio > 1 || startVB == 0) {
        startVX = startVA;
        if (sgn(startVA) != sgn(topVX)) {
            topVX *= -1;
            stopVX *= -1;
        }
        signVX = sgn(startVA);
        encX = (float)enc / (1 + 1. / ratio);
        excess =
            encX - (2 * topVX * topVX - startVA * startVA - stopVX * stopVX) /
                       2 / boost;
        maxVX = min2(
            sqrt(encX * boost + startVA * startVA / 2 + stopVX * stopVX / 2),
            fabs(topVX));
        smoothStartEncX =
            (maxVX * maxVX - startVA * startVA) / 2 / boost + max2(excess, 0);
        isSmoothA = true;
    } else {
        startVX = startVB;
        if (sgn(startVB) != sgn(topVX)) {
            topVX *= -1;
            stopVX *= -1;
        }
        signVX = sgn(startVB);
        encX = (float)enc / (1 + ratio);
        excess =
            encX - (2 * topVX * topVX - startVB * startVB - stopVX * stopVX) /
                       2 / boost;
        maxVX = min2(
            sqrt(encX * boost + startVB * startVB / 2 + stopVX * stopVX / 2),
            fabs(topVX));
        smoothStartEncX =
            (maxVX * maxVX - startVB * startVB) / 2 / boost + max2(excess, 0);
        isSmoothA = false;
    }

    if (startVA == 0 || startVB == 0) enc /= 2;

    maxVX *= signVX;

    // if (fabs(maxVX) < fabs(startVX)) {
    //     maxVX = startVX;
    //     smoothStartEncX = 0;
    //     boost = (maxVX * maxVX - stopVX * stopVX) / 2 / encX;
    // }

    float curEncA, curEncB;
    getCDValues(CDSensor);
    while (checkEncForArc(
        startVA, startVB, (curEncA = nMotorEncoder[motorA] - MTVarsA.targetEnc),
        (curEncB = nMotorEncoder[motorB] - MTVarsB.targetEnc), enc / 3.) || CDSensor->color != color) {

        motorAstop = false;
        motorBstop = false;

        getCDValues(CDSensor);
        if (isSmoothA) {
            if (fabs(curEncA) <= smoothStartEncX) {
                MTVarsA.targetV = smooth(startVA, maxVX, curEncA, boost);
                MTVarsB.targetV =
                    startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
            } else {
                MTVarsA.targetV = smooth(
                    maxVX, stopVX, curEncA - smoothStartEncX * signVX, boost);
                MTVarsB.targetV =
                    startVB == 0 ? 0 : MTVarsA.targetV * startVB / startVA;
            }
        } else {
            if (fabs(curEncB) <= smoothStartEncX) {
                MTVarsB.targetV = smooth(startVB, maxVX, curEncB, boost);
                MTVarsA.targetV =
                    startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
            } else {
                MTVarsB.targetV = smooth(
                    maxVX, stopVX, curEncB - smoothStartEncX * signVX, boost);
                MTVarsA.targetV =
                    startVA == 0 ? 0 : MTVarsB.targetV * startVA / startVB;
            }
        }

        if (startVA == 0)
            err = curEncA;
        else if (startVB == 0)
            err = curEncB;
        else
            err = curEncA * sign + curEncB * ratio;

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
void arcColor_angle(float startVA, float startVB, float topVX, float stopVX, float angle, tCDValues *CDSensor, short color, float boost = gBoost) {
    arcColor_enc(startVA, startVB, topVX, stopVX, angleToEnc(startVA, startVB, angle), CDSensor, color, boost);
}

// Only plus speed
void smartTurnLeft_enc(float startV, float topV, float stopV, float angle=angleToEnc(20, 20, 90)) {
    arcColor_enc(startV, startV, topV, stopV, angle, &CDSensor1, 1);
}

void smartTurnRight_enc(float startV, float topV, float stopV, float angle=angleToEnc(20, 20, 90)) {
    arcColor_enc(-startV, -startV, -topV, -stopV, angle, &CDSensor2, 1);
}


void smartTurnLeft_angle(float startV, float topV, float stopV, float angle=90) {
    arcColor_angle(startV, startV, topV, stopV, angle, &CDSensor1, 1);
}

void smartTurnRight_angle(float startV, float topV, float stopV, float angle=90) {
    arcColor_angle(-startV, -startV, -topV, -stopV, angle, &CDSensor2, 1);
}

void reactiveTurnRight() {
    motor[motorA] = -100;
    motor[motorB] = -100;
    getCDValues(&CDSensor2);
    unsigned long tt = nPgmTime;
    bool flag = true;
    while (-nMotorEncoder[motorA] + MTVarsA.targetEnc < 140 || CDSensor2.color != 1){
        motorAstop = false;
        motorBstop = false;

        getCDValues(&CDSensor2);
        if (flag && nPgmTime - tt >= 160) {
            flag = false;
            setMotorBrakeMode(motorB, motorBrake);
            motor[motorB] = 0;
        }
        sleep(1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void reactiveTurnLeft() {
    motor[motorA] = 100;
    motor[motorB] = 100;
    getCDValues(&CDSensor1);
    unsigned long tt = nPgmTime;
    bool flag = true;
    while (nMotorEncoder[motorB] - MTVarsB.targetEnc < 140 || CDSensor1.color != 1){
        motorAstop = false;
        motorBstop = false;

        getCDValues(&CDSensor1);
        if (flag && nPgmTime - tt >= 160) {
            flag = false;
            setMotorBrakeMode(motorA, motorBrake);
            motor[motorA] = 0;
        }
        sleep(1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void arcToBase(int startV, int topV, int endV) {
    arcEnc(-startV, startV, topV, endV, g_distBetweenSensorsAndWheelBase);
}

/*
void lineAligning(int velocity, float targetAngle, bool type = true, int color = 2){
    arcColor2Sensors(-20, 20, velocity, &CDSensor1, &CDSensor2, color);
    float zeroEnc = (nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    bool flag = true;

    tCDValues *lastSensor = &CDSensor1;
    if (CDSensor1.color == 5){
        lastSensor = &CDSensor2;
        flag = false;
    }

    arcColor(motor[motorA], motor[motorA] * -1, motor[motorA], lastSensor, color);
    float angle = radiansToDegrees(atan((((nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - zeroEnc) * ((g_wheelDiameter * PI) / 360)) / g_distBetweenSensors));

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
        stopMove(0, false, false);
        if (w_angle > 0){
            arcAngle(-30, 0, 80, 20, fabs(w_angle));
        }
        else if (w_angle < 0){
            arcAngle(0, 30, 80, 20, fabs(w_angle));
        }
    }
    else{
        arcEnc(-30, 30, 30, 20, (g_distBetweenSensorsAndWheelBase) / g_wheelDiameter / PI * 360);
        stopMove(0);
        if (w_angle > 0){
            arcAngle(-20, -20, 80, 20, fabs(w_angle));
        }
        else if (w_angle < 0){
            arcAngle(20, 20, 80, 20, fabs(w_angle));
        }
    }
}
*/
