/*
 * l86.h
 * Author: Rishin Amin
 * library header file for communication with the Quectel L86 MT33 GPS module
 *
 */

#ifndef l86_hpp
#define l86_hpp

#define DEBUGGER // uncomment to output serial data to PC


#define TEST_NODE_ID    "666"
#define TEST_NODE_TYPE  "R"

/*      PIN DEFINITIONS      */
// #define RESET_PIN       PB_14
// #define FORCE_ON_PIN    PB_15
// #define ONEPPS_PIN      PA_8
#define GPS_RX          PA_10
#define GPS_TX          PA_9
#define PC_RX           PC_5
#define PC_TX           PC_4
#define GPS_STATUS_LED  LED1

/* PMTK MMESSAGE DEFINITIONS */
#define MAX_NMEA_LENGTH  82         // maximum length of an NMEA sentence
#define PMTK_SET_NMEA_OUTPUT_RMC    "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"
#define PMTK_GET_DATA               "$PMTK622,1*29\r\n"
#define PMTK_SET_UPDATE_F_2HZ       "$PMTK300,500,0,0,0,0*28\r\n" 
#define PMTK_COLD_RESTART           "$PMTK104*37\r\n"
#define PMTK_WARM_START             "$PMTK102*31\r\n"
#define PMTK_HOT_START              "$PMTK101*32\r\n"
#define PMTK_ALWAYS_LOCATE_STANDDBY "$PMTK225,8*23\r\n"
#define PMTK_ALWAYS_LOCATE_BACKUP   "$PMTK225,922\r\n*"
#define PMTK_STANDBY_MODE           "$PMTK161,0*28\r\n" // Any UART data will retrun to Full-on mode
#define PMTK_BACKUP_MODE            "$PMTK225,4*2F\r\n" // Force_on must be low before entering backup mode!
                                                        // Pull Force_on high to exit backup mode 

static const char GPRMC_Tag[] = "$GPRMC";
static const char GNRMC_Tag[] = "$GNRMC";

typedef struct RMC_data
{
    char Message[MAX_NMEA_LENGTH];  /* Un-parsed NMEA sentence */
    char Message_ID[7];             /* RMC Protocol header */
    char UTC_Time[11];              /* hhmmss.sss */
    char Status[2];                 /* A = data valid, V = data NOT valid */
    char Latitude[10];              /* ddmm.mmmm */
    char N_S_Indicator[3];          /* N = North, S = South */
    char Longitude[11];             /* dddmm.mmmm */
    char E_W_Indicator[3];          /* E = East, W = West */
    char Speed_Over_Ground[5];      /* In Knots */
    char Course_Over_Ground[7];     /* Degrees */
    char Date[7];                   /* ddmmyy */
    char Mode[5];                   /* N = No Fix, A = autonomous mode, D = Differential mode + checksum */
}RMC_data;

typedef struct GPS_data
{
    char UTC_Time[11];
    char Latitude[11];
    char Longitude[12];
    char Speed_Over_Ground[5];
    char Course_Over_Ground[7];
    // char Date[7];
    char Valid[2];
    char Node_ID[4];
    char Node_Type[2];
}GPS_data;

extern double flipBaseGPS(char gMin);

RMC_data Parse_RMC_sentence(char RMC_sentence[MAX_NMEA_LENGTH]);
void Print_RMC_data(RMC_data *RMC_data_print);
GPS_data Parse_RMC_data(RMC_data RMC_parsed);
void Print_GPS_data(GPS_data GPS_data_print);

#endif


