#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "teclado.h"
#include "leitorLM35_v07.h"
#include <stdio.h>
#include "recept.h"
#include "dht_11.h"

#define LEDVED PORTCbits.RC0
#define LEDAMA PORTCbits.RC1
#define LEDVEM PORTCbits.RC2
char nr = 0;
char tim = 1;
int repeat = 0;
int Controle_do_retorno = 0;
int x;

DHT sensor;

void __interrupt() myISR(void)
{  
    if(TMR1IF)
    {

        TMR1IF = 0;
        T1CONbits.TMR1ON=0;
        TMR1L = TMR1H = 0x00;    
        repeat++;
        if(repeat >=2861)
        {
            repeat = 0;
            salvatemp(temperaturaLer()); //Esse codigo acontece a cada 5 minutos.
        }
        if(repeat%10 == 0 && tim == 1)
        {
                tempatt(); 
        }
        if(tim == 2 && ((repeat - Controle_do_retorno)>20))
        {
            Telaprincipal(); 
            tempatt();
            tim = 1;
            Controle_do_retorno = 0;
        }
        T1CONbits.TMR1ON=1;
    }
}

void main(void) 
{
    TRISC=0x00;
    PORTC=0;
    
    initLCD();
    tecladoIniciar();
    temperaturaInicializar();
    initDHT11();

    
    SplashScreen0();
    delay(100);
    cmdLCD(LCD_CLEAR);
    SplashScreen1();
    delay(100);
    
    tempatt();
    cmdLCD(LCD_CLEAR);
 
    tmron();
    Telaprincipal();
    tempatt(); 
    
    
   while ( 1 )
    {          
       nr = tecladoLer();
       delay(15);   
       if(nr != 0)
       {
           putLCD(nr);
       }    
                    
       switch (nr)
       {
           
           case 'A':
                GIE = 0;
                cmdLCD(LCD_CLEAR);
                Telaprincipal(); 
                tempatt(); 
                tim = 1;
                GIE = 1;
                break;
                
           case 'B':
                GIE = 0;
                tim = 0;
                cmdLCD(LCD_CLEAR);
                TempMed();
                GIE = 1;
                break;
                
           case'C':
               GIE = 0;
               cmdLCD(LCD_CLEAR);
               subtela();
//                if( dht() )
//                {
//                x = sensor.temperatura;
//                }
               tim =3;
               GIE = 1;
               break;
                
           case '*':
                GIE = 0;
                tim = 2;  
                cmdLCD(LCD_CLEAR);
                showtemp ();
                salvatemp(temperaturaLer());
                Controle_do_retorno = repeat;
                GIE = 1;
                break;
                                            
            case '#':
                GIE = 0;
                tim = 2;
                cmdLCD(LCD_CLEAR);
                erasertemp();
                resetemp();
                Controle_do_retorno = repeat;
                GIE = 1;
                break;               

         }
       


     }
 }                
