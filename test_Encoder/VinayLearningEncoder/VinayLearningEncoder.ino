const int L_PWM = 6;
const int L_EN = 7;
const int R_PWM = 3;
const int R_EN = 4;
const int ENCA = 9;
const int ENCB = 10;

int pos = 0;

void setup() {
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  digitalWrite(L_EN,LOW);
  digitalWrite(R_EN,LOW);
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH); 

  // Clockwise
  analogWrite(L_PWM, 50);
  Serial.println(pos);
  delay(200);
  analogWrite(L_PWM, 100);
  Serial.println(pos);
  delay(200);
  analogWrite(L_PWM, 150);
  Serial.println(pos);
  delay(200);
  analogWrite(L_PWM, 200);
  Serial.println(pos);
  delay(200);
  analogWrite(L_PWM, 255);
  Serial.println(pos);
  delay(200);
  analogWrite(L_PWM, 0);
  Serial.println(pos);

  // Counterclockwise
  analogWrite(R_PWM, 50);
  Serial.println(pos);
  delay(200);
  analogWrite(R_PWM, 100);
  Serial.println(pos);
  delay(200);
  analogWrite(R_PWM, 150);
  Serial.println(pos);
  delay(200);
  analogWrite(R_PWM, 200);
  Serial.println(pos);
  delay(200);
  analogWrite(R_PWM, 255);
  Serial.println(pos);
  delay(200);
  analogWrite(R_PWM, 0);
  Serial.println(pos);

  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    pos++;
  }
  else {
    pos--;
  }
}