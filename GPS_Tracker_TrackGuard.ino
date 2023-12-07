#include <WiFi.h>
#include <ThingsBoard.h>
#include "Arduino_MQTT_Client.h"
#include <TinyGPS++.h>
#include <AceButton.h>
#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>
#include <Wire.h>
#include "utilities.h"

// RX GSM D2
// TX GSM D4
// RX GPS KE TX2
// TX GPS KE RX2
// LED KE D22 SAMA BUZZER KE D23

#define rxPin 22
#define txPin 24
HardwareSerial sim800(1);

#define RXD2 27
#define TXD2 25
HardwareSerial neogps(2);

#define ledPin 39
#define buzzerPin 36

TinyGPSPlus gps;

// ThingsBoard configuration
const char* thingsboardServer = "thingsboard.cloud"; // Enter ThingsBoard server instance
const char* accessToken = "mqkb1ts57g5kwbstv04m"; // Enter your Device Access Token

// Initialize the Ethernet client object
WiFiClient espClient;
// Initalize the Mqtt client instance
Arduino_MQTT_Client mqttClient(espClient);
// Initialize ThingsBoard instance
ThingsBoard tb(mqttClient, 128U);

void setup() {
 Serial.begin(115200);
 Serial.println("esp32 serial initialize");
 
 sim800.begin(9600, SERIAL_8N1, rxPin, txPin);
 Serial.println("SIM800L serial initialize");

 neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
 Serial.println("neogps serial initialize");
 
 pinMode(ledPin, OUTPUT);
 pinMode(buzzerPin, OUTPUT);

 TinyGsm modem(sim800);
 modem.restart();
 modem.gprsConnect("your_apn", "your_username", "your_password");

     while(!tb.connected()){
      tb.connect(thingsboardServer, accessToken);
      vTaskDelay(3000 / portTICK_PERIOD_MS); // delay for 5 seconds
    }
    Serial.println("Thingsboard is Connected");
}

void loop() {
 if (gps.location.isValid()) {
   tb.sendTelemetryFloat("latitude", gps.location.lat());
   tb.sendTelemetryFloat("longitude", gps.location.lng());
 }

 if (tb.getRPCValue("led")) {
   digitalWrite(ledPin, HIGH);
 } else {
   digitalWrite(ledPin, LOW);
 }

 if (tb.getRPCValue("buzzer")) {
   digitalWrite(buzzerPin, HIGH);
 } else {
   digitalWrite(buzzerPin, LOW);
 }
}
