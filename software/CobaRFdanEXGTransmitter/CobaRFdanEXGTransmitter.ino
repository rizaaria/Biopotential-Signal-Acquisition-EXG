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

const int SWITCH_PINS1[] = { 2, 3, 4, 5 };
const int SWITCH_PINS2[] = { 6, 9, 10 };

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);

  Serial.begin(SAMPLE_RATE);
  delay(1000);
  Serial.flush();

  for (int i = 0; i < POSITION_NUM1; i++)
    pinMode(SWITCH_PINS1[i], INPUT_PULLUP);

  for (int i = 0; i < POSITION_NUM2; i++)
    pinMode(SWITCH_PINS2[i], INPUT_PULLUP);
}

void loop() {

  // Calculate elapsed time
	static unsigned long past = 0;
	unsigned long present = micros();
	unsigned long interval = present - past;
	past = present;

	// Run timer
	static long timer = 0;
	timer -= interval;

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

    //Serial.println(digitalRead(SWITCH_PINS2[i]));
  }
  
  if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[0]);
    Serial.print("RF Address: ");
    Serial.println("11100");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[1]);
    Serial.print("RF Address: ");
    Serial.println("11000");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[2]);
    Serial.print("RF Address: ");
    Serial.println("10100");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == ON && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[3]);
    Serial.print("RF Address: ");
    Serial.println("10000");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[4]);
    Serial.print("RF Address: ");
    Serial.println("01100");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == ON && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[5]);
    Serial.print("RF Address: ");
    Serial.println("01000");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == ON){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[6]);
    Serial.print("RF Address: ");
    Serial.println("00100");
  }
  else if(digitalRead(SWITCH_PINS2[0]) == OFF && digitalRead(SWITCH_PINS2[1]) == OFF && digitalRead(SWITCH_PINS2[2]) == OFF){
    delay(5);
    radio.stopListening();
    radio.openWritingPipe(address[7]);
    Serial.print("RF Address: ");
    Serial.println("00000");
  }

  Serial.println();

  //EXG
  for (int i = 0; i < POSITION_NUM1; i++) {
    delay(5);
    Serial.print("position ");
    Serial.print(i + 1);
    Serial.print(": ");
    int state = digitalRead(SWITCH_PINS1[i]);

    if (state == ON){
      Serial.println("ON ");
    }
    else
      Serial.println("OFF ");

    //Serial.println(digitalRead(SWITCH_PINS1[i]));
  }

  //Channel 0
  if(digitalRead(SWITCH_PINS1[2]) == ON && digitalRead(SWITCH_PINS1[3]) == ON){
    Serial.println("ECG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value1 = analogRead(INPUT_PIN1);
		float signal1 = ECGFilter(sensor_value1);
		Serial.println(signal1);

    radio.write(&signal1, sizeof(signal1));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[2]) == OFF && digitalRead(SWITCH_PINS1[3]) == ON){
    Serial.println("EMG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value1 = analogRead(INPUT_PIN1);
		float signal1 = EMGFilter(sensor_value1);
		Serial.println(signal1);

    radio.write(&signal1, sizeof(signal1));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[2]) == ON && digitalRead(SWITCH_PINS1[3]) == OFF){
    Serial.println("EOG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value1 = analogRead(INPUT_PIN1);
		float signal1 = EOGFilter(sensor_value1);
		Serial.println(signal1);

    radio.write(&signal1, sizeof(signal1));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[2]) == OFF && digitalRead(SWITCH_PINS1[3]) == OFF){
    Serial.println("EEG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value1 = analogRead(INPUT_PIN1);
		float signal1 = EEGFilter(sensor_value1);
		Serial.println(signal1);

    radio.write(&signal1, sizeof(signal1));
	  }
  }

  //Channel 1
  if(digitalRead(SWITCH_PINS1[0]) == ON && digitalRead(SWITCH_PINS1[1]) == ON){
    Serial.println("ECG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value2 = analogRead(INPUT_PIN2);
		float signal2 = ECGFilter(sensor_value2);
		Serial.println(signal2);

    radio.write(&signal2, sizeof(signal2));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[0]) == OFF && digitalRead(SWITCH_PINS1[1]) == ON){
    Serial.println("EMG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value2 = analogRead(INPUT_PIN2);
		float signal2 = EMGFilter(sensor_value2);
		Serial.println(signal2);

    radio.write(&signal2, sizeof(signal2));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[0]) == ON && digitalRead(SWITCH_PINS1[1]) == OFF){
    Serial.println("EOG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value2 = analogRead(INPUT_PIN2);
		float signal2 = EOGFilter(sensor_value2);
		Serial.println(signal2);

    radio.write(&signal2, sizeof(signal2));
	  }
  }
  else if(digitalRead(SWITCH_PINS1[0]) == OFF && digitalRead(SWITCH_PINS1[1]) == OFF){
    Serial.println("EEG Mode");
    if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;
		float sensor_value2 = analogRead(INPUT_PIN2);
		float signal2 = EEGFilter(sensor_value2);
		Serial.println(signal2);

    radio.write(&signal2, sizeof(signal2));
	  }
  }

  Serial.println();

  delay(1000);
}

float ECGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.70682283*z1 - 0.15621030*z2;
    output = 0.28064917*x + 0.56129834*z1 + 0.28064917*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.95028224*z1 - 0.54073140*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.95360385*z1 - 0.95423412*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.98048558*z1 - 0.98111344*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

float EEGFilter(float input) {
	float output = input;
	{
		static float z1, z2; // filter section state
		float x = output - -0.95391350*z1 - 0.25311356*z2;
		output = 0.00735282*x + 0.01470564*z1 + 0.00735282*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.20596630*z1 - 0.60558332*z2;
		output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.97690645*z1 - 0.97706395*z2;
		output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	{
		static float z1, z2; // filter section state
		float x = output - -1.99071687*z1 - 0.99086813*z2;
		output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
		z2 = z1;
		z1 = x;
	}
	return output;
}

float EMGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.05159732*z1 - 0.36347401*z2;
    output = 0.01856301*x + 0.03712602*z1 + 0.01856301*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.53945795*z1 - 0.39764934*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.47319594*z1 - 0.70744137*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.00211112*z1 - 0.74520226*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

float EOGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.02977423*z1 - 0.04296318*z2;
    output = 0.09797471*x + 0.19594942*z1 + 0.09797471*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.08383952*z1 - 0.46067709*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.92167271*z1 - 0.92347975*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.96758891*z1 - 0.96933514*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}
