#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define RXPin 16
#define TXPin 17
#define GPSBaud 9600
#define LED_PIN 22
#define BUZZER_PIN 23 // Define buzzer pin

TinyGPSPlus gps;
HardwareSerial mygps(1);

WiFiClient espClient;
PubSubClient client(espClient);

const char* server = "thingsboard.cloud";
const char* token = "mqkb1ts57g5kwbstv04m";

float latitude;
float longitude;

void setup() {
 Serial.begin(115200);
 mygps.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

 if (!mygps) {
  Serial.println("Failed to initialize GPS");
 } else {
  Serial.println("Success to initialize GPS");
 }

 // Print GPS data for 30 seconds
 for (unsigned long startMillis = millis(); millis() - startMillis < 30000; ) {
  while (mygps.available()) {
    Serial.write(mygps.read());
  }
 }

 client.setServer(server, 1883);

 WiFi.begin("ketum", "imesukses");
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi...");
 }
 Serial.println("Connected to WiFi");

 pinMode(LED_PIN, OUTPUT);
 pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
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

 if (WiFi.status() == WL_CONNECTED) {
 digitalWrite(LED_PIN, HIGH);
 digitalWrite(BUZZER_PIN, HIGH); // Turn buzzer ON
 } else {
 digitalWrite(LED_PIN, LOW);
 digitalWrite(BUZZER_PIN, LOW); // Turn buzzer OFF
 }
}

void displayInfo() {
 if (gps.location.isValid()) {
 latitude = (gps.location.lat());
 longitude = (gps.location.lng());

 Serial.print("Latitude: ");
 Serial.println(latitude, 6);
 Serial.print("Longitude: ");
 Serial.println(longitude, 6);

 String latStr = String(latitude, 6);
 String lonStr = String(longitude, 6);

 char latChar[latStr.length() + 1];
 char lonChar[lonStr.length() + 1];

 latStr.toCharArray(latChar, latStr.length() + 1);
 lonStr.toCharArray(lonChar, lonStr.length() + 1);

 client.publish("v1/devices/me/telemetry/latitude", latChar);
 client.publish("v1/devices/me/telemetry/longitude", lonChar);
 } else {
 Serial.println("GPS data is not valid");
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
