#include <Servo.h>
#include <LiquidCrystal_I2C.h> 
#include<Wire.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lector de esferas..."); // Mensaje a despegar
  delay(3000);
}
void loop() {
  topServo.write(115);
  Serial.println("inicio");
  delay(2000);

  for (int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(8);
  }
  delay(1000);

  color = readColor();
  delay(10);
  switch (color) {
    case 1:
      bottomServo.write(65);
      Serial.println("se mueve rojo");
      break;
    case 2:
      bottomServo.write(85);
      Serial.println("se mueve amarillo");
      break;
    case 3:
      bottomServo.write(105);
      Serial.println("se mueve verde");
      break;
    case 4:
      bottomServo.write(125);
      break;
    case 0:
      lcd.clear();
      lcd.print("Desconocido");
      break;
  }
  delay(300);

  for (int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(8);
  }
  delay(200);

  for (int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color = 0;
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if (R<100 & R>70 & G<150 & G>120) {
    color = 1; // Red
    lcd.clear();
    lcd.print("Rojo :)");
    Serial.println("rojo");
  }
  if (R<9x0 & R>50 & G<80 & G>55) {
    color = 2; 
    lcd.clear();
    lcd.print("Amarillo :)");
    Serial.println("amarillo");
  }
  if (R<120 & R>90 & G<100 & G>75) {
    color = 3; // Green
    lcd.clear();
    lcd.print("Verde :)");
    Serial.println("verde");
  }

  return color;
}
