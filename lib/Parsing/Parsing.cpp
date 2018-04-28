#include "Parsing.h"

/*
using namespace std;
#include <String.h>





int sendErrorDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime){
  send_packet[0] = 'E';
  send_packet[1] = 'A';
  send_packet[2] = '2';
  send_packet[3] = '1';
  int count = 4;
  int pTime = globtime;
  char anatoly[9];
  itoa(pTime, anatoly, 10);
  int timeCount = 0;
  while (anatoly[timeCount] != '\0'){
    send_packet[count] = anatoly[timeCount];
    timeCount++;
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  float roll = data.IMU_roll;
  char rollHolder[6];
  int what = snprintf(rollHolder, 6, "%f", roll);
  float derror = data.d_error;
  char derrorHolder[6];
  what = snprintf(derrorHolder, 6, "%f", derror);
  float error = data.error;
  char errorHolder[6];
  what = snprintf(errorHolder, 6, "%f", error);
  float lastError = data.last_error;
  char lerrorHolder[6];
  what = snprintf(lerrorHolder, 6, "%f", lastError);
  float intError = data.integral_error;
  char interrorHolder[6];
  what = snprintf(interrorHolder, 6, "%f", intError);
  float set = data.direction_setpoint;
  char setHolder[6];
  what = snprintf(setHolder, 6, "%f", set);
  float lastset = data.last_setpoint;
  char lastsetHolder[6];
  what = snprintf(lastsetHolder, 6, "%f", lastset);
  for (int i = 0; i < 6; i++){
    send_packet[count] = rollHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = derrorHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = errorHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = lerrorHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for(int i = 0; i < 6; i++){
    send_packet[count] = interrorHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = setHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = lastsetHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  send_packet[count] = '\r';
  int counter = 0;
  int size = 0;
  while (send_packet[counter] != '\r'){
    size++;
    counter++;
  }
}

int sendRandDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime){
  send_packet[0] = 'R';
  send_packet[1] = 'A';
  send_packet[2] = '2';
  send_packet[3] = '1';
  int count = 4;
  int pTime = globtime;
  char anatoly[9];
  itoa(pTime, anatoly, 10);
  int timeCount = 0;
  while (anatoly[timeCount] != '\0'){
    send_packet[count] = anatoly[timeCount];
    timeCount++;
    count++;
  }
  count++;
  send_packet[count] = ',';
  float velocity = data.IMU_velocity;
  char velHolder[6];
  int what = snprintf(velHolder, 6, "%f", velocity);
  float pressure = data.IMU_pressure;
  char pressHolder[6];
  what = snprintf(pressHolder, 6, "%f", pressure);
  float altitude = data.IMU_altitude;
  char altHolder[6];
  what = snprintf(altHolder, 6, "%f", altitude);
  float acceleration = data.IMU_acceleration;
  char accelHolder[6];
  what = snprintf(accelHolder, 6, "%f", acceleration);
  float temp = data.IMU_temperature;
  char tempHolder[6];
  what = snprintf(tempHolder, 6, "%f", temp);
  float omegaRead = data.omega_Reading;
  char omegaHolder[8];
  what = snprintf(omegaHolder, 8, "%f", omegaRead);
  for (int i = 0; i < 6; i++){
    send_packet[count] = velHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = pressHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = altHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = accelHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for(int i = 0; i < 6; i++){
    send_packet[count] = tempHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = omegaHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  send_packet[count] = '\r';
  int size = 0;
  int counter = 0;
  while (send_packet[counter] != '\r'){
    size++;
    counter++;
  }
}

int sendRestDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime){
  send_packet[0] = 'L';
  send_packet[1] = 'A';
  send_packet[2] = '2';
  send_packet[3] = '1';
  int count = 4;
  int pTime = globtime;
  char anatoly[9];
  itoa(pTime, anatoly, 10);
  int timeCount = 0;
  while (anatoly[timeCount] != '\0'){
    send_packet[count] = anatoly[timeCount];
    timeCount++;
    count++;
  }
  count++;
  send_packet[count] = ',';
  int elTime = currtime;
  char anatoly1[9];
  itoa(elTime, anatoly1, 10);
  int timeCount1 = 0;
  while (anatoly1[timeCount1] != '\0'){
    send_packet[count] = anatoly1[timeCount1];
    timeCount1++;
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  int holdTime = commands[current_command].Hold_time;
  char anatoly2[9];
  itoa(holdTime, anatoly2, 10);
  int timeCount2 = 0;
  while (anatoly2[timeCount2] != '\0'){
    send_packet[count] = anatoly2[timeCount2];
    timeCount2++;
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  float yaw = data.IMU_yaw;
  char yawHolder[6];
  int what = snprintf(yawHolder, 6, "%f", yaw);
  float pitch = data.IMU_pitch;
  char pitchHolder[6];
  what = snprintf(pitchHolder, 6, "%f", pitch);
  bool rollD = commands[current_command].roll_direction;
  char rollDHolder;
  if(rollD)
    rollDHolder = 'T';
  else
    rollDHolder = 'F';
  float direction = data.IMU_direction;
  char directHolder[6];
  what = snprintf(directHolder, 6, "%f", direction);
  for (int i = 0; i < 6; i++){
    send_packet[count] = yawHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = pitchHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  for (int i = 0; i < 6; i++){
    send_packet[count] = directHolder[i];
    count++;
  }
  count++;
  send_packet[count] = ',';
  count++;
  send_packet[count] = rollDHolder;
  count++;
  send_packet[count] = ',';
  count++;
  send_packet[count] = '\r';
  int size = 0;
  int counter = 0;
  while (send_packet[counter] != '\r'){
    size++;
    counter++;
  }
}


/*
takes an incoming character (provided by Serial.read()), and decides what to do with it
     - If new line character (‘\n’), then ignored and thrown away
     - If carriage return, then message complete, return number of characters in message
     - If other, add the character to the buffer (if there’s room)
*/

int read_packet(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}
