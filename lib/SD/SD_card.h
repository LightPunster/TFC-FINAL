#ifndef _SD_H_
#define _SD_H_

#include "Global.h"
#include<SD.h>
#include<SPI.h>
#include <IMU.h>
#include <BMP085.h>
#include <Status.h>

using namespace std;

const int ChipSelectPin = BUILTIN_SDCARD;
#define SD_chipSelect BUILTIN_SDCARD
extern File myFile;


void sd_setup();
void sd_write(elapsedMillis current_time, elapsedMillis global_time);

#endif
