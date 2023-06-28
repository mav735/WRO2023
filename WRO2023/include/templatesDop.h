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

// void readWelems() {
//     setDefaultLineGreyCross();
//     lineFollowCross(30, 25, 1);
//     stopMove(250);
//     arcEnc(25, -25, 60, 25, 65);
//     stopMove(150);
//     arcAngle(-25, -25, -80, -25, 80);
//     arcAngle(-25, -25, -25, -25, 10);
//     stopMove(200);
//     readColors(encodersWelems, welemsColors, 2, &CDSensor3, 0);
//     arcEnc(-25, 25, 60, 25, 120);
//     arcEnc(-25, 25, 25, 25, 35);
//     stopMove(150);
//     arcAngle(40, 0, 100, 30, 80);
//     arcAngle(30, 0, 30, 30, 10);
//     changePosGrabberC(100, grabberC.maxDown);
//     stopMove(450);
// }

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

void after() {
    setDefaultLine();
    arcAngle(60, 60, 60, 60, 180);
    lineFollowCross(70, 100, 1);
    lineFollowEncoder(100, 100, 100, 300);
    lineFollowCross(100, 40, 1);
    arcAngle(0, 50, 100, 40, 98);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(-40, 40, 100, 25, 420);
    arcEnc(-25, 25, 25, 25, 80);
    stopMove(50);
    changePosGrabberC(100, grabberC.maxUp);
    stopMove(200);
    arcEnc(-55, 55, 55, 55, 300);
    stopMove(100);
    smartTurnLeft_enc(55, 55, 55, 1);
    lineFollowCross(55, 55, 1);
    lineBase(55, 55);
    smartTurnRight_angle(55, 55, 55, 90);


    lineFollowEncoder(55, 100, 100, 600, 20);
    lineFollowCross(100, 40, 1, 20);
    arcColor_angle(-40, 0, -100, -40, 90, &CDSensor2, 1);
    lineFollowEncoder(40, 60, 30, 315);

    stopMove(200);
    arcEnc(40, -40, 100, 30, 325);
    changePosGrabberC(100, grabberC.upForDrop);
    stopMove(500);
    arcEnc(30, -30, 30, 30, 25);
    stopMove(50);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(250);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(40, -40, 100, 60, 115);
    smartTurnRight_angle(60, 100, 60);

}

void after_fast() {
    setDefaultLine();
    arcAngle(60, 60, 100, 60, 180);
    lineFollowCross(70, 100, 1);
    lineFollowEncoder(100, 100, 100, 300);
    lineFollowCross(100, 40, 1);
    arcAngle(0, 50, 100, 40, 97);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(-40, 40, 100, 25, 420);
    arcEnc(-25, 25, 25, 25, 80);
    stopMove(50);
    changePosGrabberC(100, grabberC.maxUp);
    stopMove(200);
    arcEnc(-55, 55, 100, 35, 300);
    stopMove(100);
    smartTurnLeft_enc(55, 100, 45, 1);
    lineFollowCross(45, 55, 1);
    lineBase(55, 55);
    smartTurnRight_angle(55, 100, 45, 90);


    lineFollowEncoder(55, 100, 100, 700, 20);
    lineFollowCross(100, 55, 1, 20);
    arcColor_angle(-55, 0, -100, -55, 90, &CDSensor2, 1);
    lineFollowEncoder(55, 70, 25, 315);

    stopMove(200);
    arcEnc(40, -40, 100, 30, 290);
    changePosGrabberC(100, grabberC.upForDrop);
    stopMove(500);
    arcEnc(30, -30, 30, 30, 25);
    stopMove(50);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(250);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(60, -60, 100, 60, 120);
    smartTurnRight_angle(60, 100, 60);

}

