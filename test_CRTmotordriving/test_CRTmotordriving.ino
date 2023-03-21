const int R_EN = 4;
const int L_EN = 7;
const int R_PWM = 3;
const int L_PWM = 6;
void setup() {
  // put your setup code here, to run once:
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  digitalWrite(R_EN,LOW);
  digitalWrite(L_EN,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(R_EN, HIGH);
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
  digitalWrite(R_EN, LOW);
}