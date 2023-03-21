const int L_PWM = 6;
const int L_EN = 7;
const int R_PWM = 3;
const int R_EN = 4;
void setup() {
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  digitalWrite(L_EN,LOW);
  digitalWrite(R_EN,LOW);
}
void loop() {
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  // Clockwise
  analogWrite(L_PWM, 50);
  delay(200);
  analogWrite(L_PWM, 100);
  delay(200);
  analogWrite(L_PWM, 150);
  delay(200);
  analogWrite(L_PWM, 200);
  delay(200);
  analogWrite(L_PWM, 255);
  delay(200);
  analogWrite(L_PWM, 0);
  // Counterclockwise
  analogWrite(R_PWM, 50);
  delay(200);
  analogWrite(R_PWM, 100);
  delay(200);
  analogWrite(R_PWM, 150);
  delay(200);
  analogWrite(R_PWM, 200);
  delay(200);
  analogWrite(R_PWM, 255);
  delay(200);
  analogWrite(R_PWM, 0);
  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);
}