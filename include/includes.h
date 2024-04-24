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
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    
    initMtVars();
    colorDetectInit();

	#ifdef READ
    	readMinMax();
	#endif

    setDefaultLine();
    startTask(initGrabber, kLowPriority);
    setLEDColor(ledOff);
	setSoundVolume(100);
}
