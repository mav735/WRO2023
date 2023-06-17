#define min2(a, b) ((a) < (b) ? (a) : (b))
#define min3(a, b, c) ((a) < (b)) ? (((a) < (c)) ? (a) : (c)) : (((b) < (c)) ? (b) : (c))
#define max2(a, b) ((a) > (b) ? (a) : (b))
#define max3(a, b, c) ((a) > (b)) ? (((a) > (c)) ? (a) : (c)) : (((b) > (c)) ? (b) : (c))
#define MAX_ARR_SIZE 17

void saveRatioPID(float *va, float *vb) {

    // if (fabs(*va) > 100){
    //     short sgnA = sgn(*va);
    //     *vb = *vb / *va * 100 * sgnA 
    //     *va = 100 * sgnA 
    // }
    // else if (fabs(*vb) > 100){
    //     short sgnB = sgn(*vb);
    //     *va = *va / *vb * 100 * sgnB
    //     *vb = 100 * sgnB
    // }

    if (*va < -100){
        *vb = *vb / *va * -100;
        *va = -100;
    }
    else if (*va > 100){
        *vb = *vb / *va * 100;
        *va = 100;
    }
    else if (*vb < -100){
        *va = *va / *vb * -100;
        *vb = -100;
    }
    else if (*vb > 100){
        *va = *va / *vb * 100;
        *vb = 100;
    }
}

float mapping(float raw, float min, float max, float normMin, float normMax) {
    return (raw - min) / (max - min) * (normMax - normMin) + normMin;
}

float angleToEnc(float vB, float vC, float angle) {
    return angle / 180 * PI * g_wheelBase *
           (vB == 0 || vC == 0
                ? 1
                : (1 / fabs(-vB / vC - 1) + 1 / fabs(-vC / vB - 1)) / 2.);
}

void waitTask(bool *taskFlag){
    while(*taskFlag){
        sleep(1);
    }
}


// 0 - White
// 1 - Black
// 2 - Red
// 3 - Green
// 4 - Blue
// 5 - Yellow
void colSound(int col) {
    clearSounds();
    if (col == 0) {
        playSoundFile("White");
    } else if (col == 1) {
        playSoundFile("Black");
    } else if (col == 2) {
        playSoundFile("Right");
    } else if (col == 3) {
        playSoundFile("Green");
    } else if (col == 4) {
        playSoundFile("Blue");
    } else if (col == 5) {
        playSoundFile("Yellow");
    } else {
        playSoundFile("Zero");
    }
}

typedef struct{
  ubyte request[17];
  ubyte requestLen;
  ubyte reply[17];
  ubyte replyLen;
  ubyte address;
  tSensors port;
  TSensorTypes type;
} tI2CData, *tI2CDataPtr;

typedef ubyte tByteArray[MAX_ARR_SIZE];
typedef sbyte tsByteArray[MAX_ARR_SIZE];
typedef ubyte tMassiveArray[128];             /*!< 128 byte array for very large blobs of data */
typedef ubyte tHugeByteArray[64];             /*!< 64 byte array for very large blobs of data */
typedef ubyte tBigByteArray[32];              /*!< 32 byte array for large blobs of data */
typedef ubyte tIPaddr[4];                     /*!< Struct for holding an IP address */


typedef short tIntArray[MAX_ARR_SIZE];
bool waitForI2CBus(tSensors link);
bool writeI2C(tSensors link, tByteArray &request, tByteArray &reply, short replylen);
bool writeI2C(tSensors link, tByteArray &request);


bool waitForI2CBus(tSensors link){
  while (true){
    switch(nI2CStatus[link])
    {
        case i2cStatusStopped:
        case i2cStatusNoError:
            return true;

        case i2cStatusPending:
        case i2cStatusStartTransfer:
            break;

        case i2cStatusFailed:
        case i2cStatusBadConfig:
            return false;
    }
    sleep(1);
  }
}

bool waitForI2CBus(tI2CDataPtr data){
  while (true) {
    switch (nI2CStatus[data->port]) {
        case i2cStatusStopped:
        case i2cStatusNoError:
            return true;

        case i2cStatusPending:
        case i2cStatusStartTransfer:
            break;

        case i2cStatusFailed:
        case i2cStatusBadConfig:
            return false;
    }
    sleep(1);
  }
}

bool writeI2C(tI2CDataPtr data) {
    sendI2CMsg(data->port, &data->request[0], data->replyLen);

    if (!waitForI2CBus(data)) {
        return false;
    }

    if (data->replyLen == 0)
        return true;
    readI2CReply(data->port, &data->reply[0], data->replyLen);
    return waitForI2CBus(data);
}

bool writeI2C(tSensors link, tByteArray &request) {
  sendI2CMsg(link, &request[0], 0);
  if (!waitForI2CBus(link)) {
	return false;
  }
  return true;
}

bool writeI2C(tSensors link, tByteArray &request, tByteArray &reply, short replylen) {
  sendI2CMsg(link, &request[0], replylen);
  if (!waitForI2CBus(link)) {
	return false;
  }
  readI2CReply(link, &reply[0], replylen);
  return waitForI2CBus(link);
}

void resetSensorConn(tSensors link){
    setSensorAutoID(link, false);
    sleep(10);
    setSensorConnectionType(link, CONN_NONE);
    sleep(10);
    setSensorAutoID(link, true);
    sleep(1000);
}

void offAllSensors(){
    setSensorAutoID(S1, false);
    sleep(10);
    setSensorConnectionType(S1, CONN_NONE);
    sleep(10);
    setSensorAutoID(S2, false);
    sleep(10);
    setSensorConnectionType(S2, CONN_NONE);
    sleep(10);
    setSensorAutoID(S3, false);
    sleep(10);
    setSensorConnectionType(S3, CONN_NONE);
    sleep(10);
    setSensorAutoID(S4, false);
    sleep(10);
    setSensorConnectionType(S4, CONN_NONE);
    sleep(10);
}