#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "teclado.h"
#include "leitorLM35_v07.h"
#include <stdio.h>
#include "recept.h"

#define LEDVED PORTCbits.RC0
#define LEDAMA PORTCbits.RC1
#define LEDVEM PORTCbits.RC2

char tim = 1;
int repeat = 0;

void __interrupt() myISR(void)
{  
    if(TMR1IF)
    {
        repeat++;
        TMR1IF = 0;
        TMR1L = TMR1H = 0x00;       
        if(repeat >=2861)
        {
            salvatemp(temperaturaLer()); //Esse codigo acontece a cada 5 minutos.
            repeat = 0;
        }
    }
}

void main(void) 
{
    TRISC=0x00;
    PORTC=0;
    char nr;
    
    initLCD();
    tecladoIniciar();
    temperaturaInicializar();
    
    
    SplashScreen0();
    delay(100);
    cmdLCD(LCD_CLEAR);
    SplashScreen1();
    delay(100);
    
    tempatt();
    cmdLCD(LCD_CLEAR);
 
    tmron();
    Telaprincipal();
    
   while ( 1 )
    {
      
       nr = tecladoLer();
       
       if (tim == 1)
       {         
           tempatt(); 
       }
       
       if(nr != 0)
       {
           putLCD(nr);
       }
      
                    
       switch (nr)
       {
           
           case 'A':        
                cmdLCD(LCD_CLEAR);
                adcLer();
                temperaturaLer();
                Telaprincipal(); 
                tim = 1;
                break;
                
           case 'B':
                cmdLCD(LCD_CLEAR);
                TempMed();
                tim = 0;
                break;
                
           case '*':
                cmdLCD(LCD_CLEAR);
                salvatemp(temperaturaLer());  
                showtemp ();                
                tim = 0;  
                break;
                                            
            case '#':
                cmdLCD(LCD_CLEAR);
                erasertemp();
                resetemp();
                tim = 0;
                break;               

         }
       


     }
 }                
