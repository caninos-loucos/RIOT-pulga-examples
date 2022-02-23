#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"

#include "l86.hpp"

RMC_data RMC;
GPS_data GPS_parse;
volatile int Char_index = 0;                  // index for char array
char Rx_data[MAX_NMEA_LENGTH] = "0";          // char array to store received bytes
volatile uint8_t GPS_data_ready = 0;
uint8_t valid = 0;
volatile uint8_t sending = 0;
volatile int primeiraVez=1;
double quectelLat = 0;
double quectelLon = 0;

void gps_receive(void);

void gps_receive(void) {
	// FIXME: serial code needs to be uncommented and fixed
    // Note: you need to actually read from the serial to clear the RX interrupt
    //while(uart_gps.readable()) {
    while(0) {
        if(Rx_data[0] != '$') Char_index = 0;
        //char incoming = uart_gps.getc();
        char incoming = ' ';
        
        Rx_data[Char_index] = incoming;
    
       if(Rx_data[Char_index] == '\n'){    // Received the end of an NMEA scentence
            if((strncmp(GPRMC_Tag,Rx_data,(sizeof(GPRMC_Tag)-1)) == 0) || (strncmp(GNRMC_Tag,Rx_data,(sizeof(GNRMC_Tag)-1)) == 0)){
                RMC = Parse_RMC_sentence(Rx_data);
                if(strcmp(RMC.Status, "A") == 0){
                    // GPS_status = 0;    // Turn status LED off
                    valid = 1;
                    // GPS_parse = Parse_RMC_data(RMC); // Parse into format suitable for Tom (Dinghy_RaceTrak software)
                }
                else{
                    // GPS_status = 1;
                }                
                if (sending){
                    Char_index = 0;
                    memset(Rx_data,0,sizeof(Rx_data));
                    //uart_gps.attach(&serial_gps_post_to_queue, Serial::RxIrq);
                    return;
                }
                GPS_data_ready = 0;
                GPS_parse = Parse_RMC_data(RMC); // Parse into format suitable for Tom (Dinghy_RaceTrak software)
                GPS_data_ready = 1;
                //Print_GPS_data(GPS_parse);
                quectelLat = flipBaseGPS(GPS_parse.Latitude);
                quectelLon = flipBaseGPS(GPS_parse.Longitude);
                if(quectelLat !=0){
                    //contadorLora = 0;
                    printf("...\n\r");
                    if(primeiraVez) {
			// initialized
                        primeiraVez=0; 
                    }
                }
                //send_GPS_Via_Lora();
                //contadorLora++;
            }
            Char_index = 0;
            memset(Rx_data,0,sizeof(Rx_data));
        }
        else{
            Char_index++;
        }
    }
    //uart_gps.attach(&serial_gps_post_to_queue, Serial::RxIrq);
    return;
    // store chars into a string then process into LAT, LONG, SOG, COG & DATETIME, VALID/INVLAID
}


int main(void)
{
    (void) puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
