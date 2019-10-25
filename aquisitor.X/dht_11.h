#ifndef ONEWIRE_DHT11
#define ONEWIRE_DHT11

typedef union 
{
    struct 
    {
        unsigned char ;
        unsigned char temperatura;
        unsigned char ; 
        unsigned char umidade;
    };
    struct
    {
        unsigned long umidade_temperatura;
    };
} DHT;


void initDHT11( void );
unsigned char dht( DHT * ptr );



/****************** Como usar?
 * void main( void )
 * {
 *     DHT sensor;             // Declaração da variável com o tipo que receberá 
 *                             // os dados lidos pelo sensor de temperatura e 
 *                             // umidade.
 *  
 *     initDHT11();            // Inicialização/Habilitação do pino ligado ao sensor
 *     
 *     
 *     if( dht( &sensor ) )    // Chamada da rotina com endereço da variável de 
 *                             // destino para os dados.
 *                             // Se o retorno for verdadeiro, os dados estão íntegros.
 *     {
 *         sensor.temperatura; // Valor da temperatura [ºC].
 *         sensor.umidade;     // Valor da umidade [%].
 *     }
 * }
 */

#endif
