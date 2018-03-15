#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>

//defines
#define SSID_WIFI "INSIRA O NODE DA REDE WIFI AQUI"    // Nome da rede wifi a ser conectada
#define PSWD_WIFI "INSIRA A SENHA DA REDE WIFI AQUI"       // Senha da rede wifi a ser conectada
#define SEND_DELAY 30000            // Intervalo de post ao ThingSpeak
#define HUM_SENSOR A0               // Define o pino A0 como entrada do sensor de humidade do solo
#define RELAY_PIN 12                // Define o pino do Relay (Pino D6)
#define ONE_WIRE_BUS 5              // Define o pino do sensor de temperatura (Pino D1)
#define SENSOR_INTERRUPT 2;         // Define interrupção (Pino D4)
#define FLOW_SENSOR 2;              // Define o sensor de fluxo (Pino D4)

#define DRY 50        // DEFINE QUANDO O RELE VAI SER ATIVADO
#define WET 70        // DEFINE QUANDO O RELE VAI SER DESATIVADO

char ThingSpeakAPI[] = "api.thingspeak.com";         // Define o endereÃ§o da api do ThingSpeak
String WriteKey = "INSIRA A CHAVE DE ESCRITA DO THINGSPEAK";                // Define a chave da api de escrita
long lastConnectionTime;                             // Variável que guarda o tempo da ultima conexÃ£o com a api
bool irrigationStatus = false;                       // Variável define o status da irrigaÃ§Ã£o
int iStatus = 0;                                     // Variável auxiliar para irrigação
WiFiClient client;                                   // Define o cliente Wifi

void SendInfo(String Data);             // ProtÃ³tipo da funÃ§Ã£o de envio ao ThingSpeak
void ConnectWiFi(void);                 // ProtÃ³tipo da funÃ§Ã£o que conecta a board a rede Wifi
int ReadHum(void);                      // FunÃ§Ã£o que lÃª a humidade do solo e retorna um valor entre 0 e 100 (Porcentagem)

// Fator de calibração (Número de pulsos gerados pelo sensor por cada litro)
float calibrationFactor = 4.5;

// Contador de pulso
volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;
unsigned long loopTime;                   // Guarda o tempo de clock do ciclo

OneWire oneWire(ONE_WIRE_BUS);            // Define uma instancia do oneWire para comunicacao com o sensor

/*
   FunÃ§Ã£o envia informaÃ§Ãµes ao ThingSpeak
   Recebe por parametro a string de dados a serem enviados ao canal no ThingSpeak
   NÃ£o retorna nenhum valor
*/
void SendInfo(String Data)
{
  if (client.connect(ThingSpeakAPI, 80)) // Conecta com a api do ThingSpeak na porta 80
  {
    //faz a requisiÃ§Ã£o HTTP ao ThingSpeak
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + WriteKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(Data.length());
    client.print("\n\n");
    client.print(Data);

    lastConnectionTime = millis();      // Define o tempo de ultima conexÃ£o para o momento atual
    Serial.println("Status: Valor enviado para a API");
  }
}

/*
   FunÃ§Ã£o faz a conexÃ£o com a rede wifi
   NÃ£o tem parametro
   NÃ£o retorna nenhum valor
*/
void ConnectWiFi(void)
{
  client.stop();                                  // Para o cliente para efetuar nova conexÃ£o
  Serial.println("Conectando-se Ã  rede WiFi...");
  Serial.println();
  delay(1000);                                    // Tempo de espera atÃ© a conexÃ£o
  WiFi.begin(SSID_WIFI, PSWD_WIFI);               // Conecta a rede previamente definida

  while (WiFi.status() != WL_CONNECTED)           // Aguarda atÃ© a conexÃ£o ser efetuada
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connectado com sucesso!");
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());                 // Printa o ip obtido pela board
  delay(1000);
}
/*
    FunÃ§Ã£o para leitura e processamento da humidade do solo obtida pelo sensor na porta A0
    NÃ£o tem parametros
    Retorta um valor entre 0 e 100 (porcentagem)
*/

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;


void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}



float ReadHum(int sensorValue)
{
  sensorValue = constrain(sensorValue, 475, 1023);  // 495 Define o piso e o teto do valor obtido no sensor
  float soil = map(sensorValue, 475, 1023, 100, 0); // 495 Faz o calculo da porcentagem da humidade com base na leitura do sensor
  Serial.print("Umidade do solo: ");               //
  Serial.print(soil);                               // Printa o valor, somente para fins de desenvolvimento
  Serial.println("%");                              //
  return soil;                                      // Retorna a porcentagem de humidade do solo
}

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  Serial.println("Localizando sensores DS18B20");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0))
    Serial.println("Sensores nao encontrados !");
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();

  pinMode(FLOW_SENSOR, INPUT);
  digitalWrite(FLOW_SENSOR, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  pinMode(RELAY_PIN, OUTPUT);       // Define o pino do relay como saida
  digitalWrite(RELAY_PIN, LOW);     // Marca o Relay como desligado
  attachInterrupt(SENSOR_INTERRUPT, pulseCounter, FALLING);

  lastConnectionTime = 0;          // Defina o tempo da ultima conexÃ£o em 0
  ConnectWiFi();                   // Efetua a conexÃ£o a rede wifi
  Serial.println("HortaOS READY"); // Infoma no console que o sistema esta pronto
  Serial.println("");
  Serial.println("");
}

//loop principal
void loop()
{
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    detachInterrupt(SENSOR_INTERRUPT);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Fluxo: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min   ||   ");
    // Reseta o contador de pulso para o proximo loop
    pulseCount = 0;
    attachInterrupt(SENSOR_INTERRUPT, pulseCounter, FALLING);
  }

  
  char FieldThingSpeak[50];  // String para armazenar a concatenaÃ§Ã£o de informaÃ§Ãµes
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  Serial.print("Temperatura do solo: ");
  Serial.print(tempC);
  Serial.print(" C   ||  ");

  float soil, light;                              // Variavel que vai receber a porcentagem da humidade do solo
  soil = ReadHum(analogRead(A0));         // Chama a função que retorna a porcentagem da humidade do solo
  if (soil > DRY && soil < WET && irrigationStatus == true) {
    Serial.println("Status: Irrigacao em andamento");
  }
  else if (soil <= DRY && irrigationStatus == false) { // Verifica se o solo esta seco e então liga o relay
    irrigationStatus = true;
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Status: Irrigação ligada");
  }
  else if (soil > WET && irrigationStatus == true) { // Verifica se o solo esta molhado e a irrigação esta ligada
    Serial.println("Status: Irrigação desligada");
    irrigationStatus = false;
    digitalWrite(RELAY_PIN, HIGH);
  }

  //Faz a verificaÃ§Ã£o se a board esta conectada a rede e se deve enviar informaÃ§Ãµes ao thingspeak
  if (millis() - lastConnectionTime > SEND_DELAY)
  {
    if (irrigationStatus == true) {
      iStatus = 1;
    } else {
      iStatus = 0;
    }
    sprintf(FieldThingSpeak, "field1=%.2f&field2=%.2f&field3=%d&field4=%.2f", soil, tempC, iStatus, flowRate); // Concatena as informaÃ§Ãµes dentro de uma unica string
    SendInfo(FieldThingSpeak);                   // Chama funÃ§Ã£o que envia as informaÃ§Ãµes ao ThingSpeak
  }
  delay(1000);
}

