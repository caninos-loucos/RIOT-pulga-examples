#include "l86.hpp"
#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include <errno.h>

#ifdef DEBUGGER
//RawSerial pc2(USBTX, USBRX);    // USART2
//extern RawSerial pc;
#endif

/* Parse NMEA RMC sentence into RMC data struct */
RMC_data Parse_RMC_sentence(char RMC_sentence[MAX_NMEA_LENGTH]){
    const char delimeter[2] = ",";
    const char *token = "";
    int i = 0;
    char temp[11][12];          /* [11][12]: 11 strings, of length 12 */
    RMC_data RMC_parsed;
    
    strcpy(RMC_parsed.Message, RMC_sentence);
    
    //Seperated Message
    /* get the first token */
   token = strtok(RMC_sentence, delimeter);
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
         strcpy(temp[i],token);
         i++;
     token = strtok(NULL, delimeter);
   }
     
    //Copy the message into its individual components
    strcpy(RMC_parsed.Message_ID,temp[0]);
    strcpy(RMC_parsed.UTC_Time,temp[1]);
    strcpy(RMC_parsed.Status,temp[2]);
    if(strcmp(RMC_parsed.Status,"A") == 0){
        strcpy(RMC_parsed.Latitude,temp[3]);
        strcpy(RMC_parsed.N_S_Indicator,temp[4]);
        strcpy(RMC_parsed.Longitude,temp[5]);
        strcpy(RMC_parsed.E_W_Indicator,temp[6]);
        strcpy(RMC_parsed.Speed_Over_Ground,temp[7]);
        strcpy(RMC_parsed.Course_Over_Ground,temp[8]);
        strcpy(RMC_parsed.Date,temp[9]);
        strcpy(RMC_parsed.Mode,temp[10]);
    }
    return RMC_parsed;
}

// Use GPS data parse function? // parses into data formats that will be sent over LoRa

/* Print RMC_data struct to pc USART for debugging 
void Print_RMC_data(RMC_data *RMC_data_print){
    pc.printf("RMC_Message: %s",RMC_data_print->Message);
    pc.printf("UTC_Time: %s\r\n",RMC_data_print->UTC_Time);
    pc.printf("Status: %s\r\n",RMC_data_print->Status);
    if(strcmp(RMC_data_print->Status,"A") == 0){
        pc.printf("Latitude: %s\r\n",RMC_data_print->Latitude);
        pc.printf("N/S: %s\r\n",RMC_data_print->N_S_Indicator);
        pc.printf("Longitude: %s\r\n",RMC_data_print->Longitude);
        pc.printf("E/W: %s\r\n",RMC_data_print->E_W_Indicator);
        pc.printf("Speed: %s\r\n",RMC_data_print->Speed_Over_Ground);
        pc.printf("Course: %s\r\n",RMC_data_print->Course_Over_Ground);
        pc.printf("Date: %s\r\n",RMC_data_print->Date);
        pc.printf("Mode: %s\r\n",RMC_data_print->Mode);
    }
}
*/

/* Parse RMC_data struct into GPS data struct ready for sending over LoRa */
GPS_data Parse_RMC_data(RMC_data RMC_parsed){
    GPS_data GPS_parsed;
    char tempLat[11]="0";
    char tempLong[12]="0";
    if(strcmp(RMC_parsed.Status,"A") == 0){
        strcpy(GPS_parsed.UTC_Time,RMC_parsed.UTC_Time);
        if (strcmp(RMC_parsed.N_S_Indicator, "N") == 0){
            tempLat[0] = '+';
        }
        else{
            tempLat[0] = '-';
        }
        strcat(tempLat, RMC_parsed.Latitude);
        strcpy(GPS_parsed.Latitude,tempLat);
        if (strcmp(RMC_parsed.E_W_Indicator, "E") == 0){
            tempLong[0] = '+';
        }
        else{
            tempLong[0] = '-';
        }
        strcat(tempLong, RMC_parsed.Longitude);
        strcpy(GPS_parsed.Longitude, tempLong);
        strcpy(GPS_parsed.Speed_Over_Ground,RMC_parsed.Speed_Over_Ground);
        strcpy(GPS_parsed.Course_Over_Ground,RMC_parsed.Course_Over_Ground);
        // strcpy(GPS_parsed.Date,RMC_parsed.Date);
        strcpy(GPS_parsed.Node_ID, TEST_NODE_ID);
        strcpy(GPS_parsed.Node_Type, TEST_NODE_TYPE);
        strcpy(GPS_parsed.Valid,RMC_parsed.Status);
    }
    else {
        strcpy(GPS_parsed.UTC_Time, "000000.000");
        strcpy(GPS_parsed.Latitude,"+0000.0000");
        strcpy(GPS_parsed.Longitude,"+00000.0000");
        strcpy(GPS_parsed.Speed_Over_Ground,"0.00");
        strcpy(GPS_parsed.Course_Over_Ground,"000.00");          
        strcpy(GPS_parsed.Node_ID, TEST_NODE_ID);
        strcpy(GPS_parsed.Node_Type, TEST_NODE_TYPE);
        // strcpy(GPS_parsed.Date,"000000");
        strcpy(GPS_parsed.Valid,RMC_parsed.Status);
    }
    return GPS_parsed;
}

extern double flipBaseGPS(char *gMin){
    
     /* Define temporary variables */
    char value[10];
    char *eptr;
    double grausMin;

    /* Copy a value into the variable */
    /* It's okay to have whitespace before the number */
    strcpy(value, gMin);

    /* Convert the provided value to a double */
    grausMin = strtod(value, &eptr);
    
    /*Calculate the decimal degrees from ddmm.mmmm*/
    double conv = (int)grausMin/100 +(float)((int)grausMin%100 + grausMin - (int)grausMin)/60;  
    return conv;  
}

/* Print GPS_data struct to pc USART for debugging */
void Print_GPS_data(GPS_data GPS_data_print){
    
    double lat = flipBaseGPS(GPS_data_print.Latitude);
    double lon = flipBaseGPS(GPS_data_print.Longitude);
    
    printf("UTC_Time: %s\r\n",GPS_data_print.UTC_Time);
    printf("Status: %s\r\n",GPS_data_print.Valid);
    printf("Latitude: %s\r\n",GPS_data_print.Latitude);
    printf("Longitude: %s\r\n",GPS_data_print.Longitude);
    printf("Latitude: %lf\r\n",lat);
    printf("Longitude: %lf\r\n",lon);
    printf("Speed: %s\r\n",GPS_data_print.Speed_Over_Ground);
    printf("Course: %s\r\n",GPS_data_print.Course_Over_Ground);
}