void huy() {
    lineFollowCross(50, 100, 2);
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
    smartTurnLeft_angle(50, 100, 50, 180);
    lineFollowCross(100, 100, 3);
    changePosGrabberC(100, grabberC.upForDrop);
    arcEnc(-100, 100, 100, 40, 90);
    arcAngle(-40, 0, -100, -40, 88);
    stopMove(250);
    changePosGrabberD(60, grabberD.openMin);
    stopMove(200);
    changePosGrabberC(100, grabberC.maxUp);
    arcEnc(30, -30, 60, 30, 30);
    arcAngle(50, 0, 100, 50, 71);
    smartTurnLeft_angle(50, 100, 50, 107);
    lineFollowEncoder(50, 50, 50, 340);
    arcEnc(-50, 50, 50, 25, 340);
    stopMove(200);
}

void huy_fast() {
    lineFollowCross(80, 100, 2);
    lineFollowEncoder(100, 100, 100, 600);
    lineFollowCross(100, 30, 1);
    changePosGrabberC(60, grabberC.maxDown);
    arcAngle(-40, 0, -100, -30, 95);
    changePosGrabberD(100, grabberD.openMin);
    arcEnc(-30, 30, 100, 30, 405);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(50, -50, 100, 60, 405);
    arcAngle(60, 0, 100, 50, 95);
    smartTurnLeft_angle(50, 100, 50, 180);
    lineFollowCross(100, 100, 3);
    changePosGrabberC(100, grabberC.upForDrop);
    arcEnc(-100, 100, 100, 40, 90);
    arcAngle(-40, 0, -100, -40, 88);
    stopMove(250);
    changePosGrabberD(60, grabberD.openMin);
    stopMove(200);
    changePosGrabberC(100, grabberC.maxUp);
    arcEnc(50, -50, 50, 50, 30);
    arcAngle(50, 0, 100, 50, 71);
    smartTurnLeft_angle(50, 100, 50, 107);
    lineFollowEncoder(50, 100, 50, 340);
    arcEnc(-50, 50, 50, 25, 340);
    stopMove(200);
}



void getLeftWelem(int f=0) {
    arcEnc(0, 30, 40, 30, 60);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(100);
    arcEnc(-30, 30, 40, 30, 150);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 40, 30, 150);
    if (f == 1) {
        arcEnc(0, -30, -40, -30, 60);
    }

}

void getRightWelem(int f=0) {
    arcEnc(-30, 0, -40, -30, 60);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(100);
    arcEnc(-30, 30, 40, 30, 150);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 40, 30, 150);
    arcEnc(30, 0, 40, 30, 60);
    if (f == 1) {
        arcEnc(0, -30, -40, -30, 60);
    }
}

void rideToAllThrowRed() {
    setDefaultLine();
    lineFollowCross(100, 40, 1);
    arcToBase(40, 40, 30);
    stopMove(200);
    arcAngle(-50, -50, -50, -50, 90);
    stopMove(100);
    lineFollowEncoder(40, 40, 40, 150);
    stopMove(200);
}

void throwRedCont(int pos) {
    if (pos == 0) {
        arcEnc(-45, -45, -45, -45, 60);
        stopMove(150);
        arcEnc(-45, 45, 45, 45, 360);
        stopMove(200);
        arcEnc(45, -45, 45, 45, 360);
        arcEnc(45, 45, 45, 45, 60);
        stopMove(150);
    } else if (pos == 1) {
        arcEnc(-45, -45, -45, -45, 30);
        stopMove(150);
        arcEnc(-45, 45, 45, 45, 340);
        stopMove(200);
        arcEnc(45, -45, 45, 45, 340);
        arcEnc(45, 45, 45, 45, 30);
        stopMove(150);
    } else if (pos == 2) {
        arcEnc(-45, 45, 45, 45, 340);
        stopMove(200);
        arcEnc(45, -45, 45, 45, 340);
        stopMove(150);
    } else {
        arcEnc(45, 45, 45, 45, 30);
        stopMove(150);
        arcEnc(-45, 45, 45, 45, 365);
        stopMove(200);
        arcEnc(45, -45, 45, 45, 365);
        arcEnc(-45, -45, -45, -45, 30);
        stopMove(150);
    }

}

