#include "milis.h"
#include "stm8s.h"
#include "stm8_hd44780.h"
#include <stdio.h>

/*#include "delay.h"*/
/*#include <stdio.h>*/
/*#include "../lib/uart.c"*/

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN GPIO_PIN_5
#define LED_ON GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_OFF GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_FLIP GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN) == RESET)

void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    
    lcd_init();

    init_milis();
}

int main(void)
{
    uint32_t time = 0;
    uint16_t pocitadlo = 0;
    char text[16];
    
    setup();

    lcd_gotoxy(0,0);
    lcd_puts("ahoj");

    while (1) {

        if (milis() - time > 333 && BTN_PUSH) {
            LED_FLIP;
            time = milis();
            lcd_gotoxy(0,0);
            sprintf(text, "cislo %d", pocitadlo++);
            lcd_puts(text);
        }

    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
