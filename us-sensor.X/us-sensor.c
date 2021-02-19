/*
 * File:   us-sensor.c
 * Author: Mujahid Yunus
 *
 * Created on February 16, 2021, 2:57 PM
 */


#include <xc.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 20000000
#define Trigger RB0
#define Echo RB1
#define led1 RB2
#define led2 RB3
#define led3 RB4
#define led4 RB5

int calc_distance(void){
    int distance = 0;
    TMR1 = 0;
    Trigger = 1;
    __delay_us(10);
    Trigger = 0;
    while(!Echo){
        TMR1 = 1;
    }
    while(Echo){
        TMR1 = 0;
    }
    distance = TMR1*(340*4/20000000);
    return distance;
}

void main(void) {
    TRISB0 = TRISB2 = TRISB3 = TRISB4 = TRISB5 = 0;
    TRISB1 = 1;
    
    //configuring TIMER1//
    TMR1ON = 0; //TIMER1 On bit - clear to start counting from 0
    TMR1CS = 0; //set Clock Source Select Bit to Internal Clock(FOSC/4)
    T1CKPS1 = T1CKPS0 = 0; //PreScaler set to 1:1 
    /*************************/
    
    int the_distance = 0;
    
    while(1){
        the_distance = calc_distance()/5;
        led1 = led2 = led3 = led4 = 0;
        if(the_distance==1){
            led1 = 1;
            __delay_ms(50);
        }
        else if(the_distance==2){
            led2 = 1;
            __delay_ms(50);
        }
        else if(the_distance==3){
            led3 = 1;
            __delay_ms(50);
        }
        else if(the_distance==4){
            led4 = 1;
            __delay_ms(50);
        }
        else {
            led1 = led2 = led3 = led4 = 0;
        }
    }
    return;
}