void throwRedCont_fast(int pos) {
    if (pos == 0) {
        arcEnc(-45, -45, -100, -45, 60);
        stopMove(100);
        arcEnc(-45, 45, 100, 25, 310);
        arcEnc(-25, 25, 25, 25, 40);
        stopMove(200);
        arcEnc(45, -45, 100, 45, 350);
        stopMove(50);
        arcEnc(45, 45, 100, 45, 60);
        stopMove(150);
    } else if (pos == 1) {
        arcEnc(-45, -45, -100, -45, 30);
        stopMove(100);
        arcEnc(-45, 45, 100, 25, 300);
        arcEnc(-25, 25, 25, 25, 40);
        stopMove(200);
        arcEnc(45, -45, 100, 45, 340);
        stopMove(50);
        arcEnc(45, 45, 100, 45, 30);
        stopMove(150);
    } else if (pos == 2) {
        arcEnc(-45, 45, 100, 25, 300);
        arcEnc(-25, 25, 25, 25, 40);
        stopMove(200);
        arcEnc(45, -45, 100, 45, 340);
        stopMove(150);
    } else {
        arcEnc(45, 45, 100, 45, 25);
        stopMove(150);
        arcEnc(-45, 45, 100, 25, 310);
        arcEnc(-25, 25, 25, 25, 40);
        stopMove(200);
        arcEnc(45, -45, 100, 45, 350);
        stopMove(50);
        arcEnc(-45, -45, -100, -45, 25);
        stopMove(150);
    }

}

void takeBigShipFromCrossToElements() {
    setDefaultLine();

    lineFollowEncoder(40, 100, 40, 415);
    arcAngle(0, 40, 100, 40, 90);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    arcEnc(-40, 40, 100, 25, 560);
    arcEnc(-25, 25, 25, 25, 80);
    changePosGrabberC(100, grabberC.maxUp);

    arcEnc(-25, 25, 25, 25, 40);
    stopMove(250);
    arcAngle(40, 40, 100, 40, 90);
    stopMove(100);
    arcColor_enc(-40, 40, 100, 40, 400, &CDSensor1, 1);
    arcToBase(40, 40, 40);
    stopMove(200);
    arcAngle(40, 40, 100, 40, 90);
    stopMove(200);
}

void takeTwoMarkersInLeftCoridor() {
    changePosGrabberD(100, grabberD.openMax);
    changePosGrabberC(100, grabberC.maxDown);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    arcEnc(-40, 40, 40, 40, 165);
    changePosGrabberD(60, grabberD.close);
    stopMove(500);
    arcEnc(40, -40, 100, 30, 800);
    stopMove(100);
    changePosGrabberD(60, grabberD.openMax);
    stopMove(300);
    changePosGrabberC(50, grabberC.maxUpWithoutShip);
    arcAngle(0, -40, -100, -40, 188);
    stopMove(100);
    arcAngle(40, 0, 100, 40, 98);
    stopMove(150);
    changePosGrabberC(50, grabberC.maxUp);
    stopMove(100);
    arcEnc(-40, 40, 100, 30, 500);
    changePosGrabberC(50, grabberC.maxUpWithoutShip);
    arcEnc(-30, 30, 30, 30, 150);
    stopMove(200);
    arcAngle(0, -40, -100, -40, 90);
    stopMove(250);

}

