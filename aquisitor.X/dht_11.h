# Ifndef ONEWIRE_DHT11
# define  ONEWIRE_DHT11

 união typedef 
{
    struct 
    {
         char não assinado ;
        unsigned  de char temperatura;
         char não assinado ;
         característica não assinada;
    };
    struct
    {
         longa assinado_temperatura ;
    };
DHT;


void  initDHT11 ( void );
 char  dht não assinado (DHT * ptr);



/ * ***************** Como usar?
 * vazio principal (vazio)
 * {
* Sensor DHT; // Declaração da variável com o tipo que recebe
 * // dados lidos pelo sensor de temperatura e 
 * // densidade.
 *  
* initDHT11 (); // Inicialização / Habilitação do pino ligado ao sensor
 *     
 *     
 * if (dht (& sensor)) // Chamada da rotina com endereço da variável de 
 * // destino para os dados.
 * // Se o retorno for verdadeiro, os dados estão íntegros.
 * {
* sensor.temperatura; // Valor da temperatura [ºC].
* sensor.umidade; // Valor da densidade [%].
 *}
 *}
 * /

# endif
