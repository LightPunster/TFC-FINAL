#include "Global.h"
struct command commands[MAX_NUM_COMMANDS];
int current_command = 0;

#include <BMP085.h>
struct bmp_data bmp;

#include <IMU.h>
MPU9250 imu_sensor;
struct imu imu_data;

#include <Serial.h>

#include <Status.h>
struct status_set status; //the struct holding the status of all systems

#include <Control.h>
float pwm_Duty;

void control();
void data_log(elapsedMillis current_time, elapsedMillis global_time);
void declarations();
void emergency_dump();
void print_stuff(elapsedMillis current_time, elapsedMillis global_time);

void setup() {
    declarations();  //found in other
    flight_plan();

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
    bmp_get_data();
    imu_get_data();

    control();

    if(pwm_Duty > 0) {
        digitalWrite(valve_cw, (T_sincePulsed <= (1000000*pwm_Duty*pwm_period)));
    } else if(pwm_Duty < 0) {
        digitalWrite(valve_ccw, (T_sincePulsed <= (-1000000*pwm_Duty*pwm_period)));
    } else {
        digitalWrite(valve_cw, LOW);
        digitalWrite(valve_ccw, LOW);
    }

    T_sinceEmergency = 0;
    while(status.emergency) {
        emergency_dump();
        data_log(T_sinceEmergency, T_sinceStart);
    }

    //digitalWrite(valve_cw, !(T_sincePulsed <= (Control_period*cw_pwm_Duty)));
    //digitalWrite(valve_ccw, !(T_sincePulsed <= (Control_period*ccw_pwm_Duty)));
}



//Perform the neccessary control functions:
//                                       navigate to the desired point or control roll
//                                       hold current position
//                                       iterate to the next command when conditions met
void control() {
    if (T_sincePulsed >= Control_period) {
        print_stuff(T_sinceControl, T_sinceStart); //remove this later

        if (imu_data.error <= Allowed_error) {
            if (T_sinceHold <= commands[current_command].hold_time) { //hold if we have not yet held for the appropriate elength of time
                control_hold(&imu_data);
                T_sincePulsed = T_sincePulsed - Control_period;
            }
            else { //iterate to the next command and reset the timing variables
                T_sincePulsed = Control_period;
                T_sinceHold = 0;
                current_command++;
            }
        }
        else {  //actuate if the error is greater than the error allowed to satisfy conditions
            control_actuate(&imu_data);
            T_sincePulsed = T_sincePulsed - Control_period;
            T_sinceHold = 0;
        }
        T_sinceControl = 0;
    }
}


void data_log(elapsedMillis current_time, elapsedMillis global_time) {

}

void declarations() {
    Serial.begin(2000000); //the fastest "safest" baud rate Teensy 3.6 can handle according to documentation

    /*pinMode(SD_chipSelect, OUTPUT);
    if(!SD.begin(SD_chipSelect)) {
        Serial.println("initialization failed");
    }
    sd_setup();*/

    //TFR.begin(2000000);    //increase the baud rate, check math

    imu_sensor_setup();

    bmp180.begin();
    bmpSetup();

    pinMode(valve_cw, OUTPUT);
    pinMode(valve_ccw, OUTPUT);
    pinMode(valve_dump, OUTPUT);
}


void emergency_dump() {
    digitalWrite(valve_dump, HIGH);
}


void print_stuff(elapsedMillis current_time, elapsedMillis global_time) {
    Serial.print("GLOBAL TIME: ");
    Serial.print(((global_time)/1000), DEC);
    Serial.print("\tCURRENT TIME: ");
    Serial.println(((current_time)/1000), DEC);
    //Serial.println("");


    Serial.print("SETPOINT: ");
    Serial.println(commands[current_command].setpoint);
    //Serial.print("\tLAST_SETPOINT: ");
    //Serial.println(imu.last_setpoint);

    Serial.print("HOLDTIME: ");
    Serial.print((commands[current_command].hold_time)/1000);
    Serial.print("\tROLL_DIRECTION: ");
    if(commands[current_command].roll_direction == 1) {
        Serial.println("CLOCKWISE");
    } else {
        Serial.println("COUNTERCLOCKWISE");
    }

    Serial.print("UPDATES: ");
    if(commands[current_command].is_done) {
        Serial.println("OBJECTIVE COMPLETE");
    } else if(status.active_valves) {
        Serial.println("ACTIVE VALVES");
    } else {
        Serial.println("");
    }

    Serial.println("IMU DATA");
    Serial.print("\tAcceleraton: ");
    Serial.print(imu_data.aSqrt);
    Serial.print("\t\tmDirection: ");
    Serial.println(imu_data.mDirection);

    Serial.print("\taX: ");
    Serial.print(imu_data.aX);
    Serial.print("\taZ: ");
    Serial.print(imu_data.aZ);
    Serial.print("\taY: ");
    Serial.println(imu_data.aY);

    //Serial.print("\t\tVELOCITY: ");
    //Serial.println(imu.IMU_velocity);

    Serial.print("\tgX: ");
    Serial.print(imu_data.gX);
    Serial.print("\t\tgY: ");
    Serial.print(imu_data.gY);
    Serial.print("\t\tgZ: ");
    Serial.println(imu_data.gZ);

    Serial.print("\tmX: ");
    Serial.print(imu_data.mX);
    Serial.print("\t\tmY: ");
    Serial.print(imu_data.mY);
    Serial.print("\t\tmZ: ");
    Serial.println(imu_data.mZ);

    Serial.print("\tERROR: ");
    Serial.print(imu_data.error);
    Serial.print("\t\tD_Error: ");
    Serial.println(imu_data.d_error);

    Serial.print("\tOMEGA_Z: ");
    Serial.print(imu_data.omega_z);
    Serial.print("\t\tOMEGA_Z_0: ");
    Serial.println(imu_data.omega_z_0);

    Serial.print("\tD_ERROR: ");
    Serial.print(imu_data.d_error);
    //Serial.print("\t\tINST AVG ERROR");
    //Serial.println(imu_data.);

    Serial.print("\t\tTHIS TIME: ");
    Serial.print(imu_data.this_time*.001);
    Serial.print("\t\tLAST TIME: ");
    Serial.println(imu_data.last_time*.001);

    /*Serial.println("BMP DATA");
    Serial.print("\t\tALTITUDE: ");
    Serial.print(bmp.altitude);
    Serial.print("\t\tMAX ALTITUDE");
    Serial.println(bmp.max_altitude);

    Serial.print("\t\tPRESSURE: ");
    Serial.print(bmp.pressure);
    Serial.print("\t\tTEMPERATURE: ");
    Serial.println(bmp.temperature);*/

}



///////////////////////////////////////////////////////////////////////////////////////////

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
}



void loop() {

    if((!status.apogee) && (!status.falling)) {
        status_apogee(T_sinceApogee);
        status_falling(T_sinceFalling);
        data_log(T_sinceControl, T_sinceStart);
    } else {
        emergency_dump();
        data_log(T_sinceApogee, T_sinceStart);
    }
//}

/*


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
