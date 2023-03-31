#include <Encoder.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//barometer stuff 
#define BMP_SCK  (13) 
#define BMP_MISO (12) // SDO
#define BMP_MOSI (11) // SDI/SDA
#define BMP_CS   (10)

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);


//All pins on motor itself  
// const int L_PWM = 6;
// const int L_EN = 7;
// const int R_PWM = 3;
// const int R_EN = 4;
const int Encoder_A = 8; 
const int Encoder_B = 9; 
//pins to breakout board
const int MOTOR_IN1 = 24; 
const int MOTOR_IN2 = 25;
int readValue; 

Encoder encoder(Encoder_A, Encoder_B); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Encoder_A, INPUT);
  pinMode(Encoder_B, INPUT);
  // pinMode(L_PWM, OUTPUT);
  encoder.write(0); 
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
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
  // put your main code here, to run repeatedly:
  WHATITDOBBG(4750); 

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
}