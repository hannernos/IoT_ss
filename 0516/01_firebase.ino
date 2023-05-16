

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <WiFi.h>
#include <FirebaseESP32.h>

#define DHTPIN 13     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 22 (AM2302)

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

FirebaseData firebaseData;
FirebaseJson json;

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

void setup()
{
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);

    String str= String(event.temperature);

    json.set("payload", str);
    Firebase.pushJSON(firebaseData, "/response", json); // 보내기, 송신
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("PUSH NAME: " + firebaseData.pushName());

    delay(2000);
}

