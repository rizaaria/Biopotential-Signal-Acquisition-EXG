#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define POSITION_NUM1 4
#define POSITION_NUM2 3
#define ON LOW
#define OFF HIGH
#define SAMPLE_RATE 115200
//Channel 0
#define INPUT_PIN1 A0
//Channel 1
#define INPUT_PIN2 A1

RF24 radio(7, 8); // CE, CSN
const byte address[][6] = { "11100","11000", "10100", "10000", "01100", "01000", "001000", "00000" };

const int SWITCH_PINS2[] = { 6, 9, 10 };

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);

  Serial.begin(SAMPLE_RATE);
  delay(1000);
  Serial.flush();

  for (int i = 0; i < POSITION_NUM2; i++)
    pinMode(SWITCH_PINS2[i], INPUT_PULLUP);
}

void loop() {

  //RF
  for (int i = 0; i < POSITION_NUM2; i++) {
    delay(5);
    Serial.print("position ");
    Serial.print(i + 1);
    Serial.print(": ");
    int state = digitalRead(SWITCH_PINS2[i]);

    if (state == ON){
      Serial.println("ON ");
    }
    else
      Serial.println("OFF ");

    Serial.println(digitalRead(SWITCH_PINS2[i]));
  }
  
  if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.openReadingPipe(0, address[0]);
    Serial.print("RF Address: ");
    Serial.println("11100");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.openReadingPipe(0, address[1]);
    Serial.print("RF Address: ");
    Serial.println("11000");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.openReadingPipe(0, address[2]);
    Serial.print("RF Address: ");
    Serial.println("10100");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.openReadingPipe(0, address[3]);
    Serial.print("RF Address: ");
    Serial.println("10000");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.openReadingPipe(0, address[4]);
    Serial.print("RF Address: ");
    Serial.println("01100");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.openReadingPipe(0, address[5]);
    Serial.print("RF Address: ");
    Serial.println("01000");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.openReadingPipe(0, address[6]);
    Serial.print("RF Address: ");
    Serial.println("00100");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
      radio.read(&signal2, sizeof(signal2));
      Serial.println(signal2);
      } 
    }
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.openReadingPipe(0, address[7]);
    Serial.print("RF Address: ");
    Serial.println("00000");

    radio.startListening(); 
    if(radio.available()){
      while(radio.available()){
      float signal1 = 0;
//      float signal2 = 0;
      radio.read(&signal1, sizeof(signal1));
      Serial.println(signal1);
//      radio.read(&signal2, sizeof(signal2));
//      Serial.println(signal2);
      } 
    }
  }

//  Serial.println();

  delay(1000);
}
