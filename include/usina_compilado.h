/*============================================================================================
 *                           PROGRAMA DE CONTROLE E MONITORAMENTO IOT
 *                                    AUTOR: DANILO ANDRADE
 ==============================================================================================*/

#include <Arduino.h>
#include <WiFi.h>   // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h>  // Importa a Biblioteca PubSubClient

/*============================================================================================
 *                   DEFINES DE ID MQTT E TÓPICOS PARA PUBLICAÇÃO E SUBSCRIBE
 ==============================================================================================*/

#define TOPICO_SUBSCRIBE "USINA_ON/OFF"   //tópico MQTT de escuta
#define TOPICO_PUBLISH  "PRESSAO_USINA_NATAL"  //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH1 "COMPRESSOR_1_STATUS_USINA_NATAL"
#define TOPICO_PUBLISH2 "COMPRESSOR_2_STATUS"
#define TOPICO_PUBLISH3 "CONCENTRACAO_O2_USINA_NATAL"
#define TOPICO_PUBLISH4 "OGP_CR_STATUS_USINA_NATAL"
#define TOPICO_PUBLISH5 "BLCRT_O2_E_USINA_NATAL"
#define TOPICO_PUBLISH6 "BLCRT_O2_D_USINA_NATAL"
#define TOPICO_PUBLISH7 "RFF_USINA_NATAL"
#define TOPICO_PUBLISH8 "BE_USINA_NATAL"
#define TOPICO_PUBLISH9 "COMPRESSOR_ON/OFF"
#define TOPICO_PUBLISH10 "STATUS_USINA_NATAL"




/*============================================================================================
 *                                 ID DO MODULO PARA O SERVIDOR MQTT
 *                  SEMPRE MODIFICAR PARA NÃO DAR CONFLITO ENTRE AS PLACAS INSTALADAS
 ==============================================================================================*/

#define ID_MQTT "USINA_CR_NATAL_RN"    //id mqtt (para identificação de sessão) SEMPRE MODIFICAR ESSE TOPICO

/*============================================================================================
 *                             MAPEAMENTO DOS PINOS DO NODEMCU
 ==============================================================================================*/

#define D0 26                                        //DEFINE A ENTRADA DO FALTA DE FASE
#define D1 27                                        //DEFINE A ENTRADA DO MODO AUTOMATICO
#define D2 14                                        //DEFINE A ENTRADA DO BOTAO DE EMERGENCIA
#define D3 12                                        
#define D4 13                                        //DEFINE A ENTRADA DO RELE CICLICO

#define D5 15                                       //DEFINE SAIDA DO COMPRESSOR 1
#define D6 02                                       //DEFINE SAIDA DA OGP
#define D7 04                                       //LED COMPRESSOR 1
#define D8 16                                       //LED OGP
#define D9 17                                       //ALARME

#define A0 35                                       //DEFINE A ENTRADA DO SENSOR DOS COMPRESSORES
#define A1 34                                       //DEFINE A ENTRADA DO SENSOR DE REDE
#define A2 39                                       //DEFINE A ENTRADA DO SENSOR DE OXIGENIO
#define A3 36

/*============================================================================================
 *                                         WIFI
 ==============================================================================================*/
 
const char* SSID = "4G-MIFI-07C";  // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "1234567890";  // Senha da rede WI-FI que deseja se conectar

/*============================================================================================
 *                                         MQTT
 ==============================================================================================*/
 
const char* BROKER_MQTT = "broker.hivemq.com";  //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                         // Porta do Broker MQTT

/*============================================================================================
 *                              VARIÁVEIS E OBJETOS GLOBAIS
 ==============================================================================================*/

WiFiClient espClient;          // Cria o objeto espClient
PubSubClient MQTT(espClient);  // Instancia o Cliente MQTT passando o objeto espClient

float leitura;
float pressao;
float direito;
float esquerdo;
float oxigenio;
float concentracao;
float cilindroEsq;
float cilindroDir;

int TEMP;
int TEMP1;
int TEMP2;
int TEMP3;
char timestamp[] = "";
char timestamp1[] = "";
char timestamp2[] = "";
char timestamp3[] = "";

char payload[23] = "000.00";
char payload1[23] = "000.00";
char payload2[23] = "000.00";
char payload3[23] = "000.00";


int central = '0';        //variável que armazena o estado atual da saída
int tempo = 0;
int emergencia = 0;
int automatico = 0;
int RST = 0;
int statecompressor1 = '0';
int statecompressor2 = '0';
int usina = '0';
int compressorINPUT = 0;

//Prototypes
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
void InitInput(void);