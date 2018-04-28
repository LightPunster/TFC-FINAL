#include "BMP085.h"


void bmpSetup()
{
    //bmp180.begin();
    if(getPressure()){
      baseline=bmpValues[1];
    }
}


void bmpData() {
    if(getPressure()){
      bmp.altitude = bmp180.altitude(bmpValues[1],baseline);
      bmp.temperature = bmp180.getTemperature(bmpValues[0]);
      bmp.pressure = bmp180.getPressure(bmpValues[1],bmpValues[0]);
    }
}

/*IMU_altitude = baro.getAltitude();
if(IMU_altitude >= IMU_Max_altitude){
  IMU_Max_altitude = IMU_altitude;
}
*/

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
