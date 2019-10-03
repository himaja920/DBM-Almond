#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libAlmondDBM.h"

#define DBSIZE 25600
#define ADD 22
#define DEL 2
#define EDIT 18
#define BUFSIZE 113

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

enum DD {
ID = 0,
TYPE = 1,
NAME = 2,
LOCATION = 3,
MANUFACTURER =4,
TIME = 5
};

struct deviceData {
    int id;
    int deviceType; //define some enumerations
    char name[32];
    char location[32];
    char manufacturer[32];
    int lastModifiedTime;
} ;

struct dvPair {
    int type;
    int id; // to indicate the dvPair number
    char value[20];
};


int main()
{
    printf("-------MENU------\n\n");
    printf("------1.ADD------\n");
    printf("------2.DELETE---\n");
    printf("------3.EDIT-----\n");
    printf("------4.DEL ALL--\n\n");

    deviceData Data;
    dvPair pair;
    DEPOT* depot ;
   
       
    printf("Enter the choice from MENU\n");
    int choice;
    scanf("%d",&choice);
    int sp =1,k;
   
    depot = dpopen("DBM.bin",ADD,DBSIZE);
    int rec  = dprnum(depot);
    printf(" records of depot is  %d\n",rec);
    int use = dpbusenum(depot);
    printf("used elements in record : %d\n",use);
    
    if(choice == 1)
     {
        depot = dpopen("DBM.bin",ADD,DBSIZE);
        if(depot==NULL)
          { printf("File not created\n");}
        else 
            printf("File created\n");      
        printf("Enter the Device data\n");
        scanf(" %d",&Data.id);
        
        printf("Enter the Device type\n");
        scanf("%d",&Data.deviceType);
        printf("Enter the Device name\n");
        scanf("%s",&Data.name);
        printf("Enter the Device location\n");
        scanf("%s",&Data.location);
        printf("Enter the Device manufacturer\n");
        scanf("%s",&Data.manufacturer);
       
        char *id = new char[3];
        sprintf(id,"%d",Data.id);
        printf("id is %s\n",id);
      
        time_t tt = dpmtime(depot);
        Data.lastModifiedTime = tt;
        
        char buf[BUFSIZE] ;
        snprintf( buf,BUFSIZE, "%d %s %s %s %d",Data.deviceType, Data.name,Data.location, Data.manufacturer,Data.lastModifiedTime);
      
        printf("buf is %s\n",buf);
        k = dpput(depot,id,1,buf,-1,DP_DCAT);
        printf("k is %d\n",k); 

        delete(id);
        
        printf("Enter the value count\n");
        scanf("%d",&pair.id);
        printf("%d\n",&pair.id);
        int h = pair.id,i;
        printf("%d \n",h);
        for(i = 0; i <= h;i++)
        {        
          char *s = new char[7];
          snprintf(s,7,"%d.%d",Data.id,i);
          printf("Key value is %s\n",s);
          printf("Enter the type\n"); 
          scanf("%d",&pair.type);

          printf("Enter the pair value\n");
          scanf("%s",&pair.value);
                
          char buffer[BUFSIZE];
          
          snprintf(buffer,BUFSIZE," %d  %d  %s ",pair.type,i,pair.value); 
          printf("Buffer is %s\n",buffer);         
          k = dpput(depot,s,1,buffer,-1,DP_DCAT);
          printf("k is %d\n",k);
          delete(s);
        }      
     }   
     else if (choice == 2)
     {
          printf("Enter the Device id to be deleted\n");
          scanf("%d",&Data.id);
          char *id = new char[3];
          sprintf(id,"%d",Data.id);
          depot = dpopen("DBM.bin",DEL,DBSIZE);//2 is only writing
          int d = dpout(depot,id,1);
          delete(id);
          printf(" d is %d\n",d);
          if(d == 0)
          {
            printf("Record not deleted\n");
          }
          else
           printf("Deleted successfully a record\n");
     }
 
     else if(choice == 3)
     {
          depot = dpopen("DBM.bin",EDIT,DBSIZE);
          int i,l,start,max;
          char *k = new char[3];
          char *o = new char[3];
          printf("Records present in the database :\n");
          for(i = 1; i<=rec;i++)
          {
             snprintf(o,3,"%d",i);
             printf("Device ID %d : %s\n",i,dpsnaffle("DBM.bin",o,1,&sp));
          }
          printf("Enter the device id to be edited \n");
          scanf("%d",&Data.id);
          char *b = new char[3];
          sprintf(b,"%d",Data.id);

          char buffer[BUFSIZE] = {0};
          
          printf("Enter the attribute id to be edited\n"); 
          int id;
          scanf("%d",&id);
          if(id == TYPE)
          {
             printf("Enter the new device Type\n");
             scanf("%d",&Data.deviceType);
             snprintf(k,sizeof(Data.deviceType),"%d",Data.deviceType);
             printf("Enter the starting and max values\n");
             scanf("%d %d",&start,&max);
             l = dpgetwb(depot,b,-1,start,max,k);
             printf("l is %d\n",l);
          }
          else 
              printf("NOt done\n");  
           delete(b);
           delete(k);
           delete(o);  
      }     
       else if(choice == 4)
       {
          depot = dpopen("DBM.bin",DEL,DBSIZE);//2 is only writing
          int i; int d;
         
          for(i = 1; i<=rec;i++)
          {
             char *a = new char[3];
             sprintf(a,"%d",i);
            
             d = dpout(depot,a,1);
             printf("d for %d is %d\n",i,d);
             delete(a); 
          } 
       }         
    dpclose(depot);
    return 0;
}
  
  
