typedef struct {
    tMotor nDeviceIndex;
    float maxDown;
    float maxUp;
    float maxUpWithoutShip;
    float upForDrop;
    float maxV;
    float targetPos;
} tGrabberPositionC;

typedef struct {
    tMotor nDeviceIndex;
    float close;
    float openMax;
    float openMin;
    float maxV;
    float targetPos;
} tGrabberPositionD;

tGrabberPositionC grabberC;
tGrabberPositionD grabberD;


task initGrabber() {
    motor[motorC] = 100;
    motor[motorD] = -100;
    sleep(350);

    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 0;
    motor[motorD] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    grabberC.maxUp = 0;
    grabberC.maxUpWithoutShip = -390;
    grabberC.maxDown = -820;
    grabberC.upForDrop = -680;

    grabberD.close = 0;
    grabberD.openMin = 205;
    grabberD.openMax = 400;
    stopTask(initGrabber);
}

task thr_changePosGrabberC() {
    float ce, cee, cP, cD, cU;
    float cisum = 0;
    float ckp = 2;
    float ckd = 6;
    float cki = 0.004;
    cee = 0;
    float ctt = nPgmTime;
    while (nPgmTime - ctt < 5000) {
        ce = grabberC.targetPos - nMotorEncoder[motorC];
        cisum += ce * cki;
        if (cisum > 10) {
            cisum = 10;
        } else if (cisum < -10) {
            cisum = -10;
        }
        cP = ce * ckp;
        cD = (ce - cee) * ckd;
        cU = cP + cD + cisum;
        if (cU > grabberC.maxV) {
            cU = grabberC.maxV;
        } else if (cU < (-1) * grabberC.maxV) {
            cU = (-1) * grabberC.maxV;
        }
        motor[motorC] = cU;
        cee = ce;
        sleep(1);
    }
    setMotorBrakeMode(motorC, motorBrake);
    motor[motorC] = 0;
    stopTask(thr_changePosGrabberC);
}

task thr_changePosGrabberD() {
    float de, dee, dP, dD, dU;
    float disum = 0;
    float dkp = 2;
    float dkd = 6;
    float dki = 0.004
    dee = 0;
    float dtt = nPgmTime;
    while (nPgmTime - dtt < 5000) {
        de = grabberD.targetPos - nMotorEncoder[motorD];
        disum += de * dki;
        if (disum > 10) {
            disum = 10;
        } else if (disum < -10) {
            disum = -10;
        }
        dP = de * dkp;
        dD = (de - dee) * dkd;
        dU = dP + dD + disum;
        if (dU > grabberD.maxV) {
            dU = grabberD.maxV;
        } else if (dU < (-1) * grabberD.maxV) {
            dU = (-1) * grabberD.maxV;
        }
        motor[motorD] = dU;
        dee = de;
        sleep(1);
    }
    if (grabberD.targetPos == grabberD.close) {
        motor[motorD] = -100;
    } else {
        setMotorBrakeMode(motorD, motorBrake);
        motor[motorD] = 0;
    }
    stopTask(thr_changePosGrabberD);
}
void changePosGrabberC(float v, float pos) {
    grabberC.maxV = v;
    grabberC.targetPos = pos;
    startTask(thr_changePosGrabberC, kLowPriority);
}

void changePosGrabberD(float v, float pos) {
    grabberD.maxV = v;
    grabberD.targetPos = pos;
    startTask(thr_changePosGrabberD, kLowPriority);
}
