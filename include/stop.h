void stopMove(int delayMsec = 0, bool reset = false, bool mode = true) {
    if (mode){
        setMotorBrakeMode(motorA, motorBrake);
        setMotorBrakeMode(motorB, motorBrake);
    }
    else{
        setMotorBrakeMode(motorA, motorCoast);
        setMotorBrakeMode(motorB, motorCoast);
    }
    
    motor[motorA] = 0;
    motor[motorB] = 0;

    sleep(delayMsec);

    if (reset) {
        resetMotorEncoder(motorA);
        resetMotorEncoder(motorB);
        MTVarsA.targetEnc = 0;
        MTVarsB.targetEnc = 0;
        MTVarsA.targetV = 0;
        MTVarsB.targetV = 0;
    }
}
