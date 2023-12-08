#define BLYNK_TEMPLATE_ID "TMPL6q7uABYkb"
#define BLYNK_TEMPLATE_NAME "testfinpro"
#define BLYNK_AUTH_TOKEN "tBcCdzrK-2oPaDZFF4Kc0O-aNl9QaNKT"

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>             // Only needed for Arduino 1.6.5 and earlier
#include <BlynkSimpleEsp32.h>


float latitude , longitude;
String lat_str , lng_str;
const char *ssid = "ketum";    // Enter your WiFi Name
const char *pass = "imesukses"; // Enter your WiFi Password
char auth[] = "tBcCdzrK-2oPaDZFF4Kc0O-aNl9QaNKT"; 
WidgetMap myMap(V0); 
WiFiClient client;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

void setup()
{
 Serial.begin(115200);
 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(500);
   Serial.print(".");             // print ... till not connected
 }
 Serial.println("");
 Serial.println("WiFi connected");
 SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
 Blynk.begin(auth, ssid, pass);
 Blynk.virtualWrite(V0, "clr"); 
}

void loop()
{
  Blynk.virtualWrite(V3, "Halo ini udah masuk"); 
 while (SerialGPS.available() > 0) {
  if (gps.encode(SerialGPS.read()))
  {
    if (gps.location.isValid())
    {
      latitude = gps.location.lat();
      lat_str = String(latitude , 6);
      longitude = gps.location.lng();
      lng_str = String(longitude , 6);
      Serial.print("Latitude = ");
      Serial.println(lat_str);
      Serial.print("Longitude = ");
      Serial.println(lng_str);
      Blynk.virtualWrite(V1, latitude); // send latitude to V1
      Blynk.virtualWrite(V2, longitude); // send longitude to V2
      delay(1000);
      Serial.println(); 
    }
  }
 } 
 Blynk.run();
}