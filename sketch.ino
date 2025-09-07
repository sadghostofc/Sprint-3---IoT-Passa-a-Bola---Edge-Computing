/*
------------------ FIAP --------------------
Sprint 3 - IoT Passa a Bola - Edge Computing
EDGE COMPUTING & COMPUTER SYSTEMS
Participantes:
Prof. Paulo Marcotti PF2150
Daniel Laureano da Luz RM565899
Gabriel Del Sole Speck RM562513
Marcos Antonio Da Silva RM566451
Paulo Gustavo Pessoa da Silva RM566194
Rone Cruz Santos RM566558
--------------------------------------------
*/


#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ==== Config WiFi ====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==== Config MQTT (HiveMQ) ====
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// ==== Objetos ====
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;

// ==== Variáveis ====
int passes = 0;
float velocidade = 0;
float distancia = 0;

// ==== Pinos ====
#define PIN_POT 34     // Potenciômetro
#define PIN_BUTTON 25  // Botão

// ==== Funções WiFi ====
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("BolaInteligenteESP32")) {
      // conectado
    } else {
      delay(5000);
    }
  }
}

// ==== Setup ====
void setup() {
  Serial.begin(115200);

  pinMode(PIN_BUTTON, INPUT_PULLUP);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  // Inicializa MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar MPU6050");
    while (1) { delay(10); }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("Bola Inteligente Iniciada!");
}

// ==== Loop ====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // === Leitura do botão (passe) ===
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(PIN_BUTTON);
  if (buttonState == LOW && lastButtonState == HIGH) {
    passes++;
  }
  lastButtonState = buttonState;

  // === Leitura do acelerômetro ===
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // magnitude do vetor de aceleração
  float aceleracao = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));

  // Potenciômetro para ajustar intensidade (escala da velocidade)
  int potValue = analogRead(PIN_POT);
  float escala = map(potValue, 0, 4095, 1, 5);

  // Velocidade simulada (m/s convertido para km/h)
  velocidade = (aceleracao * escala) * 3.6;

  // Distância acumulada (estimada simplificadamente)
  distancia += velocidade * 0.05; // a cada 50ms simulação

  // Criação do JSON
  String payload = "{";
  payload += "\"bola_id\":\"bola_01\",";
  payload += "\"passes\":" + String(passes) + ",";
  payload += "\"velocidade\":" + String(velocidade, 1) + ",";
  payload += "\"distancia\":" + String(distancia, 1);
  payload += "}";

  // Publica no tópico MQTT
  client.publish("passa_a_bola/bola01", payload.c_str());
  Serial.println("Publicado: " + payload);

  delay(500); // envia a cada 0.5s
}
