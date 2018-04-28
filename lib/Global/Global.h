#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <Arduino.h>
#include "SoftwareSerial.h"
#include "elapsedMillis.h"

#define wait_time 2000
#define log_period_T 100

#define valve_dump 4
#define valve_cw 5
#define valve_ccw 6
static float cw_pwm_Duty;
static float ccw_pwm_Duty;


static elapsedMillis T_sinceApogee;
static elapsedMillis T_sinceFalling;

static elapsedMillis T_sinceLogged;
static elapsedMillis T_statuscheck;
static elapsedMillis T_sinceStart;
static elapsedMillis T_sinceEmergency;

//used in the control function
static elapsedMillis T_sinceControl;
static elapsedMicros T_sincePulsed;
static elapsedMicros T_sinceHold;
static elapsedMicros T_lastTime;


enum cardinal_direction {
    North = 0,
    South = 180,
    East = 90,
    West = 270
};


struct command {
    cardinal_direction setpoint;
    unsigned int hold_time;       //unsigned to make sure that time in microseconds fits
    bool roll_direction;   //0 clockwise, 1 counterclockwise
    bool is_done; //marked off if the command has been executed
};
const int MAX_NUM_COMMANDS = 5; //max number of commands
extern int current_command; //array index number, incremented in control algorithm
extern struct command commands[MAX_NUM_COMMANDS]; //use array called commands to access current command from list of them

#endif
