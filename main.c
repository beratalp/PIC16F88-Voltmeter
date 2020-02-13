/*
 * File:   main.c
 * Author: beratalp
 *
 * Created on May 23, 2019, 2:26 PM
 */

#pragma config FOSC = INTOSCIO
#pragma config WDTE = OFF     
#pragma config PWRTE = ON    
#pragma config MCLRE = ON   
#pragma config BOREN = ON     
#pragma config LVP = OFF       
#pragma config CPD = OFF     
#pragma config WRT = OFF     
#pragma config CCPMX = RB0  
#pragma config CP = OFF    
#pragma config FCMEN = ON  
#pragma config IESO = ON    

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "lcd.h"
#define _XTAL_FREQ 4000000

int adcResult = 0;


int main(){
    OSCCON = 0b11101000;
    ANSEL = 0b00000001;
    TRISA = 0b00001111;
    LCD lcd = {&PORTB, 2, 3, 4, 5, 6, 7};
    ADCON1bits.ADFM = 1;
    ADCON0bits.ADCS = 0b01;
    ADCON1bits.ADCS2 = 0b0;
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0b000;
    LCD_Init(lcd);
    LCD_puts("  LCD INIT");
    __delay_ms(1000);
    while(1){
        LCD_Clear();
        __delay_us(25);
        ADCON0bits.GO = 1;
        while(ADCON0bits.nDONE);
        adcResult = (ADRESH<<8) + (ADRESL);
        char str[10];
        sprintf(str, "%d", adcResult);
        LCD_puts(str);
        __delay_ms(1000);
        LCD_Clear();
        LCD_puts(" test");
        __delay_ms(500);
        LCD_Clear();
    }
    return 0;
}
