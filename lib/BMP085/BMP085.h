#ifndef BMP085_H
#define BMP085_H

#include <Global.h>
#include <Teensy_BMP180.h>

//static double baseline;
//static double bmpValues[2]; //0: Temperature, 1:Pressure
static Teensy_BMP180 bmp180(&Wire1);

struct bmp_data {
    float max_altitude;
    float altitude;
    float pressure;
    float temperature;
    float baseline;
};
extern struct bmp_data bmp;


void bmpSetup();
void bmpData();
bool getPressure();

#endif
