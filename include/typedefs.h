typedef struct {
  tI2CData I2CData;
  ubyte _cmd;
} tHTCS2, *tHTCS2Ptr;

typedef struct {
    tSensors nDeviceIndex;
    tHTCS2 HTStruct;

    long rawRed;
    long rawGreen;
    long rawBlue;
    float normRed;
    float normGreen;
    float normBlue;
    float hue;
    float sat;
    float val;
    short minRed;
    short minGreen;
    short minBlue;
    short maxRed;
    short maxGreen;
    short maxBlue;

    float minSatRed;
    float maxSatRed;
    float minSatGreen;
    float maxSatGreen;
    float minSatBlue;
    float maxSatBlue;
    float minSatYellow;
    float maxSatYellow;

    float minHueRed1;
    float maxHueRed1;
    float minHueRed2;
    float maxHueRed2;
    float minHueGreen;
    float maxHueGreen;
    float minHueBlue;
    float maxHueBlue;
    float minHueYellow;
    float maxHueYellow;

    float borderValBW;
    float borderSatBW;

    short color;
    float borderZero;
} tCDValues;
