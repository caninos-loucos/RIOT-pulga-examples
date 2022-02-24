#include <stdio.h>
#include <string.h>

#include "thread.h"

#include "periph/uart.h"
#include "ringbuffer.h"
#include "xtimer.h"

#ifndef UART_BUFSIZE
#define UART_BUFSIZE        (128U)
#endif
int dev = 1;
uint32_t baud = 9600;
static void rx_cb(void *arg, uint8_t data)
{
    (void)arg;
    printf("debug rx: %c\n", data);

    if (data == '\n') {
        uart_write(UART_DEV(dev), (uint8_t *)"rx\n", 3);
    }
}

int main(void)
{
    /* initialize UART */
    int res = uart_init(UART_DEV(dev), baud, rx_cb, (void *)dev);
    if (res != UART_OK) {
        puts("Error: Unable to initialize UART device");
        return 1;
    }
    printf("Success: Initialized UART_DEV(%i) at BAUD %"PRIu32"\n", dev, baud);
    uart_write(UART_DEV(dev), (uint8_t *)"Pulga started\n", 14);

    while (1) {
	uart_write(UART_DEV(dev), (uint8_t *)"Pulga in loop\n", 14);
	printf("UART %u configured to rx=%u tx=%u \n", dev, uart_config[dev].rx_pin, uart_config[dev].tx_pin);
	xtimer_sleep(3);
    }

    return 0;
}
