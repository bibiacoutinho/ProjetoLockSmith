/*
    Code by LockSmith 
*/

//importando bibliotecas
#include <SPI.h>
#include <MFRC522.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>;

//Definindo constantes
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#define FIREBASE_HOST "locksmith-24779.firebaseio.com"
#define FIREBASE_AUTH "8Dh0XY2NOXl8EuOzubwCXMJBdWSu4zUpxLIXhhtr"

//Cria a instância FirebaseData, nela que serão armazenados
//dados buscados do Firebase
FirebaseData firebaseData;

//Algumas variáveis
String path = "/Tags/"; //Para a busca no Firebase
String sala = ""; //Para definir a sala como a qual o NodeMCU olhará para o Firebase
int statuss = 0; 
int out = 0;  

// Cria a instância MFRC522.
MFRC522 mfrc522(SS_PIN, RST_PIN);   

void setup()
{
  //Definir função dos pinos digitais
  pinMode(D0, INPUT); //Define o pino D0 como entrada
  pinMode(D4, OUTPUT); //Define o pino D4 como saída

  // Inicia a comunicação serial
  Serial.begin(9600);   

  // Inicializa o SPI bus (para o RFID)
  SPI.begin();
  // Inicializa MFRC522 (para o RFID)      
  mfrc522.PCD_Init();   

  /* Agora a parte interessante risos risos */
  //Espera uma entrada serial   
  Serial.println("Set room: ");
  while (!Serial.available()) {
    delay(100);
  }
  // Lê a string vinda da comunicação serial e atribui à variável sala
  sala = Serial.readString();
  sala.trim();
  Serial.println("Choosen: " + sala + " (This lock now works as for " + sala + ")");
  Serial.println();

  //Espera uma entrada serial
  Serial.print("WiFi SSID: ");
  while (!Serial.available()) {
    delay(100);
  }
  // Lê a String vinda da comunicação serial
  String serialRead1 = Serial.readString();
  // Pega o comprimento da String
  int length1 = serialRead1.length();
  //Define a variável WIFI_SSID como char
  char WIFI_SSID[length1];
  //Transforma a String lida para um array de caractéres (Char Array)
  serialRead1.toCharArray(WIFI_SSID, length1);
  Serial.println(WIFI_SSID);

  //Espera uma entrada serial
  Serial.print("Password: ");
  while (!Serial.available()) {
    delay(100);
  }
  // Lê a String vinda da comunicação serial
  String serialRead2 = Serial.readString();
  // Pega o comprimento da String
  int length2 = serialRead2.length();
  // Define a variável WIFI_PASSWORD como char
  char WIFI_PASSWORD[length2];
  // Transforma a String lida para um array de caractéres (Char Array)
  serialRead2.toCharArray(WIFI_PASSWORD, length2);
  Serial.println(WIFI_PASSWORD);

  //Inicia tentativa de conexão com a rede WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  //Enquanto não conectar: escreve '.' no monitor serial 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());

  //Inicia a conexão com o Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void loop()
{
  // Verifica se há um novo cartão ou tag
  // Se não, recomeça o loop
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Lê o cartão. Se não conseguir ler, recomeça o loop
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  //Mostra o ID do(a) cartão/tag no monitor serial
  Serial.println();
  Serial.print("UID tag: ");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "_"));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.print(content.substring(1));
  Serial.println();

  // Procura a permissão do cartão no Banco de Dados
  if (Firebase.getString(firebaseData, path + content.substring(1) + "/" + sala)) {
     // Se encontrar o código corespondente a essa fechadura: concede o acesso, abre a tranca e acende o led por 3 segundos
    Serial.println(" Access Granted ");
    pinMode(D0, OUTPUT); //Abre a tranca
    digitalWrite(D4, HIGH); //Acende o led
    delay(3000);
    pinMode(D0, INPUT); //Fecha a tranca
    digitalWrite(D4, LOW); //Apaga o led
    delay(2000);
  }
  else { //Se não encontrar, nada acontece
    Serial.println("Access denied");
    delay(3000);
  }

  //Código mantido para propósitos de emergência
  /*if (content.substring(1) == "8C_82_46_69") //Compara o UID lido com o valor definido
    {
    //Acesso concedido, abre a tranca(acende o led por 3 segundos)
    Serial.println(" Access Granted ");
    digitalWrite(D0, HIGH);
    statuss = 1;
    delay(2000);
    digitalWrite(D0, LOW);
    }
    else   {
    //Acesso negado, nada acontece
    Serial.println(" Access Denied ");
    delay(3000);
    }
  */

}
