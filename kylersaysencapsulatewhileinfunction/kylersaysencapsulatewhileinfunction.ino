#include <Encoder.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//barometer stuff 
#define BMP_SCK  (41) // SCL
#define BMP_MISO (38) // SDO
#define BMP_MOSI (40) // SDI/SDA
#define BMP_CS   (39)

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);


//All pins on motor itself  
// const int L_PWM = 6;
// const int L_EN = 7;
// const int R_PWM = 3;
// const int R_EN = 4;
const int Encoder_A = 23; 
const int Encoder_B = 22; 
//pins to breakout board
const int MOTOR_IN1 = 20; 
const int MOTOR_IN2 = 21;

const int SWITCH = 0;

int readValue; 
int state;
bool retractedFlaps;

bool state_printout = false;

Encoder encoder(Encoder_A, Encoder_B); 
void setup() {
  state = 0;
  retractedFlaps = (digitalRead(SWITCH) == HIGH);
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Encoder_A, INPUT);
  pinMode(Encoder_B, INPUT);
  // pinMode(L_PWM, OUTPUT);
  encoder.write(0); 
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
  pinMode(SWITCH, INPUT);

  // pinMode(R_PWM, OUTPUT);
  // pinMode(L_EN, OUTPUT);
  // pinMode(R_EN, OUTPUT);
  // digitalWrite(L_EN,LOW);
  // digitalWrite(R_EN,LOW);
  // //ramp forward 
  // digitalWrite(IN1, LOW); 
    //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
    unsigned status;
  status = bmp.begin();

  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

void loop() {
  if (digitalRead(SWITCH) == HIGH) { 
    if (!retractedFlaps){
      retractedFlaps = true;
      encoder.write(0);
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
      delay(30);
    }
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    delay(500);
    readValue = encoder.read(); 
    Serial.print("Encoder = ");
    Serial.print(readValue);
    Serial.println();
    if(state == 0){ 
      state++;
    }
    
    delay(10);
  }
  else{
    retractedFlaps = false;
    switch(state) {
    case 0:
      calibrate();
      break;
    case 1:
      delay(5000);
      state++;
      break;
    // more cases can be added here
    default:
      statePrintout();
      oscillate(4750); 
      delay(10);
      break;
    }
  }
}

void statePrintout(){
  if (state_printout){
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println(); 
  }
  readValue = encoder.read(); 
  Serial.print("Encoder = ");
  Serial.print(readValue);
  Serial.println();
}

void speed_to(int location){
  readValue = encoder.read();
  if (readValue > location){
    delay(10); 
    digitalWrite(MOTOR_IN1, LOW);
    delay(10);
    digitalWrite(MOTOR_IN2, HIGH);
  }
  else {
    delay(10); 
    digitalWrite(MOTOR_IN1, HIGH);
    delay(10);
    digitalWrite(MOTOR_IN2, LOW);
  }
}

bool go_counterclockwise = true;

void oscillate(int range){
  readValue = encoder.read(); 
  if (readValue > range) {
    go_counterclockwise = true;
  }
  if (readValue < 0){
    go_counterclockwise = false;
  }
  Serial.println(go_counterclockwise);
  if (go_counterclockwise){
    speed_to(0);
  }
  else {
    speed_to(range);
  }
} 

void calibrate(){
  delay(10);
  digitalWrite(MOTOR_IN2, LOW);
  delay(10);
  digitalWrite(MOTOR_IN1, HIGH);
}

void PWM_test(int range){
  delay(10);
  analogWrite(MOTOR_IN2, 0);
  delay(10);
  analogWrite(MOTOR_IN1, 255);  
  Serial.print(F("Temperature = "));
}

void analog_test(int range){  
    // ramp up forward
  delay(10);
  analogWrite(MOTOR_IN2, 0);
  delay(10);
  analogWrite(MOTOR_IN1, 255);  
  readValue = encoder.read(); 
  while (readValue < range) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(1);
    readValue = encoder.read(); 
    Serial.print("Encoder = ");
    Serial.print(readValue);
    Serial.println(); 
    delay(1); 
  }
  //hit one rotation; 

  delay(10); 
  analogWrite(MOTOR_IN1, 0);
  delay(10);
  analogWrite(MOTOR_IN2, 255);
  // ramp down forward
  while (readValue > 0) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(1);
    readValue = encoder.read(); 
    Serial.print("Encoder = ");
    Serial.print(readValue);
    Serial.println(); 
    delay(1);

  }
  analogWrite(MOTOR_IN1, 0);
  analogWrite(MOTOR_IN2, 0);
}

void WHATITDOBBG(int range){  
    // ramp up forward
  delay(10);
  digitalWrite(MOTOR_IN2, LOW);
  delay(10);
  digitalWrite(MOTOR_IN1, HIGH);  
  readValue = encoder.read(); 
  while (readValue < range) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(1);
    readValue = encoder.read(); 
    Serial.print("Encoder = ");
    Serial.print(readValue);
    Serial.println(); 
    delay(1); 
  }
  //hit one rotation; 

  delay(10); 
  digitalWrite(MOTOR_IN1, LOW);
  delay(10);
  digitalWrite(MOTOR_IN2, HIGH);
  // ramp down forward
  while (readValue > 0) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(1);
    readValue = encoder.read(); 
    Serial.print("Encoder = ");
    Serial.print(readValue);
    Serial.println(); 
    delay(1);

  }
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
}