/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/

#include "EspMQTTClient.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13
#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int led1 = 17;
int led2 = 16;
int led3 = 5;
int sw1 = 18;
int sw2 = 19;

const int led_1_Channel = 0;
const int frequency_1=5000;

const int resolution_1 = 8;//밝기 조절 단계

int duty_cycle_1 = 200;

// adc
int adc_val = 0;

//3
sensor_t sensor;




EspMQTTClient client(
  "MULTI_GUEST",
  "guest1357",
  "70.12.227.42",  // MQTT Broker server ip
  //"70.12.228.152",
  "MQTTUsername",   // Can be omitted if not needed
  "MQTTPassword",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

char *topic = "home/pi";
char *topic_hu = "home/hu";
char *topic_te = "home/te";
char *topic_an = "home/an";
void tx(){
  client.publish(topic,"Good morning!");
}
void tx_d(){
  client.publish(topic,"Good morning_2!");
}

void setup()
{
  dht.begin();
  dht.temperature().getSensor(&sensor);


  Serial.begin(115200);

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
    client.subscribe(topic,[](const String &payload){
      Serial.println(payload);

    });
}

void loop()
{
  sensors_event_t event;
  double hu;
  double te;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

    client.publish(topic_te,String(event.temperature));
    te=event.temperature;
  }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    client.publish(topic_hu,String(event.relative_humidity));


    client.publish(topic_an,String(event.relative_humidity));
    hu=event.relative_humidity;
    double angry=0.81*te-0.55*(1-hu/100)*(1.8*te-26)+32;
    client.publish(topic_an,String(angry));
  }

  //tx();
  //tx_d();
  client.loop(); // client.loop 이전까지의 publish들은 모두 버퍼에서 대기하다가 MQTT 브로커로 전송됩니다
  delay(5000);


}
