const float stopKP = 4;
const float stopKI = 0.06;
const float stopKD = 6;

task stopA_task {
    float u, e, ee = 0, isum = 0;
    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i) {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;

    motorAstop = true;
    while (motorAstop) {
        e = nMotorEncoder[motorA] - MTVarsA.targetEnc;

        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        isum -= err[curErrIdx];
        isum += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;

        u = e * stopKP + isum * stopKI + (e - ee) * stopKD;
        motor[motorA] = -u;
        ee = e;
        sleep(1);
    }
    
    stopTask(stopA_task);
}

task stopB_task {
    float u, e, ee = 0, isum = 0;
    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i) {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;

    motorBstop = true;
    while (motorBstop) {
        e = nMotorEncoder[motorB] - MTVarsB.targetEnc;
        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        isum -= err[curErrIdx];
        isum += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;
        u = e * stopKP + isum * stopKI + (e - ee) * stopKD;
        motor[motorB] = -u;
        ee = e;
        sleep(1);
    }

    stopTask(stopB_task);
}

void stopMoveA(int delayMsec = 0, bool reset = false){
    startTask(stopA_task, kLowPriority);
    sleep(delayMsec);
    if (reset) {
        nMotorEncoder[motorA] = 0;
        MTVarsA.targetEnc = 0;
        MTVarsA.targetV = 0;
    }
}

void stopMoveB(int delayMsec = 0, bool reset = false){
    startTask(stopB_task, kLowPriority);
    sleep(delayMsec);
    if (reset) {
        nMotorEncoder[motorB] = 0;
        MTVarsB.targetEnc = 0;
        MTVarsB.targetV = 0;
    }
}

void stopMove(int delayMsec = 0, bool reset = false, bool mode = true) {
    startTask(stopA_task, kLowPriority);
    startTask(stopB_task, kLowPriority);

    sleep(delayMsec);

    if (reset) {
        nMotorEncoder[motorA] = 0;
        nMotorEncoder[motorB] = 0;
        MTVarsA.targetEnc = 0;
        MTVarsB.targetEnc = 0;
        MTVarsA.targetV = 0;
        MTVarsB.targetV = 0;
    }
}
