#include <stdlib.h>
#include <stdio.h>
#include "libAlmondDBM.h"

enum deviceType{
 UnknownDeviceType = 0,
 TemperatureSensor = 1,
 WaterSensor = 2,
 FireSensor = 3,
 DoorSensor = 4,
 MoistureSensor = 5,  
 PressureSensor = 6,
 GasSensor = 7
};

enum type{
 DoorState = 1,
 WaterState = 2,
 GasState = 3,
 FireState = 4,
 Temperature = 5,
 Pressure = 6,
 Humidity = 7
};


struct deviceData {
    char id;
    int deviceType; //define some enumerations
    char name;
    char location;
    char manufacturer;
    int lastModifiedTime;
} Data;

struct dvPair {
    int type;
    int id; // to indicate the dvPair number
    char value[32];
} Pair;


int main()
{
    printf("-------MENU------\n\n");
    printf("------1.ADD------\n");
    printf("------2.DELETE---\n");
    printf("------3.EDIT-----\n");
    printf("------4.DEL ALL--\n\n");

    DEPOT* depot;
    DEPOT *dpopen(const char *name, int omode, int bnum);
    int dpput(DEPOT *depot, const char *kbuf, int ksiz, const char *vbuf, int vsiz, int dmode);
    char *dpget(DEPOT *depot, const char *kbuf, int ksiz, int start, int max, int *sp);
    depot = dpopen("DBM.bin",6,350);
    int sp = 11;
    printf("%s \n",dpget(depot,"0",1,0,11,&sp));

    printf("Enter the choice from MENU\n");
    int choice;
    scanf("%d",&choice);
    
    /*if(choice == 1)
    {
       printf("Enter the Device id\n");
       scanf("%d",&Data.id);*/

    dpclose(depot);
    return 0;
}
