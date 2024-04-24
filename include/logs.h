char * filename = "RGB_min_max.txt";

#ifdef READ
    long fileHandle = fileOpenRead(filename);
#endif

#ifdef WRITE
    long fileHandle = fileOpenWrite(filename);
#endif


#ifdef WRITE
    void writeRGB(short red, short green, short blue){
        fileWriteShort(fileHandle, red);
        fileWriteShort(fileHandle, green);
        fileWriteShort(fileHandle, blue);
    }
#endif


#ifdef READ
    void readRGB(short *red, short *green, short *blue){
        fileReadShort(fileHandle, red);
        fileReadShort(fileHandle, green);
        fileReadShort(fileHandle, blue);
    }

    void readMinMax(){
        readRGB(&CDSensor1.maxRed, &CDSensor1.maxGreen, &CDSensor1.maxBlue);
        readRGB(&CDSensor1.minRed, &CDSensor1.minGreen, &CDSensor1.minBlue);
        readRGB(&CDSensor2.maxRed, &CDSensor2.maxGreen, &CDSensor2.maxBlue);
        readRGB(&CDSensor2.minRed, &CDSensor2.minGreen, &CDSensor2.minBlue);
    }
#endif