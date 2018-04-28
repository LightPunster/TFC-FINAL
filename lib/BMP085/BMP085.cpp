#include "BMP085.h"


void bmpSetup()
{
    //bmp180.begin();
    if(getPressure()){
      bmp.baseline = bmp.pressure;
    }
}


void bmpData() {
    if(getPressure()){
      bmp180.altitude();
      bmp180.getTemperature();
      bmp180.getPressure();
    }
}

/*IMU_altitude = baro.getAltitude();
if(IMU_altitude >= IMU_Max_altitude){
  IMU_Max_altitude = IMU_altitude;
}
*/
/*
bool getPressure() {
  if (bmp180.startTemperature() != 0)
  {
    if (bmp180.getTemperature(bmpValues[0]) != 0)
    {
      if (bmp180.startPressure() != 0)
      {
        if (bmp180.getPressure(bmpValues[1],bmpValues[0]) != 0)
        {
          return(1);
        }
      }
    }
  }
  return 0;
}
*/
