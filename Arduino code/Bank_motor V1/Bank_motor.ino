#include <Wire.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11
#define TX_PIN 6
#define RX_PIN 5

SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);

int motor1 = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(4);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  static unsigned long EUR10 = millis();
  static unsigned long EUR20 = millis();

  motor1 = Wire.read();
  Serial.println(motor1);
  
  if (motor1 == 1) {
    if (millis() - EUR10 < 1000) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
    }
  }
  else if (motor1 == 2) {
    if (millis() - EUR20 < 1000) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW); 
    }
  }
  else if (motor1 == 3) {
    if (millis() - EUR10 < 1000 & millis() - EUR20 < 1000) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW); 
    }
  }
  else if (motor1 == 0) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }
}

/*void printer() {
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(9600);
  printer.begin();

  printer.justify('C');
  printer.setSize('L');
  printer.boldOn();
  printer.println("MoneyMakers");
  printer.println("________________");

  printer.justify('L');
  printer.setSize('S');
  printer.setLineHeight(30);
  printer.println("Terminal: 3");
  printer.println("Account: XXXX XXXX XXXX ..");
  printer.println("Transactie: 00000001");

  printer.setSize('M');
  printer.println("BETALING");
  printer.boldOff();
  printer.setSize('S');
  printer.println("'Datum & Tijd'");

  printer.setSize('M');
  printer.boldOn();
  printer.println("Totaal: 'Prijs' EUR");
  printer.justify('C');
  printer.setSize('L');
  printer.println("SUCCES");
  printer.boldOff();
  printer.feed(3);
  
  printer.sleep();
  delay(3000L);
  printer.wake();
  printer.setDefault();
}*/
