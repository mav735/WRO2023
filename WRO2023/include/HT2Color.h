#pragma systemFile

#define HTCS2_I2C_ADDR        0x02      /*!< HTCS2 I2C device address */
#define HTCS2_CMD_REG         0x41      /*!< Command register */
#define HTCS2_OFFSET          0x42      /*!< Offset for data registers */

#define HTCS2_COLNUM_REG      0x00      /*!< Color number */
#define HTCS2_RED_REG         0x01      /*!< Red reading */
#define HTCS2_GREEN_REG       0x02      /*!< Green reading */
#define HTCS2_BLUE_REG        0x03      /*!< Blue reading */
#define HTCS2_WHITE_REG       0x04      /*!< White channel reading */
#define HTCS2_COL_INDEX_REG   0x05      /*!< Color index number */
#define HTCS2_RED_NORM_REG    0x06      /*!< Normalised red reading */
#define HTCS2_GREEN_NORM_REG  0x07      /*!< Normalised green reading */
#define HTCS2_BLUE_NORM_REG   0x08      /*!< Normalised blue reading */

#define HTCS2_MODE_ACTIVE     0x00      /*!< Use ambient light cancellation */
#define HTCS2_MODE_PASSIVE    0x01      /*!< Disable ambient light cancellation */
#define HTCS2_MODE_RAW        0x03      /*!< Raw data from light sensor */
#define HTCS2_MODE_50HZ       0x35      /*!< Set sensor to 50Hz cancellation mode */
#define HTCS2_MODE_60HZ       0x36      /*!< Set sensor to 60Hz cancellation mode */

bool _sensorSendCommand(tHTCS2Ptr htcs2Ptr) {
  memset(htcs2Ptr->I2CData.request, 0, sizeof(htcs2Ptr->I2CData.request));

  htcs2Ptr->I2CData.request[0] = 3;                     // Message size
  htcs2Ptr->I2CData.request[1] = HTCS2_I2C_ADDR;        // I2C Address
  htcs2Ptr->I2CData.request[2] = HTCS2_CMD_REG;         // Command register
  htcs2Ptr->I2CData.request[3] = htcs2Ptr->_cmd;        // Command to be sent
  return writeI2C(&htcs2Ptr->I2CData);
}

bool initSensor(tCDValues *CDSensorPtr, ubyte mode = HTCS2_MODE_ACTIVE){
  memset(CDSensorPtr->HTStruct, 0, sizeof(tHTCS2Ptr));

  CDSensorPtr->HTStruct.I2CData.address = HTCS2_I2C_ADDR;
  CDSensorPtr->HTStruct.I2CData.port = CDSensorPtr->nDeviceIndex;
  CDSensorPtr->HTStruct.I2CData.type = sensorI2CCustom9V;
  CDSensorPtr->HTStruct._cmd = mode;

  if (SensorType[CDSensorPtr->HTStruct.I2CData.port] != CDSensorPtr->HTStruct.I2CData.type)
    SensorType[CDSensorPtr->HTStruct.I2CData.port] = CDSensorPtr->HTStruct.I2CData.type;

  return _sensorSendCommand(&CDSensorPtr->HTStruct);
}

bool readHTrgb(tCDValues *CDSensorPtr){
  memset(CDSensorPtr->HTStruct.I2CData.request, 0, sizeof(CDSensorPtr->HTStruct.I2CData.request));

  CDSensorPtr->HTStruct.I2CData.request[0] = 2;                               // Message size
  CDSensorPtr->HTStruct.I2CData.request[1] = CDSensorPtr->HTStruct.I2CData.address;       // I2C Address
  CDSensorPtr->HTStruct.I2CData.request[2] = HTCS2_OFFSET + HTCS2_COLNUM_REG;
  CDSensorPtr->HTStruct.I2CData.replyLen = 4;
  CDSensorPtr->HTStruct.I2CData.requestLen = 2;

  if (!writeI2C(&CDSensorPtr->HTStruct.I2CData))
    return false;
    
  CDSensorPtr->rawRed   = (short)CDSensorPtr->HTStruct.I2CData.reply[1];
  CDSensorPtr->rawGreen = (short)CDSensorPtr->HTStruct.I2CData.reply[2];
  CDSensorPtr->rawBlue  = (short)CDSensorPtr->HTStruct.I2CData.reply[3];

  return true;
}

bool setModeHT(tCDValues *CDSensorPtr, ubyte mode){
    CDSensorPtr->HTStruct._cmd = mode;
    return _sensorSendCommand(&CDSensorPtr->HTStruct);
}
