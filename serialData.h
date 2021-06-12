#ifndef SERIAL_DATA_H
#define SERIAL_DATA_H
#include<stdint.h>

#ifdef __linux__

#endif
/*
 * this file contains all the structures and unions required to easily serialize data and send it accross the serial port or write to EEPROM.
 */
//tray position
struct __attribute__((__packed__)) Tray{
    int32_t x; // index 0
    int32_t y; // index 1
};

//initalization data, required to start machine
struct __attribute__((__packed__)) StartData{
    uint8_t start_mode; //start mode can be 0 or 1 respectively normal run and calibration
    uint32_t mills; //ms/w
    uint8_t endWellIndex;
    uint8_t trayIndex;
};

union StartDataSerialized{
    StartData startData;
    uint8_t bytes[sizeof(StartData)];
};


//EEPROM serializable data

struct __attribute__((__packed__)) CalibrationValues{
    //distance between wells
    int16_t WELL_DIST_X;
    int16_t WELL_DIST_Y;

    bool Y_END_DIR;
    bool X_END_DIR;
    //positions of the 8 trays on machine
    Tray trays[8];
};
union CalibrationValueSerialized{
    uint8_t bytes[sizeof(CalibrationValues)];
    CalibrationValues values;
};

struct __attribute__((__packed__)) updateData{
    bool rowFinished;
    bool colFinished;
    bool trayFinished;
    bool calibrated;
};
union updateDataSerialized{
    uint8_t bytes[sizeof(updateData)];
    updateData values;
};


#endif
