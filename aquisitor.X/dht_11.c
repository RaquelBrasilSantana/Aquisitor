*
 * File:   OneWire-DHT11.c
 * Author: curtaeletronica
 *
 * Created on 14 de Outubro de 2019, 13:51
 * 
 * Objetivo: 
 *      Comunicação com módulo Sensor de Temperatura DHT11 via comunicação 
 *      a 1 fio (1-wire).
 *          
 * 
 * Pinos    |nº     |Conexão
 *  RC4     |23     | 1-wire
 * 
 */


#include <xc.h>
#include "config.h"
#include "oneWire-DHT11.h"

#define INPUT               1
#define OUTPUT              0
#define DHT_DIR( x )        TRISCbits.TRISC4 = x

#define DHT_DATA_OUT( x )   PORTCbits.RC4 = x
#define DHT_DATA_IN         PORTCbits.RC4


#define DELAY_START()       __delay_ms( 20 )
#define DELAY_DATA_READ()   __delay_us(40);

void initDHT11( void )
{
    SSPCONbits.SSPEN = 0;
    DHT_DATA_OUT( 1 );
    DHT_DIR( INPUT );
}

unsigned char dht( DHT * ptr )
{
    unsigned char i;
    unsigned char crc = 0;

    DHT_DIR( OUTPUT );
    DHT_DATA_OUT( 0 );             // ''\....
    DELAY_START();
    DHT_DATA_OUT( 1 );             // ../'''''

    DHT_DIR( INPUT );
    while(  DHT_DATA_IN );          // ''\..
    while( !DHT_DATA_IN );          //      ../''  
    while(  DHT_DATA_IN );          //           ''\..

    for( i=0; i<32; i++ )
    {
        while( !DHT_DATA_IN );          //             ../''  
        DELAY_DATA_READ();
        ptr->umidade_temperatura <<= 1; 
        if( DHT_DATA_IN )
        {
            ptr->umidade_temperatura |= 1; 
            while(  DHT_DATA_IN );       //                 ''\..
        }
    }

    for( i=0; i<8; i++ )
    {
        while( !DHT_DATA_IN );          //                      ../''  
        DELAY_DATA_READ();
        crc <<= 1; 
        if( DHT_DATA_IN )
        {
            crc |= 1; 
            while(  DHT_DATA_IN );       //                          ''\..
        }
    }
    
    return( crc == (ptr->temperatura + ptr->umidade) );
}
