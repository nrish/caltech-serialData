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
    uint32_t mills; //ms/w
    uint8_t endWellIndex;
    uint8_t trayIndex;
};

union StartDataSerialized{
    StartData values;
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

struct __attribute__((__packed__)) setPos{
    uint32_t x;
    uint32_t y;
    bool speed;
    bool home;
};
union setPosSerialized{
    uint8_t bytes[sizeof(setPos)];
    setPos values;
};
#define CMD_STARTDATA 1
#define CMD_CALIBRATION 2
#define CMD_UPDATE 3
#define CMD_SETPOS 4
struct __attribute__((__packed__)) expect{
    uint32_t bytes;
    uint8_t cmd;
    bool request;
};
union expectSerialized{
    uint8_t bytes[sizeof(expect)];
    expect value;
    
};
#endif

