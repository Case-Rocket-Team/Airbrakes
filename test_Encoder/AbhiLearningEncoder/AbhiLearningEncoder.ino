const int L_PWM = 6;
const int L_EN = 7;
const int R_PWM = 3;
const int R_EN = 4;
const int Encoder_A_Output = 9; 
const int Encoder_B_Output = 10; 

// Create an Encoder object
void setup() {
  Serial.begin(9600);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(Encoder_A_Output, INPUT);
  pinMode(Encoder_B_Output, INPUT);
  digitalWrite(L_EN,LOW);
  digitalWrite(R_EN,LOW);
}

// This is a loop
void loop() {
  
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);
  // Clockwise
  for(int pwmVal = 50; pwmVal <= 255; pwmVal += 50) {
  analogWrite(L_PWM, pwmVal);
  Serial.println("Position: " + String(Encoder_A_Output));
  delay(200);
}
analogWrite(R_PWM, 0);
  // Counterclockwise
for(int pwmVal = 50; pwmVal <= 255; pwmVal += 50) {
  analogWrite(R_PWM, pwmVal);
  Serial.println("Position: " + String(Encoder_A_Output));
  delay(200);
}
analogWrite(R_PWM, 0);
  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);
}

void printFromEncoder(){
  Serial.println("Position: " + Encoder_A_Output );
}
