#include "DHT.h"
#define DHTPIN 25
#include "WiFi.h" // Librairie pour l'utilisation du WiFi
#include <HTTPClient.h> // Librairie pour le client http
#define DHTTYPE DHT11
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const char* ssid="iPhone de Joey";
const char* password="galligani";
const char* numerosecu="12345678900";
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(9600);
 Serial.println(F("DHTxx test!"));
 dht.begin();
 Serial.println("");

 WiFi.mode(WIFI_STA); // Configurer en Station WiFi
 WiFi.disconnect();

 WiFi.begin(ssid,password); // Demande de connexion au réseau WiFi
 while(WiFi.status() != WL_CONNECTED)

 configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 printLocalTime();
 
 { Serial.println("Tentative de connexion...");
 delay(1000);
 }

 Serial.println("");
 Serial.println("Connecté au réseau WiFi !");
 Serial.println("");
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "Date et Heure : %d/%m/%Y - %H:%M");
  Serial.println();
}

void loop() {
 delay(2000);
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 printLocalTime();
 
 if (isnan(h) || isnan(t)) {
 Serial.println(F("Failed to read from DHT sensor!"));
 return;
 Serial.begin(9600); // Pour afficher via la liaison série
 Serial.println("");
 }

 delay(3600);
    
 float hic = dht.computeHeatIndex(t, h, false);
 Serial.print("Numéro de sécurité sociale : ");
 Serial.print(numerosecu);
 Serial.print(F("\n"));
 Serial.print(F("Humidité: "));
 Serial.print(h);
 Serial.print(F("% Temperature: "));
 Serial.print(t);
 Serial.print(F("°C "));
 Serial.print(F("\n"));
}
