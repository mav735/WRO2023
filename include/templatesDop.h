void takeElemFromPusherPetrol() {
    lineFollowEncoder(100, 100, 100, 600);
    lineFollowCross(100, 40, 1);
    changePosGrabberC(60, grabberC.maxDown);
    arcAngle(-40, 0, -100, -30, 95);
    changePosGrabberD(100, grabberD.openMin);
    arcEnc(-30, 30, 100, 30, 405);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(30, -30, 100, 30, 405);
    arcAngle(40, 0, 100, 30, 95);
    stopMove(200);
    // smartTurnLeft_angle(50, 100, 50, 180);
}

void takeElemFromLeftOfPusherPetrol() {
    lineFollowEncoder(100, 100, 100, 600);
    lineFollowCross(100, 40, 1);
    changePosGrabberC(60, grabberC.maxDown);
    arcAngle(-40, 0, -100, -30, 85);
    changePosGrabberD(100, grabberD.openMin);
    arcEnc(-30, 30, 100, 30, 435);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(30, -30, 100, 30, 435);
    arcAngle(40, 0, 100, 30, 85);
    stopMove(200);
    // smartTurnLeft_angle(50, 100, 50, 180);
}


void takeElemFromRightOfPusherPetrol() {
    lineFollowEncoder(100, 100, 100, 600);
    lineFollowCross(100, 40, 1);
    stopMove(200);
    arcAngle(-30, -30, -100, -30, 95);
    stopMove(150);
    changePosGrabberC(60, grabberC.maxDown);
    changePosGrabberD(100, grabberD.openMin);
    arcEnc(-30, 30, 100, 30, 600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(30, -30, 100, 30, 600);
    arcAngle(-30, -30, -100, -30, 85);
    stopMove(200);
    // smartTurnLeft_angle(50, 100, 50, 180);
}

void readWelems() {
    setDefaultLineGreyCross();
    lineFollowCross(30, 25, 1);
    stopMove(250);
    arcEnc(25, -25, 60, 25, 65);
    stopMove(150);
    arcAngle(-25, -25, -80, -25, 80);
    arcAngle(-25, -25, -25, -25, 10);
    stopMove(200);
    readColors(encodersWelems, welemsColors, 2, &CDSensor3, 0);
    arcEnc(-25, 25, 60, 25, 120);
    arcEnc(-25, 25, 25, 25, 35);
    stopMove(150);
    arcAngle(40, 0, 100, 30, 80);
    arcAngle(30, 0, 30, 30, 10);
    changePosGrabberC(100, grabberC.maxDown);
    stopMove(450);
}

void takeTwoWhiteElements() {
    changePosGrabberC(100, grabberC.maxUp);
    setDefaultLine();
    lineFollowCross(80, 100, 1);
    reactiveTurnRight();
    setDefaultLineGreyCross();
    lineFollowEncoder(100, 100, 40, 450);
    lineFollowCross(40, 40, 1);
    arcEnc(-40, 40, 30, 30, 100);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(-40, 40, 30, 30, 40);
    stopMove(200);
    arcEnc(0, -50, -100, -50, 400);
    arcEnc(50, -50, 100, 50, 810);
    arcColor_enc(50, 0, 100, 50, 100, &CDSensor1, 1);
}

void toRightWelemBlueLine() {
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    lineFollowEncoder(40, 40, 30, 50);
    stopMove(100);
    arcAngle(-40, -40, -100, -40, 90);
    stopMove(100);
    changePosGrabberC(40, grabberC.maxDown);
    changePosGrabberD(100, grabberD.openMin);
    setLeftSensorBlueLineBlackStop(1, 2);
    lineFollowEncoder(30, 100, 30, 600);
    stopMove(400);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 100, 30, 600);
    stopMove(150);
    arcAngle(40, 40, 100, 40, 90);
    stopMove(200);
}

void toLeftWelemBlueLine() {
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    lineFollowEncoder(40, 40, 30, 120);
    stopMove(100);
    arcAngle(-40, -40, -100, -40, 90);
    stopMove(100);
    changePosGrabberC(40, grabberC.maxDown);
    changePosGrabberD(100, grabberD.openMin);
    
    setRightSensorBlueLineBlackStop(1, 2);
    lineFollowEncoder(30, 100, 30, 600);
    stopMove(400);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 100, 30, 600);
    stopMove(150);
    arcAngle(40, 40, 100, 40, 90);
    stopMove(200);
}