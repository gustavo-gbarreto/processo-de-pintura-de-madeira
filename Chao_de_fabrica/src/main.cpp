#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <ultrasonic.h>
#include <esp_now.h>


uint8_t monitorMac[] = {0x98, 0x88, 0xE8, 0x04, 0x38, 0xBC}; // Substitua pelos últimos bytes do MAC do monitor

//definições de pinos
#define DHTTYPE DHT11
#define DHTpin  25
const int LDRpin = 34;
const int PIRpin = 14;
const int LEDRed = 12;
const int LEDGreen = 13;
const int Trig = 26;
const int Echo = 27;

//definiçôes de bibliotecas
Ultrasonic ultrasonic(Trig, Echo);
DHT dht(DHTpin, DHTTYPE);

bool Alert = false;


struct Data{
  float temperature;
  float humidity;
  int lightLevel;
  int presence;
  float distance;
};

esp_now_peer_info_t peerInfo;  // Cria uma estrutura esp_now_peer_info_t, que é utilizada para registrar informações sobre um peer (dispositivo) que será adicionado à rede ESPNOW

Data Datatosend = {
  .temperature = dht.readTemperature(),
  .humidity = dht.readHumidity(),
  .lightLevel = analogRead(LDRpin),
  .presence = digitalRead(PIRpin),
  .distance = ultrasonic.read()
};

void setup() {
 Serial.begin(115200);
 pinMode(LDRpin, INPUT);
 pinMode(PIRpin, INPUT);
 pinMode(LEDRed, OUTPUT);
 pinMode(LEDGreen, OUTPUT);
 pinMode(Trig, OUTPUT);
 pinMode(Echo, INPUT);

 dht.begin();

}

void loop() {
  /* float humidity = dht.readHumidity();
  
  int LDRvalue = analogRead(LDRpin);
*/
  float temperature = dht.readTemperature();
  int presence = digitalRead(PIRpin);
  float distance = ultrasonic.read();

  if(distance < 20){
    digitalWrite(LEDRed, HIGH);
    digitalWrite(LEDGreen, LOW);
    Alert != Alert;
  }
  else{
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDGreen, HIGH);
  }

  float temperatperature();
  float humidity = dht.readHumidity();


  Serial.println("-------------------------------------------------------------");
  Serial.print("Sistema: "); Serial.println(Alert = true ? "ALERTA! Verificar nível do tanque" : "Operação normal"); 
  Serial.print("Nível do tanque: "); Serial.print(distance); Serial.println(" %");
  Serial.print("Temperatura: "); Serial.print(temperature); Serial.print(" °C | ");
  Serial.print("Umidade: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Luminosidade: "); Serial.println(analogRead(LDRpin));
  Serial.print("Presença: "); Serial.println(presence == HIGH ? "Presença detectada" : "Sem presença");
  Serial.println("-------------------------------------------------------------");
}

