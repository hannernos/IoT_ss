//requirement
// 1 digital input
//     if sw1 input -> led lighter
//     if sw2 input -> led darker
//
// 2 ADC
//     30 ++ led 1 on
//     15 -- led 2 on
//
// 3 Serial
//     print ID PWM TEMP (always)
//     input Serial and turn LED light by it (duty cycle)

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
//~ 3


int led1 = 17;
int led2 = 16;
int led3 = 5;
int sw1 = 18;
int sw2 = 19;

const int led_1_Channel = 0;


const int frequency_1=5000;
const int frequency_2=5000;

const int resolution_1 = 8;//밝기 조절 단계

int duty_cycle_1 = 200;

// adc
int adc_val = 0;


//3
sensor_t sensor;


void setup() {
//1
    ledcSetup(led_1_Channel,frequency_1,resolution_1);
    ledcAttachPin(led1, led_1_Channel);

//2
    pinMode(A0,INPUT);
    Serial.begin(9600);




  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  //pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);



  //3

    Serial.begin(9600);
    // Initialize device.
    dht.begin();

    dht.temperature().getSensor(&sensor);
}

void loop() {
    //1 digital input
    if( digitalRead(sw1)==0 ){
        if(duty_cycle_1>10){
            duty_cycle_1=duty_cycle_1-10;
        }
    }

    if( digitalRead(sw2)==0 ){
        if(duty_cycle_1<250){
            duty_cycle_1=duty_cycle_1+10;
        }
    }

    ledcWrite(led_1_Channel,duty_cycle_1);
    delay(15);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
//2
    adc_val = analogRead(A0);
    if(adc_val>30){
        digitalWrite(led2, 1);
    }else if(adc_val<15){
        digitalWrite(led3, 1);
    }else{
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
    }
    Serial.println(adc_val);
    delay(100);
//3
    delay(delayMS);
    sensors_event_t event;
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }

}