bool motorAstop = false;
bool motorBstop = false;

#include "robotConfig.h"
#include "common.h"
#include "common-light.h"
#include "typedefs.h"
#include "HT2Color.h"
#include "colorDetect.h"
#include "currentMTVars.h"
#include "stop.h"
#include "smooth.h"
#include "arc.h"
#include "lineFollow.h"
#include "grabberPID.h"
#include "logs.h"
#include "async.h"

void initAll(){
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    
    initMtVars();
    colorDetectInit();

	#ifdef READ
    	readMinMax();
	#endif

    setDefaultLine();
    setMotorBrakeMode(motorA, motorBrake);
    setMotorBrakeMode(motorB, motorBrake);
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);

	initSensor(&CDSensor3, HTCS2_MODE_ACTIVE);
	initSensor(&CDSensor4, HTCS2_MODE_ACTIVE);
    startTask(initGrabber, kLowPriority);
}
