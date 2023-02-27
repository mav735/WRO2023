typedef struct {
    tMotor nDeviceIndex;
    float maxDown;
    float maxUp;
    float maxUpWithoutShip;
    float upForShipThrow;
    float upForShipPush;
    float maxV;
    float targetPos;
} tGrabberPositionC;

typedef struct {
    tMotor nDeviceIndex;
    float closeBoth;
    float openForwardMax;
    float openForwardMin;
    float openBackwardMax;
    float openBackwardMin;
    float maxV;
    float targetPos;
} tGrabberPositionD;

tGrabberPositionC grabberC;
tGrabberPositionD grabberD;


task initGrabber() {
    motor[motorC] = 50;
    motor[motorD] = -50;
    sleep(400);
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 0;
    motor[motorD] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    grabberC.maxUp = 0;
    grabberC.maxUpWithoutShip = -600;
    grabberC.maxDown = -1400;
    grabberC.upForShipThrow = -1000;
    grabberC.upForShipPush = -450;

    grabberD.closeBoth = 0;
    grabberD.openForwardMax = 450;
    grabberD.openForwardMin = 260;
    grabberD.openBackwardMax = 800;
    grabberD.openBackwardMin = 660;
    stopTask(initGrabber);
}

task thr_changePosGrabberC() {
    float ce, cee, cP, cD, cU;
    float ckp = 1;
    float ckd = 3;
    cee = 0;
    clearTimer(T2);
    while (time1[T2] < 2000 || abs(cU) < 2) {
        ce = grabberC.targetPos - nMotorEncoder[motorC];
        cP = ce * ckp;
        cD = (ce - cee) * ckd;
        cU = cP + cD;
        if (cU > grabberC.maxV) {
            cU = grabberC.maxV;
        } else if (cU < (-1) * grabberC.maxV) {
            cU = (-1) * grabberC.maxV;
        }
        motor[motorC] = cU;
        cee = ce;
    }
    setMotorBrakeMode(motorC, motorBrake);
    motor[motorC] = 0;
    stopTask(thr_changePosGrabberC);
}

task thr_changePosGrabberD() {
    float de, dee, dP, dD, dU;
    float dkp = 1;
    float dkd = 3;
    dee = 0;
    clearTimer(T3);
    while (time1[T3] < 2000 || abs(dU) < 5) {
        de = grabberD.targetPos - nMotorEncoder[motorD];
        dP = de * dkp;
        dD = (de - dee) * dkd;
        dU = dP + dD;
        if (dU > grabberD.maxV) {
            dU = grabberD.maxV;
        } else if (dU < (-1) * grabberD.maxV) {
            dU = (-1) * grabberD.maxV;
        }
        motor[motorD] = dU;
        dee = de;
    }
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorD] = 0;
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
