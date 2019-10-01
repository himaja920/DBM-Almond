#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libAlmondDBM.h"
#define SIZE 120

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
    int id;
    int deviceType; //define some enumerations
    char name[30];
    char location[30];
    char manufacturer[30];
    int lastModifiedTime;
} ;

struct dvPair {
    int type;
    int id; // to indicate the dvPair number
    char value[20];
} ;


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
    int sp =1;
   
    depot = dpopen("DBM.bin",22,25600);
    int rec  = dprnum(depot);
    printf(" records of depot is  %d\n",rec);
    int use = dpbusenum(depot);
    printf("used elements in record : %d\n",use);

    if(choice == 1)
     {
        depot = dpopen("DBM.bin",22,25600);
        if(depot==NULL)
          { printf("File not created\n");}
        else 
            printf("File created\n");

        printf("Enter the Device ID\n");
        scanf("%d",&Data.id);
       
        printf("Enter the Device Type\n");
        scanf("%s",&Data.deviceType);
       
        printf("Enter the Device data\n");
        scanf("%s %s %s",&Data.name,&Data.location,&Data.manufacturer);
       
        char buf[100];
        char *d = new char[1];
        sprintf(d,"%d",Data.deviceType);
        strcpy(buf,d);
        strcat(buf,Data.name);
        strcat(buf,Data.location);
        strcat(buf,Data.manufacturer);
        time_t t =  dpmtime(depot);
        printf("Last modified time is %d\n",t);
        char *tt = new char[10];
        sprintf(tt,"%ld",t);
        strcat(buf,tt);
             
        char *id = new char[1];
        sprintf(id,"%d",Data.id);
        printf("id is %s\n",id);
       
        int k = dpput(depot,id,1,buf,97,DP_DCAT);
        printf("k is %d\n",k);     
       
        char i;
        printf("Enter the value count\n");
        scanf("%d",&pair.id);
        printf("%d\n",&pair.id);
        int h = pair.id;
        printf("%d \n",h);
        for(i = 0; i <= h;i++)
        {        
          char *s = new char[2];
          strcpy(s,id);
          strcat(s,".");
          char * b = new char[1];
          sprintf(b,"%d",i);
          strcat(s,b);
          printf(" s is %s\n",s);
         
          printf("Enter the pair value\n");
          scanf("%s",&pair.value);
                
          char buffer[100];
          printf("Enter the type\n"); 
          scanf("%d",pair.type);
         
          char *c = new char[1];
          sprintf(c,"%d",pair.type);
          strcpy(buffer,c);
          strcat(buffer,pair.value);
          
          k = dpput(depot,s,1,buffer,100,DP_DCAT);
          printf("k is %d\n",k);
        }
         printf("Buffer is %s\n",buf);
         int size = dpvsiz(depot, id, 1);
         printf("Size of the entered record is %d\n",size);        
     }   
     else if (choice == 2)
     {
          printf("Enter the Device id to be deleted\n");
          scanf("%d",&Data.id);
          char *id = new char[1];
          sprintf(id,"%d",Data.id);
          depot = dpopen("DBM.bin",2,25600);//2 is only writing
          int d = dpout(depot,id,1);
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
          depot = dpopen("DBM.bin",18,25600);
          int sp = 10,s,l;
          printf("Enter the device id\n");
          scanf("%d",&Data.id);
          char *b = new char[1];
          sprintf(b,"%d",Data.id);
         
          printf("Previous record is %s\n",dpsnaffle("DBM.bin",b,1,&sp));//'sp' specifies the pointer to a variable to which the size of the region of the return value is assigned         

          printf("Enter the device data\n");
          scanf("%d %s %s %s %d",&Data.deviceType,&Data.name,&Data.location,&Data.manufacturer,&Data.lastModifiedTime);
          
          char buf[100];
          char *d = new char[1];
          sprintf(d,"%d",&Data.deviceType);
          strcpy(buf,d);
          strcat(buf,Data.name);
          strcat(buf,Data.location);
          strcat(buf,Data.manufacturer);
          char *a = new char[10];
          sprintf(a, "%d", &Data.lastModifiedTime); 
          strcat(buf,a);
          l = dpput(depot,b,1,buf,97,DP_DOVER);
          printf(" l is %d\n",l);

          printf("Enter the device value pair to be edited\n");
          float p;
          scanf("%f",&p);

          char *st = new char[2];
          char buffer[100];
          sprintf(st,"%f",p);

          printf("Previous key value pairs are %s\n",dpsnaffle("DBM.bin",st,1,&sp));
      } 
       else if(choice == 4)
       {
          depot = dpopen("DBM.bin",2,25600);//2 is only writing
          int i; int d,c=0;
          
          for(i = 1; i<=rec;i++)
          {
             char *a = new char[1];
             sprintf(a,"%d",i);
             d = dpout(depot,a,1);
             printf("d is %d\n",d);
          }       
       }     
    dpclose(depot);
    return 0;
}
  
  