void takeElemFromCenterOfBigShip() {
    changePosGrabberD(60, grabberD.openMin);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    stopMove(100);
    changePosGrabberC(70, grabberC.upForTakeFromShip);
    stopMove(600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
}

void takeElemFromDefLeftBigShip() {
    changePosGrabberD(60, grabberD.openMin);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    stopMove(100);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(0, -40, -60, -40, 190);
    stopMove(100);
    arcEnc(40, 0, 60, 40, 190);
    stopMove(100);
    arcEnc(-30, 30, 50, 30, 180);
    changePosGrabberC(70, grabberC.upForTakeFromShip);
    stopMove(600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(30, -30, 50, 30, 180);
    stopMove(200);
    arcEnc(-40, 0, -60, -40, 190);
    stopMove(200);
    arcEnc(0, 40, 60, 40, 190);
    stopMove(200);

}

void takeElemFromDefRightBigShip() {
    changePosGrabberD(60, grabberD.openMin);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    stopMove(100);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(40, 0, 60, 40, 190);
    stopMove(100);
    arcEnc(0, -40, -60, -40, 190);
    stopMove(100);
    arcEnc(-30, 30, 50, 30, 180);
    changePosGrabberC(70, grabberC.upForTakeFromShip);
    stopMove(600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(30, -30, 50, 30, 180);
    stopMove(200);
    arcEnc(0, 40, 60, 40, 190);
    stopMove(200);
    arcEnc(-40, 0, -60, -40, 190);
    stopMove(200);
}

void takeElemFromSupLeftBigShip() {
    changePosGrabberD(60, grabberD.openMin);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    stopMove(100);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(0, -40, -60, -40, 350);
    stopMove(100);
    arcEnc(40, 0, 60, 40, 350);
    stopMove(100);
    arcEnc(-30, 30, 50, 30, 290);
    changePosGrabberC(70, grabberC.upForTakeFromShip);
    stopMove(600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(30, -30, 50, 30, 290);
    stopMove(200);
    arcEnc(-40, 0, -60, -40, 350);
    stopMove(200);
    arcEnc(0, 40, 60, 40, 350);
    stopMove(200);
}

void takeElemFromSupRightBigShip() {
    changePosGrabberD(60, grabberD.openMin);
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    stopMove(100);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(40, 0, 60, 40, 350);
    stopMove(100);
    arcEnc(0, -40, -60, -40, 350);
    stopMove(100);
    arcEnc(-30, 30, 50, 30, 290);
    changePosGrabberC(70, grabberC.upForTakeFromShip);
    stopMove(600);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    changePosGrabberC(70, grabberC.maxUpWithoutShip);
    stopMove(200);
    arcEnc(30, -30, 50, 30, 290);
    stopMove(200);
    arcEnc(0, 40, 60, 40, 350);
    stopMove(200);
    arcEnc(-40, 0, -60, -40, 350);
    stopMove(200);
}

void takeLeftMayk() {
    setDefaultLine();
    changePosGrabberC(40, grabberC.upForDrop);
    changePosGrabberD(100, grabberD.openMax);
    lineFollowCross(70, 100, 1);
    lineFollowEncoder(100, 100, 25, 770);
    stopMove(250);
    arcAngle(30, 30, 100, 30, 85);
    arcAngle(30, 30, 30, 30, 5);
    stopMove(300);
    arcEnc(-30, 30, 40, 30, 60);
    stopMove(100);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 40, 30, 60);
    stopMove(200);
    arcAngle(30, 30, 100, 30, 85);
    arcAngle(30, 30, 30, 30, 5);
    stopMove(250);
}

void takeRightMayk() {
    setDefaultLine();
    changePosGrabberC(40, grabberC.upForDrop);
    changePosGrabberD(100, grabberD.openMax);
    lineFollowCross(70, 100, 1);
    lineFollowEncoder(100, 100, 25, 770);
    stopMove(250);
    arcAngle(-30, -30, -100, -30, 85);
    arcAngle(-30, -30, -30, -30, 5);
    stopMove(300);
    arcEnc(-30, 30, 40, 30, 60);
    stopMove(100);
    changePosGrabberD(100, grabberD.close);
    stopMove(200);
    arcEnc(30, -30, 40, 30, 60);
    stopMove(200);
    arcAngle(-30, -30, -100, -30, 85);
    arcAngle(-30, -30, -30, -30, 5);
    stopMove(250);
}

void pushOnSecondLeftWall() {
    setDefaultLine();
    lineFollowCross(40, 40, 1);
    lineBase(40, 30);
    stopMove(200);
    arcAngle(40, 40, 60, 35, 90);
    stopMove(200);
    lineFollowEncoder(40, 40, 40, 600);
    stopMove(200);
    arcAngle(-40, 40, 40, 40, 90);
    stopMove(200);
}