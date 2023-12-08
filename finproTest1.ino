#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define RXPin 27
#define TXPin 25
#define GPSBaud 9600

TinyGPSPlus gps;
SoftwareSerial mygps(RXPin, TXPin);

WiFiClient espClient;
PubSubClient client(espClient);

const char* server = "thingsboard.cloud";
const char* token = "mqkb1ts57g5kwbstv04m";

float latitude;
float longitude;

void setup() {
 Serial.begin(115200);
 mygps.begin(GPSBaud);
 client.setServer(server, 1883);

 WiFi.begin("DTE Student", "DteStudent2@23");
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.println("Connecting to WiFi...");
 }
 Serial.println("Connected to WiFi");
}

void loop() {
 while (mygps.available() > 0) {
 if (gps.encode(mygps.read())) {
   displayInfo();
 }
 }

 if (!client.connected()) {
 reconnect();
 }
 client.loop();
}

void displayInfo() {
 if (gps.location.isValid()) {
 latitude = (gps.location.lat());
 longitude = (gps.location.lng());

 client.publish("v1/devices/me/telemetry", String(latitude, 6).c_str());
 client.publish("v1/devices/me/telemetry", String(longitude, 6).c_str());
 }
}

void reconnect() {
 while (!client.connected()) {
 if (client.connect("ESP32Client", token, NULL)) {
   Serial.println("Connected to Thingsboard");
 } else {
   Serial.println("Failed to connect, retrying...");
   delay(5000);
 }
 }
}