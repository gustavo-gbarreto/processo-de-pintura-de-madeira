
#include <WiFi.h>
#include "DHT.h"
#include <Ultrassonic.h>
#include "time.h"

#define PIN_FOTORRESISTOR 34

#define PIN_TRIG 4      // Pino Trig do Ultrassônico
#define PIN_ECHO 5      // Pino Echo do Ultrassônico

#define PIN_DHT 18     
#define DHTTYPE DHT11

#define PIN_LED_VERDE 25    
#define PIN_LED_VERMELHO 26

#define DISTANCIA_MAX_CM 100.0 
#define DISTANCIA_MIN_CM 10.0  

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_VERMELHO, OUTPUT);

  pinMode(PIN_FOTORRESISTOR, INPUT);

  float nivel_tinta = 0.0;
  float temperatura = 0.0;
  float umidade = 0.0;
  int luminosidade = 0;
  bool alerta_nivel_baixo = false;
  bool presenca_detectada_bool = false;

}


int lerLuminosidade() {
   
    int luminosidade = analogRead(PIN_FOTORRESISTOR); 
    
    return luminosidade;
    }

void lerTemperaturaUmidade() {
    
    float umid = dht.readHumidity();
    float temp = dht.readTemperature(); 

}

float calcularNivelTinta() { 
  
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);

  long duration = pulseIn(PIN_ECHO, HIGH, 30000);

  float distancia_lida = duration * FATOR_CONVERSAO_ULTRASSOM;

  float nivel_porcentagem = map(distancia_lida * 10, DISTANCIA_MIN_CM * 10, DISTANCIA_MAX_CM * 10, 100, 0) / 10.0;

  if (nivel_porcentagem < 0) nivel_porcentagem = 0;
  if (nivel_porcentagem > 100) nivel_porcentagem = 100;

  Serial.print("Distância em CM: ");
  Serial.println(distancia_lida, 1);

  if (nivel_porcentagem < 20.0) {
        digitalWrite(PIN_LED_VERMELHO, HIGH);
        digitalWrite(PIN_LED_VERDE, LOW);   
        Serial.println("Alerta! Nível de tinta baixo.");
}
   else {
        digitalWrite(PIN_LED_VERMELHO, LOW);
        digitalWrite(PIN_LED_VERDE, HIGH);
        Serial.println("Estado do Sistema: Operação normal");
    }

    Serial.print("Nível do tanque: ");
    Serial.print(nivel_porcentagem, 1); 
    Serial.println("%");

    return nivel_porcentagem;
    }

//APLICAR O PIR
void loop() {
    
        calcularNivelTinta();
        lerTemperaturaUmidade();
        lerLuminosidade();
        
        Serial.println("--- Leitura do Chão de Fábrica ---");
        
        Serial.print("Nível do tanque: ");
        Serial.print(nivel_tinta, 1);
        Serial.println("%"); 
        
        if (isnan(umid) || isnan(temp)) {
        Serial.println("Falha ao ler o sensor DHT!");
        return;
    }
        Serial.print("Temperatura: ");
        Serial.print(temp, 1);
        Serial.print(" ºC | Umidade: ");
        Serial.print(umid, 1);
        Serial.println("%");
        
        Serial.print("Luminosidade: ");
        Serial.println(luminosidade);
        
        Serial.println("------------------------------------");

    delay(2000);}

