#ifndef SERIAL_DATA_H
#define SERIAL_DATA_H

#define CMD_STARTDATA 1
#define CMD_CALIBRATION 2
#define CMD_UPDATE 3
#define CMD_SETPOS 4
#define DEBUG_MSG 5

#if  defined(__linux__) | defined( __MINGW32__)
#include<stdint.h>
#endif
/*
 * this file contains all the structures and unions required to easily serialize data and send it accross the serial port or write to EEPROM.
 */
//tray position
struct __attribute__((__packed__)) Tray{
    Tray(){}
    Tray(uint32_t x_in, uint32_t y_in) : x(x_in), y(y_in){};
    int32_t x; // index 0
    int32_t y; // index 1
};

//initalization data, required to start machine
struct __attribute__((__packed__)) StartData{
    StartData(){}
    StartData(uint32_t m, uint8_t e, uint8_t t) : mills(m), endWellIndex(e), trayIndex(t){}
    uint32_t mills; //ms/w
    uint8_t endWellIndex;
    uint8_t trayIndex;
};

union __attribute__((__packed__)) StartDataSerialized{
    StartDataSerialized(){}
    StartDataSerialized(StartData v) : values(v){};
    StartData values;
    uint8_t bytes[sizeof(StartData)];
};


//EEPROM serializable data

struct __attribute__((__packed__)) CalibrationValues{
    CalibrationValues(){}
    //missing constructor as it shouldn't ever need initalization.
    //distance between wells
    int16_t WELL_DIST_X;
    int16_t WELL_DIST_Y;

    bool Y_END_DIR;
    bool X_END_DIR;
    //positions of the 8 trays on machine
    Tray trays[10];
};
union __attribute__((__packed__))  CalibrationValueSerialized{
    CalibrationValueSerialized(){}
    CalibrationValueSerialized(CalibrationValues v): values(v){};
    uint8_t bytes[sizeof(CalibrationValues)];
    CalibrationValues values;
};

struct __attribute__((__packed__)) updateData{
    updateData(){}
    updateData(bool r, bool c, bool t, bool cal): rowFinished(r), colFinished(c), trayFinished(t), calibrated(cal){};
    bool rowFinished;
    bool colFinished;
    bool trayFinished;
    bool calibrated;
};
union __attribute__((__packed__))  updateDataSerialized{
    updateDataSerialized(){};
    updateDataSerialized(updateData v) : values(v){}
    uint8_t bytes[sizeof(updateData)];
    updateData values;
};

struct __attribute__((__packed__)) setPos{
    setPos(){}
    setPos(uint32_t x, uint32_t y, bool s, bool h) : x(x), y(y), speed(s), home(h){}
    uint32_t x;
    uint32_t y;
    bool speed;
    bool home;
};
union __attribute__((__packed__)) setPosSerialized{
    setPosSerialized(){}
    setPosSerialized(setPos v) : values(v){}
    uint8_t bytes[sizeof(setPos)];
    setPos values;
};

struct __attribute__((__packed__)) expect{
    expect(){}
    expect(uint8_t c, bool r) : cmd(c), request(r) {
        if(cmd == CMD_CALIBRATION)
            bytes = sizeof(CalibrationValues);
        if(cmd == CMD_SETPOS)
            bytes = sizeof(setPos);
        if(cmd == CMD_STARTDATA)
            bytes = sizeof(StartData);
        if(cmd == CMD_UPDATE)
            bytes = sizeof(updateData);
    };
    expect(uint8_t c, uint32_t b, bool r) : bytes(b), cmd(c), request(r){};
    uint32_t bytes;
    uint8_t cmd;
    bool request;
};
union __attribute__((__packed__)) expectSerialized{
    expectSerialized(){}
    expectSerialized(expect v) : values(v){}
    uint8_t bytes[sizeof(expect)];
    expect values;

};
#endif

