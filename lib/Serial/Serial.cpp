#include "Serial.h"

/*
    Serial.print("STATUS: ");
    int temp2 = ((status.TFC_1_connected) + (status.TFC_2_connected*2) + (status.TFC_3_connected*4));
    switch (temp2) {
        case 0:
            Serial.println("WARNING: ALL CONTROLLERS DOWN");
            break;
        case 1:
            Serial.println("WARNING: TFC2 AND TFC3 DOWN");
            break;
        case 2:
            Serial.println("WARNING: TFC1 AND TFC3 DOWN");
            break;
        case 3:
            Serial.println("WARNING: TFC3 DOWN");
            break;
        case 4:
            Serial.println("WARNING: TFC1 AND TFC2 DOWN");
            break;
        case 5:
            Serial.println("WARNING: TFC2 DOWN");
            break;
        case 6:
            Serial.println("WARNING: TFC1 DOWN");
            break;
        case 7:
            Serial.println("NOMINAL");
            break;
    }
}

*/

/*
void serialPrint(elapsedMillis current_time, elapsedMillis global_time) {

    Serial.print("GLOBAL TIME: ");
    Serial.print(global_time, DEC);
    Serial.print("\tCURRENT TIME: ");
    Serial.println(current_time, DEC);
    //Serial.println("");

    Serial.print("\tCURRENT STATE: ");

    //odd numbers mean that the emergency dump valve was triggered
    int temp1 = ((status.emergency) + (status.liftoff*2) + (status.burnout*4) + (status.apogee*8) + (status.falling*16));
    switch (temp1) {
        case 0:
            Serial.println("PAD");
            break;
        case 1:
            Serial.println("WARNING: emergency dump triggered on PAD");
            break;
        case 2:
            Serial.println("LIFTOFF");
            break;
        case 3:
            Serial.println("WARNING: emergency dump triggered after LIFTOFF");
            break;
        case 6:
            Serial.println("BURNOUT");
            break;
        case 7:
            Serial.println("WARNING: emergency dump triggered after BURNOUT");
            break;
        case 14:
            Serial.println("APOGEE");
            break;
        case 15:
            Serial.println("WARNING: emergency dump triggered after APOGEE");
            break;
        case 30:
            Serial.println("FALLING");
            break;
        case 31:
            Serial.println("WARNING: emergency dump triggered after FALLING");
            break;
        default:
            Serial.println("ERROR. INVALID SYSTEM STATE.");
    };

    Serial.print("SETPOINT: ");
    Serial.print(imu.direction_setpoint);
    Serial.print("\tLAST_SETPOINT: ");
    Serial.println(imu.last_setpoint);

    Serial.print("HOLDTIME: ");
    Serial.print(commands[current_command].hold_time);
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

    /*Serial.print("\t\tCONNECTIONS: ");
    int temp = (((TFC.IMU_connected)) + ((TFC.TFC_L_connected)*2) + ((TFC.TFC_R_connected)*4));
    switch (temp) {
        case 0:
            Serial.println("WARNING: NO devices are connected.");
            break;
        case 1:
            Serial.println("WARNING: The TFC_R is not connected.");
            break;
        case 2:
            Serial.println("WARNING: The TFC_L is not connected.");
            break;
        case 3:
            Serial.println("WARNING: The TFC_R and TFC_L are not connected.");
            break;
        case 4:
            Serial.println("WARNING: The IMU is not connected.");
            break;
        case 5:
            Serial.println("WARNING: The IMU and TFC_R are not connected.");
            break;
        case 6:
            Serial.println("WARNING: The IMU and TFC_L are not connected.");
            break;
        case 7:
            Serial.println("GOOD");
            break;
        default:
            Serial.println("ERROR");
            break;
    }*/

/*    Serial.println("IMU DATA");
    Serial.print("\tDIRECTION: ");
    Serial.print(imu.IMU_direction);
    Serial.print("\t\tROLL: ");
    Serial.println(imu.IMU_roll);

    Serial.print("\tPITCH: ");
    Serial.print(imu.IMU_pitch);
    Serial.print("\tYAW: ");
    Serial.println(imu.IMU_yaw);

    Serial.print("\t\tACCELERATION: ");
    Serial.print(imu.IMU_acceleration);
    Serial.print("\t\tVELOCITY: ");
    Serial.println(imu.IMU_velocity);

    Serial.print("\t\tDIRECTION SETPOINT: ");
    Serial.print(imu.direction_setpoint);
    Serial.print("\t\tLAST SETPOINT: ");
    Serial.println(imu.last_setpoint);

    Serial.print("\t\tERROR: ");
    Serial.print(imu.error);
    Serial.print("\t\tLAST_ERROR: ");
    Serial.println(imu.last_error);

    Serial.print("\t\tINTEGRAL_ERROR: ");
    Serial.print(imu.integral_error);
    Serial.print("\tOMEGA_READING: ");
    Serial.println(imu.omega_Reading);


    Serial.print("\t\tD_ERROR: ");
    Serial.print(imu.d_error);
    Serial.print("\t\tINST AVG ERROR");
    Serial.println(imu.inst_avg_error);

    Serial.print("\t\tTHIS TIME: ");
    Serial.print(imu.this_time);
    Serial.print("\t\tLAST TIME");
    Serial.println(imu.last_time);

    Serial.println("BMP DATA");
    Serial.print("\t\tALTITUDE: ");
    Serial.print(bmp.altitude);
    Serial.print("\t\tMAX ALTITUDE");
    Serial.println(bmp.max_altitude);

    Serial.print("\t\tPRESSURE: ");
    Serial.print(bmp.pressure);
    Serial.print("\t\tTEMPERATURE: ");
    Serial.println(bmp.temperature);
}*/
