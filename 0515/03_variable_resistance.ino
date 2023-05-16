int adc_val = 0;
void setup(){
    pinMode(A0,INPUT);
    Serial.begin(9600);
}
void loop(){
    adc_val = analogRead(A0);
    Serial.println(adc_val);
    delay(100);
}