#include "Global.h"
struct command commands[MAX_NUM_COMMANDS];
int current_command = 0;

#include <BMP085.h>
struct bmp_data bmp;

#include <IMU.h>
//MPU9250_DMP imu_sensor;
//IMU_data imu;


void declarations();



void setup() {
    declarations();  //found in other
}

void loop() {
    // put your main code here, to run repeatedly:
}


void declarations() {
    Serial.begin(2000000); //the fastest "safest" baud rate Teensy 3.6 can handle according to documentation

    /*pinMode(SD_chipSelect, OUTPUT);
    if(!SD.begin(SD_chipSelect)) {
        Serial.println("initialization failed");
    }
    sd_setup();*/

    //TFR.begin(2000000);    //increase the baud rate, check math

    //while (imu.begin() != INV_SUCCESS) {
    //  Serial.println("IMU error");
    //  delay(100);
    //}

    bmp180.begin();
    bmpSetup();

    pinMode(valve_cw, OUTPUT);
    pinMode(valve_ccw, OUTPUT);
    pinMode(valve_dump, OUTPUT);
}


/*
#include <Control.h>

//#include <Other.h>

#include <Parsing.h>

#include <SD_card.h>
File myFile;

#include <Serial.h>

#include <Status.h>
struct status_set status;

//SoftwareSerial TFR(7, 8);  //serial to TFR


void data_log(elapsedMillis current_time, elapsedMillis global_time);
void emergency_dump();
void control();
void getData();



void setup() {
    flight_plan();//construct the flight plan before launch


    //the preflight loop, runs until liftoff
    elapsedMillis T_preLiftoff = 0;
    elapsedMillis T_sinceLiftoff = 0;
    while(!status.liftoff) {
        //imu.updateDirection();
        data_log(T_preLiftoff, T_sinceStart);
        status_liftoff(T_sinceLiftoff);
    }


    //launch has occured, runs until burnout
    elapsedMillis T_sinceBurnout = 0;
    while(!status.burnout) {
        data_log(T_sinceLiftoff, T_sinceStart);
        status_burnout(T_sinceBurnout);
    }

    //wait for two seconds before moving on to the main control loop(contest rules)
    while(T_sinceBurnout < wait_time) {
        data_log(T_sinceBurnout, T_sinceStart);
    }


    //do these to setup for loop functions after burnout wait period
    T_sinceControl = 0;
    T_sincePulsed = Control_period;
    T_sinceHold = 0;
    //T_currentTime = 0;
    T_lastTime = 0;
    T_sinceApogee = 0;
    T_sinceFalling = 0;
}



void loop() {

    imuData();
    bmpData();

    if((!status.apogee) && (!status.falling)) {
        control();
        digitalWrite(valve_cw, !(T_sincePulsed <= (Control_period*cw_pwm_Duty)));
        digitalWrite(valve_ccw, !(T_sincePulsed <= (Control_period*ccw_pwm_Duty)));

        status_apogee(T_sinceApogee);
        status_falling(T_sinceFalling);
        data_log(T_sinceControl, T_sinceStart);
    } else {
        emergency_dump();
        data_log(T_sinceApogee, T_sinceStart);
    }

    /*T_sinceEmergency = 0;
    while(status.emergency) {
        emergency_dump();
        data_log(T_sinceEmergency, T_sinceStart);
    }*/
//}

/*

void emergency_dump() {
    digitalWrite(valve_dump, HIGH);
}


//Perform the neccessary control functions:
//                                       navigate to the desired point or control roll
//                                       hold current position
//                                       iterate to the next command when conditions met
void control() {
    if (T_sincePulsed >= Control_period) {
        if (imu.error <= Allowed_error) {
            if (T_sinceHold <= commands[current_command].hold_time) { //hold if we have not yet held for the appropriate elength of time
                control_hold(&imu);
                T_sincePulsed = T_sincePulsed - Control_period;
            }
            else { //iterate to the next command and reset the timing variables
                T_sincePulsed = Control_period;
                T_sinceHold = 0;
                current_command++;
            }
        }
        else {  //actuate if the error is greater than the error allowed to satisfy conditions
            control_actuate(&imu);
            T_sincePulsed = T_sincePulsed - Control_period;
            T_sinceHold = 0;
        }
    }
}


void getData() {
    imuData();
    bmpData();
}


void data_log(elapsedMillis current_time, elapsedMillis global_time) {

    getData();

    if(T_sinceLogged >= log_period_T) {
        sd_write(current_time, global_time);
        serialPrint(current_time, global_time);
        T_sinceLogged = 0;
    }*/

    /*static char receive_packet[64];
    static int receive_size = 0;

    char sendRand[56];
    int size_Rand = 0;
    char sendError[61];
    int size_Error = 0;
    char sendRest[53];
    int size_Rest = 0;

    if(TFR.peek() > 0) {
        receive_size = read_packet(TFR.read(), receive_packet, 64);
        if(receive_size > 0) {
            //newParse(receive_packet);
            status_check();
            //add either function, loop, or make sure parsing code zeroes out the packet after reading it????
        }
    }

    //this is true if it is time to write to SD and send to TFR
    if (T_sinceLogged >= log_period_T) {
        data.IMU_all_data(); //called to get all IMU data points to send to the TFR and write to SD

        size_Error = sendErrorDataToTFR(sendError, current_time, global_time);
        TFR.flush();    //should never have to run, but acts as a stopgap to prevent overflow issues
        for(size_Error; size_Error >= 0; size_Error--) {
            TFR.print(sendError[size_Error]);
            Serial.print(sendError[size_Error]);
            Serial.print("TEST");
        }

        sd_write(); //put here to give time after the largest char array of data is sent

        size_Rand = sendRandDataToTFR(sendRand, current_time, global_time);
        TFR.flush();    //should never have to run, but acts as a stopgap to prevent overflow issues
        for(size_Rand; size_Rand >= 0; size_Rand--) {
            TFR.print(sendRand[size_Rand]);
        }

        size_Rest = sendRestDataToTFR(sendRest, current_time, global_time);
        TFR.flush();    //should never have to run, but acts as a stopgap to prevent overflow issues
        for(size_Rest; size_Rest >= 0; size_Rest--) {
            TFR.print(sendRest[size_Rest]);
        }

        T_sinceLogged = 0;
    }*/
//}
//*/
