#pragma once

typedef struct {
    tMotor nDeviceIndex;
    float first;
    float second;
    float maxUp;
    float third;
    float fourth;
    float kran;
    float kranUp;
    float closeClaws;
    float maxV;
    float targetPos;
    float upForTakeFromShip;
    float firstLevel;
    float firstLevelT;
    float maxDown;
    float secondLevel;
    float secondLevelGrob;
    float secondLevelT;
    float fourthLevel;
    float smallUp;
    float smallerUp;
    float almostFloor;
} tGrabberPositionC;

typedef struct {
    tMotor nDeviceIndex;
    float openBack;
    float openFront;
    float close;
    float maxV;
    float targetPos;
    float kran;
    float openTrash;
    float openMax;
    float openKran;
    float smallOpen;
    float smallerOpen;
    float openStack;
    float openStack2;
    float openTower;
    float maxOpenFront;
    float maxOpenBack;
    float bigOpen;
    float smallOpenFront;
} tGrabberPositionD;

tGrabberPositionC grabberC;
tGrabberPositionD grabberD;


task initGrabber() {
        setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 100;
    motor[motorD] = -100;
    sleep(1000);


    motor[motorC] = 0;
    motor[motorD] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    grabberC.maxUp = 0;
    grabberC.kran = -530;
    grabberC.kranUp = 700;      
    grabberC.closeClaws = -240;
    grabberC.maxDown = -800;
    grabberC.almostFloor = -700;
     grabberC.smallUp = 770;
     grabberC.smallerUp = 870;
            grabberC.firstLevel = -380;
            grabberC.firstLevelT = -470;
    grabberC.secondLevel = 550;
    grabberC.secondLevelGrob = 670;
grabberC.secondLevelT = 620;
grabberC.fourthLevel = 460;

    grabberD.close = 0;
    grabberD.kran = -80;
    grabberD.openTrash = -120
    grabberD.smallerOpen = -90;
    grabberD.openTower = -150;
    grabberD.maxOpenFront = -400;
    grabberD.smallOpenFront = -200;
    grabberD.maxOpenBack = -900;
    grabberD.smallOpen = 150;
    grabberD.openStack = 150;
     grabberD.openStack2 = 145;
     grabberD.bigOpen = 300;
    stopTask(initGrabber);
}

task thr_changePosGrabberC() {
    float ce, cee, cP, cD, cU;
    float cisum = 0;
    float ckp = 4;
    float ckd = 6;
    float cki = 0.006;
    cee = 0;
    float ctt = nPgmTime;
    while (nPgmTime - ctt < 4000) {
        ce = grabberC.targetPos - nMotorEncoder[motorC];

        if (ce == 0) {
            cisum = 0;
        } else if (ce > 0 && cee <= 0) {
            cisum = 0;
        } else if (ce < 0 && cee >= 0) {
            cisum = 0;
        }

        cisum += ce * cki;



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
    float dkp = 3;
    float dkd = 7;
    float dki = 0.002;
    dee = 0;
    float dtt = nPgmTime;
    
    if (grabberD.targetPos == grabberD.close) {
        motor[motorD] = -grabberD.maxV;
        sleep(250);
        motor[motorD] = -100;
    } else {
        while (nPgmTime - dtt < 4000) {
        de = grabberD.targetPos - nMotorEncoder[motorD];
        if (de == 0) {
            disum = 0;
        } else if (de > 0 && dee <= 0) {
            disum = 0;
        } else if (de < 0 && dee >= 0) {
            disum = 0;
        }
        disum += de * dki;
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
        setMotorBrakeMode(motorD, motorBrake);
        motor[motorD] = 0;
    }


    stopTask(thr_changePosGrabberD);
}
void changePosGrabberC(float v, float pos) {
    // stopTask(thr_changePosGrabberC);
    // motor[motorC] = 0;
    grabberC.maxV = v;
    grabberC.targetPos = pos;
    startTask(thr_changePosGrabberC, kLowPriority);
}

void changePosGrabberD(float v, float pos) {
    // stopTask(thr_changePosGrabberD);
    // motor[motorD] = 0;
    grabberD.maxV = v;
    grabberD.targetPos = pos;
    startTask(thr_changePosGrabberD, kLowPriority);
}
