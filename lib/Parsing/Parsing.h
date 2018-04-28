#if !defined PARSING_H
#define PARSING_H

/*
#include "Global.h"
#include <IMU.h>
#include <Status.h>

int sendErrorDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime);
int sendRandDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime);
int sendRestDataToTFR(char send_packet[], elapsedMillis currtime, elapsedMillis globtime);

/*
int determinePacketSize(int);
int newParse(char []);
void returnData(int, char []);
void sendAllDataToTFR();
//void sendPacket(char []);
//char[] createPacket(int);
/*EXAMPLE OF HOW THIS SHOULD BE USED, ALTERNATIVELY, PASS IT IN AND USE IT, BUT DONT RETRUN LIKE THIS, THERE IS UNDEFINED BEHAVIOR BEVAUSE OF SCOPING ISSUES
enum MethodDown {Fell, Tumbled, Unknown};

char *Who(MethodDown  value)
{
    switch (value)
    {
         case Fell:  return "Jack";
         case Tumbled: return "Jill";
         default : return (char *) NULL;
     }
}
*/



int read_packet(int readch, char *buffer, int len);

#define TRUE 1
#define FALSE 0
#define NULL 0

#endif
