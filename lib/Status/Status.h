#ifndef _STATUS_H_
#define _STATUS_H_

#include "Global.h"
#include <IMU.h>
#include <BMP085.h>


struct status_set {
    bool liftoff = 0;
    bool burnout = 0;
    bool apogee = 0;
    bool falling = 0;
    bool emergency = 0;
    bool active_valves = 0;
    bool IMU_connected = 0;
    bool TFR_connected = 0; //doesn't need to sent to TFR, for internal decision making only
    bool TFC_L_connected = 0;
    bool TFC_R_connected = 0;
};
extern struct status_set status; //the struct holding the status of all systems


#define lift_check_T 50
#define burn_check_T 50
#define apo_check_T 50
#define fall_check_T 50
#define liftoff_Gforce_check 110 //gforce_check should be about 7 Gs, reduced sightly(125) to deal with weight problems
#define burnout_Gforce_check 10
#define apogee_velocity_check 2.5 //check should be about 2.5 m/s


//perform status check and update flags, will disbale control and trigger landing loop code when apogee has been reached, will activate emergency dump valve if given signal by ground, etc.
void status_liftoff(elapsedMillis T_sinceLiftoff);
void status_burnout(elapsedMillis T_sinceBurnout);
void status_apogee(elapsedMillis T_sinceApogee);
void status_falling(elapsedMillis T_sinceFalling);
void status_check();    //check the status struct sent by the TFR in the case of a power outage
void flight_plan();

#endif
