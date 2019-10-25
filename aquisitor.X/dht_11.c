/ *
 * Arquivo: OneWire-DHT11.c
 * Autor: curtaeletronica
 *
 * Criado em 14 de outubro de 2019, 13:51
 * 
 * Objetivo: 
 * Comunicação com módulo Sensor de temperatura DHT11 via comunicação 
 * 1 fio (1 fio).
 *          
 * 
 * Pinos | nº | Conexão
* RC4 | 23 | 1 fio
 * 
 * /


# include  < xc.h >
# Incluem  " config.h "
# include  " oneWire-DHT11.h "

# define  INPUT                1
# define  OUTPUT               0
# define  DHT_DIR ( x ) TRISCbits.TRISC4 = x

# define  DHT_DATA_OUT ( x ) PORTCbits.RC4 = x
# define  DHT_DATA_IN          PORTCbits.RC4


# define  DELAY_START () __delay_ms ( 20 )
# define  DELAY_DATA_READ () __delay_us ( 40 );

void  initDHT11 ( void )
{
    SSPCONbits. SSPEN = 0 ;
    DHT_DATA_OUT ( 1 );
    DHT_DIR (ENTRADA);
}

 char  não assinado dht (DHT * ptr)
{
     char não assinado i;
     char não assinado crc = 0 ;

    DHT_DIR (SAÍDA);
    DHT_DATA_OUT ( 0 );             // '' \ ....
    DELAY_START ();
    DHT_DATA_OUT ( 1 );             // ../ '' '' '

    DHT_DIR (ENTRADA);
    while (DHT_DATA_IN);          // '' \ ..
    while (! DHT_DATA_IN);          //       ../ ''  
    while (DHT_DATA_IN);          //            '' \ ..

    para (i = 0 ; i < 32 ; i ++)
    {
        while (! DHT_DATA_IN);          //              ../ ''  
        DELAY_DATA_READ ();
        ptr-> temperatura_temperatura << = 1 ;
        if (DHT_DATA_IN)
        {
            ptr-> densidade_temperatura | = 1 ;
            while (DHT_DATA_IN);       //                  '' \ ..
        }
    }

    para (i = 0 ; i < 8 ; i ++)
    {
        while (! DHT_DATA_IN);          //                       ../ ''  
        DELAY_DATA_READ ();
        crc << = 1 ;
        if (DHT_DATA_IN)
        {
            crc | = 1 ;
            while (DHT_DATA_IN);       //                           '' \ ..
        }
    }
    
    return (crc == (ptr-> temperatura + ptr-> temperatura ));
}
