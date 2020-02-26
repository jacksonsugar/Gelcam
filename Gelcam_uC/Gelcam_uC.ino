#include "LowPower.h"

int Pi_off = 2;
int Pi_on = 3;
int WIFI_SIG = 4;
int WIFI_LED = 13;

void setup(void)
{
  pinMode(WIFI_LED, OUTPUT);
  pinMode(Pi_on, OUTPUT);
  pinMode(WIFI_SIG, INPUT_PULLUP);

  // ensure pi is off
  digitalWrite(Pi_on, LOW);
  digitalWrite(Pi_off, HIGH);
  delay(500);
  digitalWrite(Pi_off, LOW);

  digitalWrite(WIFI_LED, LOW);

  for (int i = 0; i < 3; i++) {
    digitalWrite(WIFI_LED, HIGH);
    delay(400);
    digitalWrite(WIFI_LED, LOW);
    delay(100);
  }
}

void loop(void)
{
  sample();

}

void sample(){
  
  digitalWrite(Pi_on, HIGH);
  delay(500);
  digitalWrite(Pi_on, LOW);

  for (int i = 1; i <= 12; i++) {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }

  digitalWrite(WIFI_LED, HIGH);

  int sensorVal = digitalRead(WIFI_SIG);

  do {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
    sensorVal = digitalRead(WIFI_SIG);
  }
  while (sensorVal == HIGH);

  for (int i = 1; i <= 2; i++) {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }

  digitalWrite(Pi_off, HIGH);
  delay(500);
  digitalWrite(Pi_off, LOW);

  //This is the sleep cycle! Set for 150 cycles of 4 seconds for 10 minutes
  for (int i = 1; i <= 30; i++) {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }
}
